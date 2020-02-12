/**
 *	@file	remove_pointer.hpp
 *
 *	@brief	remove_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_REMOVE_POINTER_HPP
#define BKSGE_FND_TYPE_TRAITS_REMOVE_POINTER_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief		型Tからポインタを除去する。
 *
 *	@tparam		T
 *
 *	remove_pointerは、型Tが何らかの型Uへの(cv修飾された)ポインタである場合、
 *	型に含まれるポインタを除去した型Uを、メンバ型typeとして定義する。
 *	そうでなければ、型Tをそのままメンバ型typeとして定義する。
 */
using std::remove_pointer;

template <typename T>
using remove_pointer_t = typename remove_pointer<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_REMOVE_POINTER_HPP
