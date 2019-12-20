/**
 *	@file	blend_state_inl.hpp
 *
 *	@brief	BlendState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_BLEND_STATE_INL_HPP
#define BKSGE_CORE_RENDER_INL_BLEND_STATE_INL_HPP

#include <bksge/core/render/blend_state.hpp>
#include <bksge/core/render/blend_operation.hpp>
#include <bksge/core/render/blend_factor.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
BlendState::BlendState(void)
	: m_enable(false)
	, m_operation(BlendOperation::kAdd)
	, m_src_factor(BlendFactor::kOne)
	, m_dst_factor(BlendFactor::kZero)
	, m_alpha_operation(BlendOperation::kAdd)
	, m_alpha_src_factor(BlendFactor::kOne)
	, m_alpha_dst_factor(BlendFactor::kZero)
{
}

BKSGE_INLINE bool
BlendState::enable(void) const
{
	return m_enable;
}

BKSGE_INLINE BlendOperation
BlendState::operation(void) const
{
	return m_operation;
}

BKSGE_INLINE BlendFactor
BlendState::src_factor(void) const
{
	return m_src_factor;
}

BKSGE_INLINE BlendFactor
BlendState::dst_factor(void) const
{
	return m_dst_factor;
}

BKSGE_INLINE BlendOperation
BlendState::alpha_operation(void) const
{
	return m_alpha_operation;
}

BKSGE_INLINE BlendFactor
BlendState::alpha_src_factor(void) const
{
	return m_alpha_src_factor;
}

BKSGE_INLINE BlendFactor
BlendState::alpha_dst_factor(void) const
{
	return m_alpha_dst_factor;
}

BKSGE_INLINE void
BlendState::SetEnable(bool enable)
{
	m_enable = enable;
}

BKSGE_INLINE void
BlendState::SetOperation(BlendOperation op)
{
	SetOperation(op, op);
}

BKSGE_INLINE void
BlendState::SetOperation(BlendOperation rgb_op, BlendOperation alpha_op)
{
	m_operation = rgb_op;
	m_alpha_operation = alpha_op;
}

BKSGE_INLINE void
BlendState::SetFactor(BlendFactor src, BlendFactor dst)
{
	SetFactor(src, dst, src, dst);
}

BKSGE_INLINE void
BlendState::SetFactor(
	BlendFactor rgb_src, BlendFactor rgb_dst,
	BlendFactor alpha_src, BlendFactor alpha_dst)
{
	m_src_factor = rgb_src;
	m_dst_factor = rgb_dst;
	m_alpha_src_factor = alpha_src;
	m_alpha_dst_factor = alpha_dst;
}

BKSGE_INLINE bool
operator==(BlendState const& lhs, BlendState const& rhs)
{
	return
		lhs.enable()           == rhs.enable() &&
		lhs.operation()        == rhs.operation() &&
		lhs.src_factor()       == rhs.src_factor() &&
		lhs.dst_factor()       == rhs.dst_factor() &&
		lhs.alpha_operation()  == rhs.alpha_operation() &&
		lhs.alpha_src_factor() == rhs.alpha_src_factor() &&
		lhs.alpha_dst_factor() == rhs.alpha_dst_factor();
}

BKSGE_INLINE bool
operator!=(BlendState const& lhs, BlendState const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_BLEND_STATE_INL_HPP
