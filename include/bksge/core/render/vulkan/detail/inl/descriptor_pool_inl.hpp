﻿/**
 *	@file	descriptor_pool_inl.hpp
 *
 *	@brief	DescriptorPool クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_POOL_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_POOL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/descriptor_pool.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
DescriptorPool::DescriptorPool(
	vulkan::DeviceSharedPtr const& device,
	vulkan::ShaderReflection const& reflection)
	: m_device(device)
	, m_descriptor_pool(VK_NULL_HANDLE)
{
	std::vector<::VkDescriptorPoolSize> type_count;

	// TODO ハードコーディングを取り除く
	{
		::VkDescriptorPoolSize pool_size;
		pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		pool_size.descriptorCount = (uint32_t)reflection.GetUniformBuffers().size();
		type_count.push_back(pool_size);
	}
	{
		::VkDescriptorPoolSize pool_size;
		pool_size.type = VK_DESCRIPTOR_TYPE_SAMPLER;
		pool_size.descriptorCount = 100;
		type_count.push_back(pool_size);
	}
	{
		::VkDescriptorPoolSize pool_size;
		pool_size.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		pool_size.descriptorCount = 100;
		type_count.push_back(pool_size);
	}
	{
		::VkDescriptorPoolSize pool_size;
		pool_size.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
		pool_size.descriptorCount = 100;
		type_count.push_back(pool_size);
	}

	vk::DescriptorPoolCreateInfo info;
	info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;	// vkFreeDescriptorSets() を呼び出すときはこれを指定する
	info.maxSets = reflection.GetMaxSets() + 1;
	info.SetPoolSizes(type_count);

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

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_POOL_INL_HPP
