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
#include <bksge/core/render/gl/detail/frame_buffer.hpp>
#include <bksge/core/render/gl/detail/geometry.hpp>
#include <bksge/core/render/gl/detail/glsl_program.hpp>
#include <bksge/core/render/gl/detail/query.hpp>
#include <bksge/core/render/gl/detail/render_buffer.hpp>
#include <bksge/core/render/gl/detail/render_pass_info.hpp>
#include <bksge/core/render/gl/detail/render_state.hpp>
#include <bksge/core/render/gl/detail/resource_pool.hpp>
#include <bksge/core/render/gl/detail/sampler.hpp>
#include <bksge/core/render/gl/detail/texture.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
//#include <bksge/core/render/gl/detail/egl/egl_context.hpp>
#include <bksge/core/render/gl/detail/wgl/wgl_context.hpp>
#include <bksge/core/render/gl/detail/glx/glx_context.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/core/render/render_pass_info.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/vertex.hpp>
#include <bksge/core/render/vertex_element.hpp>
#include <bksge/core/window/window.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/make_shared.hpp>
#include <bksge/fnd/pair.hpp>
#include <bksge/fnd/assert.hpp>
#include <cstdio>	// printf
#include <cstdint>

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
//	return new gl::EglContext(window);
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

// 問題 1.
// OpenGLはスクリーン座標が左下原点なので、オフスクリーンレンダリングすると上下反転してしまう。
// この対策のためにオフスクリーンレンダリングのときとそうでないときで
// ビューポートの設定やポリゴンの時計回り/反時計回りを変えないといけない。
// 
// 問題 2.
// OpenGLはウィンドウのサイズが変わったときに自動的にバックバッファのサイズを変更して描画するが、
// これはDirectXと挙動が違う
//
// そこで以下のように実装する
// 1. glClipControl で左上を原点にする。
// 2. デフォルトでFrameBufferを作り、必ずそこにレンダリングする。
// 3. FrameBufferのテクスチャをウィンドウに描画する。このときUV座標を上下反転させる。
//
// これで問題は解消され、他のレンダリングエンジンとも挙動を合わせられる。

struct GlRenderer::OffscreenBufferDrawer
{
private:
	static bksge::Shader const& GetShader(void)
	{
		static char const* vs_source =
			"#version 420											\n"
			"#extension GL_ARB_separate_shader_objects : enable		\n"
			"														\n"
			"layout (location = 0) in vec3 aPosition;				\n"
			"layout (location = 1) in vec2 aTexCoord;				\n"
			"														\n"
			"layout (location = 0) out vec2 vTexCoord;				\n"
			"														\n"
			"void main()											\n"
			"{														\n"
			"	gl_Position = vec4(aPosition, 1.0);					\n"
			"	vTexCoord   = aTexCoord;							\n"
			"}														\n"
		;

		static char const* fs_source =
			"#version 420											\n"
			"#extension GL_ARB_separate_shader_objects : enable		\n"
			"														\n"
			"layout (location = 0) in vec2 vTexCoord;				\n"
			"														\n"
			"layout (location = 0) out vec4 oColor;					\n"
			"														\n"
			"layout (binding = 1) uniform sampler2D uSampler2D;		\n"
			"														\n"
			"void main()											\n"
			"{														\n"
			"	oColor = texture(uSampler2D, vTexCoord);			\n"
			"}														\n"
		;

		static bksge::Shader const s_shader
		{
			{ bksge::ShaderStage::kVertex,   vs_source },
			{ bksge::ShaderStage::kFragment, fs_source },
		};

		return s_shader;
	}

	static bksge::Geometry const& GetGeometry(void)
	{
		// ・全画面を覆う三角形
		// ・ここのUVで上下反転させる
		static bksge::Vertex<bksge::VPosition, bksge::VTexCoord> const vertices[] =
		{
			{{{-1.0,  3.0, 0.0}}, {{0, 2}}},
			{{{-1.0, -1.0, 0.0}}, {{0, 0}}},
			{{{ 3.0, -1.0, 0.0}}, {{2, 0}}},
		};
		static std::uint16_t const indices[] =
		{
			0, 1, 2,
		};
		static bksge::Geometry const s_geometry(
			bksge::PrimitiveTopology::kTriangles, vertices, indices);

		return s_geometry;
	}

public:
	OffscreenBufferDrawer()
	{
		bksge::Sampler sampler;
		m_sampler = bksge::make_shared<gl::Sampler>(sampler);
	}

