/**
 *	@file	scissor_state_inl.hpp
 *
 *	@brief	ScissorState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_SCISSOR_STATE_INL_HPP
#define BKSGE_RENDER_INL_SCISSOR_STATE_INL_HPP

#include <bksge/render/scissor_state.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
ScissorState::ScissorState(void)
	: m_enable(false)
	, m_rect()
{
}

BKSGE_INLINE bool
ScissorState::enable(void) const
{
	return m_enable;
}

BKSGE_INLINE Rectf const&
ScissorState::rect(void) const
{
	return m_rect;
}

BKSGE_INLINE void
ScissorState::SetEnable(bool enable)
{
	m_enable = enable;
}

BKSGE_INLINE void
ScissorState::SetRect(Rectf const& rect)
{
	m_rect = rect;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_SCISSOR_STATE_INL_HPP
