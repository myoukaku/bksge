/**
 *	@file	gl_renderer_inl.hpp
 *
 *	@brief	GlRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_RENDERER_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_RENDERER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_renderer.hpp>
#include <bksge/render/gl/gl_geometry.hpp>
#include <bksge/render/gl/gl_glsl_program.hpp>
#include <bksge/render/gl/gl_texture.hpp>
#include <bksge/render/gl/gl_frame_buffer.hpp>
#include <bksge/render/gl/wgl/wgl_context.hpp>
#include <bksge/render/gl/glx/glx_context.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/render_state.hpp>
#include <bksge/render/texture.hpp>
#include <bksge/window/window.hpp>
#include <bksge/assert.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace gl_renderer_detail
{

///////////////////////////////////////////////////////////////////////////////
//
//	非メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
inline GlContext* MakeGlContext(Window const& window)
{
#if defined(BKSGE_PLATFORM_WIN32)
	return new WglContext(window);
#else
	return new GlxContext(window);
#endif
}

}	// namespace gl_renderer_detail

///////////////////////////////////////////////////////////////////////////////
//
//	メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
GlRenderer::GlRenderer(void)
	: m_gl_context()
{
	::glGenQueries(2, m_timer_queries);
}

BKSGE_INLINE
GlRenderer::~GlRenderer()
{
	::glDeleteQueries(2, m_timer_queries);
}

BKSGE_INLINE
void GlRenderer::VSetRenderTarget(Window const& window)
{
	m_gl_geometry_map.clear();
	m_gl_shader_map.clear();
	m_gl_texture_map.clear();

	m_gl_context.reset(gl_renderer_detail::MakeGlContext(window));
}

BKSGE_INLINE
void GlRenderer::VBegin(void)
{
	::glQueryCounter(m_timer_queries[0], GL_TIMESTAMP);
}

BKSGE_INLINE
void GlRenderer::VEnd(void)
{
	::glQueryCounter(m_timer_queries[1], GL_TIMESTAMP);

	m_gl_context->SwapBuffers();

	GLuint64 time_0;
	GLuint64 time_1;
	::glGetQueryObjectui64v(m_timer_queries[0], GL_QUERY_RESULT, &time_0);
	::glGetQueryObjectui64v(m_timer_queries[1], GL_QUERY_RESULT, &time_1);
	// TODO
	//m_draw_time = NanoSeconds(static_cast<float>(time_1 - time_0));
}

BKSGE_INLINE
void GlRenderer::VClear(ClearFlag clear_flag, Color4f const& clear_color)
{
	GLbitfield mask = 0;

	// カラーバッファをクリアするときはglColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE)を呼ぶ必要がある
	if ((clear_flag & ClearFlag::kColor) != ClearFlag::kNone)
	{
		::glClearColor(clear_color.r(), clear_color.g(), clear_color.b(), clear_color.a());
		::glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		mask |= GL_COLOR_BUFFER_BIT;
	}

	// デプスバッファをクリアするときはglDepthMask(GL_TRUE)を呼ぶ必要がある
	if ((clear_flag & ClearFlag::kDepth) != ClearFlag::kNone)
	{
		::glClearDepth(0);
		::glDepthMask(GL_TRUE);
		mask |= GL_DEPTH_BUFFER_BIT;
	}

	// ステンシルバッファをクリアするときはglStencilMask(0xFFFFFFFF)を呼ぶ必要がある
	if ((clear_flag & ClearFlag::kStencil) != ClearFlag::kNone)
	{
		::glClearStencil(0);
		::glStencilMask(~0u);
		mask |= GL_STENCIL_BUFFER_BIT;
	}

	::glClear(mask);
}

BKSGE_INLINE
void GlRenderer::VRender(Geometry const& geometry, RenderState const& render_state)
{
	auto gl_shader = GetGlGLSLProgram(render_state.glsl_shader());
	BKSGE_ASSERT(gl_shader != nullptr);

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	auto gl_geometry = GetGlGeometry(geometry);
	gl_shader->Render(gl_geometry.get());
}

namespace gl_renderer_detail
{

template <typename Ret, typename Map, typename Src, typename... Args> inline
typename Map::mapped_type GetOrCreate(Map& map, Src const& src, Args... args)
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

}	// namespace gl_renderer_detail

BKSGE_INLINE
std::shared_ptr<GlGeometry>
GlRenderer::GetGlGeometry(Geometry const& geometry)
{
	return gl_renderer_detail::GetOrCreate<GlGeometry>(m_gl_geometry_map, geometry);
}

BKSGE_INLINE
std::shared_ptr<GlGLSLProgram>
GlRenderer::GetGlGLSLProgram(Shader const& shader)
{
	return gl_renderer_detail::GetOrCreate<GlGLSLProgram>(m_gl_shader_map, shader, this);
}

BKSGE_INLINE
std::shared_ptr<GlTexture>
GlRenderer::GetGlTexture(Texture const& texture)
{
	return gl_renderer_detail::GetOrCreate<GlTexture>(m_gl_texture_map, texture);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_RENDERER_INL_HPP
