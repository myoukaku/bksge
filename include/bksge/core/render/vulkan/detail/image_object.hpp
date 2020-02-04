﻿/**
 *	@file	image_object.hpp
 *
 *	@brief	ImageObject クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_OBJECT_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_OBJECT_HPP

#include <bksge/core/render/vulkan/detail/fwd/image_object_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_memory_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class ImageObject
{
public:
	explicit ImageObject(
		vulkan::DeviceSharedPtr const& device,
		::VkFormat                     format,
		::VkExtent2D const&            extent,
		::VkSampleCountFlagBits        num_samples,
		::VkImageTiling                tiling,
		::VkImageUsageFlags            usage,
		::VkImageLayout                initial_layout,
		::VkFlags                      requirements_mask);

	~ImageObject();

	void* MapMemory(::VkDeviceSize size);

	void UnmapMemory(void);

	::VkImage GetImage(void) const;

	::VkFormat const& GetFormat(void) const;

private:
	// noncopyable
	ImageObject(ImageObject const&) = delete;
	ImageObject& operator=(ImageObject const&) = delete;

private:
	vulkan::ImageUniquePtr			m_image;
	vulkan::DeviceMemoryUniquePtr	m_device_memory;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/image_object_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_OBJECT_HPP