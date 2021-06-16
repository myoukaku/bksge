/**
 *	@file	add_rvalue_reference.hpp
 *
 *	@brief	add_rvalue_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
#define BKSGE_FND_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief		型に右辺値参照を追加する
 *
 *	@tparam		T
 *
 *	Tがオブジェクト型もしくは関数型の場合(cv修飾や参照型でない)、T&&をメンバ型typeとして定義する。
 *	そうでない場合、Tをメンバ型typeとして定義する。
 *
 *	例)
 *	add_rvalue_reference<int>::type is int&&
 *	add_rvalue_reference<int&>::type is int&
 *	add_rvalue_reference<int&&>::type is int&&
 */
using std::add_rvalue_reference;

/**
 *	@brief	add_rvalue_referenceのエイリアステンプレート
 */
template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
