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
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct ImageViewCreateInfo : public ::VkImageViewCreateInfo
{
	ImageViewCreateInfo(void);
};

class ImageView
{
public:
	explicit ImageView(
		std::shared_ptr<vk::Device> const& device,
		vk::ImageViewCreateInfo const& info);

	~ImageView();

	operator ::VkImageView() const;

private:
	::VkImageView				m_image_view;
	std::shared_ptr<vk::Device> m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/image_view_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP
