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
#include <bksge/core/render/vulkan/detail/queue.hpp>
#include <bksge/core/render/vulkan/detail/extent2d.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/memory/make_shared.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <cstdint>
#include <utility>

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
	::VkFormat surface_format)
	: m_swapchain(VK_NULL_HANDLE)
	, m_info()
	, m_device(device)
	, m_images()
	, m_present_queue()
{
	auto physical_device = device->physical_device();

	auto const surface_capabilities = surface.GetCapabilities(*physical_device);

	vulkan::Extent2D swapchain_extent = surface_capabilities.currentExtent;
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

	m_info.surface          = surface.Get();
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

	auto const graphics_queue_family_index =
		physical_device->GetGraphicsQueueFamilyIndex();
	auto const present_queue_family_index =
		surface.GetPresentQueueFamilyIndex(*physical_device);

	std::uint32_t const queue_family_indices[] =
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

	m_swapchain = m_device->CreateSwapchain(m_info);

	// Create ImageViews
	auto images = m_device->GetSwapchainImages(m_swapchain);
	for (auto&& img : images)
	{
		auto image = bksge::make_shared<vulkan::Image>(
			m_device,
			img,
			surface_format,
			swapchain_extent,
			1);

		image->TransitionLayout(
			command_pool,
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

		m_images.push_back(std::move(image));
	}

	m_present_queue = bksge::make_unique<vulkan::Queue>(
		m_device, present_queue_family_index, 0);
}

BKSGE_INLINE
Swapchain::~Swapchain()
{
	m_device->DestroySwapchain(m_swapchain);
}

BKSGE_INLINE ::VkResult
Swapchain::AcquireNextImage(
	std::uint64_t   timeout,
	::VkSemaphore   semaphore,
	::VkFence       fence,
	std::uint32_t*	image_index)
{
	return m_device->AcquireNextImage(
		m_swapchain,
		timeout,
		semaphore,
		fence,
		image_index);
}

BKSGE_INLINE bksge::vector<vulkan::ImageSharedPtr> const&
Swapchain::images(void) const
{
	return m_images;
}

BKSGE_INLINE vulkan::Extent2D
Swapchain::extent(void) const
{
	return m_info.imageExtent;
}

BKSGE_INLINE std::uint32_t
Swapchain::width(void) const
{
	return m_info.imageExtent.width;
}

BKSGE_INLINE std::uint32_t
Swapchain::height(void) const
{
	return m_info.imageExtent.height;
}

BKSGE_INLINE ::VkFormat
Swapchain::format(void) const
{
	return m_info.imageFormat;
}

BKSGE_INLINE ::VkResult
Swapchain::Present(std::uint32_t image_index)
{
	vk::PresentInfoKHR present;
	present.SetSwapchains(m_swapchain);
	present.SetWaitSemaphores(nullptr);
	present.pImageIndices = &image_index;
	present.pResults      = nullptr;

	return m_present_queue->Present(present);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SWAPCHAIN_INL_HPP
