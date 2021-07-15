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
#include <bksge/core/render/vulkan/detail/fwd/image_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/queue_fwd.hpp>
#include <bksge/core/render/vulkan/detail/extent2d.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

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
		::VkFormat surface_format);

	~Swapchain();

	::VkResult AcquireNextImage(
		std::uint64_t    timeout,
		::VkSemaphore    semaphore,
		::VkFence        fence,
		std::uint32_t*   image_index);

public:
	bksge::vector<vulkan::ImageSharedPtr> const& images(void) const;

public:
	vulkan::Extent2D extent(void) const;

	std::uint32_t width(void) const;
	std::uint32_t height(void) const;

public:
	::VkFormat format(void) const;

public:
	::VkResult Present(std::uint32_t image_index);

private:
	// noncopyable
	Swapchain(Swapchain const&) = delete;
	Swapchain& operator=(Swapchain const&) = delete;

private:
	::VkSwapchainKHR				m_swapchain;
	vk::SwapchainCreateInfoKHR		m_info;
	vulkan::DeviceSharedPtr			m_device;
	bksge::vector<vulkan::ImageSharedPtr>	m_images;
	vulkan::QueueUniquePtr			m_present_queue;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/swapchain_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SWAPCHAIN_HPP
