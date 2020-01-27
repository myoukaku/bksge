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
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CommandPool
{
public:
	explicit CommandPool(
		vulkan::DeviceSharedPtr const& device,
		std::uint32_t queue_family_index);

	~CommandPool();

	operator ::VkCommandPool() const;

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkCommandPool				m_command_pool;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/command_pool_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP
