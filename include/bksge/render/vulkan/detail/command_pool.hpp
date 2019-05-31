/**
 *	@file	command_pool.hpp
 *
 *	@brief	CommandPool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct CommandPoolCreateInfo : public ::VkCommandPoolCreateInfo
{
	CommandPoolCreateInfo(void)
	{
		sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pNext            = nullptr;
		flags            = 0;
		queueFamilyIndex = 0;
	}
};

class CommandPool
{
public:
	explicit CommandPool(
		std::shared_ptr<vk::Device> const& device,
		vk::CommandPoolCreateInfo const& info)
		: m_command_pool(VK_NULL_HANDLE)
		, m_device(device)
	{
		vk::CreateCommandPool(*m_device, &info, nullptr, &m_command_pool);
	}

	~CommandPool()
	{
		vk::DestroyCommandPool(*m_device, m_command_pool, nullptr);
	}

	operator ::VkCommandPool() const
	{
		return m_command_pool;
	}

private:
	::VkCommandPool				m_command_pool;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_COMMAND_POOL_HPP
