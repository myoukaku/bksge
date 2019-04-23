/**
 *	@file	render_state_inl.hpp
 *
 *	@brief	RenderState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_RENDER_STATE_INL_HPP
#define BKSGE_RENDER_INL_RENDER_STATE_INL_HPP

#include <bksge/render/render_state.hpp>
#include <bksge/render/rasterizer_state.hpp>
#include <bksge/render/blend_state.hpp>
#include <bksge/render/depth_state.hpp>
#include <bksge/render/stencil_state.hpp>
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
RenderState::RenderState(void)
	: m_rasterizer_state()
	, m_blend_state()
	, m_depth_state()
	, m_stencil_state()
	, m_hlsl_shader()
	, m_glsl_shader()
{
}

BKSGE_INLINE Shader const&
RenderState::hlsl_shader(void) const
{
	return m_hlsl_shader;
}

BKSGE_INLINE Shader const&
RenderState::glsl_shader(void) const
{
	return m_glsl_shader;
}

BKSGE_INLINE Shader&
RenderState::hlsl_shader(void)
{
	return m_hlsl_shader;
}

BKSGE_INLINE Shader&
RenderState::glsl_shader(void)
{
	return m_glsl_shader;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_RENDER_STATE_INL_HPP
