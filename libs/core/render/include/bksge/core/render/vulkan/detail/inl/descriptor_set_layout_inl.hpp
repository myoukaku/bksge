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
#include <bksge/fnd/vector.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline bksge::vector<bksge::vector<::VkDescriptorSetLayoutBinding>>
CreateDescriptorSetLayoutBindingList(vulkan::ShaderReflection const& reflection)
{
	std::size_t const max_sets = reflection.GetMaxSets() + 1;
	bksge::vector<bksge::vector<::VkDescriptorSetLayoutBinding>>
		layout_bindings_list(max_sets);

	for (auto const& uniform : reflection.GetUniforms())
	{
		auto& layout_bindings = layout_bindings_list[uniform.set];

		::VkDescriptorSetLayoutBinding layout_binding;
		layout_binding.binding            = uniform.binding;
		layout_binding.descriptorType     = uniform.descriptor_type;
		layout_binding.descriptorCount    = 1;		// TODO 配列のときは配列サイズを入れる?
		layout_binding.stageFlags         = uniform.stage_flags;
		layout_binding.pImmutableSamplers = nullptr;
		layout_bindings.push_back(layout_binding);
	}

	return layout_bindings_list;
}

}	// namespace detail

BKSGE_INLINE
DescriptorSetLayout::DescriptorSetLayout(
	vulkan::DeviceSharedPtr const& device,
	vulkan::ShaderReflection const& reflection)
	: m_device(device)
{
	auto layout_bindings_list =
		detail::CreateDescriptorSetLayoutBindingList(reflection);
	auto const max_sets = layout_bindings_list.size();

	m_descriptor_set_layout.resize(max_sets);

	for (std::size_t i = 0; i < max_sets; ++i)
	{
		vk::DescriptorSetLayoutCreateInfo info;
		info.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR;
		info.SetBindings(layout_bindings_list[i]);

		m_descriptor_set_layout[i] = m_device->CreateDescriptorSetLayout(info);
	}
}

BKSGE_INLINE
DescriptorSetLayout::~DescriptorSetLayout()
{
	for (auto&& layout : m_descriptor_set_layout)
	{
		m_device->DestroyDescriptorSetLayout(layout);
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
