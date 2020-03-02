/**
 *	@file	image_object_inl.hpp
 *
 *	@brief	ImageObject クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_OBJECT_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_OBJECT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/image_object.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/device_memory.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
ImageObject::ImageObject(
	vulkan::DeviceSharedPtr const& device,
	::VkFormat                     format,
	::VkExtent2D const&            extent,
	bksge::uint32_t                mipmap_count,
	::VkSampleCountFlagBits        num_samples,
	::VkImageTiling                tiling,
	::VkImageUsageFlags            usage,
	::VkImageLayout                initial_layout,
	::VkFlags                      requirements_mask)
{
	m_image = bksge::make_unique<vulkan::Image>(
		device, format, extent, mipmap_count, num_samples, tiling, usage, initial_layout);

	auto const mem_reqs = m_image->requirements();

	m_device_memory = bksge::make_unique<vulkan::DeviceMemory>(
		device, mem_reqs, requirements_mask);

	vk::BindImageMemory(*device, *m_image, *m_device_memory, 0);
}

BKSGE_INLINE
ImageObject::~ImageObject()
{
}

BKSGE_INLINE void*
ImageObject::MapMemory(::VkDeviceSize size)
{
	return m_device_memory->MapMemory(size);
}

BKSGE_INLINE void
ImageObject::UnmapMemory(void)
{
	m_device_memory->UnmapMemory();
}

BKSGE_INLINE void
ImageObject::TransitionLayout(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkImageAspectFlags aspect_mask,
	bksge::uint32_t mipmap_count,
	::VkImageLayout old_layout,
	::VkImageLayout new_layout)
{
	m_image->TransitionLayout(
		command_pool, aspect_mask, mipmap_count, old_layout, new_layout);
}

BKSGE_INLINE ::VkImage
ImageObject::GetImage(void) const
{
	return *m_image;
}

BKSGE_INLINE ::VkFormat const&
ImageObject::GetFormat(void) const
{
	return m_image->format();
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_OBJECT_INL_HPP
