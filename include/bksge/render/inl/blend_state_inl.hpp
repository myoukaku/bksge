/**
 *	@file	blend_state_inl.hpp
 *
 *	@brief	BlendState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_BLEND_STATE_INL_HPP
#define BKSGE_RENDER_INL_BLEND_STATE_INL_HPP

#include <bksge/render/blend_state.hpp>
#include <bksge/render/blend_operation.hpp>
#include <bksge/render/blend_factor.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
BlendState::BlendState(void)
	: m_enable(false)
	, m_op(BlendOperation::kAdd)
	, m_src(BlendFactor::kOne)
	, m_dst(BlendFactor::kZero)
	, m_alpha_op(BlendOperation::kAdd)
	, m_alpha_src(BlendFactor::kOne)
	, m_alpha_dst(BlendFactor::kZero)
{
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_BLEND_STATE_INL_HPP
