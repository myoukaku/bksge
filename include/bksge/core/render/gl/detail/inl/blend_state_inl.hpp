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

BKSGE_INLINE
BlendState::BlendState(bksge::BlendState const& state)
	: m_enable(state.enable())
	, m_color_src_factor(gl::BlendFactor(state.color_src_factor()))
	, m_color_dst_factor(gl::BlendFactor(state.color_dst_factor()))
	, m_alpha_src_factor(gl::BlendFactor(state.alpha_src_factor()))
	, m_alpha_dst_factor(gl::BlendFactor(state.alpha_dst_factor()))
	, m_color_operation(gl::BlendOperation(state.color_operation()))
	, m_alpha_operation(gl::BlendOperation(state.alpha_operation()))
	, m_color_mask_red  (gl::Bool(Test(state.color_write_mask(), ColorWriteFlag::kRed)))
	, m_color_mask_green(gl::Bool(Test(state.color_write_mask(), ColorWriteFlag::kGreen)))
	, m_color_mask_blue (gl::Bool(Test(state.color_write_mask(), ColorWriteFlag::kBlue)))
	, m_color_mask_alpha(gl::Bool(Test(state.color_write_mask(), ColorWriteFlag::kAlpha)))
	, m_logic_op_enable(state.logic_op_enable())
	, m_logic_op(gl::LogicOperation(state.logic_operation()))
{}

BKSGE_INLINE void
BlendState::Apply(void)
{
	if (m_enable)
	{
		::glEnable(GL_BLEND);
	}
	else
	{
		::glDisable(GL_BLEND);
	}

	::glBlendFuncSeparate(
		m_color_src_factor,
		m_color_dst_factor,
		m_alpha_src_factor,
		m_alpha_dst_factor);

	::glBlendEquationSeparate(
		m_color_operation,
		m_alpha_operation);

	::glColorMask(
		m_color_mask_red,
		m_color_mask_green,
		m_color_mask_blue,
		m_color_mask_alpha);

	if (m_logic_op_enable)
	{
		::glEnable(GL_COLOR_LOGIC_OP);
	}
	else
	{
		::glDisable(GL_COLOR_LOGIC_OP);
	}

	::glLogicOp(m_logic_op);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_STATE_INL_HPP
