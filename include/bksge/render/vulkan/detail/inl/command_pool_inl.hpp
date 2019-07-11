/**
 *	@file	command_pool_inl.hpp
 *
 *	@brief	CommandPool クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_INL_COMMAND_POOL_INL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_INL_COMMAND_POOL_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/render/vulkan/detail/command_pool.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
CommandPoolCreateInfo::CommandPoolCreateInfo(void)
{
	sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pNext            = nullptr;
	flags            = 0;
	queueFamilyIndex = 0;
}

BKSGE_INLINE
CommandPool::CommandPool(
	std::shared_ptr<vk::Device> const& device,
	vk::CommandPoolCreateInfo const& info)
	: m_command_pool(VK_NULL_HANDLE)
	, m_device(device)
{
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

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_RENDER_VULKAN_DETAIL_INL_COMMAND_POOL_INL_HPP
