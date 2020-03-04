﻿/**
 *	@file	is_nothrow_constructible.hpp
 *
 *	@brief	is_nothrow_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP

namespace bksge
{

/**
 *	@brief	型Tのコンストラクタ呼出しが適格であり、かつそのコンストラクタが例外を投げないか調べる
 *
 *	@tparam		T		チェックする型
 *	@tparam		Args...	パラメータパック
 *
 *	@require	型TおよびパラメータパックArgs...のすべての型は完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_nothrow_constructibleは、型Tが例外を投げない保証のもとに構築可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	is_constructible<T, Args...>::value == trueかつ、いかなる例外も投げないならば、
 *	例外を投げない構築が可能であると判断される。
 */
template <typename T, typename... Args>
struct is_nothrow_constructible;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_nothrow_constructible_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP