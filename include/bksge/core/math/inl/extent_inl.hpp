/**
 *	@file	extent_inl.hpp
 *
 *	@brief	Extent の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_INL_EXTENT_INL_HPP
#define BKSGE_CORE_MATH_INL_EXTENT_INL_HPP

#include <bksge/core/math/extent.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T, bksge::size_t N>
template <typename U, typename>
inline BKSGE_CONSTEXPR
Extent<T, N>::Extent(Extent<U, N> const& rhs)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: BaseType(rhs.as_array())
{}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR auto
Extent<T, N>::Zero() BKSGE_NOEXCEPT
-> Extent
{
	return Extent{};
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Extent<T, N>
operator+(Extent<T, N> const& v) BKSGE_NOEXCEPT
{
	return v;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Extent<T, N>
operator-(Extent<T, N> const& v) BKSGE_NOEXCEPT
{
	return bksge::math::detail::negate_per_elem(v);
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator+=(Extent<T, N>& lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs + rhs;
	return lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Extent<T, N>
operator+(Extent<T, N> const& lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::add_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator-=(Extent<T, N>& lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs - rhs;
	return lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Extent<T, N>
operator-(Extent<T, N> const& lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::sub_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator*=(Extent<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator*=(Extent<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Extent<T, N>
operator*(Extent<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Extent<T, N>
operator*(ArithmeticType lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return rhs * lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Extent<T, N> const
operator*(Extent<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator/=(Extent<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Extent<T, N>
operator/(Extent<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::div_per_elem(lhs, rhs);
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_INL_EXTENT_INL_HPP
