/**
 *	@file	render_state_inl.hpp
 *
 *	@brief	RenderState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_RENDER_STATE_INL_HPP
#define BKSGE_CORE_RENDER_INL_RENDER_STATE_INL_HPP

#include <bksge/core/render/render_state.hpp>
#include <bksge/core/render/rasterizer_state.hpp>
#include <bksge/core/render/blend_state.hpp>
#include <bksge/core/render/depth_state.hpp>
#include <bksge/core/render/stencil_state.hpp>

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
{
}

BKSGE_INLINE RasterizerState const&
RenderState::rasterizer_state(void) const
{
	return m_rasterizer_state;
}

BKSGE_INLINE BlendState const&
RenderState::blend_state(void) const
{
	return m_blend_state;
}

BKSGE_INLINE DepthState const&
RenderState::depth_state(void) const
{
	return m_depth_state;
}

BKSGE_INLINE StencilState const&
RenderState::stencil_state(void) const
{
	return m_stencil_state;
}

BKSGE_INLINE RasterizerState&
RenderState::rasterizer_state(void)
{
	return m_rasterizer_state;
}

BKSGE_INLINE BlendState&
RenderState::blend_state(void)
{
	return m_blend_state;
}

BKSGE_INLINE DepthState&
RenderState::depth_state(void)
{
	return m_depth_state;
}

BKSGE_INLINE StencilState&
RenderState::stencil_state(void)
{
	return m_stencil_state;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_RENDER_STATE_INL_HPP
