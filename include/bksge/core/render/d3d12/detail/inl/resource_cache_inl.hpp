/**
 *	@file	resource_cache_inl.hpp
 *
 *	@brief	ResourceCache クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_RESOURCE_CACHE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_RESOURCE_CACHE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/resource_cache.hpp>
#include <bksge/core/render/d3d12/detail/constant_buffer.hpp>
#include <bksge/core/render/d3d12/detail/pipeline_state.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_program.hpp>
#include <bksge/core/render/d3d12/detail/geometry.hpp>
#include <bksge/core/render/d3d12/detail/texture.hpp>
#include <bksge/core/render/d3d12/detail/sampler.hpp>
#include <bksge/core/render/d3d12/detail/command_queue.hpp>
#include <bksge/core/render/d3d12/detail/command_list.hpp>
#include <bksge/core/render/d3d12/detail/fence.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/primitive_topology.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
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

	auto p = std::make_shared<Ret>(bksge::forward<Args>(args)...);
	map[id] = p;
	return p;
}

}	// namespace detail

BKSGE_INLINE
ResourceCache::ResourceCache(Device* device)
{
	m_command_queue = bksge::make_unique<CommandQueue>(device);
	m_command_list  = bksge::make_unique<CommandList>(device, 1);
	m_fence         = bksge::make_unique<Fence>(device, 1);
	m_command_list->Close();

	m_constant_buffer = std::make_shared<ConstantBuffer>(device, 256 * 1024);
}

BKSGE_INLINE
ResourceCache::~ResourceCache()
{
}

BKSGE_INLINE ConstantBufferShared
ResourceCache::GetD3D12ConstantBuffer()
{
	return m_constant_buffer;
}

BKSGE_INLINE PipelineStateShared
ResourceCache::GetD3D12PipelineState(
	Device* device,
	bksge::Shader const& shader,
	bksge::RenderState const& render_state,
	bksge::PrimitiveTopology primitive_topology)
{
	auto const id = bksge::hash_combine(shader.id(), render_state, primitive_topology);
	return detail::GetOrCreate<PipelineState>(
		m_pipeline_state,
		id,
		device,
		*GetD3D12HlslProgram(device, shader),
		render_state,
		primitive_topology);
}

BKSGE_INLINE HlslProgramShared
ResourceCache::GetD3D12HlslProgram(Device* device, bksge::Shader const& shader)
{
	return detail::GetOrCreate<HlslProgram>(
		m_hlsl_program_map, shader.id(), device, shader);
}

BKSGE_INLINE GeometryShared
ResourceCache::GetD3D12Geometry(Device* device, bksge::Geometry const& geometry)
{
	return detail::GetOrCreate<Geometry>(
		m_geometry_map, geometry.id(), device, geometry);
}

BKSGE_INLINE TextureShared
ResourceCache::GetD3D12Texture(Device* device, bksge::Texture const& texture)
{
	return detail::GetOrCreate<Texture>(
		m_texture_map,
		texture.id(),
		device,
		m_command_list.get(),
		m_command_queue.get(),
		m_fence.get(),
		texture);
}

BKSGE_INLINE SamplerShared
ResourceCache::GetD3D12Sampler(bksge::Sampler const& sampler)
{
	auto const id = bksge::hash_combine(sampler);
	return detail::GetOrCreate<Sampler>(
		m_sampler_map,
		id,
		sampler);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_RESOURCE_CACHE_INL_HPP
