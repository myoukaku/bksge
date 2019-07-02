/**
 *	@file	command_buffer.hpp
 *
 *	@brief	CommandBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct CommandBufferInheritanceInfo : public ::VkCommandBufferInheritanceInfo
{
	CommandBufferInheritanceInfo(void)
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
};

struct CommandBufferBeginInfo : public ::VkCommandBufferBeginInfo
{
	CommandBufferBeginInfo(void)
	{
		sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		pNext            = nullptr;
		flags            = 0;
		pInheritanceInfo = nullptr;
	}
};

struct CommandBufferAllocateInfo : public ::VkCommandBufferAllocateInfo
{
	CommandBufferAllocateInfo(void)
	{
		sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		pNext              = nullptr;
		commandPool        = VK_NULL_HANDLE;
		level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferCount = 0;
	}
};

class CommandBuffer
{
public:
	explicit CommandBuffer(
		std::shared_ptr<vk::Device> const& device,
		vk::CommandBufferAllocateInfo const& info)
		: m_command_buffer(VK_NULL_HANDLE)
		, m_command_pool(info.commandPool)
		, m_device(device)
	{
		vk::AllocateCommandBuffers(*m_device, &info, &m_command_buffer);
	}

	~CommandBuffer()
	{
		vk::FreeCommandBuffers(*m_device, m_command_pool, 1, &m_command_buffer);
	}

	operator ::VkCommandBuffer() const
	{
		return m_command_buffer;
	}

	::VkCommandBuffer const* GetAddress() const
	{
		return &m_command_buffer;
	}

private:
	::VkCommandBuffer			m_command_buffer;
	::VkCommandPool				m_command_pool;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP
