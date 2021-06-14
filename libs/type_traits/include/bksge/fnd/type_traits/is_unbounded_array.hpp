/**
 *	@file	is_unbounded_array.hpp
 *
 *	@brief	is_unbounded_array の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_bounded_array_traits) && (__cpp_lib_bounded_array_traits >= 201902)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

template <typename T>
struct is_unbounded_array
	: public detail::constant_wrapper<
		std::is_unbounded_array<T>
	>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

/**
 *	@brief		型Tが要素数の不明な配列型かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_unbounded_arrayは、Tが要素型の不明な配列型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	要素数の不明な配列型とは、T[N]やT*を含まないT[]形式の配列型である。
 */
template <typename>
struct is_unbounded_array : public bksge::false_type {};

template <typename T>
struct is_unbounded_array<T[]> : public bksge::true_type {};

}	// namespace bksge

#endif

namespace bksge
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_unbounded_array_v  = is_unbounded_array<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
