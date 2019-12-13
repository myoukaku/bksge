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
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
ImageViewCreateInfo::ImageViewCreateInfo(void)
{
	sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	pNext                           = nullptr;
	flags                           = 0;
	image                           = VK_NULL_HANDLE;
	viewType                        = VK_IMAGE_VIEW_TYPE_2D;
	format                          = VK_FORMAT_UNDEFINED;
	components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
	components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
	components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
	components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;
	subresourceRange.aspectMask     = 0;
	subresourceRange.baseMipLevel   = 0;
	subresourceRange.levelCount     = 0;
	subresourceRange.baseArrayLayer = 0;
	subresourceRange.layerCount     = 0;
}

BKSGE_INLINE
ImageView::ImageView(
	std::shared_ptr<vk::Device> const& device,
	vk::ImageViewCreateInfo const& info)
	: m_image_view(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::CreateImageView(*m_device, &info, nullptr, &m_image_view);
}

BKSGE_INLINE
ImageView::~ImageView()
{
	vk::DestroyImageView(*m_device, m_image_view, nullptr);
}

BKSGE_INLINE
ImageView::operator ::VkImageView() const
{
	return m_image_view;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_IMAGE_VIEW_INL_HPP
