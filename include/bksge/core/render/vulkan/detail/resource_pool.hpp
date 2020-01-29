/**
 *	@file	resource_pool.hpp
 *
 *	@brief	ResourcePool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_RESOURCE_POOL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_RESOURCE_POOL_HPP

#include <bksge/core/render/vulkan/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/shader_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/graphics_pipeline_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/render_pass_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class ResourcePool
{
public:
	explicit ResourcePool(void);

	~ResourcePool();

	vulkan::ShaderSharedPtr GetShader(
		vulkan::DeviceSharedPtr const& device,
		bksge::Shader const& shader);

	vulkan::GeometrySharedPtr GetGeometry(
		vulkan::DeviceSharedPtr const& device,
		bksge::Geometry const& geometry);

	vulkan::GraphicsPipelineSharedPtr GetGraphicsPipeline(
		vulkan::DeviceSharedPtr const& device,
		::VkSampleCountFlagBits num_samples,
		bksge::Geometry const& geometry,
		bksge::Shader const& shader,
		bksge::RenderState const& render_state,
		vulkan::RenderPass const& render_pass);

private:
	vulkan::ShaderSharedPtrMap				m_shader_map;
	vulkan::GeometrySharedPtrMap			m_geometry_map;
	vulkan::GraphicsPipelineSharedPtrMap	m_graphics_pipeline_map;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/resource_pool_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_RESOURCE_POOL_HPP
