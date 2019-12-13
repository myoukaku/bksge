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

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_BLEND_STATE_INL_HPP
