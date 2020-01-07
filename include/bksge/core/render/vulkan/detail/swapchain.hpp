/**
 *	@file	swapchain.hpp
 *
 *	@brief	Swapchain クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP

#include <bksge/core/render/vulkan/detail/fwd/swapchain_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/surface_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Swapchain
{
public:
	explicit Swapchain(
		vulkan::DeviceSharedPtr const& device,
		vulkan::Surface const& surface,
		::VkFormat surface_format,
		std::uint32_t graphics_queue_family_index,
		std::uint32_t present_queue_family_index);

	~Swapchain();

	//std::vector<VkImage> GetImages(void) const;

	std::vector<::VkImageView> const& GetImageViews(void) const;

	::VkExtent2D extent(void) const;

	std::uint32_t width(void) const;
	std::uint32_t height(void) const;

	::VkFormat format(void) const;

	operator ::VkSwapchainKHR() const;

	::VkSwapchainKHR const* GetAddressOf() const;

private:
	vulkan::DeviceSharedPtr			m_device;
	vk::SwapchainCreateInfoKHR		m_info;
	::VkSwapchainKHR				m_swap_chain;
	std::vector<::VkImageView>		m_image_views;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/swapchain_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP
