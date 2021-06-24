/**
 *	@file	resource_pool_inl.hpp
 *
 *	@brief	ResourcePool クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_RESOURCE_POOL_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_RESOURCE_POOL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/resource_pool.hpp>
#include <bksge/core/render/gl/detail/geometry.hpp>
#include <bksge/core/render/gl/detail/glsl_program.hpp>
#include <bksge/core/render/gl/detail/texture.hpp>
#include <bksge/core/render/gl/detail/sampler.hpp>
#include <bksge/core/render/gl/detail/render_buffer.hpp>
#include <bksge/core/render/gl/detail/frame_buffer.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/core/render/frame_buffer.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/memory/make_shared.hpp>

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

	auto p = bksge::make_shared<Ret>(bksge::forward<Args>(args)...);
	map[id] = p;
	return p;
}

}	// namespace detail

BKSGE_INLINE
ResourcePool::ResourcePool()
{
}

BKSGE_INLINE
ResourcePool::~ResourcePool()
{
}

BKSGE_INLINE GeometryShared
ResourcePool::GetGlGeometry(bksge::Geometry const& geometry)
{
	return detail::GetOrCreate<gl::Geometry>(
		m_geometry_map, geometry.id(), geometry);
}

BKSGE_INLINE GlslProgramShared
ResourcePool::GetGlslProgram(bksge::Shader const& shader)
{
	return detail::GetOrCreate<gl::GlslProgram>(
		m_shader_map, shader.id(), shader);
}

BKSGE_INLINE TextureShared
ResourcePool::GetGlTexture(bksge::Texture const& texture)
{
	return detail::GetOrCreate<gl::Texture>(
		m_texture_map, texture.id(), texture);
}

BKSGE_INLINE TextureShared
ResourcePool::GetGlTexture(bksge::RenderTexture const& texture)
{
	return detail::GetOrCreate<gl::Texture>(
		m_texture_map, texture.id(), texture);
}

BKSGE_INLINE SamplerShared
ResourcePool::GetGlSampler(bksge::Sampler const& sampler)
{
	auto const id = bksge::hash_combine(sampler);
	return detail::GetOrCreate<gl::Sampler>(
		m_sampler_map, id, sampler);
}

BKSGE_INLINE RenderBufferShared
ResourcePool::GetGlRenderBuffer(bksge::RenderTexture const& render_buffer)
{
	return detail::GetOrCreate<gl::RenderBuffer>(
		m_render_buffer_map, render_buffer.id(), render_buffer);
}

BKSGE_INLINE FrameBufferShared
ResourcePool::GetGlFrameBuffer(bksge::FrameBuffer const& frame_buffer)
{
	return detail::GetOrCreate<gl::FrameBuffer>(
		m_frame_buffer_map, frame_buffer.id(), frame_buffer, this);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_RESOURCE_POOL_INL_HPP
