/**
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
#include <bksge/core/render/gl/detail/query.hpp>
#include <bksge/core/render/gl/detail/resource_pool.hpp>
#include <bksge/core/render/gl/detail/rasterizer_state.hpp>
#include <bksge/core/render/gl/detail/blend_state.hpp>
#include <bksge/core/render/gl/detail/depth_state.hpp>
#include <bksge/core/render/gl/detail/stencil_state.hpp>
#include <bksge/core/render/gl/detail/clear_state.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/gl/detail/wgl/wgl_context.hpp>
#include <bksge/core/render/gl/detail/glx/glx_context.hpp>
#include <bksge/core/render/blend_state.hpp>
#include <bksge/core/render/clear_state.hpp>
#include <bksge/core/render/depth_state.hpp>
#include <bksge/core/render/rasterizer_state.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/core/render/render_pass_info.hpp>
#include <bksge/core/render/scissor_state.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/stencil_state.hpp>
#include <bksge/core/render/viewport.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/assert.hpp>
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

inline void
ApplyScissorState(bksge::ScissorState const& scissor_state)
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

inline void
ApplyRasterizerState(bksge::RasterizerState const& rasterizer_state)
{
	gl::RasterizerState state(rasterizer_state);
	state.Apply();
}

inline void
ApplyBlendState(bksge::BlendState const& blend_state)
{
	gl::BlendState state(blend_state);
	state.Apply();
}

inline void
ApplyStencilState(bksge::StencilState const& stencil_state)
{
	gl::StencilState state(stencil_state);
	state.Apply();
}

inline void
ApplyDepthState(bksge::DepthState const& depth_state)
{
	gl::DepthState state(depth_state);
	state.Apply();
}

inline void
ApplyViewport(bksge::Viewport const& viewport)
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

inline void
ApplyClearState(bksge::ClearState const& clear_state)
{
	gl::ClearState state(clear_state);
	state.Apply();
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

	::glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE); // notificationレベルの報告を無効化
	::glDebugMessageCallback(gl::detail::DebugCallback, nullptr);
//	::glEnable(GL_DEBUG_OUTPUT);
	::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	m_timer_queries[0] = bksge::make_unique<gl::Query>();
	m_timer_queries[1] = bksge::make_unique<gl::Query>();
}

BKSGE_INLINE
GlRenderer::~GlRenderer()
{
}

BKSGE_INLINE void
GlRenderer::VBegin(void)
{
	m_timer_queries[0]->QueryCounter(GL_TIMESTAMP);

//	::glClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);
}

BKSGE_INLINE void
GlRenderer::VEnd(void)
{
	m_timer_queries[1]->QueryCounter(GL_TIMESTAMP);

	m_gl_context->SwapBuffers();

	::GLuint64 time_0;
	::GLuint64 time_1;
	m_timer_queries[0]->GetResult(&time_0);
	m_timer_queries[1]->GetResult(&time_1);

	m_draw_time = NanoSeconds(static_cast<float>(time_1 - time_0));
}

BKSGE_INLINE void
GlRenderer::VBeginRenderPass(RenderPassInfo const& render_pass_info)
{
	gl::detail::ApplyClearState(render_pass_info.clear_state());
	gl::detail::ApplyViewport(render_pass_info.viewport());
	gl::detail::ApplyScissorState(render_pass_info.scissor_state());
}

BKSGE_INLINE void
GlRenderer::VEndRenderPass(void)
{
}

BKSGE_INLINE bool
GlRenderer::VRender(
	Geometry const& geometry,
	Shader const& shader,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	gl::detail::ApplyRasterizerState(render_state.rasterizer_state());
	gl::detail::ApplyBlendState(render_state.blend_state());
	gl::detail::ApplyStencilState(render_state.stencil_state());
	gl::detail::ApplyDepthState(render_state.depth_state());

	auto glsl_program = m_resource_pool->GetGlslProgram(shader);
	BKSGE_ASSERT(glsl_program != nullptr);

	auto gl_geometry = m_resource_pool->GetGlGeometry(geometry);
	glsl_program->Render(m_resource_pool.get(), gl_geometry.get(), shader_parameter_map);

	return true;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_INL_GL_RENDERER_INL_HPP
