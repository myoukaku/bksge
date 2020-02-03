/**
 *	@file	gl_renderer.hpp
 *
 *	@brief	GlRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_GL_RENDERER_HPP
#define BKSGE_CORE_RENDER_GL_GL_RENDERER_HPP

#include <bksge/core/render/gl/fwd/gl_renderer_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/context_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>
#include <bksge/core/render/fwd/blend_state_fwd.hpp>
#include <bksge/core/render/fwd/depth_state_fwd.hpp>
#include <bksge/core/render/fwd/rasterizer_state_fwd.hpp>
#include <bksge/core/render/fwd/viewport_fwd.hpp>
#include <bksge/core/render/fwd/scissor_state_fwd.hpp>
#include <bksge/core/render/fwd/clear_state_fwd.hpp>
#include <bksge/core/render/renderer.hpp>
#include <bksge/core/window/fwd/window_fwd.hpp>
#include <bksge/fnd/units/time.hpp>
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
	GlRenderer(Window const& window);

	virtual ~GlRenderer();

private:
	void VBegin(void) override;
	void VEnd(void) override;
	void VBeginRenderPass(RenderPassInfo const& render_pass_info) override;
	void VEndRenderPass(void) override;
	bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;

	void ApplyClearState(ClearState const& clear_state);
	void ApplyViewport(Viewport const& viewport);
	void ApplyScissorState(ScissorState const& scissor_state);
	void ApplyRasterizerState(RasterizerState const& rasterizer_state);
	void ApplyBlendState(BlendState const& blend_state);
	void ApplyDepthState(DepthState const& depth_state);

	using MilliSeconds = bksge::units::milliseconds<float>;
	using NanoSeconds  = bksge::units::nanoseconds<float>;

private:
	std::unique_ptr<gl::Context>		m_gl_context;
	std::unique_ptr<gl::ResourcePool>	m_resource_pool;
	::GLuint							m_timer_queries[2];	///< 描画時間を図るためのクエリ
	MilliSeconds						m_draw_time;		///< 描画時間
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/inl/gl_renderer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_GL_RENDERER_HPP
