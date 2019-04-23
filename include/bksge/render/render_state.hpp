/**
 *	@file	render_state.hpp
 *
 *	@brief	RenderState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_RENDER_STATE_HPP
#define BKSGE_RENDER_RENDER_STATE_HPP

#include <bksge/render/fwd/render_state_fwd.hpp>
#include <bksge/render/rasterizer_state.hpp>
#include <bksge/render/blend_state.hpp>
#include <bksge/render/depth_state.hpp>
#include <bksge/render/stencil_state.hpp>
#include <bksge/render/shader.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class RenderState
{
public:
	RenderState(void);

	Shader const& hlsl_shader(void) const;
	Shader const& glsl_shader(void) const;

	Shader& hlsl_shader(void);
	Shader& glsl_shader(void);

private:
	RasterizerState		m_rasterizer_state;
	BlendState			m_blend_state;
	DepthState			m_depth_state;
	StencilState		m_stencil_state;
	Shader				m_hlsl_shader;
	Shader				m_glsl_shader;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/render_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_RENDER_STATE_HPP
