/**
 *	@file	graphics_pipeline.hpp
 *
 *	@brief	GraphicsPipeline クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_GRAPHICS_PIPELINE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_GRAPHICS_PIPELINE_HPP

#include <bksge/core/render/vulkan/detail/fwd/graphics_pipeline_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/render_pass_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/shader_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/pipeline_cache_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/pipeline_layout_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class GraphicsPipeline
{
public:
	explicit GraphicsPipeline(
		vulkan::DeviceSharedPtr const& device,
		::VkSampleCountFlagBits num_samples,
		bksge::Geometry const& geometry,
		vulkan::RenderPass const& render_pass,
		vulkan::Shader const& shader,
		bksge::RenderState const& render_state);

	~GraphicsPipeline();

	operator ::VkPipeline() const;

	::VkPipelineLayout GetLayout(void) const;

private:
	vulkan::DeviceSharedPtr			m_device;
	vulkan::PipelineCacheUniquePtr	m_pipeline_cache;
	vulkan::PipelineLayoutUniquePtr	m_pipeline_layout;
	::VkPipeline					m_pipeline;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/graphics_pipeline_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_GRAPHICS_PIPELINE_HPP
