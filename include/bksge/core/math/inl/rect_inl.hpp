﻿/**
 *	@file	rect_inl.hpp
 *
 *	@brief	Rect の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_INL_RECT_INL_HPP
#define BKSGE_CORE_MATH_INL_RECT_INL_HPP

#include <bksge/core/math/rect.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/extent2.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/utility/swap.hpp>

namespace bksge
{

namespace math
{

template <typename T>
inline BKSGE_CONSTEXPR
Rect<T>::Rect(void)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: m_left(0)
	, m_top(0)
	, m_right(0)
	, m_bottom(0)
{
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR
Rect<T>::Rect(Vector2<T> const& p1, Vector2<T> const& p2)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: Rect(
		inter_ctor_tag(),
		p1.x(),
		p1.y(),
		p2.x(),
		p2.y())
{
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR
Rect<T>::Rect(Vector2<T> const& pos, Extent2<T> const& extent)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: Rect(
		inter_ctor_tag(),
		pos.x(),
		pos.y(),
		pos.x() + extent.width(),
		pos.y() + extent.height())
{}

template <typename T>
template <typename U>
inline BKSGE_CONSTEXPR
Rect<T>::Rect(Rect<U> const& rhs)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: m_left  (static_cast<T>(rhs.left()))
	, m_top   (static_cast<T>(rhs.top()))
	, m_right (static_cast<T>(rhs.right()))
	, m_bottom(static_cast<T>(rhs.bottom()))
{
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR
Rect<T>::Rect(inter_ctor_tag, T l, T t, T r, T b)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: m_left  (bksge::min(l, r))
	, m_top   (bksge::min(t, b))
	, m_right (bksge::max(l, r))
	, m_bottom(bksge::max(t, b))
{
}

template <typename T>
inline BKSGE_CONSTEXPR T
Rect<T>::left(void) const
{
	return m_left;
}

template <typename T>
inline BKSGE_CONSTEXPR T
Rect<T>::top(void) const
{
	return m_top;
}

template <typename T>
inline BKSGE_CONSTEXPR T
Rect<T>::right(void) const
{
	return m_right;
}

template <typename T>
inline BKSGE_CONSTEXPR T
Rect<T>::bottom(void) const
{
	return m_bottom;
}

template <typename T>
inline BKSGE_CONSTEXPR T
Rect<T>::width(void) const
{
	return right() - left();
}

template <typename T>
inline BKSGE_CONSTEXPR T
Rect<T>::height(void) const
{
	return bottom() - top();
}

template <typename T>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR T const*
Rect<T>::data() const BKSGE_NOEXCEPT_OR_NOTHROW
{
	return &m_left;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
Rect<T>::swap(Rect& other)
	BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value)
{
	using bksge::swap;
	swap(m_left,   other.m_left);
	swap(m_top,    other.m_top);
	swap(m_right,  other.m_right);
	swap(m_bottom, other.m_bottom);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
swap(Rect<T>& lhs, Rect<T>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(Rect<T> const& lhs, Rect<T> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return
		lhs.left()   == rhs.left()  &&
		lhs.top()    == rhs.top()   &&
		lhs.right()  == rhs.right() &&
		lhs.bottom() == rhs.bottom();
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(Rect<T> const& lhs, Rect<T> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename T>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, Rect<T> const& rhs)
{
	return
		os << "{ "
			<< rhs.left()  << ", "
			<< rhs.top()   << ", "
			<< rhs.right() << ", "
			<< rhs.bottom()
		<< " }";
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_INL_RECT_INL_HPP
