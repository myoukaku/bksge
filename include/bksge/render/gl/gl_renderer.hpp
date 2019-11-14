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
#include <bksge/render/gl/detail/fwd/context_fwd.hpp>
#include <bksge/render/gl/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/render/fwd/render_state_fwd.hpp>
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

private:
	void Clear(void);

	void VSetRenderTarget(Window const& window) override;
	void VBegin(void) override;
	void VEnd(void) override;
	bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;

	// TODO
	//using MilliSeconds = bksge::units::milliseconds<float>;
	//using NanoSeconds  = bksge::units::nanoseconds<float>;

private:
	std::unique_ptr<gl::Context>		m_gl_context;
	std::unique_ptr<gl::ResourceCache>	m_resource_cache;
	::GLuint                      m_timer_queries[2];  ///< 描画時間を図るためのクエリ
//	MilliSeconds                  m_draw_time;		   ///< 描画時間
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_RENDERER_HPP
