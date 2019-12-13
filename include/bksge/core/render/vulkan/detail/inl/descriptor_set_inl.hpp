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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <cstdint>
#include <vector>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
DescriptorSetAllocateInfo::DescriptorSetAllocateInfo(void)
{
	sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	pNext              = nullptr;
	descriptorPool     = VK_NULL_HANDLE;
	descriptorSetCount = 0;
	pSetLayouts        = nullptr;
}

BKSGE_INLINE
DescriptorSet::DescriptorSet(
	std::shared_ptr<vk::Device> const& device,
	vk::DescriptorSetAllocateInfo const& info,
	std::uint32_t num)
	: m_device(device)
{
	m_descriptor_sets.resize(num);
	vk::AllocateDescriptorSets(*m_device, &info, m_descriptor_sets.data());
}

BKSGE_INLINE
DescriptorSet::~DescriptorSet()
{
//	vk::FreeDescriptorSets(*m_device, *m_descriptor_pool, m_descriptor_sets.size(), m_descriptor_sets.data());
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DESCRIPTOR_SET_INL_HPP
