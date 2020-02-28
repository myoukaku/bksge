/**
 *	@file	is_trivially_constructible.hpp
 *
 *	@brief	is_trivially_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP

namespace bksge
{

/**
 *	@brief	型Tがトリビアルに構築可能か調べる。
 *			T( Args... ) の形式のコンストラクタ呼び出しがトリビアルに可能であるか。
 *
 *	@tparam		T		チェックする型
 *	@tparam		Args...	パラメータパック
 *
 *	@require	型TおよびパラメータパックArgs...のすべての型は、完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_trivially_constructibleは、T( Args... )の形式のコンストラクタ呼出しがトリビアルに可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	「トリビアルに構築可能」とは、ユーザー定義されないコンストラクタを持っていることを意味する。
 */
template <typename T, typename... Args>
struct is_trivially_constructible;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_trivially_constructible_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
