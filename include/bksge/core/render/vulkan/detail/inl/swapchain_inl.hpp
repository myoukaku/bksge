/**
 *	@file	swapchain_inl.hpp
 *
 *	@brief	Swapchain クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SWAPCHAIN_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SWAPCHAIN_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/swapchain.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/surface.hpp>
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/clear_state.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Swapchain::Swapchain(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	vulkan::Surface const& surface,
	::VkFormat surface_format,
	bksge::uint32_t graphics_queue_family_index,
	bksge::uint32_t present_queue_family_index)
	: m_device(device)
	, m_info()
	, m_swapchain(VK_NULL_HANDLE)
{
	auto physical_device = device->GetPhysicalDevice();

	::VkSurfaceCapabilitiesKHR surface_capabilities;
	vk::GetPhysicalDeviceSurfaceCapabilitiesKHR(*physical_device, surface, &surface_capabilities);

	::VkExtent2D swapchain_extent = surface_capabilities.currentExtent;
	// width and height are either both 0xFFFFFFFF, or both not 0xFFFFFFFF.
	//if (surface_capabilities.currentExtent.width == 0xFFFFFFFF) {
	//	// If the surface size is undefined, the size is set to
	//	// the size of the images requested.
	//	swapchain_extent.width = info.width;
	//	swapchain_extent.height = info.height;
	//	if (swapchain_extent.width < surface_capabilities.minImageExtent.width) {
	//		swapchain_extent.width = surface_capabilities.minImageExtent.width;
	//	}
	//	else if (swapchain_extent.width > surface_capabilities.maxImageExtent.width) {
	//		swapchain_extent.width = surface_capabilities.maxImageExtent.width;
	//	}

	//	if (swapchain_extent.height < surface_capabilities.minImageExtent.height) {
	//		swapchain_extent.height = surface_capabilities.minImageExtent.height;
	//	}
	//	else if (swapchain_extent.height > surface_capabilities.maxImageExtent.height) {
	//		swapchain_extent.height = surface_capabilities.maxImageExtent.height;
	//	}
	//}

	::VkSurfaceTransformFlagBitsKHR pre_transform;
	if (surface_capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
	{
		pre_transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	}
	else
	{
		pre_transform = surface_capabilities.currentTransform;
	}

	::VkCompositeAlphaFlagBitsKHR composite_alpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	::VkCompositeAlphaFlagBitsKHR const composite_alpha_flags[] =
	{
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
	};

	for (auto flag : composite_alpha_flags)
	{
		if (surface_capabilities.supportedCompositeAlpha & flag)
		{
			composite_alpha = flag;
			break;
		}
	}

	m_info.surface          = surface;
	m_info.minImageCount    = surface_capabilities.minImageCount;
	m_info.imageFormat      = surface_format;
	m_info.imageColorSpace  = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	m_info.imageExtent      = swapchain_extent;
	m_info.imageArrayLayers = 1;
	m_info.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
		                      VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
							  VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	m_info.preTransform     = pre_transform;
	m_info.compositeAlpha   = composite_alpha;
	m_info.presentMode      = VK_PRESENT_MODE_FIFO_KHR;
#if !defined(__ANDROID__)
	m_info.clipped          = VK_TRUE;
#else
	m_info.clipped          = VK_FALSE;
#endif
	m_info.oldSwapchain     = VK_NULL_HANDLE;

	bksge::uint32_t const queue_family_indices[] =
	{
		graphics_queue_family_index,
		present_queue_family_index,
	};

	if (graphics_queue_family_index != present_queue_family_index)
	{
		m_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		m_info.SetQueueFamilyIndices(queue_family_indices);
	}
	else
	{
		m_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		m_info.SetQueueFamilyIndices(nullptr);
	}

	vk::CreateSwapchainKHR(*m_device, &m_info, nullptr, &m_swapchain);

	// Create ImageViews
	auto images = vk::GetSwapchainImagesKHR(*m_device, m_swapchain);
	for (auto&& image : images)
	{
		vk::ImageViewCreateInfo info;
		info.format                          = surface_format;
		info.components.r                    = VK_COMPONENT_SWIZZLE_R;
		info.components.g                    = VK_COMPONENT_SWIZZLE_G;
		info.components.b                    = VK_COMPONENT_SWIZZLE_B;
		info.components.a                    = VK_COMPONENT_SWIZZLE_A;
		info.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
		info.subresourceRange.baseMipLevel   = 0;
		info.subresourceRange.levelCount     = 1;
		info.subresourceRange.baseArrayLayer = 0;
		info.subresourceRange.layerCount     = 1;
		info.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
		info.image                           = image;

		::VkImageView view;
		vk::CreateImageView(*m_device, &info, nullptr, &view);
		m_image_views.push_back(view);

		TransitionImageLayout(
			command_pool,
			image,
			VK_IMAGE_ASPECT_COLOR_BIT,
			1,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
	}

	vk::GetDeviceQueue(*m_device, present_queue_family_index, 0, &m_present_queue);
}

BKSGE_INLINE
Swapchain::~Swapchain()
{
	for (auto&& image_view : m_image_views)
	{
		vk::DestroyImageView(*m_device, image_view, nullptr);
	}

	vk::DestroySwapchainKHR(*m_device, m_swapchain, nullptr);
}

BKSGE_INLINE bksge::uint32_t
Swapchain::AcquireNextImage(
	bksge::uint64_t timeout,
	::VkSemaphore semaphore,
	::VkFence     fence)
{
	bksge::uint32_t image_index;
	vk::AcquireNextImageKHR(
		*m_device,
		m_swapchain,
		timeout,
		semaphore,
		fence,
		&image_index);
	return image_index;
}

BKSGE_INLINE void
Swapchain::ClearColor(
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::uint32_t index,
	bksge::ClearState const& clear_state)
{
	if (!Test(clear_state.flag(), bksge::ClearFlag::kColor))
	{
		return;
	}

	auto images = vk::GetSwapchainImagesKHR(*m_device, m_swapchain);
	auto image = images[index];

	TransitionImageLayout(
		command_pool,
		image,
		VK_IMAGE_ASPECT_COLOR_BIT,
		1,
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	auto const clear_color = clear_state.color();

	::VkClearColorValue clear_value;
	clear_value.float32[0] = clear_color[0];
	clear_value.float32[1] = clear_color[1];
	clear_value.float32[2] = clear_color[2];
	clear_value.float32[3] = clear_color[3];

	::VkImageSubresourceRange range;
	range.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
	range.baseMipLevel   = 0;
	range.levelCount     = 1;
	range.baseArrayLayer = 0;
	range.layerCount     = 1;

	auto command_buffer = BeginSingleTimeCommands(command_pool);
	::vkCmdClearColorImage(
		*command_buffer,
		image,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		&clear_value,
		1, &range);
	EndSingleTimeCommands(command_pool, command_buffer);

	TransitionImageLayout(
		command_pool,
		image,
		VK_IMAGE_ASPECT_COLOR_BIT,
		1,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
}

//BKSGE_INLINE std::vector<VkImage>
//Swapchain::GetImages(void) const
//{
//	bksge::uint32_t count = 0;
//	vk::GetSwapchainImagesKHR(*m_device, m_swapchain, &count, nullptr);
//
//	std::vector<VkImage> images;
//	images.resize(count);
//	vk::GetSwapchainImagesKHR(*m_device, m_swapchain, &count, images.data());
//
//	return images;
//}

BKSGE_INLINE std::vector<::VkImageView> const&
Swapchain::GetImageViews(void) const
{
	return m_image_views;
}

BKSGE_INLINE ::VkExtent2D
Swapchain::extent(void) const
{
	return m_info.imageExtent;
}

BKSGE_INLINE bksge::uint32_t
Swapchain::width(void) const
{
	return m_info.imageExtent.width;
}

BKSGE_INLINE bksge::uint32_t
Swapchain::height(void) const
{
	return m_info.imageExtent.height;
}

BKSGE_INLINE ::VkFormat
Swapchain::format(void) const
{
	return m_info.imageFormat;
}

BKSGE_INLINE void
Swapchain::Present(bksge::uint32_t const& image_index)
{
	vk::PresentInfoKHR present;
	present.SetSwapchains(&m_swapchain);
	present.SetWaitSemaphores(nullptr);
	present.pImageIndices = &image_index;
	present.pResults      = nullptr;

	vk::QueuePresentKHR(m_present_queue, &present);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SWAPCHAIN_INL_HPP
