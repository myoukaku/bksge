/**
 *	@file	fill.hpp
 *
 *	@brief	fill の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_FILL_HPP
#define BKSGE_FND_ALGORITHM_FILL_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された値を出力の範囲に書き込む
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	value は output iterator へ書き込み可能でなければならない
 *
 *	@effect		[first,last) 内の全ての要素に value を代入する
 *
 *	@complexity	正確に last - first 回の代入を行う
 */
template <typename ForwardIterator, typename T>
BKSGE_CXX14_CONSTEXPR void
fill(ForwardIterator first, ForwardIterator last, T const& value);

}	// namespace algorithm

using algorithm::fill;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/fill_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_FILL_HPP
