/**
 *	@file	queue_inl.hpp
 *
 *	@brief	Queue の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_QUEUE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_QUEUE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/queue.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Queue::Queue(
	vulkan::DeviceSharedPtr const& device,
	bksge::uint32_t queue_family_index,
	bksge::uint32_t queue_index)
	: Queue(device->GetQueue(queue_family_index, queue_index))
{}

BKSGE_INLINE
Queue::Queue(::VkQueue queue)
	: m_queue(queue)
{}

BKSGE_INLINE ::VkResult
Queue::Submit(
	vk::SubmitInfo const& submit_info,
	::VkFence fence)
{
	return vk::QueueSubmit(m_queue, 1, &submit_info, fence);
}

BKSGE_INLINE ::VkResult
Queue::Present(vk::PresentInfoKHR const& present_info)
{
	return vk::QueuePresentKHR(m_queue, &present_info);
}

BKSGE_INLINE ::VkResult
Queue::WaitIdle(void)
{
	return vk::QueueWaitIdle(m_queue);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_QUEUE_INL_HPP
