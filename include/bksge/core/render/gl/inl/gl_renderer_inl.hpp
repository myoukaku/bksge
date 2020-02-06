﻿/**
 *	@file	gl_renderer_inl.hpp
 *
 *	@brief	GlRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_INL_GL_RENDERER_INL_HPP
#define BKSGE_CORE_RENDER_GL_INL_GL_RENDERER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/gl_renderer.hpp>
#include <bksge/core/render/gl/detail/geometry.hpp>
#include <bksge/core/render/gl/detail/glsl_program.hpp>
#include <bksge/core/render/gl/detail/texture.hpp>
#include <bksge/core/render/gl/detail/frame_buffer.hpp>
#include <bksge/core/render/gl/detail/fill_mode.hpp>
#include <bksge/core/render/gl/detail/front_face.hpp>
#include <bksge/core/render/gl/detail/cull_mode.hpp>
#include <bksge/core/render/gl/detail/blend_factor.hpp>
#include <bksge/core/render/gl/detail/blend_operation.hpp>
#include <bksge/core/render/gl/detail/comparison_function.hpp>
#include <bksge/core/render/gl/detail/bool.hpp>
#include <bksge/core/render/gl/detail/resource_pool.hpp>
#include <bksge/core/render/gl/detail/wgl/wgl_context.hpp>
#include <bksge/core/render/gl/detail/glx/glx_context.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/core/render/render_pass_info.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/core/window/window.hpp>
#include <bksge/fnd/assert.hpp>
#include <memory>
#include <cstdio>	// printf

namespace bksge
{

namespace render
{

///////////////////////////////////////////////////////////////////////////////
//
//	非メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
namespace gl
{

namespace detail
{

inline gl::Context* MakeGlContext(Window const& window)
{
#if defined(BKSGE_PLATFORM_WIN32)
	return new gl::WglContext(window);
#else
	return new gl::GlxContext(window);
#endif
}

void APIENTRY DebugCallback(
	::GLenum /*source*/,
	::GLenum /*type*/,
	::GLuint /*id*/,
	::GLenum /*severity*/,
	::GLsizei /*length*/,
	::GLchar const* message,
	void const* /*userParam*/)
{
	(void)message;
	std::printf("%s\n", message);
}

}	// namespace detail

}	// namespace gl

///////////////////////////////////////////////////////////////////////////////
//
//	メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
GlRenderer::GlRenderer(Window const& window)
	: m_gl_context(gl::detail::MakeGlContext(window))
	, m_resource_pool(new gl::ResourcePool())
{
	//std::printf("GL_VENDOR : %s\n",     ::glGetString(GL_VENDOR));		// ベンダー情報の取得
	//std::printf("GL_RENDERER : %s\n",   ::glGetString(GL_RENDERER));		// レンダラー情報の取得
	//std::printf("GL_VERSION : %s\n",    ::glGetString(GL_VERSION));		// バージョン情報の取得
	//std::printf("GL_SHADING_LANGUAGE_VERSION : %s\n", ::glGetString(GL_SHADING_LANGUAGE_VERSION));	// シェーダのバージョン情報
	//std::printf("GL_EXTENSIONS : %s\n", ::glGetString(GL_EXTENSIONS));	// OpenGL拡張の取得

	::glGenQueries(2, m_timer_queries);

	::glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE); // notificationレベルの報告を無効化
	::glDebugMessageCallback(gl::detail::DebugCallback, nullptr);
//	::glEnable(GL_DEBUG_OUTPUT);
	::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

BKSGE_INLINE
GlRenderer::~GlRenderer()
{
	::glDeleteQueries(2, m_timer_queries);
}

BKSGE_INLINE void
GlRenderer::VBegin(void)
{
	::glQueryCounter(m_timer_queries[0], GL_TIMESTAMP);

//	::glClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);
}

BKSGE_INLINE void
GlRenderer::VEnd(void)
{
	::glQueryCounter(m_timer_queries[1], GL_TIMESTAMP);

	m_gl_context->SwapBuffers();

	::GLuint64 time_0;
	::GLuint64 time_1;
	::glGetQueryObjectui64v(m_timer_queries[0], GL_QUERY_RESULT, &time_0);
	::glGetQueryObjectui64v(m_timer_queries[1], GL_QUERY_RESULT, &time_1);

	m_draw_time = NanoSeconds(static_cast<float>(time_1 - time_0));
}

BKSGE_INLINE void
GlRenderer::VBeginRenderPass(RenderPassInfo const& render_pass_info)
{
	ApplyClearState(render_pass_info.clear_state());
	ApplyViewport(render_pass_info.viewport());
	ApplyScissorState(render_pass_info.scissor_state());
}

BKSGE_INLINE void
GlRenderer::VEndRenderPass(void)
{
}

