/**
 *	@file	add_const.hpp
 *
 *	@brief	add_const の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_ADD_CONST_HPP
#define BKSGE_FND_TYPE_TRAITS_ADD_CONST_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief		型をconst修飾する
 *
 *	@tparam		T
 *
 *	add_constは、型Tにconst修飾を付加した型を、メンバ型typeとして定義する。
 *	型Tが参照、関数、すでに最上位がconst修飾された型である場合は、型Tをそのままメンバ型typeとして定義する。
 */
using std::add_const;

/**
 *	@brief	add_constのエイリアステンプレート
 */
template <typename T>
using add_const_t = typename add_const<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_ADD_CONST_HPP
