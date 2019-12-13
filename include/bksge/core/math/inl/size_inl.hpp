/**
 *	@file	size_inl.hpp
 *
 *	@brief	Size の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_INL_SIZE_INL_HPP
#define BKSGE_CORE_MATH_INL_SIZE_INL_HPP

#include <bksge/core/math/size.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
template <typename U, typename>
inline BKSGE_CONSTEXPR
Size<T, N>::Size(Size<U, N> const& rhs)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: BaseType(rhs.as_array())
{}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR auto
Size<T, N>::Zero() BKSGE_NOEXCEPT
-> Size
{
	return Size{};
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Size<T, N>
operator+(Size<T, N> const& v) BKSGE_NOEXCEPT
{
	return v;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Size<T, N>
operator-(Size<T, N> const& v) BKSGE_NOEXCEPT
{
	return bksge::math::detail::negate_per_elem(v);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator+=(Size<T, N>& lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs + rhs;
	return lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Size<T, N>
operator+(Size<T, N> const& lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::add_per_elem(lhs, rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator-=(Size<T, N>& lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs - rhs;
	return lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Size<T, N>
operator-(Size<T, N> const& lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::sub_per_elem(lhs, rhs);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator*=(Size<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator*=(Size<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Size<T, N>
operator*(Size<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Size<T, N>
operator*(ArithmeticType lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return rhs * lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Size<T, N> const
operator*(Size<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator/=(Size<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename T, std::size_t N, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Size<T, N>
operator/(Size<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::div_per_elem(lhs, rhs);
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_INL_SIZE_INL_HPP
