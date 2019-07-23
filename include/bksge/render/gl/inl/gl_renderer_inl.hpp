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
#include <bksge/render/gl/gl_fill_mode.hpp>
#include <bksge/render/gl/gl_front_face.hpp>
#include <bksge/render/gl/gl_cull_mode.hpp>
#include <bksge/render/gl/wgl/wgl_context.hpp>
#include <bksge/render/gl/glx/glx_context.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/render_state.hpp>
#include <bksge/render/texture.hpp>
#include <bksge/window/window.hpp>
#include <bksge/assert.hpp>
#include <memory>
#include <cstdio>	// printf

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

void APIENTRY DebugCallback(GLenum /*source*/, GLenum /*type*/, GLuint /*id*/, GLenum /*severity*/, GLsizei /*length*/, const GLchar *message, const void* /*userParam*/)
{
	(void)message;
	std::printf("%s\n", message);
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

	//std::printf("GL_VENDOR : %s\n",     ::glGetString(GL_VENDOR));		// ベンダー情報の取得
	//std::printf("GL_RENDERER : %s\n",   ::glGetString(GL_RENDERER));		// レンダラー情報の取得
	//std::printf("GL_VERSION : %s\n",    ::glGetString(GL_VERSION));		// バージョン情報の取得
	//std::printf("GL_SHADING_LANGUAGE_VERSION : %s\n", ::glGetString(GL_SHADING_LANGUAGE_VERSION));	// シェーダのバージョン情報
	//std::printf("GL_EXTENSIONS : %s\n", ::glGetString(GL_EXTENSIONS));	// OpenGL拡張の取得

	::glGenQueries(2, m_timer_queries);

	::glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE); // notificationレベルの報告を無効化
	::glDebugMessageCallback(gl_renderer_detail::DebugCallback, nullptr);
//	::glEnable(GL_DEBUG_OUTPUT);
	::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
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

	Clear();
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
void GlRenderer::Clear(void)
{
	GLbitfield mask = 0;

	// カラーバッファをクリアするときは
	// glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE)を呼ぶ必要がある
	if ((m_clear_flag & ClearFlag::kColor) != ClearFlag::kNone)
	{
		::glClearColor(
			m_clear_color.r(),
			m_clear_color.g(),
			m_clear_color.b(),
			m_clear_color.a());
		::glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		mask |= GL_COLOR_BUFFER_BIT;
	}

	// デプスバッファをクリアするときは
	// glDepthMask(GL_TRUE)を呼ぶ必要がある
	if ((m_clear_flag & ClearFlag::kDepth) != ClearFlag::kNone)
	{
		::glClearDepth(0);
		::glDepthMask(GL_TRUE);
		mask |= GL_DEPTH_BUFFER_BIT;
	}

	// ステンシルバッファをクリアするときは
	// glStencilMask(0xFFFFFFFF)を呼ぶ必要がある
	if ((m_clear_flag & ClearFlag::kStencil) != ClearFlag::kNone)
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
bool GlRenderer::VRender(
	Geometry const& geometry,
	Shader const& shader,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	if (shader.type() != ShaderType::kGLSL)
	{
		return false;
	}

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

	auto glsl_program = GetGlGLSLProgram(shader);
	BKSGE_ASSERT(glsl_program != nullptr);

	auto const& rasterizer_state = render_state.rasterizer_state();
	auto const& cull_mode  = rasterizer_state.cull_mode();
	auto const& front_face = rasterizer_state.front_face();
	auto const& fill_mode  = rasterizer_state.fill_mode();

	if (cull_mode == CullMode::kNone)
	{
		::glDisable(GL_CULL_FACE);
	}
	else
	{
		::glEnable(GL_CULL_FACE);
		::glCullFace(ToGlCullMode(cull_mode));
	}

	::glFrontFace(ToGlFrontFace(front_face));
	::glPolygonMode(GL_FRONT_AND_BACK, ToGlFillMode(fill_mode));

	auto gl_geometry = GetGlGeometry(geometry);
	glsl_program->Render(gl_geometry.get(), shader_parameter_map);

	return true;
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
