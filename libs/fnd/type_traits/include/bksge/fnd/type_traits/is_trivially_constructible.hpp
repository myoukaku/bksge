﻿/**
 *	@file	is_trivially_constructible.hpp
 *
 *	@brief	is_trivially_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	型Tがトリビアルに構築可能か調べる。
 *
 *	@tparam		T		チェックする型
 *	@tparam		Args...	パラメータパック
 *
 *	@require	型TおよびパラメータパックArgs...のすべての型は、完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_trivially_constructibleは、T obj(std::declval<Args>()...);の形式の変数定義がトリビアルに可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	このとき、std::declvalはトリビアルであるとみなされる。
 */
template <typename T, typename... Args>
struct is_trivially_constructible;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename... Args>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_trivially_constructible_v = is_trivially_constructible<T, Args...>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_trivially_constructible_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
