/**
 *	@file	command_buffer.hpp
 *
 *	@brief	CommandBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP

#include <bksge/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct CommandBufferInheritanceInfo : public ::VkCommandBufferInheritanceInfo
{
	CommandBufferInheritanceInfo(void);
};

struct CommandBufferBeginInfo : public ::VkCommandBufferBeginInfo
{
	CommandBufferBeginInfo(void);
};

struct CommandBufferAllocateInfo : public ::VkCommandBufferAllocateInfo
{
	CommandBufferAllocateInfo(void);
};

class CommandBuffer
{
public:
	explicit CommandBuffer(
		std::shared_ptr<vk::Device> const& device,
		vk::CommandBufferAllocateInfo const& info);

	~CommandBuffer();

	operator ::VkCommandBuffer() const;

	::VkCommandBuffer const* GetAddress() const;

private:
	::VkCommandBuffer			m_command_buffer;
	::VkCommandPool				m_command_pool;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/command_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP
