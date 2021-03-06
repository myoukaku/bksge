﻿/**
 *	@file	iota.hpp
 *
 *	@brief	iota の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_IOTA_HPP
#define BKSGE_FND_NUMERIC_IOTA_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		指定された値から始まる整数列を生成する。
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	ForwardIteratorの値型が、型Tに変換可能であること
 *				型Tの値valに対して、式++valが有効であること
 *
 *	@effect		範囲[first, last)の各要素itについて、先頭から順番に *it = value; ++value; を行う
 *
 *	@complexity	範囲[first, last)の要素数をnとして、n回のインクリメントと代入が行われる。
 */
template <typename ForwardIterator, typename T>
BKSGE_CXX14_CONSTEXPR void
iota(ForwardIterator first, ForwardIterator last, T value);

}	// namespace bksge

#include <bksge/fnd/numeric/inl/iota_inl.hpp>

#endif // BKSGE_FND_NUMERIC_IOTA_HPP
