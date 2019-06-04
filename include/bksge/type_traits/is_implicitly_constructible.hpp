/**
 *	@file	is_implicitly_constructible.hpp
 *
 *	@brief	is_implicitly_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP
#define BKSGE_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP

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

}	// namespace bksge

#include <bksge/type_traits/inl/is_implicitly_constructible_inl.hpp>

#endif // BKSGE_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP
