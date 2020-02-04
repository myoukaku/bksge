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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
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

	std::uint32_t AcquireNextImage(
		std::uint64_t timeout,
		::VkSemaphore semaphore,
		::VkFence     fence);

	//std::vector<VkImage> GetImages(void) const;

	std::vector<::VkImageView> const& GetImageViews(void) const;

	::VkExtent2D extent(void) const;

	std::uint32_t width(void) const;
	std::uint32_t height(void) const;

	::VkFormat format(void) const;

	void Present(std::uint32_t const& image_index);

private:
	// noncopyable
	Swapchain(Swapchain const&) = delete;
	Swapchain& operator=(Swapchain const&) = delete;

private:
	vulkan::DeviceSharedPtr			m_device;
	vk::SwapchainCreateInfoKHR		m_info;
	::VkSwapchainKHR				m_swapchain;
	std::vector<::VkImageView>		m_image_views;
	::VkQueue						m_present_queue;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/swapchain_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP
