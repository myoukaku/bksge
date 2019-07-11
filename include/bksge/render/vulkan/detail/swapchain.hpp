/**
 *	@file	swapchain.hpp
 *
 *	@brief	SwapchainKHR クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP

#include <bksge/render/vulkan/detail/fwd/swapchain_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace vk
{

struct SwapchainCreateInfoKHR : public ::VkSwapchainCreateInfoKHR
{
	SwapchainCreateInfoKHR(void);
};

class SwapchainKHR
{
public:
	explicit SwapchainKHR(
		std::shared_ptr<vk::Device> const& device,
		vk::SwapchainCreateInfoKHR const& info);

	~SwapchainKHR();

	std::vector<VkImage> GetImages(void) const;

	::VkExtent2D extent(void) const;

	std::uint32_t width(void) const;
	std::uint32_t height(void) const;

	::VkFormat format(void) const;

	operator ::VkSwapchainKHR() const;

	::VkSwapchainKHR const* GetAddress() const;

private:
	::VkSwapchainKHR			m_swap_chain;
	vk::SwapchainCreateInfoKHR	m_info;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/swapchain_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP
