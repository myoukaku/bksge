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
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/clear_state_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/cstdint/uint64_t.hpp>
#include <bksge/fnd/vector.hpp>

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
		vulkan::CommandPoolSharedPtr const& command_pool,
		vulkan::Surface const& surface,
		::VkFormat surface_format,
		bksge::uint32_t graphics_queue_family_index,
		bksge::uint32_t present_queue_family_index);

	~Swapchain();

	::VkResult AcquireNextImage(
		bksge::uint64_t  timeout,
		::VkSemaphore    semaphore,
		::VkFence        fence,
		bksge::uint32_t* image_index);

	void ClearColor(
		vulkan::CommandPoolSharedPtr const& command_pool,
		bksge::uint32_t index,
		bksge::ClearState const& clear_state);

	//bksge::vector<VkImage> GetImages(void) const;

	bksge::vector<::VkImageView> const& image_views(void) const;

	::VkExtent2D extent(void) const;

	bksge::uint32_t width(void) const;
	bksge::uint32_t height(void) const;

	::VkFormat format(void) const;

	::VkResult Present(bksge::uint32_t image_index);

private:
	// noncopyable
	Swapchain(Swapchain const&) = delete;
	Swapchain& operator=(Swapchain const&) = delete;

private:
	vulkan::DeviceSharedPtr			m_device;
	vk::SwapchainCreateInfoKHR		m_info;
	::VkSwapchainKHR				m_swapchain;
	bksge::vector<::VkImageView>	m_image_views;
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
