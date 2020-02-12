/**
 *	@file	remove_reference.hpp
 *
 *	@brief	remove_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_REMOVE_REFERENCE_HPP
#define BKSGE_FND_TYPE_TRAITS_REMOVE_REFERENCE_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief		型Tから参照を除去する。
 *
 *	@tparam		T
 *
 *	remove_referenceは、型Tが何らかの型Uへの参照である場合、
 *	型に含まれる参照を除去した型Uを、メンバ型typeとして定義する。
 *	そうでなければ、型Tをそのままメンバ型typeとして定義する。
 */
using std::remove_reference;

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_REMOVE_REFERENCE_HPP
