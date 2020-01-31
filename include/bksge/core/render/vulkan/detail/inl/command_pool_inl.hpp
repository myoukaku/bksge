/**
 *	@file	command_pool_inl.hpp
 *
 *	@brief	CommandPool クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_POOL_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_POOL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
CommandPool::CommandPool(
	vulkan::DeviceSharedPtr const& device,
	std::uint32_t queue_family_index)
	: m_device(device)
	, m_queue_family_index(queue_family_index)
{
	m_command_pool =
		m_device->CreateCommandPool(
			VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
			queue_family_index);
}

BKSGE_INLINE
CommandPool::~CommandPool()
{
	m_device->DestroyCommandPool(m_command_pool);
}

BKSGE_INLINE ::VkQueue
CommandPool::GetQueue(void) const
{
	::VkQueue queue;
	vk::GetDeviceQueue(*m_device, m_queue_family_index, 0, &queue);
	return queue;
}

BKSGE_INLINE ::VkCommandBuffer
CommandPool::AllocateCommandBuffer(::VkCommandBufferLevel level)
{
	vk::CommandBufferAllocateInfo info;
	info.commandPool        = m_command_pool;
	info.level              = level;
	info.commandBufferCount = 1;

	::VkCommandBuffer buffer;
	vk::AllocateCommandBuffers(*m_device, &info, &buffer);
	return buffer;
}

BKSGE_INLINE void
CommandPool::FreeCommandBuffer(::VkCommandBuffer buffer)
{
	vk::FreeCommandBuffers(*m_device, m_command_pool, 1, &buffer);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_POOL_INL_HPP
