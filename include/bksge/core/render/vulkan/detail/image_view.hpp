/**
 *	@file	image_view.hpp
 *
 *	@brief	ImageView クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP

#include <bksge/core/render/vulkan/detail/fwd/image_view_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

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
		::VkImageAspectFlags aspect_mask,
		std::uint32_t mipmap_count);

	~ImageView();

	operator ::VkImageView() const;

private:
	// noncopyable
	ImageView(ImageView const&) = delete;
	ImageView& operator=(ImageView const&) = delete;

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkImageView				m_image_view;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/image_view_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP
