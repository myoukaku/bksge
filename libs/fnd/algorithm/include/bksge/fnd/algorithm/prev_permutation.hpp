﻿/**
 *	@file	prev_permutation.hpp
 *
 *	@brief	prev_permutation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_PREV_PERMUTATION_HPP
#define BKSGE_FND_ALGORITHM_PREV_PERMUTATION_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		前の順列を生成する
 *
 *	@tparam		BidirectionalIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	BidriectionalIteratorがValueSwappableの要件を満たしていること。
 *
 *	@effect		[first, last)の範囲を前の順列に変換する。
 *				operator<によって辞書順に並んでいる全ての順列の集合があると仮定すると、
 *				前の順列が発見される。
 *
 *	@return		前の順列が存在する場合はtrueを返し、そうでなければfalseを返す。
 *
 *	@complexity	高々(last - first)/2回の要素の交換
 */
template <typename BidirectionalIterator>
bool
prev_permutation(BidirectionalIterator first, BidirectionalIterator last);

/**
 *	@brief		前の順列を生成する
 *
 *	@tparam		BidirectionalIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	BidriectionalIteratorがValueSwappableの要件を満たしていること。
 *
 *	@effect		[first, last)の範囲を前の順列に変換する。
 *				compによって辞書順に並んでいる全ての順列の集合があると仮定すると、
 *				前の順列が発見される。
 *
 *	@return		前の順列が存在する場合はtrueを返し、そうでなければfalseを返す。
 *
 *	@complexity	高々(last - first)/2回の要素の交換
 */
template <typename BidirectionalIterator, typename Compare>
bool
prev_permutation(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Compare comp);

}	// namespace algorithm

using algorithm::prev_permutation;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/prev_permutation_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_PREV_PERMUTATION_HPP
