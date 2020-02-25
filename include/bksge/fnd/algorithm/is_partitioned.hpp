/**
 *	@file	is_partitioned.hpp
 *
 *	@brief	is_partitioned の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_IS_PARTITIONED_HPP
#define BKSGE_FND_ALGORITHM_IS_PARTITIONED_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		与えられた範囲が条件によって区分化されているか判定する。
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	InputIteratorのvalue typeは Predicate の引数型へ変換可能でなければならない。
 *				つまり pred(*first) という式が有効でなければならない。
 *
 *	@return		[first,last) が空、 または [first,last) が pred によって区分化されているなら true 、
 *				そうでなければ false を返す。
 *				つまり、pred を満たす全ての要素が、pred を満たさない全ての要素より前に出現するなら true を返す。
 *
 *	@complexity	線形時間。最大で last - first 回 pred が適用される。
 */
template <
	typename InputIterator,
	typename Predicate,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
is_partitioned(InputIterator first, InputIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::is_partitioned;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/is_partitioned_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_IS_PARTITIONED_HPP
