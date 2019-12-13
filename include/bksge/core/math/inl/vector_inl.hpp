/**
 *	@file	vector_inl.hpp
 *
 *	@brief	Vector の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_INL_VECTOR_INL_HPP
#define BKSGE_CORE_MATH_INL_VECTOR_INL_HPP

#include <bksge/core/math/vector.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
template <typename U, typename>
inline BKSGE_CONSTEXPR
Vector<T, N>::Vector(Vector<U, N> const& rhs)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: BaseType(rhs.as_array())
{}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR auto
Vector<T, N>::Zero() BKSGE_NOEXCEPT
-> Vector
{
	return Vector{};
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Vector<T, N>
operator+(Vector<T, N> const& v) BKSGE_NOEXCEPT
{
	return v;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Vector<T, N>
operator-(Vector<T, N> const& v) BKSGE_NOEXCEPT
{
	return bksge::math::detail::negate_per_elem(v);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator+=(Vector<T, N>& lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs + rhs;
	return lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Vector<T, N>
operator+(Vector<T, N> const& lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::add_per_elem(lhs, rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator-=(Vector<T, N>& lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs - rhs;
	return lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Vector<T, N>
operator-(Vector<T, N> const& lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::sub_per_elem(lhs, rhs);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Vector<T, N>
operator*(Vector<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Vector<T, N>
operator*(ArithmeticType lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return rhs * lhs;
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator/=(Vector<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Vector<T, N>
operator/(Vector<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::div_per_elem(lhs, rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR T
Dot(Vector<T, N> const& v1, Vector<T, N> const& v2)
{
	return bksge::math::detail::accumulate(
		bksge::math::detail::mul_per_elem(v1, v2));
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR T
SquaredLength(Vector<T, N> const& v)
{
	return Dot(v, v);
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR bksge::float_promote_t<T>
Length(Vector<T, N> const& v)
{
	return std::sqrt(SquaredLength(v));
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Vector<T, N>
Normalized(Vector<T, N> const& v)
{
	return
		SquaredLength(v) == 0 ?
			Vector<T, N>{} :
		v / Length(v);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Vector<T, N>
Lerp(
	Vector<T, N> const& from,
	Vector<T, N> const& to,
	ArithmeticType const& t) BKSGE_NOEXCEPT
{
	return bksge::math::detail::lerp_per_elem(from, to, t);
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_INL_VECTOR_INL_HPP
