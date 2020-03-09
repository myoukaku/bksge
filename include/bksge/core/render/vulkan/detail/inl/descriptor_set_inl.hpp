/**
 *	@file	descriptor_set_inl.hpp
 *
 *	@brief	DescriptorSet クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/descriptor_set.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/descriptor_pool.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
DescriptorSet::DescriptorSet(
	vulkan::DeviceSharedPtr const& device,
	vulkan::DescriptorPoolSharedPtr const& descriptor_pool,
	bksge::vector<::VkDescriptorSetLayout> const& descriptor_set_layouts)
	: m_device(device)
	, m_descriptor_pool(descriptor_pool)
{
	m_descriptor_sets.resize(descriptor_set_layouts.size());
	m_descriptor_pool->AllocateDescriptorSets(
		descriptor_set_layouts,
		m_descriptor_sets.data());
}

BKSGE_INLINE
DescriptorSet::~DescriptorSet()
{
	m_descriptor_pool->FreeDescriptorSets(m_descriptor_sets);
}

BKSGE_INLINE bksge::vector<::VkDescriptorSet> const&
DescriptorSet::Get(void) const
{
	return m_descriptor_sets;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_INL_HPP
