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
#include <bksge/core/render/color_write_flag.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
BlendState::BlendState(void)
	: m_enable(false)
	, m_color_operation(BlendOperation::kAdd)
	, m_color_src_factor(BlendFactor::kOne)
	, m_color_dst_factor(BlendFactor::kZero)
	, m_alpha_operation(BlendOperation::kAdd)
	, m_alpha_src_factor(BlendFactor::kOne)
	, m_alpha_dst_factor(BlendFactor::kZero)
	, m_color_write_mask(ColorWriteFlag::kAll)
	, m_logic_op_enable(false)
	, m_logic_operation(LogicOperation::kCopy)
{}

BKSGE_INLINE bool
BlendState::enable(void) const
{
	return m_enable;
}

BKSGE_INLINE BlendOperation
BlendState::color_operation(void) const
{
	return m_color_operation;
}

BKSGE_INLINE BlendFactor
BlendState::color_src_factor(void) const
{
	return m_color_src_factor;
}

BKSGE_INLINE BlendFactor
BlendState::color_dst_factor(void) const
{
	return m_color_dst_factor;
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

BKSGE_INLINE ColorWriteFlag
BlendState::color_write_mask(void) const
{
	return m_color_write_mask;
}

BKSGE_INLINE bool
BlendState::logic_op_enable(void) const
{
	return m_logic_op_enable;
}

BKSGE_INLINE LogicOperation
BlendState::logic_operation(void) const
{
	return m_logic_operation;
}

BKSGE_INLINE void
BlendState::SetEnable(bool enable)
{
	m_enable = enable;
}

BKSGE_INLINE void
BlendState::SetOperation(BlendOperation op)
{
	SetColorOperation(op);
	SetAlphaOperation(op);
}

BKSGE_INLINE void
BlendState::SetColorOperation(BlendOperation op)
{
	m_color_operation = op;
}

BKSGE_INLINE void
BlendState::SetAlphaOperation(BlendOperation op)
{
	m_alpha_operation = op;
}

BKSGE_INLINE void
BlendState::SetFactor(BlendFactor src, BlendFactor dst)
{
	SetColorSrcFactor(src);
	SetColorDstFactor(dst);
	SetAlphaSrcFactor(src);
	SetAlphaDstFactor(dst);
}

BKSGE_INLINE void
BlendState::SetColorSrcFactor(BlendFactor factor)
{
	m_color_src_factor = factor;
}

BKSGE_INLINE void
BlendState::SetColorDstFactor(BlendFactor factor)
{
	m_color_dst_factor = factor;
}

BKSGE_INLINE void
BlendState::SetAlphaSrcFactor(BlendFactor factor)
{
	m_alpha_src_factor = factor;
}

BKSGE_INLINE void
BlendState::SetAlphaDstFactor(BlendFactor factor)
{
	m_alpha_dst_factor = factor;
}

BKSGE_INLINE void
BlendState::SetColorWriteFlag(ColorWriteFlag flag)
{
	m_color_write_mask = flag;
}

BKSGE_INLINE void
BlendState::SetLogicOpEnable(bool enable)
{
	m_logic_op_enable = enable;
}

BKSGE_INLINE void
BlendState::SetLogicOperation(LogicOperation op)
{
	m_logic_operation = op;
}

BKSGE_INLINE bool
operator==(BlendState const& lhs, BlendState const& rhs)
{
	return
		lhs.enable()           == rhs.enable()           &&
		lhs.color_operation()  == rhs.color_operation()  &&
		lhs.color_src_factor() == rhs.color_src_factor() &&
		lhs.color_dst_factor() == rhs.color_dst_factor() &&
		lhs.alpha_operation()  == rhs.alpha_operation()  &&
		lhs.alpha_src_factor() == rhs.alpha_src_factor() &&
		lhs.alpha_dst_factor() == rhs.alpha_dst_factor() &&
		lhs.color_write_mask() == rhs.color_write_mask() &&
		lhs.logic_op_enable()  == rhs.logic_op_enable()  &&
		lhs.logic_operation()  == rhs.logic_operation();
}

BKSGE_INLINE bool
operator!=(BlendState const& lhs, BlendState const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_BLEND_STATE_INL_HPP
