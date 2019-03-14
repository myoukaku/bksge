/**
 *	@file	vector_functions.hpp
 *
 *	@brief	vector_value用の関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_DETAIL_VECTOR_FUNCTIONS_HPP
#define BKSGE_MATH_DETAIL_VECTOR_FUNCTIONS_HPP

#include <bksge/math/detail/vector_value.hpp>
#include <bksge/utility/index_sequence.hpp>
#include <bksge/utility/make_index_sequence.hpp>
#include <bksge/cmath/lerp.hpp>
#include <bksge/config.hpp>
#include <cstddef>
#include <utility>
#include <type_traits>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, std::size_t N, std::size_t... Is>
inline BKSGE_CONSTEXPR vector_value<T, N>
negate_per_elem_impl(vector_value<T, N> const& v, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {-v[Is]...};
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR vector_value<T, N>
negate_per_elem(vector_value<T, N> const& v) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return negate_per_elem_impl(v, bksge::make_index_sequence<N>());
}

template <typename T, std::size_t N, std::size_t... Is>
inline BKSGE_CONSTEXPR vector_value<T, N>
add_per_elem_impl(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] + rhs[Is])...};
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR vector_value<T, N>
add_per_elem(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return add_per_elem_impl(lhs, rhs, bksge::make_index_sequence<N>());
}

template <typename T, std::size_t N, std::size_t... Is>
inline BKSGE_CONSTEXPR vector_value<T, N>
sub_per_elem_impl(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] - rhs[Is])...};
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR vector_value<T, N>
sub_per_elem(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return sub_per_elem_impl(lhs, rhs, bksge::make_index_sequence<N>());
}

template <typename T, std::size_t N, typename U, std::size_t... Is,
	typename = typename std::enable_if<
		std::is_arithmetic<U>::value
	>::type
>
inline BKSGE_CONSTEXPR vector_value<T, N>
mul_per_elem_impl(vector_value<T, N> const& lhs, U const& rhs, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] * rhs)...};
}

template <typename T, std::size_t N, std::size_t... Is>
inline BKSGE_CONSTEXPR vector_value<T, N>
mul_per_elem_impl(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] * rhs[Is])...};
}

template <typename T, std::size_t N, typename U>
inline BKSGE_CONSTEXPR vector_value<T, N>
mul_per_elem(vector_value<T, N> const& lhs, U const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return mul_per_elem_impl(lhs, rhs, bksge::make_index_sequence<N>());
}

template <typename T, std::size_t N, typename U, std::size_t... Is,
	typename = typename std::enable_if<
		std::is_arithmetic<U>::value
	>::type
>
inline BKSGE_CONSTEXPR vector_value<T, N>
div_per_elem_impl(vector_value<T, N> const& lhs, U const& rhs, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] / rhs)...};
}

template <typename T, std::size_t N, std::size_t... Is>
inline BKSGE_CONSTEXPR vector_value<T, N>
div_per_elem_impl(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] / rhs[Is])...};
}

template <typename T, std::size_t N, typename U>
inline BKSGE_CONSTEXPR vector_value<T, N>
div_per_elem(vector_value<T, N> const& lhs, U const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return div_per_elem_impl(lhs, rhs, bksge::make_index_sequence<N>());
}

template <typename T, std::size_t N, std::size_t I = 0u>
struct accumulate_impl
{
	static BKSGE_CONSTEXPR T
	invoke(vector_value<T, N> const& lhs) BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return lhs[I] + accumulate_impl<T, N, I + 1>::invoke(lhs);
	}
};

template <typename T, std::size_t N>
struct accumulate_impl<T, N, N>
{
	static BKSGE_CONSTEXPR T
	invoke(vector_value<T, N> const&) BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return T{};
	}
};

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR T
accumulate(vector_value<T, N> const& lhs) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return accumulate_impl<T, N>::invoke(lhs);
}

template <typename T, std::size_t N, std::size_t I = 0u>
struct equal_per_elem_impl
{
	static BKSGE_CONSTEXPR bool
	invoke(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return lhs[I] == rhs[I] &&
			equal_per_elem_impl<T, N, I + 1>::invoke(lhs, rhs);
	}
};

template <typename T, std::size_t N>
struct equal_per_elem_impl<T, N, N>
{
	static BKSGE_CONSTEXPR bool
	invoke(vector_value<T, N> const&, vector_value<T, N> const&) BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return true;
	}
};

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR bool
equal_per_elem(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return equal_per_elem_impl<T, N>::invoke(lhs, rhs);
}

template <typename T, std::size_t N, typename U, std::size_t... Is>
inline BKSGE_CONSTEXPR vector_value<T, N>
lerp_per_elem_impl(vector_value<T, N> const& from, vector_value<T, N> const& to, U const& t, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {bksge::lerp(from[Is], to[Is], t)...};
}

template <typename T, std::size_t N, typename U>
inline BKSGE_CONSTEXPR vector_value<T, N>
lerp_per_elem(vector_value<T, N> const& from, vector_value<T, N> const& to, U const& t) BKSGE_NOEXCEPT
{
	return lerp_per_elem_impl(from, to, t, bksge::make_index_sequence<N>());
}

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_MATH_DETAIL_VECTOR_FUNCTIONS_HPP