BKSGE_INLINE void
GlRenderer::ApplyViewport(Viewport const& viewport)
{
//	int const width  = 800;	// TODO
	int const height = 600;	// TODO

	::glViewport(
		static_cast<::GLint>(viewport.rect().left()),
		static_cast<::GLint>(height - viewport.rect().bottom()),
		static_cast<::GLsizei>(viewport.rect().width()),
		static_cast<::GLsizei>(viewport.rect().height()));

	::glDepthRangef(viewport.min_depth(), viewport.max_depth());
}

BKSGE_INLINE void
GlRenderer::ApplyClearState(ClearState const& clear_state)
{
	auto const clear_flag    = clear_state.flag();
	auto const clear_color   = clear_state.color();
	auto const clear_depth   = clear_state.depth();
	auto const clear_stencil = clear_state.stencil();

	::GLbitfield mask = 0;

	// カラーバッファをクリアするときは
	// glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE)を呼ぶ必要がある
	if ((clear_flag & ClearFlag::kColor) != ClearFlag::kNone)
	{
		::glClearColor(
			clear_color.r(),
			clear_color.g(),
			clear_color.b(),
			clear_color.a());
		::glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		mask |= GL_COLOR_BUFFER_BIT;
	}

	// デプスバッファをクリアするときは
	// glDepthMask(GL_TRUE)を呼ぶ必要がある
	if ((clear_flag & ClearFlag::kDepth) != ClearFlag::kNone)
	{
		::glClearDepth(clear_depth);
		::glDepthMask(GL_TRUE);
		mask |= GL_DEPTH_BUFFER_BIT;
	}

	// ステンシルバッファをクリアするときは
	// glStencilMask(0xFFFFFFFF)を呼ぶ必要がある
	if ((clear_flag & ClearFlag::kStencil) != ClearFlag::kNone)
	{
		::glClearStencil(clear_stencil);
		::glStencilMask(~0u);
		mask |= GL_STENCIL_BUFFER_BIT;
	}

	::glDisable(GL_SCISSOR_TEST);
	::glClear(mask);
}

BKSGE_INLINE bool
GlRenderer::VRender(
	Geometry const& geometry,
	Shader const& shader,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	if (shader.type() != ShaderType::kGLSL)
	{
		return false;
	}

	ApplyRasterizerState(render_state.rasterizer_state());
	ApplyBlendState(render_state.blend_state());
	ApplyDepthState(render_state.depth_state());

	auto glsl_program = m_resource_pool->GetGlslProgram(shader);
	BKSGE_ASSERT(glsl_program != nullptr);

	auto gl_geometry = m_resource_pool->GetGlGeometry(geometry);
	glsl_program->Render(m_resource_pool.get(), gl_geometry.get(), shader_parameter_map);

	return true;
}

BKSGE_INLINE void
GlRenderer::ApplyScissorState(ScissorState const& scissor_state)
{
//	int const width  = 800;	// TODO
	int const height = 600;	// TODO

	if (scissor_state.enable())
	{
		auto const& rect = scissor_state.rect();
		::glEnable(GL_SCISSOR_TEST);
		::glScissor(
			static_cast<::GLint>(rect.left()),
			static_cast<::GLint>(height - rect.bottom()),//rect.top()),
			static_cast<::GLsizei>(rect.width()),
			static_cast<::GLsizei>(rect.height()));
	}
	else
	{
		::glDisable(GL_SCISSOR_TEST);
	}
}

BKSGE_INLINE void
GlRenderer::ApplyRasterizerState(RasterizerState const& rasterizer_state)
{
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
		::glCullFace(gl::CullMode(cull_mode));
	}

	::glFrontFace(gl::FrontFace(front_face));
	::glPolygonMode(GL_FRONT_AND_BACK, gl::FillMode(fill_mode));
}

BKSGE_INLINE void
GlRenderer::ApplyBlendState(BlendState const& blend_state)
{
	if (blend_state.enable())
	{
		::glEnable(GL_BLEND);
	}
	else
	{
		::glDisable(GL_BLEND);
	}

	::glBlendFuncSeparate(
		gl::BlendFactor(blend_state.color_src_factor()),
		gl::BlendFactor(blend_state.color_dst_factor()),
		gl::BlendFactor(blend_state.alpha_src_factor()),
		gl::BlendFactor(blend_state.alpha_dst_factor()));

	::glBlendEquationSeparate(
		gl::BlendOperation(blend_state.color_operation()),
		gl::BlendOperation(blend_state.alpha_operation()));
}

BKSGE_INLINE void
GlRenderer::ApplyDepthState(DepthState const& depth_state)
{
	if (depth_state.enable())
	{
		::glEnable(GL_DEPTH_TEST);
	}
	else
	{
		::glDisable(GL_DEPTH_TEST);
	}

	::glDepthMask(gl::Bool(depth_state.write()));
	::glDepthFunc(gl::ComparisonFunction(depth_state.func()));
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_INL_GL_RENDERER_INL_HPP
