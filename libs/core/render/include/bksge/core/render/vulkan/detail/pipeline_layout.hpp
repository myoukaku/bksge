﻿/**
 *	@file	pipeline_layout.hpp
 *
 *	@brief	PipelineLayout クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_LAYOUT_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_LAYOUT_HPP

#include <bksge/core/render/vulkan/detail/fwd/pipeline_layout_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/descriptor_set_layout_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class PipelineLayout
{
public:
	explicit PipelineLayout(
		vulkan::DeviceSharedPtr const& device,
		vulkan::DescriptorSetLayout const& descriptor_set_layout);

	~PipelineLayout();

public:
	operator ::VkPipelineLayout() const;

private:
	// noncopyable
	PipelineLayout(PipelineLayout const&) = delete;
	PipelineLayout& operator=(PipelineLayout const&) = delete;

private:
	::VkPipelineLayout			m_pipeline_layout = VK_NULL_HANDLE;
	vulkan::DeviceSharedPtr		m_device;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/pipeline_layout_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_LAYOUT_HPP
