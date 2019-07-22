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

template <typename>
struct color_scale
{
	static BKSGE_CONSTEXPR double get() { return 255.0; }
};
template <>
struct color_scale<float>
{
	static BKSGE_CONSTEXPR double get() { return 1.0; }
};
template <>
struct color_scale<double>
{
	static BKSGE_CONSTEXPR double get() { return 1.0; }
};
template <>
struct color_scale<long double>
{
	static BKSGE_CONSTEXPR double get() { return 1.0; }
};

template <typename To, typename T, std::size_t N>
inline BKSGE_CONSTEXPR To
color_cast(Color<T, N> const& c) BKSGE_NOEXCEPT
{
	using T1 = typename To::value_type;
	using T2 = T;
	return (Color<double, N>(c.as_array())
		* color_scale<T1>::get()
		/ color_scale<T2>::get()
	).as_array();
}

template <typename T, std::size_t N>
template <typename U, typename>
inline BKSGE_CONSTEXPR
Color<T, N>::Color(Color<U, N> const& rhs)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: BaseType(color_cast<Color<T, N>>(rhs).as_array())
{}

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
Lerp(
	Color<T, N> const& from,
	Color<T, N> const& to,
	ArithmeticType const& t) BKSGE_NOEXCEPT
{
	return bksge::math::detail::lerp_per_elem(from, to, t);
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_MATH_INL_COLOR_INL_HPP
