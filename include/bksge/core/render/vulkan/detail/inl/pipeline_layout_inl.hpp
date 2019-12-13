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
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
PipelineLayoutCreateInfo::PipelineLayoutCreateInfo(void)
{
	sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pNext                  = nullptr;
	flags                  = 0;
	setLayoutCount         = 0;
	pSetLayouts            = nullptr;
	pushConstantRangeCount = 0;
	pPushConstantRanges    = nullptr;
}

BKSGE_INLINE
PipelineLayout::PipelineLayout(
	std::shared_ptr<vk::Device> const& device,
	vk::PipelineLayoutCreateInfo const& info)
	: m_pipeline_layout(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::CreatePipelineLayout(*m_device, &info, nullptr, &m_pipeline_layout);
}

BKSGE_INLINE
PipelineLayout::~PipelineLayout()
{
	vk::DestroyPipelineLayout(*m_device, m_pipeline_layout, nullptr);
}

BKSGE_INLINE
PipelineLayout::operator ::VkPipelineLayout() const
{
	return m_pipeline_layout;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_LAYOUT_INL_HPP
