/**
 *	@file	pipeline_layout_inl.hpp
 *
 *	@brief	PipelineLayout クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_LAYOUT_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_LAYOUT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/pipeline_layout.hpp>
#include <bksge/core/render/vulkan/detail/descriptor_set_layout.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
PipelineLayout::PipelineLayout(
	vulkan::DeviceSharedPtr const& device,
	vulkan::DescriptorSetLayout const& descriptor_set_layout)
	: m_pipeline_layout(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::PipelineLayoutCreateInfo info;
	info.SetSetLayouts(descriptor_set_layout.GetLayouts());
	info.SetPushConstantRanges(nullptr);

	m_pipeline_layout = m_device->CreatePipelineLayout(info);
}

BKSGE_INLINE
PipelineLayout::~PipelineLayout()
{
	m_device->DestroyPipelineLayout(m_pipeline_layout);
}

BKSGE_INLINE
PipelineLayout::operator ::VkPipelineLayout() const
{
	return m_pipeline_layout;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_LAYOUT_INL_HPP
