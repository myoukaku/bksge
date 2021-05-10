﻿/**
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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/memory/make_unique.hpp>

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

inline void
TransitionImageLayout(
	vulkan::CommandBuffer* command_buffer,
	::VkImage image,
	::VkImageAspectFlags aspect_mask,
	bksge::uint32_t mipmap_count,
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
	::VkImage image,
	::VkFormat format,
	vulkan::Extent2D const& extent,
	bksge::uint32_t mipmap_count)
	: m_image(image)
	, m_device()
	, m_device_memory()
	, m_format(format)
	, m_extent(extent)
	, m_mipmap_count(mipmap_count)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
{
}

BKSGE_INLINE
Image::Image(
	vulkan::DeviceSharedPtr const& device,
	::VkFormat format,
	vulkan::Extent2D const& extent,
	bksge::uint32_t mipmap_count,
	::VkSampleCountFlagBits num_samples,
	::VkImageUsageFlags usage)
	: m_image(VK_NULL_HANDLE)
	, m_device(device)
	, m_device_memory()
	, m_format(format)
	, m_extent(extent)
	, m_mipmap_count(mipmap_count)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
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

	auto const mem_reqs = device->GetImageMemoryRequirements(m_image);

	m_device_memory = bksge::make_unique<vulkan::DeviceMemory>(
		device, mem_reqs, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	m_device_memory->BindImage(m_image, 0);
}

BKSGE_INLINE
Image::~Image()
{
	if (m_device)
	{
		m_device->DestroyImage(m_image);
	}
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
		aspect_mask,
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
		aspect_mask,
		current_layout);
}

BKSGE_INLINE void
Image::ClearDepthStencil(
	vulkan::CommandBuffer* command_buffer,
	::VkImageAspectFlags aspect_mask,
	float depth,
	bksge::uint32_t stencil)
{
	if (aspect_mask == 0)
	{
		return;
	}

	auto const current_layout = this->TransitionLayout(
		command_buffer,
		aspect_mask,
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
		aspect_mask,
		current_layout);
}

BKSGE_INLINE ::VkImageLayout
Image::TransitionLayout(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkImageAspectFlags aspect_mask,
	::VkImageLayout new_layout)
{
	vulkan::ScopedOneTimeCommandBuffer command_buffer(command_pool);
	return TransitionLayout(command_buffer.Get(), aspect_mask, new_layout);
}

BKSGE_INLINE ::VkImageLayout
Image::TransitionLayout(
	vulkan::CommandBuffer* command_buffer,
	::VkImageAspectFlags aspect_mask,
	::VkImageLayout new_layout)
{
	auto const old_layout = m_layout;
	m_layout = new_layout;
	detail::TransitionImageLayout(
		command_buffer,
		m_image,
		aspect_mask,
		m_mipmap_count,
		old_layout,
		new_layout);
	return old_layout;
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

BKSGE_INLINE bksge::uint32_t
Image::mipmap_count(void) const
{
	return m_mipmap_count;
}

BKSGE_INLINE ::VkImageLayout
Image::layout(void) const
{
	return m_layout;
}

BKSGE_INLINE
Image::operator ::VkImage() const
{
	return m_image;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_INL_HPP
