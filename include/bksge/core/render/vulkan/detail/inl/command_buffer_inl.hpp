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
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
CommandBufferInheritanceInfo::CommandBufferInheritanceInfo(void)
{
	sType                = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	pNext                = nullptr;
	renderPass           = VK_NULL_HANDLE;
	subpass              = 0;
	framebuffer          = VK_NULL_HANDLE;
	occlusionQueryEnable = VK_FALSE;
	queryFlags           = 0;
	pipelineStatistics   = 0;
}

BKSGE_INLINE
CommandBufferBeginInfo::CommandBufferBeginInfo(void)
{
	sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	pNext            = nullptr;
	flags            = 0;
	pInheritanceInfo = nullptr;
}

BKSGE_INLINE
CommandBufferAllocateInfo::CommandBufferAllocateInfo(void)
{
	sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	pNext              = nullptr;
	commandPool        = VK_NULL_HANDLE;
	level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferCount = 0;
}

BKSGE_INLINE
CommandBuffer::CommandBuffer(
	std::shared_ptr<vk::Device> const& device,
	vk::CommandBufferAllocateInfo const& info)
	: m_command_buffer(VK_NULL_HANDLE)
	, m_command_pool(info.commandPool)
	, m_device(device)
{
	vk::AllocateCommandBuffers(*m_device, &info, &m_command_buffer);
}

BKSGE_INLINE
CommandBuffer::~CommandBuffer()
{
	vk::FreeCommandBuffers(*m_device, m_command_pool, 1, &m_command_buffer);
}

BKSGE_INLINE
CommandBuffer::operator ::VkCommandBuffer() const
{
	return m_command_buffer;
}

BKSGE_INLINE
::VkCommandBuffer const* CommandBuffer::GetAddress() const
{
	return &m_command_buffer;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_BUFFER_INL_HPP
