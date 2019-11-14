/**
 *	@file	resource_cache_inl.hpp
 *
 *	@brief	ResourceCache クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_RESOURCE_CACHE_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_RESOURCE_CACHE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/resource_cache.hpp>
#include <bksge/render/gl/detail/geometry.hpp>
#include <bksge/render/gl/detail/glsl_program.hpp>
#include <bksge/render/gl/detail/texture.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/texture.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

template <typename Ret, typename Map, typename Src, typename... Args>
inline typename Map::mapped_type
GetOrCreate(Map& map, Src const& src, Args... args)
{
	auto const& id = src.id();
	{
		auto const& it = map.find(id);

		if (it != map.end())
		{
			return it->second;
		}
	}

	auto p = std::make_shared<Ret>(src, args...);
	map[id] = p;
	return p;
}

}	// namespace detail

BKSGE_INLINE GeometryShared
ResourceCache::GetGlGeometry(bksge::Geometry const& geometry)
{
	return detail::GetOrCreate<gl::Geometry>(m_geometry_map, geometry);
}

BKSGE_INLINE GlslProgramShared
ResourceCache::GetGlslProgram(bksge::Shader const& shader)
{
	return detail::GetOrCreate<gl::GlslProgram>(m_shader_map, shader);
}

BKSGE_INLINE TextureShared
ResourceCache::GetGlTexture(bksge::Texture const& texture)
{
	return detail::GetOrCreate<gl::Texture>(m_texture_map, texture);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_RESOURCE_CACHE_INL_HPP
