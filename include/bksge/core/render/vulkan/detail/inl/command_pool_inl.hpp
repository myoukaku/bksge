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
	vk::CommandPoolCreateInfo info;
	info.queueFamilyIndex = queue_family_index;
	info.flags            = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	vk::CreateCommandPool(*m_device, &info, nullptr, &m_command_pool);
}

BKSGE_INLINE
CommandPool::~CommandPool()
{
	vk::DestroyCommandPool(*m_device, m_command_pool, nullptr);
}

BKSGE_INLINE
CommandPool::operator ::VkCommandPool() const
{
	return m_command_pool;
}

BKSGE_INLINE ::VkQueue
CommandPool::GetQueue(void) const
{
	::VkQueue queue;
	vk::GetDeviceQueue(*m_device, m_queue_family_index, 0, &queue);
	return queue;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_POOL_INL_HPP
