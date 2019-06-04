/**
 *	@file	is_implicitly_move_constructible.hpp
 *
 *	@brief	is_implicitly_move_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_HPP
#define BKSGE_TYPE_TRAITS_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_HPP

namespace bksge
{

/**
 *	@brief	型Tが暗黙にムーブ構築可能か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_implicitly_move_constructible は、型Tが暗黙にムーブ構築可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_implicitly_move_constructible;

}	// namespace bksge

#include <bksge/type_traits/inl/is_implicitly_move_constructible_inl.hpp>

#endif // BKSGE_TYPE_TRAITS_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_HPP
