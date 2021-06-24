/**
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
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/vector.hpp>

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
	: m_descriptor_pool(VK_NULL_HANDLE)
	, m_device(device)
{
	bksge::vector<::VkDescriptorPoolSize> type_count;

	::VkDescriptorType const descriptor_type_tbl[] =
	{
		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		VK_DESCRIPTOR_TYPE_SAMPLER,
		VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
	};

	for (auto const& descriptor_type : descriptor_type_tbl)
	{
		::VkDescriptorPoolSize pool_size;
		pool_size.type = descriptor_type;
		pool_size.descriptorCount = reflection.GetUniformCount(descriptor_type);
		type_count.push_back(pool_size);
	}

	vk::DescriptorPoolCreateInfo info;
	info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;	// vkFreeDescriptorSets() を呼び出すときはこれを指定する
	info.maxSets = reflection.GetMaxSets() + 1;
	info.SetPoolSizes(type_count);

	m_descriptor_pool = m_device->CreateDescriptorPool(info);
}

BKSGE_INLINE
DescriptorPool::~DescriptorPool()
{
	m_device->DestroyDescriptorPool(m_descriptor_pool);
}

BKSGE_INLINE bksge::vector<::VkDescriptorSet>
DescriptorPool::AllocateDescriptorSets(
	bksge::vector<::VkDescriptorSetLayout> const& descriptor_set_layouts)
{
	vk::DescriptorSetAllocateInfo info;
	info.descriptorPool = m_descriptor_pool;
	info.SetSetLayouts(descriptor_set_layouts);

	return m_device->AllocateDescriptorSets(info);
}

BKSGE_INLINE void
DescriptorPool::FreeDescriptorSets(
	bksge::vector<::VkDescriptorSet> const& descriptor_sets)
{
	m_device->FreeDescriptorSets(m_descriptor_pool, descriptor_sets);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_POOL_INL_HPP
