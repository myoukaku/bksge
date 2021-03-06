﻿/**
 *	@file	is_nothrow_swappable.hpp
 *
 *	@brief	is_nothrow_swappable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_swappable) && (__cpp_lib_is_swappable >= 201603)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

template <typename T>
struct is_nothrow_swappable
	: public detail::constant_wrapper<
		std::is_nothrow_swappable<T>
	>
{};

}	// namespace bksge

#else

namespace bksge
{

/**
 *	@brief		型T が Swap可能かつ、そのSwapが例外を投げないかどうか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_swappableは、型T がSwappableコンセプトを満たしており、そのswap関数が例外を投げないならtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	参照可能な型に対して、is_nothrow_swappable_with<T&, T&>::valueと同じ結果となり、参照可能でない型に対してはfalseとなる。
 *
 *	参照可能な型とは、以下のいずれかの条件に合致する型である：
 *	・オブジェクト型
 *	・CV修飾されていない、もしくは参照修飾されていない関数型
 *	・参照修飾されている型
 */
template <typename T>
struct is_nothrow_swappable;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_nothrow_swappable_inl.hpp>

#endif

namespace bksge
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_HPP
