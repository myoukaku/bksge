/**
 *	@file	remove_const.hpp
 *
 *	@brief	remove_const の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_REMOVE_CONST_HPP
#define BKSGE_FND_TYPE_TRAITS_REMOVE_CONST_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief		型のconst修飾を除去する。
 *
 *	@tparam		T
 *
 *	remove_constは、型Tに含まれる最上位のconst修飾を除去した型を、メンバ型typeとして定義する。
 */
using std::remove_const;

template <typename T>
using remove_const_t = typename remove_const<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_REMOVE_CONST_HPP
