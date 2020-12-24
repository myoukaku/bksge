/**
 *	@file	descriptor_set_layout_inl.hpp
 *
 *	@brief	DescriptorSetLayout クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_LAYOUT_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_LAYOUT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/descriptor_set_layout.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline void CreateDescriptorSetLayoutBindingList(
	bksge::vector<ShaderReflectionUniform> const& reflection_list,
	bksge::vector<bksge::vector<::VkDescriptorSetLayoutBinding>>* layout_bindings_list)
{
	for (auto const& reflection : reflection_list)
	{
		auto& layout_bindings = layout_bindings_list->at(reflection.set);

		::VkDescriptorSetLayoutBinding layout_binding;
		layout_binding.binding            = reflection.binding;
		layout_binding.descriptorType     = reflection.descriptor_type;
		layout_binding.descriptorCount    = 1;		// TODO 配列のときは配列サイズを入れる?
		layout_binding.stageFlags         = reflection.stage_flags;
		layout_binding.pImmutableSamplers = nullptr;
		layout_bindings.push_back(layout_binding);
	}
}

}	// namespace detail

BKSGE_INLINE
DescriptorSetLayout::DescriptorSetLayout(
	vulkan::DeviceSharedPtr const& device,
	vulkan::ShaderReflection const& reflection)
	: m_device(device)
{
	bksge::size_t const descriptor_set_count = reflection.GetMaxSets() + 1;

	bksge::vector<bksge::vector<::VkDescriptorSetLayoutBinding>>
		descriptor_set_layout_bindings_list(descriptor_set_count);

	detail::CreateDescriptorSetLayoutBindingList(
		reflection.GetUniforms(),
		&descriptor_set_layout_bindings_list);

	bksge::vector<vk::DescriptorSetLayoutCreateInfo> info;
	info.resize(descriptor_set_count);

	for (bksge::size_t i = 0; i < descriptor_set_count; ++i)
	{
		info[i].flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR;
		info[i].SetBindings(descriptor_set_layout_bindings_list[i]);
	}

	m_descriptor_set_layout.resize(descriptor_set_count);

	for (bksge::size_t i = 0; i < descriptor_set_count; ++i)
	{
		vk::CreateDescriptorSetLayout(
			*m_device, &info[i], nullptr, &m_descriptor_set_layout[i]);
	}
}

BKSGE_INLINE
DescriptorSetLayout::~DescriptorSetLayout()
{
	for (auto&& layout : m_descriptor_set_layout)
	{
		vk::DestroyDescriptorSetLayout(*m_device, layout, nullptr);
	}
}

BKSGE_INLINE bksge::vector<::VkDescriptorSetLayout> const&
DescriptorSetLayout::GetLayouts(void) const
{
	return m_descriptor_set_layout;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_LAYOUT_INL_HPP
