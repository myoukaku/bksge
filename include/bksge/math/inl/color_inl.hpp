/**
 *	@file	color_inl.hpp
 *
 *	@brief	Color の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_INL_COLOR_INL_HPP
#define BKSGE_MATH_INL_COLOR_INL_HPP

#include <bksge/math/color.hpp>
#include <bksge/math/detail/vector_functions.hpp>
#include <bksge/config.hpp>
#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR auto
Color<T, N>::Zero() BKSGE_NOEXCEPT
-> Color
{
	return Color{};
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Color<T, N>
operator+(Color<T, N> const& v) BKSGE_NOEXCEPT
{
	return v;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Color<T, N>
operator-(Color<T, N> const& v) BKSGE_NOEXCEPT
{
	return bksge::math::detail::negate_per_elem(v);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator+=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs + rhs;
	return lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Color<T, N>
operator+(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::add_per_elem(lhs, rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator-=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs - rhs;
	return lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Color<T, N>
operator-(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::sub_per_elem(lhs, rhs);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator*=(Color<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Color<T, N>
operator*(Color<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Color<T, N>
operator*(ArithmeticType lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return rhs * lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator*=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Color<T, N> const
operator*(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator/=(Color<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Color<T, N>
operator/(Color<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::div_per_elem(lhs, rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator/=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Color<T, N> const
operator/(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::div_per_elem(lhs, rhs);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Color<T, N>
Lerp(Color<T, N> const& from, Color<T, N> const& to, ArithmeticType const& t) BKSGE_NOEXCEPT
{
	return bksge::math::detail::lerp_per_elem(from, to, t);
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_MATH_INL_COLOR_INL_HPP
