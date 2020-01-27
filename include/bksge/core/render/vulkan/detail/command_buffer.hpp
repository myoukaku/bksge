/**
 *	@file	command_buffer.hpp
 *
 *	@brief	CommandBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CommandBuffer
{
public:
	explicit CommandBuffer(
		vulkan::DeviceSharedPtr const& device,
		vulkan::CommandPoolSharedPtr const& command_pool);

	~CommandBuffer();

	operator ::VkCommandBuffer() const;

	::VkCommandBuffer const* GetAddressOf(void) const;

private:
	vulkan::DeviceSharedPtr			m_device;
	vulkan::CommandPoolSharedPtr	m_command_pool;
	::VkCommandBuffer				m_command_buffer;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/command_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP
