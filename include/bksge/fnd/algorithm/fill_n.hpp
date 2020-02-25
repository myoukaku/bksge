/**
 *	@file	fill_n.hpp
 *
 *	@brief	fill_n の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_FILL_N_HPP
#define BKSGE_FND_ALGORITHM_FILL_N_HPP

#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された値を出力の範囲に指定された個数書き込む
 *
 *	@tparam		OutputIterator
 *	@tparam		Size
 *	@tparam		T
 *
 *	@param		first
 *	@param		n
 *	@param		value
 *
 *	@require	value は output iterator へ書き込み可能でなければならない
 *				Size は integral type に変換可能でなければならない
 *
 *	@return		n が 1 以上の場合は first + n、そうでない場合は first を返す。
 *
 *	@effect		n が 1 以上の場合は [first,first + n) 内の全ての要素に value を代入し、
 *				そうでない場合は何もしない。
 *
 *	@complexity	n が 1 以上の場合は n 回、そうでない場合は 0 回の代入を行う。
 */
template <
	typename OutputIterator,
	typename Size,
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_iterator<OutputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR OutputIterator
fill_n(OutputIterator first, Size n, T const& value);

}	// namespace algorithm

using algorithm::fill_n;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/fill_n_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_FILL_N_HPP
