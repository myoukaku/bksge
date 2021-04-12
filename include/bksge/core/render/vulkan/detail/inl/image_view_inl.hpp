/**
 *	@file	image_view_inl.hpp
 *
 *	@brief	ImageView クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_VIEW_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_VIEW_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
ImageView::ImageView(
	vulkan::DeviceSharedPtr const& device,
	vulkan::Image const& image,
	::VkImageAspectFlags aspect_mask)
	: m_device(device)
	, m_image_view(VK_NULL_HANDLE)
	, m_aspect_mask(aspect_mask)
{
	vk::ImageViewCreateInfo info;
	info.image                           = image;
	info.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
	info.format                          = image.format();
	info.components.r                    = VK_COMPONENT_SWIZZLE_R;
	info.components.g                    = VK_COMPONENT_SWIZZLE_G;
	info.components.b                    = VK_COMPONENT_SWIZZLE_B;
	info.components.a                    = VK_COMPONENT_SWIZZLE_A;
	info.subresourceRange.aspectMask     = aspect_mask;
	info.subresourceRange.baseMipLevel   = 0;
	info.subresourceRange.levelCount     = image.mipmap_count();
	info.subresourceRange.baseArrayLayer = 0;
	info.subresourceRange.layerCount     = 1;

	vk::CreateImageView(*m_device, &info, nullptr, &m_image_view);
}

BKSGE_INLINE
ImageView::~ImageView()
{
	vk::DestroyImageView(*m_device, m_image_view, nullptr);
}

BKSGE_INLINE ::VkImageAspectFlags
ImageView::aspect_mask(void) const
{
	return m_aspect_mask;
}

BKSGE_INLINE
ImageView::operator ::VkImageView() const
{
	return m_image_view;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_VIEW_INL_HPP
