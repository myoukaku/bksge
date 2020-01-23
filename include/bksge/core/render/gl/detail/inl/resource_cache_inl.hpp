﻿/**
 *	@file	resource_cache_inl.hpp
 *
 *	@brief	ResourceCache クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_RESOURCE_CACHE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_RESOURCE_CACHE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/resource_cache.hpp>
#include <bksge/core/render/gl/detail/geometry.hpp>
#include <bksge/core/render/gl/detail/glsl_program.hpp>
#include <bksge/core/render/gl/detail/texture.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/texture.hpp>

namespace bksge
{

namespace render
{

namespace gl
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

BKSGE_INLINE GeometryShared
ResourceCache::GetGlGeometry(bksge::Geometry const& geometry)
{
	return detail::GetOrCreate<gl::Geometry>(
		m_geometry_map, geometry.id(), geometry);
}

BKSGE_INLINE GlslProgramShared
ResourceCache::GetGlslProgram(bksge::Shader const& shader)
{
	return detail::GetOrCreate<gl::GlslProgram>(
		m_shader_map, shader.id(), shader);
}

BKSGE_INLINE TextureShared
ResourceCache::GetGlTexture(bksge::Texture const& texture)
{
	return detail::GetOrCreate<gl::Texture>(
		m_texture_map, texture.id(), texture);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_RESOURCE_CACHE_INL_HPP
