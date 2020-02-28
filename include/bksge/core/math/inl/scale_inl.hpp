/**
 *	@file	scale_inl.hpp
 *
 *	@brief	Scale の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_INL_SCALE_INL_HPP
#define BKSGE_CORE_MATH_INL_SCALE_INL_HPP

#include <bksge/core/math/scale.hpp>
#include <bksge/core/math/vector.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace math
{

template <typename T, bksge::size_t N>
template <typename U, typename>
inline BKSGE_CONSTEXPR
Scale<T, N>::Scale(Scale<U, N> const& rhs)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: BaseType(rhs.as_array())
{}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR auto
Scale<T, N>::Zero() BKSGE_NOEXCEPT
-> Scale
{
	return Scale{};
}

namespace detail
{

template <typename T, bksge::size_t N, bksge::size_t... Is>
inline BKSGE_CONSTEXPR Scale<T, N>
identity_impl(bksge::index_sequence<Is...>) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return { ((void)Is, T(1))... };
}

}	// namespace detail

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR auto
Scale<T, N>::Identity() BKSGE_NOEXCEPT
-> Scale
{
	return detail::identity_impl<T, N>(bksge::make_index_sequence<N>());
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Scale<T, N>
operator+(Scale<T, N> const& v) BKSGE_NOEXCEPT
{
	return v;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Scale<T, N>
operator-(Scale<T, N> const& v) BKSGE_NOEXCEPT
{
	return bksge::math::detail::negate_per_elem(v);
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator+=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs + rhs;
	return lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Scale<T, N>
operator+(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::add_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator-=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs - rhs;
	return lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Scale<T, N>
operator-(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::sub_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator*=(Scale<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Scale<T, N>
operator*(Scale<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Scale<T, N>
operator*(ArithmeticType lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return rhs * lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator*=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Scale<T, N> const
operator*(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator/=(Scale<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Scale<T, N>
operator/(Scale<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::div_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator/=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Scale<T, N> const
operator/(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::div_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Vector<T, N> const
operator*(Vector<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Scale<T, N>
Lerp(
	Scale<T, N> const& from,
	Scale<T, N> const& to,
	ArithmeticType const& t) BKSGE_NOEXCEPT
{
	return bksge::math::detail::lerp_per_elem(from, to, t);
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_INL_SCALE_INL_HPP
