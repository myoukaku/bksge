/**
 *	@file	resource_pool_inl.hpp
 *
 *	@brief	ResourcePool クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RESOURCE_POOL_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RESOURCE_POOL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/resource_pool.hpp>
#include <bksge/core/render/vulkan/detail/shader.hpp>
#include <bksge/core/render/vulkan/detail/geometry.hpp>
#include <bksge/core/render/vulkan/detail/graphics_pipeline.hpp>
#include <bksge/core/render/vulkan/detail/sampler.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/render_pass.hpp>
#include <bksge/core/render/vulkan/detail/render_state.hpp>
#include <bksge/core/render/vulkan/detail/pipeline_input_assembly_state.hpp>
#include <bksge/core/render/vulkan/detail/pipeline_vertex_input_state.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/memory/make_shared.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

template <typename Ret, typename Map, typename Id, typename... Args>
inline typename Map::mapped_type
GetOrCreate(Map& map, Id const& id, Args&&... args)
{
	{
		auto const& it = map.find(id);

		if (it != map.end())
		{
			return it->second;
		}
	}

	auto p = bksge::make_shared<Ret>(bksge::forward<Args>(args)...);
	map[id] = p;
	return p;
}

}	// namespace detail

BKSGE_INLINE
ResourcePool::ResourcePool(vulkan::DeviceSharedPtr const& device)
	: m_device(device)
{}

BKSGE_INLINE
ResourcePool::~ResourcePool()
{}

BKSGE_INLINE vulkan::ShaderSharedPtr
ResourcePool::GetShader(
	bksge::Shader const& shader)
{
	return detail::GetOrCreate<vulkan::Shader>(
		m_shader_map, shader.id(), m_device, shader);
}

BKSGE_INLINE vulkan::GeometrySharedPtr
ResourcePool::GetGeometry(
	bksge::Geometry const& geometry)
{
	return detail::GetOrCreate<vulkan::Geometry>(
		m_geometry_map, geometry.id(), m_device, geometry);
}

BKSGE_INLINE vulkan::GraphicsPipelineSharedPtr
ResourcePool::GetGraphicsPipeline(
	vulkan::RenderPass const& render_pass,
	bksge::Geometry const& geometry,
	bksge::Shader const& shader,
	bksge::RenderState const& render_state)
{
	auto const id = bksge::hash_combine(
		static_cast<std::uint32_t>(render_pass.samples()),
		geometry.id(),
		// TODO
		//geometry.primitive_topology(),
		//geometry.vertex_layout(),
		shader.id(),
		render_state);

	return detail::GetOrCreate<vulkan::GraphicsPipeline>(
		m_graphics_pipeline_map,
		id,
		m_device,
		render_pass,
		vulkan::PipelineInputAssemblyState(geometry.primitive_topology()),
		vulkan::PipelineVertexInputState(geometry.vertex_layout()),
		*(this->GetShader(shader)),
		vulkan::RenderState(render_state));
}

BKSGE_INLINE vulkan::SamplerSharedPtr
ResourcePool::GetSampler(
	bksge::Sampler const& sampler)
{
	auto const id = bksge::hash_combine(sampler);
	return detail::GetOrCreate<vulkan::Sampler>(
		m_sampler_map, id, m_device, sampler);
}

BKSGE_INLINE vulkan::ImageSharedPtr
ResourcePool::GetImage(
	bksge::Texture const& texture,
	vulkan::CommandPoolSharedPtr const& command_pool)
{
	return detail::GetOrCreate<vulkan::Image>(
		m_image_map, texture.id(), m_device, texture, command_pool);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RESOURCE_POOL_INL_HPP
