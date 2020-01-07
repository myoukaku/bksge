/**
 *	@file	command_buffer_inl.hpp
 *
 *	@brief	CommandBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
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
CommandBuffer::CommandBuffer(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool)
	: m_device(device)
	, m_command_pool(command_pool)
	, m_command_buffer(VK_NULL_HANDLE)
{
	vk::CommandBufferAllocateInfo info;
	info.commandPool        = *command_pool;
	info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	info.commandBufferCount = 1;

	vk::AllocateCommandBuffers(*m_device, &info, &m_command_buffer);
}

BKSGE_INLINE
CommandBuffer::~CommandBuffer()
{
	vk::FreeCommandBuffers(*m_device, *m_command_pool, 1, &m_command_buffer);
}

BKSGE_INLINE
CommandBuffer::operator ::VkCommandBuffer() const
{
	return m_command_buffer;
}

BKSGE_INLINE
::VkCommandBuffer const* CommandBuffer::GetAddressOf(void) const
{
	return &m_command_buffer;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_BUFFER_INL_HPP
