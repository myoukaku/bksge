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
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Image::Image(
	vulkan::DeviceSharedPtr const& device,
	::VkFormat format,
	::VkExtent2D const& extent,
	bksge::uint32_t mipmap_count,
	::VkSampleCountFlagBits num_samples,
	::VkImageTiling tiling,
	::VkImageUsageFlags usage,
	::VkImageLayout initial_layout)
	: m_device(device)
	, m_image(VK_NULL_HANDLE)
	, m_format(format)
{
	vk::ImageCreateInfo info;
	info.imageType     = VK_IMAGE_TYPE_2D;
	info.format        = format;
	info.extent.width  = extent.width;
	info.extent.height = extent.height;
	info.extent.depth  = 1;
	info.mipLevels     = mipmap_count;
	info.arrayLayers   = 1;
	info.samples       = num_samples;
	info.tiling        = tiling;
	info.usage         = usage;
	info.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
	info.initialLayout = initial_layout;
	info.SetQueueFamilyIndices(nullptr);

	vk::CreateImage(*device, &info, nullptr, &m_image);
}

BKSGE_INLINE
Image::~Image()
{
	vk::DestroyImage(*m_device, m_image, nullptr);
}

BKSGE_INLINE void
Image::TransitionLayout(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkImageAspectFlags aspect_mask,
	bksge::uint32_t mipmap_count,
	::VkImageLayout old_layout,
	::VkImageLayout new_layout)
{
	TransitionImageLayout(
		command_pool, m_image, aspect_mask, mipmap_count, old_layout, new_layout);
}

BKSGE_INLINE void
TransitionImageLayout(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkImage image,
	::VkImageAspectFlags aspect_mask,
	bksge::uint32_t mipmap_count,
	::VkImageLayout old_layout,
	::VkImageLayout new_layout)
{
	auto command_buffer = BeginSingleTimeCommands(command_pool);

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

	::VkPipelineStageFlags src_stage;
	switch (old_layout)
	{
	case VK_IMAGE_LAYOUT_UNDEFINED:
		barrier.srcAccessMask = 0;
		src_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		break;
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		src_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		src_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		barrier.srcAccessMask =
			VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
			VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		src_stage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		break;
	case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
		barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		src_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		break;
	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		barrier.srcAccessMask =
			VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
			VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
		src_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		break;
	case VK_IMAGE_LAYOUT_GENERAL:
		barrier.srcAccessMask =
			VK_ACCESS_SHADER_READ_BIT |
			VK_ACCESS_SHADER_WRITE_BIT;
		src_stage = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
		break;
	case VK_IMAGE_LAYOUT_PREINITIALIZED:
		barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
		src_stage = VK_PIPELINE_STAGE_HOST_BIT;
		break;
	default:
		throw std::runtime_error("unsupported layout transition!");
	}

	::VkPipelineStageFlags dst_stage;
	switch (new_layout)
	{
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		break;
	case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		barrier.dstAccessMask =
			VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
			VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		dst_stage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		break;
	case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
		barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dst_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		break;
	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		barrier.dstAccessMask =
			VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
			VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
		dst_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		break;
	case VK_IMAGE_LAYOUT_GENERAL:
		barrier.dstAccessMask =
			VK_ACCESS_SHADER_READ_BIT |
			VK_ACCESS_SHADER_WRITE_BIT;
		dst_stage = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
		break;
	default:
		throw std::runtime_error("unsupported layout transition!");
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

	EndSingleTimeCommands(command_pool, command_buffer);
}

BKSGE_INLINE
Image::operator ::VkImage() const
{
	return m_image;
}

BKSGE_INLINE ::VkFormat const&
Image::format(void) const
{
	return m_format;
}

BKSGE_INLINE ::VkMemoryRequirements
Image::requirements(void) const
{
	::VkMemoryRequirements result;
	vk::GetImageMemoryRequirements(*m_device, m_image, &result);
	return result;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_INL_HPP
