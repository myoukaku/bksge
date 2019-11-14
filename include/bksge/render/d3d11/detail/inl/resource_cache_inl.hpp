/**
 *	@file	resource_cache_inl.hpp
 *
 *	@brief	ResourceCache クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_RESOURCE_CACHE_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_RESOURCE_CACHE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/resource_cache.hpp>
#include <bksge/render/d3d11/detail/hlsl_program.hpp>
#include <bksge/render/d3d11/detail/geometry.hpp>
#include <bksge/render/d3d11/detail/texture.hpp>
#include <bksge/render/d3d11/detail/sampler.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/texture.hpp>
#include <bksge/render/sampler.hpp>
#include <bksge/utility/forward.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

template <typename Ret, typename Map, typename Src, typename... Args>
inline typename Map::mapped_type
GetOrCreate(Device* device, Map& map, Src const& src, Args... args)
{
	auto const& id = src.id();
	{
		auto const& it = map.find(id);

		if (it != map.end())
		{
			return it->second;
		}
	}

	auto p = std::make_shared<Ret>(device, src, bksge::forward<Args>(args)...);
	map[id] = p;
	return p;
}

}	// namespace detail

BKSGE_INLINE
ResourceCache::ResourceCache(Device* device)
	: m_device(device)
{
}

BKSGE_INLINE
ResourceCache::~ResourceCache()
{
}

BKSGE_INLINE HlslProgramShared
ResourceCache::GetD3D11HlslProgram(bksge::Shader const& shader)
{
	return detail::GetOrCreate<HlslProgram>(
		m_device, m_hlsl_program_map, shader);
}

BKSGE_INLINE GeometryShared
ResourceCache::GetD3D11Geometry(bksge::Geometry const& geometry)
{
	return detail::GetOrCreate<Geometry>(
		m_device, m_geometry_map, geometry);
}

BKSGE_INLINE TextureShared
ResourceCache::GetD3D11Texture(bksge::Texture const& texture)
{
	return detail::GetOrCreate<Texture>(
		m_device, m_texture_map, texture);
}

BKSGE_INLINE SamplerShared
ResourceCache::GetD3D11Sampler(bksge::Sampler const& sampler)
{
	return detail::GetOrCreate<Sampler>(
		m_device, m_sampler_map, sampler);
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_RESOURCE_CACHE_INL_HPP
