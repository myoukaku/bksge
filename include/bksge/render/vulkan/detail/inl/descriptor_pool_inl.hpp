/**
 *	@file	descriptor_pool_inl.hpp
 *
 *	@brief	DescriptorPool クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_POOL_INL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_POOL_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/render/vulkan/detail/descriptor_pool.hpp>
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
DescriptorPoolCreateInfo::DescriptorPoolCreateInfo(void)
{
	sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	pNext         = nullptr;
	flags         = 0;
	maxSets       = 0;
	poolSizeCount = 0;
	pPoolSizes    = nullptr;
}

BKSGE_INLINE
DescriptorPool::DescriptorPool(
	std::shared_ptr<vk::Device> const& device,
	vk::DescriptorPoolCreateInfo const& info)
	: m_descriptor_pool(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::CreateDescriptorPool(*m_device, &info, nullptr, &m_descriptor_pool);
}

BKSGE_INLINE
DescriptorPool::~DescriptorPool()
{
	vk::DestroyDescriptorPool(*m_device, m_descriptor_pool, nullptr);
}

BKSGE_INLINE
DescriptorPool::operator ::VkDescriptorPool() const
{
	return m_descriptor_pool;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_POOL_INL_HPP