	void Draw(
		GlRenderer* renderer,
		gl::TextureShared const& texture,
		bksge::Extent2f const& extent)
	{
		m_render_pass_info.clear_state().SetFlag(bksge::ClearFlag::kNone);
		m_render_pass_info.viewport().SetRect({{0, 0}, extent});

		m_shader_parameter_map.SetParameter("uSampler2D", bksge::make_pair(m_sampler, texture));

//		renderer->BeginRenderPass(m_render_pass_info);
		gl::RenderPassInfo::Apply(m_render_pass_info);
		renderer->Render(
			GetGeometry(),
			GetShader(),
			m_shader_parameter_map,
			m_render_state);
//		renderer->EndRenderPass();
	}

private:
	bksge::RenderPassInfo		m_render_pass_info;
	bksge::RenderState			m_render_state;
	bksge::ShaderParameterMap	m_shader_parameter_map;
	gl::SamplerShared			m_sampler;
};

///////////////////////////////////////////////////////////////////////////////
//
//	メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
GlRenderer::GlRenderer(Window const& window)
	: m_gl_context(gl::detail::MakeGlContext(window))
	, m_resource_pool(new gl::ResourcePool())
	, m_offscreen_buffer_drawer(new OffscreenBufferDrawer())
{
	auto const width  = window.client_size().width();
	auto const height = window.client_size().height();

	//std::printf("GL_VENDOR : %s\n",     ::glGetString(GL_VENDOR));		// ベンダー情報の取得
	//std::printf("GL_RENDERER : %s\n",   ::glGetString(GL_RENDERER));		// レンダラー情報の取得
	//std::printf("GL_VERSION : %s\n",    ::glGetString(GL_VERSION));		// バージョン情報の取得
	//std::printf("GL_SHADING_LANGUAGE_VERSION : %s\n", ::glGetString(GL_SHADING_LANGUAGE_VERSION));	// シェーダのバージョン情報
	//std::printf("GL_EXTENSIONS : %s\n", ::glGetString(GL_EXTENSIONS));	// OpenGL拡張の取得

	::glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE); // notificationレベルの報告を無効化
	::glDebugMessageCallback(gl::detail::DebugCallback, nullptr);
//	::glEnable(GL_DEBUG_OUTPUT);
	::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	// クリップ座標を左上原点にするので、オフスクリーンレンダリングでも上下反転しない
	::glClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);

	// Create Offscreen FrameBuffer
	{
		m_offscreen_buffer = bksge::make_shared<gl::FrameBuffer>();
		{
			auto texture = bksge::make_shared<gl::Texture>(
				bksge::TextureFormat::kRGBA_U8_NORM,
				width,
				height,
				1,
				nullptr);
			m_offscreen_buffer->AttachColorBuffer(0, texture);
		}
		{
			auto depth_stencil = bksge::make_shared<gl::RenderBuffer>(
				bksge::TextureFormat::kDepth24_Stencil8,
				width,
				height);
			m_offscreen_buffer->AttachDepthStencilBuffer(depth_stencil);
		}
	}

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
}

BKSGE_INLINE void
GlRenderer::VEnd(void)
{
	m_offscreen_buffer_drawer->Draw(
		this,
		m_offscreen_buffer->GetColorBuffer(0),
		m_gl_context->extent());

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
	if (render_pass_info.frame_buffer() != nullptr)
	{
		m_current_frame_buffer = m_resource_pool->GetGlFrameBuffer(
			*render_pass_info.frame_buffer());
	}
	else
	{
		m_current_frame_buffer = m_offscreen_buffer;
	}

	m_current_frame_buffer->Bind();
	gl::RenderPassInfo::Apply(render_pass_info);
}

BKSGE_INLINE void
GlRenderer::VEndRenderPass(void)
{
	m_current_frame_buffer->Unbind();
}

BKSGE_INLINE bool
GlRenderer::VRender(
	Geometry const& geometry,
	Shader const& shader,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	gl::RenderState::Apply(render_state);

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
