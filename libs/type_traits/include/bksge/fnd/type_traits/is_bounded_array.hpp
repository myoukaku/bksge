/**
 *	@file	is_bounded_array.hpp
 *
 *	@brief	is_bounded_array の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_bounded_array_traits) && (__cpp_lib_bounded_array_traits >= 201902)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

template <typename T>
struct is_bounded_array
	: public detail::constant_wrapper<
		std::is_bounded_array<T>
	>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

/**
 *	@brief		型Tが要素数の判明している配列型かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_bounded_arrayは、Tが要素型の判明している配列型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	要素数の判明している配列型とは、T[]を含まないT[N]形式の配列型である。
 */
template <typename T>
struct is_bounded_array : public bksge::false_type {};

template <typename T, bksge::size_t N>
struct is_bounded_array<T[N]> : public bksge::true_type {};

}	// namespace bksge

#endif

namespace bksge
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_bounded_array_v  = is_bounded_array<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
