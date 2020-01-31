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

	vk::CreateDescriptorPool(*m_device, &info, nullptr, &m_descriptor_pool);
}

BKSGE_INLINE
DescriptorPool::~DescriptorPool()
{
	vk::DestroyDescriptorPool(*m_device, m_descriptor_pool, nullptr);
}

BKSGE_INLINE void
DescriptorPool::AllocateDescriptorSets(
	std::vector<::VkDescriptorSetLayout> const& descriptor_set_layouts,
	VkDescriptorSet*                            descriptor_sets)
{
	vk::DescriptorSetAllocateInfo info;
	info.descriptorPool = m_descriptor_pool;
	info.SetSetLayouts(descriptor_set_layouts);
	vk::AllocateDescriptorSets(*m_device, &info, descriptor_sets);
}

BKSGE_INLINE void
DescriptorPool::FreeDescriptorSets(
	std::vector<::VkDescriptorSet> const& descriptor_sets)
{
	vk::FreeDescriptorSets(
		*m_device,
		m_descriptor_pool,
		static_cast<std::uint32_t>(descriptor_sets.size()),
		descriptor_sets.data());
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_POOL_INL_HPP
