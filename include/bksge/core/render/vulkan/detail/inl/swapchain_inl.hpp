/**
 *	@file	swapchain_inl.hpp
 *
 *	@brief	SwapchainKHR クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SWAPCHAIN_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SWAPCHAIN_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/swapchain.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
SwapchainCreateInfoKHR::SwapchainCreateInfoKHR(void)
{
	sType                 = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	pNext                 = nullptr;
	flags                 = 0;
	surface               = VK_NULL_HANDLE;
	minImageCount         = 0;
	imageFormat           = VK_FORMAT_UNDEFINED;
	imageColorSpace       = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	imageExtent.width     = 0;
	imageExtent.height    = 0;
	imageArrayLayers      = 0;
	imageUsage            = 0;
	imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
	queueFamilyIndexCount = 0;
	pQueueFamilyIndices   = nullptr;
	preTransform          = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	compositeAlpha        = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	presentMode           = VK_PRESENT_MODE_IMMEDIATE_KHR;
	clipped               = VK_FALSE;
	oldSwapchain          = VK_NULL_HANDLE;
}

BKSGE_INLINE
SwapchainKHR::SwapchainKHR(
	std::shared_ptr<vk::Device> const& device,
	vk::SwapchainCreateInfoKHR const& info)
	: m_swap_chain(VK_NULL_HANDLE)
	, m_info(info)
	, m_device(device)
{
	vk::CreateSwapchainKHR(*m_device, &info, nullptr, &m_swap_chain);
}

BKSGE_INLINE
SwapchainKHR::~SwapchainKHR()
{
	vk::DestroySwapchainKHR(*m_device, m_swap_chain, nullptr);
}

BKSGE_INLINE std::vector<VkImage>
SwapchainKHR::GetImages(void) const
{
	std::uint32_t count = 0;
	vk::GetSwapchainImagesKHR(*m_device, m_swap_chain, &count, nullptr);

	std::vector<VkImage> images;
	images.resize(count);
	vk::GetSwapchainImagesKHR(*m_device, m_swap_chain, &count, images.data());

	return images;
}

BKSGE_INLINE ::VkExtent2D
SwapchainKHR::extent(void) const
{
	return m_info.imageExtent;
}

BKSGE_INLINE std::uint32_t
SwapchainKHR::width(void) const
{
	return m_info.imageExtent.width;
}

BKSGE_INLINE std::uint32_t
SwapchainKHR::height(void) const
{
	return m_info.imageExtent.height;
}

BKSGE_INLINE ::VkFormat
SwapchainKHR::format(void) const
{
	return m_info.imageFormat;
}

BKSGE_INLINE
SwapchainKHR::operator ::VkSwapchainKHR() const
{
	return m_swap_chain;
}

BKSGE_INLINE ::VkSwapchainKHR const*
SwapchainKHR::GetAddress() const
{
	return &m_swap_chain;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SWAPCHAIN_INL_HPP
