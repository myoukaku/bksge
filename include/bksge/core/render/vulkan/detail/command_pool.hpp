/**
 *	@file	command_pool.hpp
 *
 *	@brief	CommandPool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP

#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CommandPool
{
public:
	explicit CommandPool(vulkan::DeviceSharedPtr const& device);

	~CommandPool();

	::VkQueue GetQueue(void) const;

	::VkCommandBuffer AllocateCommandBuffer(::VkCommandBufferLevel level);

	void FreeCommandBuffer(::VkCommandBuffer buffer);

	vulkan::DeviceSharedPtr const&	device(void) const;

private:
	// noncopyable
	CommandPool(CommandPool const&) = delete;
	CommandPool& operator=(CommandPool const&) = delete;

private:
	::VkCommandPool				m_command_pool = VK_NULL_HANDLE;
	vulkan::DeviceSharedPtr		m_device;
	bksge::uint32_t				m_queue_family_index = 0;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/command_pool_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP
