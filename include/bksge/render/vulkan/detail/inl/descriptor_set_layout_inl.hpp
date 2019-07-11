/**
 *	@file	descriptor_set_layout_inl.hpp
 *
 *	@brief	DescriptorSetLayout クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_LAYOUT_INL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_LAYOUT_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/render/vulkan/detail/descriptor_set_layout.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
DescriptorSetLayoutBinding::DescriptorSetLayoutBinding(void)
{
	binding            = 0;
	descriptorType     = VK_DESCRIPTOR_TYPE_SAMPLER;
	descriptorCount    = 0;
	stageFlags         = 0;
	pImmutableSamplers = nullptr;
}

BKSGE_INLINE
DescriptorSetLayoutCreateInfo::DescriptorSetLayoutCreateInfo(void)
{
	sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	pNext        = nullptr;
	flags        = 0;
	bindingCount = 0;
	pBindings    = nullptr;
}

BKSGE_INLINE
DescriptorSetLayout::DescriptorSetLayout(
	std::shared_ptr<vk::Device> const& device,
	vk::DescriptorSetLayoutCreateInfo const& info,
	std::uint32_t num)
	: m_device(device)
{
	m_descriptor_set_layout.resize(num);
	vk::CreateDescriptorSetLayout(*m_device, &info, nullptr, m_descriptor_set_layout.data());
}

BKSGE_INLINE
DescriptorSetLayout::~DescriptorSetLayout()
{
	for (auto&& layout : m_descriptor_set_layout)
	{
		vk::DestroyDescriptorSetLayout(*m_device, layout, nullptr);
	}
}

BKSGE_INLINE ::VkDescriptorSetLayout const*
DescriptorSetLayout::get(void) const
{
	return m_descriptor_set_layout.data();
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_LAYOUT_INL_HPP
