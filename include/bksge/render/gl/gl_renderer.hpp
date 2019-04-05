/**
 *	@file	gl_renderer.hpp
 *
 *	@brief	GlRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_RENDERER_HPP
#define BKSGE_RENDER_GL_GL_RENDERER_HPP

#include <bksge/render/gl/fwd/gl_renderer_fwd.hpp>
#include <bksge/render/gl/fwd/gl_context_fwd.hpp>
#include <bksge/render/gl/fwd/gl_geometry_fwd.hpp>
#include <bksge/render/gl/fwd/gl_glsl_program_fwd.hpp>
#include <bksge/render/gl/fwd/gl_texture_fwd.hpp>
#include <bksge/render/gl/fwd/gl_frame_buffer_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/texture_fwd.hpp>
#include <bksge/render/renderer.hpp>
#include <bksge/window/fwd/window_fwd.hpp>
//#include <bksge/units/time.hpp>
#include <memory>

namespace bksge
{

namespace render
{

/**
 *	@brief	OpenGLレンダラー
 */
class GlRenderer : public Renderer
{
public:
	GlRenderer(void);

	virtual ~GlRenderer();

public:		// TODO privateにする
	GlGeometryShared    GetGlGeometry(Geometry const& geometry);
	GlGLSLProgramShared GetGlGLSLProgram(Shader const& shader);
	GlTextureShared     GetGlTexture(Texture const& texture);

private:
	virtual void VSetRenderTarget(Window const& window) override;
	virtual void VBegin(void) override;
	virtual void VEnd(void) override;
	virtual void VClear(ClearFlag clear_flag, Color4f const& clear_color) override;
	virtual void VRender(Geometry const& geometry, Shader const& shader) override;

	// TODO
	//using MilliSeconds = bksge::units::milliseconds<float>;
	//using NanoSeconds  = bksge::units::nanoseconds<float>;

private:
	std::unique_ptr<GlContext>  m_gl_context;
	GlGeometryMap               m_gl_geometry_map;
	GlGLSLProgramMap            m_gl_shader_map;
	GlTextureMap                m_gl_texture_map;
	GLuint                      m_timer_queries[2];  ///< 描画時間を図るためのクエリ
//	MilliSeconds                m_draw_time;		 ///< 描画時間
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_RENDERER_HPP
