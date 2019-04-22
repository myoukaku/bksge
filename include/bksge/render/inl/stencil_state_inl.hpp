/**
 *	@file	stencil_state_inl.hpp
 *
 *	@brief	StencilState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_STENCIL_STATE_INL_HPP
#define BKSGE_RENDER_INL_STENCIL_STATE_INL_HPP

#include <bksge/render/stencil_state.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
StencilState::StencilState(void)
	: m_enable(false)
	, m_read_mask(0u)
	, m_write_mask(0u)
	, m_func(ComparisonFunction::kNever)
	, m_fail_op(StencilOperation::kKeep)
	, m_depth_fail_op(StencilOperation::kKeep)
	, m_pass_op(StencilOperation::kKeep)
{
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_STENCIL_STATE_INL_HPP
