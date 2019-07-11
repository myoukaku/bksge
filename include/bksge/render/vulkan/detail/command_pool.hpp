/**
 *	@file	command_pool.hpp
 *
 *	@brief	CommandPool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP

#include <bksge/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct CommandPoolCreateInfo : public ::VkCommandPoolCreateInfo
{
	CommandPoolCreateInfo(void);
};

class CommandPool
{
public:
	explicit CommandPool(
		std::shared_ptr<vk::Device> const& device,
		vk::CommandPoolCreateInfo const& info);

	~CommandPool();

	operator ::VkCommandPool() const;

private:
	::VkCommandPool				m_command_pool;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/command_pool_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP
