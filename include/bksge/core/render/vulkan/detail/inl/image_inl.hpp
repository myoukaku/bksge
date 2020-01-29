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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

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
	info.mipLevels     = 1;
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
