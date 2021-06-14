/**
 *	@file	add_lvalue_reference.hpp
 *
 *	@brief	add_lvalue_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
#define BKSGE_FND_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief		型に左辺値参照を追加する
 *
 *	@tparam		T
 *
 *	Tがオブジェクト型もしくは関数型の場合(cv修飾や参照型でない)、T&をメンバ型typeとして定義する。
 *	Tが何らかの型Uの右辺値参照型の場合、U&をメンバ型typeとして定義する。
 *	いずれでもない場合、Tをメンバ型typeとして定義する。
 *
 *	例)
 *	add_lvalue_reference<int>::type is int&
 *	add_lvalue_reference<int&>::type is int&
 *	add_lvalue_reference<int&&>::type is int&
 */
using std::add_lvalue_reference;

/**
 *	@brief	add_lvalue_referenceのエイリアステンプレート
 */
template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
