/**
 *	@file	resource_pool_inl.hpp
 *
 *	@brief	ResourcePool クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_RESOURCE_POOL_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_RESOURCE_POOL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/resource_pool.hpp>
#include <bksge/core/render/d3d11/detail/hlsl_program.hpp>
#include <bksge/core/render/d3d11/detail/geometry.hpp>
#include <bksge/core/render/d3d11/detail/texture.hpp>
#include <bksge/core/render/d3d11/detail/sampler.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/memory/make_shared.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
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
ResourcePool::ResourcePool(void)
{
}

BKSGE_INLINE
ResourcePool::~ResourcePool()
{
}

BKSGE_INLINE HlslProgramShared
ResourcePool::GetD3D11HlslProgram(Device* device, bksge::Shader const& shader)
{
	return detail::GetOrCreate<HlslProgram>(
		m_hlsl_program_map, shader.id(), device, shader);
}

BKSGE_INLINE GeometryShared
ResourcePool::GetD3D11Geometry(Device* device, bksge::Geometry const& geometry)
{
	return detail::GetOrCreate<Geometry>(
		m_geometry_map, geometry.id(), device, geometry);
}

BKSGE_INLINE TextureShared
ResourcePool::GetD3D11Texture(Device* device, bksge::Texture const& texture)
{
	return detail::GetOrCreate<Texture>(
		m_texture_map, texture.id(), device, texture);
}

BKSGE_INLINE SamplerShared
ResourcePool::GetD3D11Sampler(Device* device, bksge::Sampler const& sampler)
{
	auto const id = bksge::hash_combine(sampler);
	return detail::GetOrCreate<Sampler>(
		m_sampler_map, id, device, sampler);
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_RESOURCE_POOL_INL_HPP
