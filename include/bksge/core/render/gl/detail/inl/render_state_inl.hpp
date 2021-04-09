/**
 *	@file	render_state_inl.hpp
 *
 *	@brief	RenderState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_STATE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/render_state.hpp>
#include <bksge/core/render/gl/detail/rasterizer_state.hpp>
#include <bksge/core/render/gl/detail/blend_state.hpp>
#include <bksge/core/render/gl/detail/stencil_state.hpp>
#include <bksge/core/render/gl/detail/depth_state.hpp>
#include <bksge/core/render/render_state.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE void
RenderState::Apply(bksge::RenderState const& state)
{
	gl::RasterizerState::Apply(state.rasterizer_state());
	gl::BlendState::Apply(state.blend_state());
	gl::StencilState::Apply(state.stencil_state());
	gl::DepthState::Apply(state.depth_state());
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_STATE_INL_HPP
