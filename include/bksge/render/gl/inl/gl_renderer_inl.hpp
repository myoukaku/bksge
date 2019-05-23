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
#include <bksge/render/shader_map.hpp>
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
//	int const width  = 800;	// TODO
	int const height = 600;	// TODO

	::glQueryCounter(m_timer_queries[0], GL_TIMESTAMP);

//	::glClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);

	if (m_viewport)
	{
		::glViewport(
			static_cast<GLint>(m_viewport->left()),
			static_cast<GLint>(height - m_viewport->bottom()),//m_viewport->top()),
			static_cast<GLsizei>(m_viewport->width()),
			static_cast<GLsizei>(m_viewport->height()));
	}
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

	::glDisable(GL_SCISSOR_TEST);
	::glClear(mask);
	::glEnable(GL_SCISSOR_TEST);
}

BKSGE_INLINE
void GlRenderer::VRender(
	Geometry const& geometry,
	ShaderMap const& shader_map,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
//	int const width  = 800;	// TODO
	int const height = 600;	// TODO

	{
		auto const& scissor = render_state.scissor_state();
		if (scissor.enable())
		{
			auto const& rect = scissor.rect();
			::glEnable(GL_SCISSOR_TEST);
			::glScissor(
				static_cast<GLint>(rect.left()),
				static_cast<GLint>(height - rect.bottom()),//rect.top()),
				static_cast<GLsizei>(rect.width()),
				static_cast<GLsizei>(rect.height()));
		}
		else
		{
			::glDisable(GL_SCISSOR_TEST);
		}
	}

	auto* shader = shader_map.GetShader(ShaderType::kGLSL);
	if (shader == nullptr)
	{
		return;
	}

	auto glsl_program = GetGlGLSLProgram(*shader);
	BKSGE_ASSERT(glsl_program != nullptr);

	auto const& rasterizer_state = render_state.rasterizer_state();
	auto const& cull_mode = rasterizer_state.cull_mode();
	auto const& front_face = rasterizer_state.front_face();

	if (cull_mode == CullMode::kNone)
	{
		glDisable(GL_CULL_FACE);
	}
	else
	{
		glEnable(GL_CULL_FACE);
		glCullFace(cull_mode == CullMode::kBack ? GL_BACK : GL_FRONT);
	}

	glFrontFace(front_face == FrontFace::kClockwise ? GL_CW : GL_CCW);

	auto gl_geometry = GetGlGeometry(geometry);
	glsl_program->Render(gl_geometry.get(), shader_parameter_map);
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
	return gl_renderer_detail::GetOrCreate<GlGLSLProgram>(m_gl_shader_map, shader);
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
