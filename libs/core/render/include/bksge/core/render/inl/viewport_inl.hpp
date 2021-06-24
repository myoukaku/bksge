/**
 *	@file	viewport_inl.hpp
 *
 *	@brief	Viewport の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_VIEWPORT_INL_HPP
#define BKSGE_CORE_RENDER_INL_VIEWPORT_INL_HPP

#include <bksge/core/render/viewport.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Viewport::Viewport(void)
	: m_rect()
	, m_min_depth(0.0f)
	, m_max_depth(1.0f)
{
}

BKSGE_INLINE Rectf const&
Viewport::rect(void) const
{
	return m_rect;
}

BKSGE_INLINE float
Viewport::min_depth(void) const
{
	return m_min_depth;
}

BKSGE_INLINE float
Viewport::max_depth(void) const
{
	return m_max_depth;
}

BKSGE_INLINE void
Viewport::SetRect(Rectf const& rect)
{
	m_rect = rect;
}

BKSGE_INLINE void
Viewport::SetMinDepth(float min_depth)
{
	m_min_depth = min_depth;
}

BKSGE_INLINE void
Viewport::SetMaxDepth(float max_depth)
{
	m_max_depth = max_depth;
}

BKSGE_INLINE bool
operator==(Viewport const& lhs, Viewport const& rhs)
{
	return
		lhs.rect()      == rhs.rect()      &&
		lhs.min_depth() == rhs.min_depth() &&
		lhs.max_depth() == rhs.max_depth();
}

BKSGE_INLINE bool
operator!=(Viewport const& lhs, Viewport const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_VIEWPORT_INL_HPP
