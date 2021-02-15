/**
 *	@file	is_implicitly_constructible.hpp
 *
 *	@brief	is_implicitly_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	型Tが暗黙に構築可能か調べる。
 *			T( Args... ) の形式のコンストラクタ呼び出しが暗黙に可能であるか。
 *
 *	@tparam		T		チェックする型
 *	@tparam		Args...	パラメータパック
 *
 *	@require	型TおよびパラメータパックArgs...のすべての型は、完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_implicitly_constructibleは、T( Args... )の形式のコンストラクタ呼出しが暗黙に可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T, typename... Args>
struct is_implicitly_constructible;


#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename... Args>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_implicitly_constructible_v = is_implicitly_constructible<T, Args...>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_implicitly_constructible_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP
