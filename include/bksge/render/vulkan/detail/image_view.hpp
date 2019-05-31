/**
 *	@file	image_view.hpp
 *
 *	@brief	Surface クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/instance.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct ImageViewCreateInfo : public ::VkImageViewCreateInfo
{
	ImageViewCreateInfo(void)
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
		subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
		subresourceRange.baseMipLevel   = 0;
		subresourceRange.levelCount     = 0;
		subresourceRange.baseArrayLayer = 0;
		subresourceRange.layerCount     = 0;
	}
};

class ImageView
{
public:
	explicit ImageView(
		std::shared_ptr<vk::Device> const& device,
		vk::ImageViewCreateInfo const& info)
		: m_image_view(VK_NULL_HANDLE)
		, m_device(device)
	{
		vk::CreateImageView(*m_device, &info, nullptr, &m_image_view);
	}

	~ImageView()
	{
		vk::DestroyImageView(*m_device, m_image_view, nullptr);
	}

	operator ::VkImageView() const
	{
		return m_image_view;
	}

private:
	::VkImageView				m_image_view;
	std::shared_ptr<vk::Device> m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_IMAGE_VIEW_HPP
