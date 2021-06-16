/**
 *	@file	remove_extent.hpp
 *
 *	@brief	remove_extent の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_REMOVE_EXTENT_HPP
#define BKSGE_FND_TYPE_TRAITS_REMOVE_EXTENT_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief		配列型Tから次元を除去する。
 *
 *	@tparam		T
 *
 *	remove_extentは、型Tが、何らかの型Uの配列型である場合はU型を、
 *	そうでなければ型Tをメンバ型typeとして定義する。
 */
using std::remove_extent;

template <typename T>
using remove_extent_t = typename remove_extent<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_REMOVE_EXTENT_HPP
