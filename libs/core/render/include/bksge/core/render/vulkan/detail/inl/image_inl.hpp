/**
 *	@file	image_inl.hpp
 *
 *	@brief	Image クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/device_memory.hpp>
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/texture_format.hpp>
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/core/render/texture_format.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/cstring/memcpy.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkAccessFlags
GetAccessMask(::VkImageLayout layout)
{
	switch (layout)
	{
	case VK_IMAGE_LAYOUT_UNDEFINED:
		return 0;
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		return VK_ACCESS_TRANSFER_WRITE_BIT;
	case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
		return VK_ACCESS_TRANSFER_READ_BIT;
	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		return VK_ACCESS_SHADER_READ_BIT;
	case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		return VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
			   VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
		return VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		return VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
			   VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
	case VK_IMAGE_LAYOUT_GENERAL:
		return VK_ACCESS_SHADER_READ_BIT |
			   VK_ACCESS_SHADER_WRITE_BIT;
	case VK_IMAGE_LAYOUT_PREINITIALIZED:
		return VK_ACCESS_HOST_WRITE_BIT;
	default:
		bksge::throw_runtime_error("unsupported layout transition!");
	}
}

inline ::VkPipelineStageFlags
GetPipelineStage(::VkImageLayout layout)
{
	switch (layout)
	{
	case VK_IMAGE_LAYOUT_UNDEFINED:
		return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		return VK_PIPELINE_STAGE_TRANSFER_BIT;
	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		return VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
		return VK_PIPELINE_STAGE_TRANSFER_BIT;
	case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		return VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
		return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	case VK_IMAGE_LAYOUT_GENERAL:
		return VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
	case VK_IMAGE_LAYOUT_PREINITIALIZED:
		return VK_PIPELINE_STAGE_HOST_BIT;
	default:
		bksge::throw_runtime_error("unsupported layout transition!");
	}
}

inline ::VkImageAspectFlags
GetImageAspectFlags(::VkFormat format)
{
	switch (format)
	{
	case VK_FORMAT_D16_UNORM_S8_UINT:
	case VK_FORMAT_D24_UNORM_S8_UINT:
	case VK_FORMAT_D32_SFLOAT_S8_UINT:
		return VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
	case VK_FORMAT_D16_UNORM:
	case VK_FORMAT_X8_D24_UNORM_PACK32:
	case VK_FORMAT_D32_SFLOAT:
		return VK_IMAGE_ASPECT_DEPTH_BIT;
	default:
		return VK_IMAGE_ASPECT_COLOR_BIT;
	}
}

inline void
TransitionImageLayout(
	vulkan::CommandBuffer* command_buffer,
	::VkImage image,
	::VkImageAspectFlags aspect_mask,
	std::uint32_t mipmap_count,
	::VkImageLayout old_layout,
	::VkImageLayout new_layout)
{
	vk::ImageMemoryBarrier barrier;
    barrier.srcAccessMask                   = 0;
    barrier.dstAccessMask                   = 0;
	barrier.oldLayout                       = old_layout;
	barrier.newLayout                       = new_layout;
	barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
	barrier.image                           = image;
	barrier.subresourceRange.aspectMask     = aspect_mask;
	barrier.subresourceRange.baseMipLevel   = 0;
	barrier.subresourceRange.levelCount     = mipmap_count;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount     = 1;

	barrier.srcAccessMask = detail::GetAccessMask(old_layout);
	barrier.dstAccessMask = detail::GetAccessMask(new_layout);
	auto const src_stage = detail::GetPipelineStage(old_layout);
	auto const dst_stage = detail::GetPipelineStage(new_layout);

	command_buffer->PipelineBarrier(
		src_stage,
		dst_stage,
		0,
		0, nullptr,
		0, nullptr,
		1, &barrier);
}

}	// namespace detail

BKSGE_INLINE
Image::Image(
	vulkan::DeviceSharedPtr const& device,
	::VkImage image,
	::VkFormat format,
	vulkan::Extent2D const& extent,
	std::uint32_t mipmap_count)
	: m_image(image)
	, m_image_view(VK_NULL_HANDLE)
	, m_device_memory()
	, m_aspect_mask(detail::GetImageAspectFlags(format))
	, m_format(format)
	, m_extent(extent)
	, m_mipmap_count(mipmap_count)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
	, m_device(device)
{
	{
		vk::ImageViewCreateInfo info;
		info.image                           = image;
		info.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
		info.format                          = format;
		info.components.r                    = VK_COMPONENT_SWIZZLE_R;
		info.components.g                    = VK_COMPONENT_SWIZZLE_G;
		info.components.b                    = VK_COMPONENT_SWIZZLE_B;
		info.components.a                    = VK_COMPONENT_SWIZZLE_A;
		info.subresourceRange.aspectMask     = m_aspect_mask;
		info.subresourceRange.baseMipLevel   = 0;
		info.subresourceRange.levelCount     = mipmap_count;
		info.subresourceRange.baseArrayLayer = 0;
		info.subresourceRange.layerCount     = 1;

		m_image_view = m_device->CreateImageView(info);
	}
}

BKSGE_INLINE
Image::Image(
	vulkan::DeviceSharedPtr const& device,
	::VkFormat format,
	vulkan::Extent2D const& extent,
	std::uint32_t mipmap_count,
	::VkSampleCountFlagBits num_samples,
	::VkImageUsageFlags usage)
	: m_image(VK_NULL_HANDLE)
	, m_image_view(VK_NULL_HANDLE)
	, m_device_memory()
	, m_aspect_mask(detail::GetImageAspectFlags(format))
	, m_format(format)
	, m_extent(extent)
	, m_mipmap_count(mipmap_count)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
	, m_device(device)
{
	{
		vk::ImageCreateInfo info;
		info.imageType     = VK_IMAGE_TYPE_2D;
		info.format        = format;
		info.extent        = { extent.width, extent.height, 1 };
		info.mipLevels     = mipmap_count;
		info.arrayLayers   = 1;
		info.samples       = num_samples;
		info.tiling        = VK_IMAGE_TILING_OPTIMAL;
		info.usage         = usage;
		info.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
		info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		info.SetQueueFamilyIndices(nullptr);

		m_image = device->CreateImage(info);
	}

	{
		auto const mem_reqs = device->GetImageMemoryRequirements(m_image);
		m_device_memory = bksge::make_unique<vulkan::DeviceMemory>(
			device, mem_reqs, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		m_device_memory->BindImage(m_image, 0);
	}

	{
		vk::ImageViewCreateInfo info;
		info.image                           = m_image;
		info.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
		info.format                          = format;
		info.components.r                    = VK_COMPONENT_SWIZZLE_R;
		info.components.g                    = VK_COMPONENT_SWIZZLE_G;
		info.components.b                    = VK_COMPONENT_SWIZZLE_B;
		info.components.a                    = VK_COMPONENT_SWIZZLE_A;
		info.subresourceRange.aspectMask     = m_aspect_mask;
		info.subresourceRange.baseMipLevel   = 0;
		info.subresourceRange.levelCount     = mipmap_count;
		info.subresourceRange.baseArrayLayer = 0;
		info.subresourceRange.layerCount     = 1;

		m_image_view = m_device->CreateImageView(info);
	}
}

BKSGE_INLINE
Image::Image(
	vulkan::DeviceSharedPtr const& device,
	bksge::Texture const& texture,
	vulkan::CommandPoolSharedPtr const& command_pool)
	: Image(
		device,
		vulkan::TextureFormat(texture.format()),
		texture.extent(),
		static_cast<std::uint32_t>(texture.mipmap_count()),
		VK_SAMPLE_COUNT_1_BIT,
		VK_IMAGE_USAGE_SAMPLED_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT)
{
	auto image_size = GetMipmappedSizeInBytes(
		texture.format(),
		texture.width(),
		texture.height(),
		texture.mipmap_count());

	auto staging_buffer = bksge::make_unique<vulkan::Buffer>(
		device,
		image_size,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	{
		void* dst = staging_buffer->MapMemory(VK_WHOLE_SIZE);
		bksge::memcpy(dst, texture.data(), image_size);
		staging_buffer->UnmapMemory();
	}

	{
		vulkan::ScopedOneTimeCommandBuffer command_buffer(command_pool);

		this->CopyFromBuffer(
			command_buffer.Get(),
			*staging_buffer->GetAddressOf(),
			texture.format());

		this->TransitionLayout(
			command_buffer.Get(),
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	}
}

BKSGE_INLINE
Image::~Image()
{
	if (m_device_memory)
	{
		m_device->DestroyImage(m_image);
	}
	m_device->DestroyImageView(m_image_view);
}

BKSGE_INLINE void*
Image::MapMemory(::VkDeviceSize size)
{
	if (m_device_memory)
	{
		return m_device_memory->MapMemory(size);
	}
	return nullptr;
}

BKSGE_INLINE void
Image::UnmapMemory(void)
{
	if (m_device_memory)
	{
		m_device_memory->UnmapMemory();
	}
}

BKSGE_INLINE void
Image::CopyFromBuffer(
	vulkan::CommandBuffer* command_buffer,
	::VkBuffer buffer,
	bksge::TextureFormat format)
{
	this->TransitionLayout(
		command_buffer,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	::VkDeviceSize src_offset = 0;
	auto width  = m_extent.width;
	auto height = m_extent.height;

	for (std::uint32_t i = 0; i < m_mipmap_count; ++i)
	{
		::VkBufferImageCopy region {};
		region.bufferOffset                    = src_offset;
		region.bufferRowLength                 = 0;
		region.bufferImageHeight               = 0;
		region.imageSubresource.aspectMask     = m_aspect_mask;
		region.imageSubresource.mipLevel       = i;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount     = 1;
		region.imageOffset                     = {0, 0, 0};
		region.imageExtent                     = {width, height, 1};

		command_buffer->CopyBufferToImage(
			buffer,
			m_image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&region);

		src_offset += GetSizeInBytes(format, width, height);
		width  = bksge::max(width  / 2, 1u);
		height = bksge::max(height / 2, 1u);
	}
}

BKSGE_INLINE void
Image::ClearColor(
	vulkan::CommandBuffer* command_buffer,
	::VkImageAspectFlags aspect_mask,
	bksge::Color4f const& color)
{
	if (aspect_mask == 0)
	{
		return;
	}

	auto const current_layout = this->TransitionLayout(
		command_buffer,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	::VkClearColorValue clear_value;
	clear_value.float32[0] = color[0];
	clear_value.float32[1] = color[1];
	clear_value.float32[2] = color[2];
	clear_value.float32[3] = color[3];

	::VkImageSubresourceRange range;
	range.aspectMask     = aspect_mask;
	range.baseMipLevel   = 0;
	range.levelCount     = 1;
	range.baseArrayLayer = 0;
	range.layerCount     = 1;

	command_buffer->ClearColorImage(
		m_image,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		&clear_value,
		1, &range);

	this->TransitionLayout(
		command_buffer,
		current_layout);
}

BKSGE_INLINE void
Image::ClearDepthStencil(
	vulkan::CommandBuffer* command_buffer,
	::VkImageAspectFlags aspect_mask,
	float depth,
	std::uint32_t stencil)
{
	if (aspect_mask == 0)
	{
		return;
	}

	auto const current_layout = this->TransitionLayout(
		command_buffer,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	::VkClearDepthStencilValue clear_value;
	clear_value.depth   = depth;
	clear_value.stencil = stencil;

	::VkImageSubresourceRange range;
	range.aspectMask     = aspect_mask;
	range.baseMipLevel   = 0;
	range.levelCount     = 1;
	range.baseArrayLayer = 0;
	range.layerCount     = 1;

	command_buffer->ClearDepthStencilImage(
		m_image,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		&clear_value,
		1, &range);

	this->TransitionLayout(
		command_buffer,
		current_layout);
}

BKSGE_INLINE ::VkImageLayout
Image::TransitionLayout(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkImageLayout new_layout)
{
	vulkan::ScopedOneTimeCommandBuffer command_buffer(command_pool);
	return TransitionLayout(command_buffer.Get(), new_layout);
}

BKSGE_INLINE ::VkImageLayout
Image::TransitionLayout(
	vulkan::CommandBuffer* command_buffer,
	::VkImageLayout new_layout)
{
	auto const old_layout = m_layout;
	m_layout = new_layout;
	detail::TransitionImageLayout(
		command_buffer,
		m_image,
		m_aspect_mask,
		m_mipmap_count,
		old_layout,
		new_layout);
	return old_layout;
}

BKSGE_INLINE ::VkImageAspectFlags
Image::aspect_mask(void) const
{
	return m_aspect_mask;
}

BKSGE_INLINE ::VkFormat const&
Image::format(void) const
{
	return m_format;
}

BKSGE_INLINE vulkan::Extent2D const&
Image::extent(void) const
{
	return m_extent;
}

BKSGE_INLINE std::uint32_t
Image::mipmap_count(void) const
{
	return m_mipmap_count;
}

BKSGE_INLINE ::VkImageLayout
Image::layout(void) const
{
	return m_layout;
}

BKSGE_INLINE ::VkImage
Image::image(void) const
{
	return m_image;
}

BKSGE_INLINE ::VkImageView
Image::image_view(void) const
{
	return m_image_view;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_INL_HPP
