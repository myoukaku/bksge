﻿/**
 *	@file	image_view.hpp
 *
 *	@brief	ImageView クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP

#include <bksge/core/render/vulkan/detail/fwd/image_view_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class ImageView
{
public:
	explicit ImageView(
		vulkan::DeviceSharedPtr const& device,
		::VkImage image,
		::VkFormat format,
		bksge::uint32_t mipmap_count,
		::VkImageAspectFlags aspect_mask);

	explicit ImageView(
		vulkan::DeviceSharedPtr const& device,
		vulkan::Image const& image,
		::VkImageAspectFlags aspect_mask);

	~ImageView();

public:
	::VkImageAspectFlags aspect_mask(void) const;

public:
	operator ::VkImageView() const;

private:
	// noncopyable
	ImageView(ImageView const&) = delete;
	ImageView& operator=(ImageView const&) = delete;

private:
	::VkImageView				m_image_view = VK_NULL_HANDLE;
	::VkImageAspectFlags		m_aspect_mask;
	vulkan::DeviceSharedPtr		m_device;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/image_view_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP
