/**
 *	@file	is_move_constructible.hpp
 *
 *	@brief	is_move_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがムーブ構築可能か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_move_constructibleは、型Tがムーブ構築可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_move_constructible
	: public detail::constant_wrapper<
		std::is_move_constructible<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP
