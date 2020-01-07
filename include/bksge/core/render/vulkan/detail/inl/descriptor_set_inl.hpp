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
#include <bksge/core/render/vulkan/detail/descriptor_set_layout.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <vector>
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
	vulkan::ShaderReflection const& reflection)
	: m_device(device)
	, m_descriptor_pool(
		bksge::make_unique<vulkan::DescriptorPool>(device, reflection))
	, m_descriptor_set_layout(
		bksge::make_unique<vulkan::DescriptorSetLayout>(device, reflection))
{
	vk::DescriptorSetAllocateInfo info;
	info.descriptorPool = *m_descriptor_pool;
	info.SetSetLayouts(m_descriptor_set_layout->GetLayouts());

	m_descriptor_sets.resize(m_descriptor_set_layout->GetLayouts().size());
	vk::AllocateDescriptorSets(*m_device, &info, m_descriptor_sets.data());
}

BKSGE_INLINE
DescriptorSet::~DescriptorSet()
{
	vk::FreeDescriptorSets(
		*m_device,
		*m_descriptor_pool,
		static_cast<std::uint32_t>(m_descriptor_sets.size()),
		m_descriptor_sets.data());
}

BKSGE_INLINE std::vector<::VkDescriptorSet> const&
DescriptorSet::Get(void) const
{
	return m_descriptor_sets;
}

BKSGE_INLINE vulkan::DescriptorSetLayout const&
DescriptorSet::GetDescriptorSetLayout(void) const
{
	return *m_descriptor_set_layout;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_INL_HPP
