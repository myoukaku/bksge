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
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
CommandPool::CommandPool(vulkan::DeviceSharedPtr const& device)
	: m_device(device)
{
	auto const& physical_device = device->physical_device();
	m_queue_family_index = physical_device->GetGraphicsQueueFamilyIndex();
	m_command_pool =
		m_device->CreateCommandPool(
			VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
			m_queue_family_index);
}

BKSGE_INLINE
CommandPool::~CommandPool()
{
	m_device->DestroyCommandPool(m_command_pool);
}

BKSGE_INLINE ::VkQueue
CommandPool::GetQueue(void) const
{
	return m_device->GetQueue(m_queue_family_index, 0);
}

BKSGE_INLINE ::VkCommandBuffer
CommandPool::AllocateCommandBuffer(::VkCommandBufferLevel level)
{
	return m_device->AllocateCommandBuffer(m_command_pool, level);
}

BKSGE_INLINE void
CommandPool::FreeCommandBuffer(::VkCommandBuffer buffer)
{
	m_device->FreeCommandBuffer(m_command_pool, buffer);
}

BKSGE_INLINE vulkan::DeviceSharedPtr const&
CommandPool::device(void) const
{
	return m_device;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_POOL_INL_HPP
