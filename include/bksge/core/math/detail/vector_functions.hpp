/**
 *	@file	vector_functions.hpp
 *
 *	@brief	Vector 用の関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_VECTOR_FUNCTIONS_HPP
#define BKSGE_CORE_MATH_DETAIL_VECTOR_FUNCTIONS_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/tpp/accumulate.hpp>
#include <bksge/fnd/tpp/all_of.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/cmath/lerp.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename Vec, bksge::size_t... Is>
inline BKSGE_CONSTEXPR Vec
negate_per_elem_impl(Vec const& v, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {-v[Is]...};
}

template <typename Vec>
inline BKSGE_CONSTEXPR Vec
negate_per_elem(Vec const& v)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return negate_per_elem_impl(v,
		bksge::make_index_sequence<bksge::tuple_size<Vec>::value>());
}

template <typename Vec, bksge::size_t... Is>
inline BKSGE_CONSTEXPR Vec
add_per_elem_impl(Vec const& lhs, Vec const& rhs, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] + rhs[Is])...};
}

template <typename Vec>
inline BKSGE_CONSTEXPR Vec
add_per_elem(Vec const& lhs, Vec const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return add_per_elem_impl(lhs, rhs,
		bksge::make_index_sequence<bksge::tuple_size<Vec>::value>());
}

template <typename Vec, bksge::size_t... Is>
inline BKSGE_CONSTEXPR Vec
sub_per_elem_impl(Vec const& lhs, Vec const& rhs, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] - rhs[Is])...};
}

template <typename Vec>
inline BKSGE_CONSTEXPR Vec
sub_per_elem(Vec const& lhs, Vec const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return sub_per_elem_impl(lhs, rhs,
		bksge::make_index_sequence<bksge::tuple_size<Vec>::value>());
}

template <typename Vec, typename U, bksge::size_t... Is,
	bksge::enable_if_t<
		bksge::is_arithmetic<U>::value
	>* = nullptr
>
inline BKSGE_CONSTEXPR Vec
mul_per_elem_impl(Vec const& lhs, U const& rhs, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] * rhs)...};
}

template <typename Vec1, typename Vec2, bksge::size_t... Is,
	bksge::enable_if_t<
		!bksge::is_arithmetic<Vec2>::value
	>* = nullptr
>
inline BKSGE_CONSTEXPR Vec1
mul_per_elem_impl(Vec1 const& lhs, Vec2 const& rhs, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] * rhs[Is])...};
}

template <typename Vec, typename U>
inline BKSGE_CONSTEXPR Vec
mul_per_elem(Vec const& lhs, U const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return mul_per_elem_impl(lhs, rhs,
		bksge::make_index_sequence<bksge::tuple_size<Vec>::value>());
}

template <typename Vec, typename U, bksge::size_t... Is,
	bksge::enable_if_t<
		bksge::is_arithmetic<U>::value
	>* = nullptr
>
inline BKSGE_CONSTEXPR Vec
div_per_elem_impl(Vec const& lhs, U const& rhs, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] / rhs)...};
}

template <typename Vec1, typename Vec2, bksge::size_t... Is,
	bksge::enable_if_t<
		!bksge::is_arithmetic<Vec2>::value
	>* = nullptr
>
inline BKSGE_CONSTEXPR Vec1
div_per_elem_impl(Vec1 const& lhs, Vec2 const& rhs, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {(lhs[Is] / rhs[Is])...};
}

template <typename Vec, typename U>
inline BKSGE_CONSTEXPR Vec
div_per_elem(Vec const& lhs, U const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return div_per_elem_impl(lhs, rhs,
		bksge::make_index_sequence<bksge::tuple_size<Vec>::value>());
}

template <typename R, typename Vec, bksge::size_t... Is>
inline BKSGE_CONSTEXPR R
accumulate_impl(Vec const& lhs, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return bksge::tpp::accumulate<R>(lhs[Is]...);
}

template <typename Vec>
inline BKSGE_CONSTEXPR typename Vec::value_type
accumulate(Vec const& lhs) BKSGE_NOEXCEPT_OR_NOTHROW
{
	return accumulate_impl<typename Vec::value_type>(lhs,
		bksge::make_index_sequence<bksge::tuple_size<Vec>::value>());
}

template <typename Vec, bksge::size_t... Is>
inline BKSGE_CONSTEXPR bool
equal_per_elem_impl(Vec const& lhs, Vec const& rhs, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return bksge::tpp::all_of(lhs[Is] == rhs[Is]...);
}

template <typename Vec>
inline BKSGE_CONSTEXPR bool
equal_per_elem(Vec const& lhs, Vec const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return equal_per_elem_impl(lhs, rhs,
		bksge::make_index_sequence<bksge::tuple_size<Vec>::value>());
}

template <typename Vec, typename U, bksge::size_t... Is>
inline BKSGE_CONSTEXPR Vec
lerp_per_elem_impl(Vec const& from, Vec const& to, U const& t, bksge::index_sequence<Is...>)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return {bksge::lerp(from[Is], to[Is], t)...};
}

template <typename Vec, typename U>
inline BKSGE_CONSTEXPR Vec
lerp_per_elem(Vec const& from, Vec const& to, U const& t)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return lerp_per_elem_impl(from, to, t,
		bksge::make_index_sequence<bksge::tuple_size<Vec>::value>());
}

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_DETAIL_VECTOR_FUNCTIONS_HPP
