/**
 *	@file	queue.hpp
 *
 *	@brief	Queue クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_QUEUE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_QUEUE_HPP

#include <bksge/core/render/vulkan/detail/fwd/queue_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class Queue
{
public:
	explicit Queue(
		vulkan::DeviceSharedPtr const& device,
		bksge::uint32_t queue_family_index,
		bksge::uint32_t queue_index);

	explicit Queue(::VkQueue queue);

	::VkResult Submit(
		vk::SubmitInfo const& submit_info,
		::VkFence fence);

	::VkResult Present(vk::PresentInfoKHR const& present_info);

	::VkResult WaitIdle(void);

private:
	::VkQueue	m_queue;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/queue_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_QUEUE_HPP
