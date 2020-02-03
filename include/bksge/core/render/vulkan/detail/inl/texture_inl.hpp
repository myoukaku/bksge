/**
 *	@file	texture_inl.hpp
 *
 *	@brief	Texture クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/texture.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/device_memory.hpp>
#include <bksge/core/render/vulkan/detail/texture_format.hpp>
#include <bksge/core/render/vulkan/detail/extent2d.hpp>
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <cstring>

namespace bksge
{

namespace render
{

namespace vulkan
{

inline std::unique_ptr<vulkan::CommandBuffer>
beginSingleTimeCommands(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool)
{
	auto command_buffer = bksge::make_unique<vulkan::CommandBuffer>(
		device, command_pool);

	vk::CommandBufferBeginInfo begin_info;
	begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vk::BeginCommandBuffer(*command_buffer, &begin_info);

	return command_buffer;
}

inline void
endSingleTimeCommands(
	std::unique_ptr<vulkan::CommandBuffer> const& command_buffer,
	::VkQueue graphics_queue)
{
	vk::EndCommandBuffer(*command_buffer);

	vk::SubmitInfo submit_info;
	submit_info.SetCommandBuffers(command_buffer->GetAddressOf());

	vk::QueueSubmit(graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
	vk::QueueWaitIdle(graphics_queue);
}

inline void
transitionImageLayout(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkQueue graphics_queue,
	::VkImage image,
	::VkImageLayout old_layout,
	::VkImageLayout new_layout,
	::VkPipelineStageFlags src_stage,
	::VkPipelineStageFlags dst_stage)
{
	auto command_buffer = beginSingleTimeCommands(device, command_pool);

	vk::ImageMemoryBarrier barrier;
    barrier.srcAccessMask                   = 0;
    barrier.dstAccessMask                   = 0;
	barrier.oldLayout                       = old_layout;
	barrier.newLayout                       = new_layout;
	barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
	barrier.image                           = image;
	barrier.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel   = 0;
	barrier.subresourceRange.levelCount     = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount     = 1;

	switch (old_layout)
	{
	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_PREINITIALIZED:
		barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
		break;

	default:
		break;
	}

    switch (new_layout)
	{
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		break;

	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		break;

	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		break;

	default:
		break;
	}

	vk::CmdPipelineBarrier(
		*command_buffer,
		src_stage,
		dst_stage,
		0,
		0, nullptr,
		0, nullptr,
		1, &barrier
	);

	endSingleTimeCommands(command_buffer, graphics_queue);
}

inline void copyBufferToImage(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkQueue graphics_queue,
	::VkBuffer buffer,
	::VkImage image,
	::VkExtent2D extent)
{
	auto command_buffer = beginSingleTimeCommands(device, command_pool);

	::VkBufferImageCopy region {};
	region.bufferOffset                    = 0;
	region.bufferRowLength                 = 0;
	region.bufferImageHeight               = 0;
	region.imageSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel       = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount     = 1;
	region.imageOffset                     = {0, 0, 0};
	region.imageExtent = {extent.width,extent.height,1};

	vk::CmdCopyBufferToImage(
		*command_buffer,
		buffer,
		image,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1,
		&region);

	endSingleTimeCommands(command_buffer, graphics_queue);
}

BKSGE_INLINE
Texture::Texture(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::Texture const& texture)
{
	auto const& physical_device = device->GetPhysicalDevice();

	::VkFormat format = vulkan::TextureFormat(texture.format());

	::VkFormatProperties format_props;
	vk::GetPhysicalDeviceFormatProperties(
		*physical_device, format, &format_props);

	::VkFormatFeatureFlags const features = VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT;

	bool const needs_staging =
		((format_props.linearTilingFeatures & features) != features);

	::VkImageTiling const tiling = needs_staging ?
		VK_IMAGE_TILING_OPTIMAL :
		VK_IMAGE_TILING_LINEAR;

	::VkImageUsageFlags usage = VK_IMAGE_USAGE_SAMPLED_BIT;
	if (needs_staging)
	{
		usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	}

	::VkImageLayout const initial_layout = needs_staging ?
		VK_IMAGE_LAYOUT_UNDEFINED :
		VK_IMAGE_LAYOUT_PREINITIALIZED;

	::VkExtent2D extent = vulkan::Extent2D(texture.size());
	m_image = bksge::make_unique<vulkan::Image>(
		device,
		format,
		extent,
		VK_SAMPLE_COUNT_1_BIT,
		tiling,
		usage,
		initial_layout);

	{
		auto const mem_reqs = m_image->requirements();

		::VkFlags requirements_mask = needs_staging ?
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT :
			(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			 VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		m_device_memory =
			bksge::make_unique<vulkan::DeviceMemory>(
				device,
				mem_reqs,
				requirements_mask);
	}

	vk::BindImageMemory(*device, *m_image, *m_device_memory, 0);

	auto image_size = texture.stride() * texture.height();

	std::unique_ptr<vulkan::Buffer>			staging_buffer;
	std::unique_ptr<vulkan::DeviceMemory>	staging_device_memory;

	if (needs_staging)
	{
		staging_buffer = bksge::make_unique<vulkan::Buffer>(
			device,
			image_size,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT);

		auto const mem_reqs = staging_buffer->requirements();

		staging_device_memory = bksge::make_unique<vulkan::DeviceMemory>(
			device,
			mem_reqs,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		vk::BindBufferMemory(*device, *staging_buffer, *staging_device_memory, 0);
	}

	std::uint8_t* dst;
	vk::MapMemory(
		*device,
		*(needs_staging ? staging_device_memory : m_device_memory),
		0,
		VK_WHOLE_SIZE,
		0,
		reinterpret_cast<void**>(&dst));

	auto src = texture.data();
	std::memcpy(dst, src, image_size);

	vk::UnmapMemory(*device, *(needs_staging ? staging_device_memory : m_device_memory));

	if (!needs_staging)
	{
		transitionImageLayout(
			device,
			command_pool,
			command_pool->GetQueue(),
			*m_image,
			initial_layout,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			VK_PIPELINE_STAGE_HOST_BIT,
			VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
	}
	else
	{
		transitionImageLayout(
			device,
			command_pool,
			command_pool->GetQueue(),
			*m_image,
			initial_layout,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
			VK_PIPELINE_STAGE_TRANSFER_BIT);

		copyBufferToImage(
			device,
			command_pool,
			command_pool->GetQueue(),
			*staging_buffer,
			*m_image,
			extent);

		transitionImageLayout(
			device,
			command_pool,
			command_pool->GetQueue(),
			*m_image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			VK_PIPELINE_STAGE_TRANSFER_BIT,
			VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
	}


	m_image_view = bksge::make_unique<vulkan::ImageView>(
		device, *m_image, VK_IMAGE_ASPECT_COLOR_BIT);
}

BKSGE_INLINE
Texture::~Texture()
{
}

BKSGE_INLINE vulkan::ImageViewUniquePtr const&
Texture::GetImageView(void) const
{
	return m_image_view;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_INL_HPP
