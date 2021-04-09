/**
 *	@file	blend_state_inl.hpp
 *
 *	@brief	BlendState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_STATE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/blend_state.hpp>
#include <bksge/core/render/gl/detail/blend_factor.hpp>
#include <bksge/core/render/gl/detail/blend_operation.hpp>
#include <bksge/core/render/gl/detail/logic_operation.hpp>
#include <bksge/core/render/gl/detail/bool.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/blend_state.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE void
BlendState::Apply(bksge::BlendState const& state)
{
	if (state.enable())
	{
		::glEnable(GL_BLEND);
	}
	else
	{
		::glDisable(GL_BLEND);
	}

	::glBlendFuncSeparate(
		gl::BlendFactor(state.color_src_factor()),
		gl::BlendFactor(state.color_dst_factor()),
		gl::BlendFactor(state.alpha_src_factor()),
		gl::BlendFactor(state.alpha_dst_factor()));

	::glBlendEquationSeparate(
		gl::BlendOperation(state.color_operation()),
		gl::BlendOperation(state.alpha_operation()));

	::glColorMask(
		gl::Bool(Test(state.color_write_mask(), ColorWriteFlag::kRed)),
		gl::Bool(Test(state.color_write_mask(), ColorWriteFlag::kGreen)),
		gl::Bool(Test(state.color_write_mask(), ColorWriteFlag::kBlue)),
		gl::Bool(Test(state.color_write_mask(), ColorWriteFlag::kAlpha)));

	if (state.logic_op_enable())
	{
		::glEnable(GL_COLOR_LOGIC_OP);
	}
	else
	{
		::glDisable(GL_COLOR_LOGIC_OP);
	}

	::glLogicOp(gl::LogicOperation(state.logic_operation()));
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_STATE_INL_HPP
