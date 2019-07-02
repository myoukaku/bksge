/**
 *	@file	swapchain.hpp
 *
 *	@brief	Swapchain クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct SwapchainCreateInfoKHR : public ::VkSwapchainCreateInfoKHR
{
	SwapchainCreateInfoKHR(void)
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
};

class Swapchain
{
public:
	explicit Swapchain(
		std::shared_ptr<vk::Device> const& device,
		vk::SwapchainCreateInfoKHR const& info)
		: m_swap_chain(VK_NULL_HANDLE)
		, m_info(info)
		, m_device(device)
	{
		vk::CreateSwapchainKHR(*m_device, &info, nullptr, &m_swap_chain);
	}

	~Swapchain()
	{
		vk::DestroySwapchainKHR(*m_device, m_swap_chain, nullptr);
	}

	std::vector<VkImage> GetImages(void) const
	{
		std::uint32_t count = 0;
		vk::GetSwapchainImagesKHR(*m_device, m_swap_chain, &count, nullptr);

		std::vector<VkImage> images;
		images.resize(count);
		vk::GetSwapchainImagesKHR(*m_device, m_swap_chain, &count, images.data());

		return images;
	}

	std::uint32_t width(void) const
	{
		return m_info.imageExtent.width;
	}

	std::uint32_t height(void) const
	{
		return m_info.imageExtent.height;
	}

	::VkFormat format(void) const
	{
		return m_info.imageFormat;
	}

	operator ::VkSwapchainKHR() const
	{
		return m_swap_chain;
	}

	::VkSwapchainKHR const* GetAddress() const
	{
		return &m_swap_chain;
	}

private:
	::VkSwapchainKHR			m_swap_chain;
	vk::SwapchainCreateInfoKHR	m_info;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP
