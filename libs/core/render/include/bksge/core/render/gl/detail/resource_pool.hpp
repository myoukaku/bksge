﻿/**
 *	@file	resource_pool.hpp
 *
 *	@brief	ResourcePool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_RESOURCE_POOL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_RESOURCE_POOL_HPP

#include <bksge/core/render/gl/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/glsl_program_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/sampler_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/render_buffer_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/frame_buffer_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/texture_fwd.hpp>
#include <bksge/core/render/fwd/render_texture_fwd.hpp>
#include <bksge/core/render/fwd/sampler_fwd.hpp>
#include <bksge/core/render/fwd/frame_buffer_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class ResourcePool
{
public:
	ResourcePool();

	~ResourcePool();

	GeometryShared		GetGlGeometry(bksge::Geometry const& geometry);
	GlslProgramShared	GetGlslProgram(bksge::Shader const& shader);
	TextureShared		GetGlTexture(bksge::Texture const& texture);
	TextureShared		GetGlTexture(bksge::RenderTexture const& texture);
	SamplerShared		GetGlSampler(bksge::Sampler const& sampler);
	RenderBufferShared	GetGlRenderBuffer(bksge::RenderTexture const& render_buffer);
	FrameBufferShared	GetGlFrameBuffer(bksge::FrameBuffer const& frame_buffer);

private:
	// noncopyable
	ResourcePool(ResourcePool const&) = delete;
	ResourcePool& operator=(ResourcePool const&) = delete;

private:
	GeometryMap     m_geometry_map;
	GlslProgramMap  m_shader_map;
	TextureMap      m_texture_map;
	SamplerMap      m_sampler_map;
	RenderBufferMap m_render_buffer_map;
	FrameBufferMap  m_frame_buffer_map;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/resource_pool_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_RESOURCE_POOL_HPP
