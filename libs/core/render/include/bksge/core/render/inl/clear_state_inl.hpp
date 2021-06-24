/**
 *	@file	clear_state_inl.hpp
 *
 *	@brief	ClearState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_CLEAR_STATE_INL_HPP
#define BKSGE_CORE_RENDER_INL_CLEAR_STATE_INL_HPP

#include <bksge/core/render/clear_state.hpp>
#include <bksge/core/render/clear_flag.hpp>
#include <bksge/core/math/color4.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
ClearState::ClearState(void)
	: m_flag(ClearFlag::kAll)
	, m_color(0, 0, 0, 0)
	, m_depth(1.0f)
	, m_stencil(0)
{
}

BKSGE_INLINE ClearFlag const&
ClearState::flag(void) const
{
	return m_flag;
}

BKSGE_INLINE Color4f const&
ClearState::color(void) const
{
	return m_color;
}

BKSGE_INLINE float
ClearState::depth(void) const
{
	return m_depth;
}

BKSGE_INLINE bksge::uint8_t
ClearState::stencil(void) const
{
	return m_stencil;
}

BKSGE_INLINE void
ClearState::SetFlag(ClearFlag const& flag)
{
	m_flag = flag;
}

BKSGE_INLINE void
ClearState::SetColor(Color4f const& color)
{
	m_color = color;
}

BKSGE_INLINE void
ClearState::SetDepth(float depth)
{
	m_depth = depth;
}

BKSGE_INLINE void
ClearState::SetStencil(bksge::uint8_t stencil)
{
	m_stencil = stencil;
}

BKSGE_INLINE bool
operator==(ClearState const& lhs, ClearState const& rhs)
{
	return
		lhs.flag()    == rhs.flag()  &&
		lhs.color()   == rhs.color() &&
		lhs.depth()   == rhs.depth() &&
		lhs.stencil() == rhs.stencil();
}

BKSGE_INLINE bool
operator!=(ClearState const& lhs, ClearState const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_CLEAR_STATE_INL_HPP
