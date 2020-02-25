/**
 *	@file	unique.hpp
 *
 *	@brief	unique の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_UNIQUE_HPP
#define BKSGE_FND_ALGORITHM_UNIQUE_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		重複した要素を取り除く
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	*first は MoveAssignable の要求を満たす必要がある。
 *				比較関数は equivalence relation でなければならない。
 *
 *	@effect		[first,last) が空の範囲でない場合、
 *				[first + 1,last) 内のイテレータ i について、
 *				*(i - 1) == *i による等値の比較によって連続したグループに分け、
 *				それぞれのグループの先頭以外を削除する。
 *
 *	@return		結果の範囲の終端を返す
 *
 *	@complexity	[first,last) が空の範囲でない場合、
 *				正確に last - first - 1 回の比較を行う
 */
template <
	typename ForwardIterator,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
unique(ForwardIterator first, ForwardIterator last);

/**
 *	@brief		重複した要素を取り除く
 *
 *	@tparam		ForwardIterator
 *	@tparam		BinaryPredicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	*first は MoveAssignable の要求を満たす必要がある。
 *				比較関数は equivalence relation でなければならない。
 *
 *	@effect		[first,last) が空の範囲でない場合、
 *				[first + 1,last) 内のイテレータ i について、
 *				pred(*(i - 1), *i) != false による等値の比較によって連続したグループに分け、
 *				それぞれのグループの先頭以外を削除する。
 *
 *	@return		結果の範囲の終端を返す
 *
 *	@complexity	[first,last) が空の範囲でない場合、
 *				正確に last - first - 1 回の述語の適用を行う
 */
template <
	typename ForwardIterator,
	typename BinaryPredicate,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
unique(ForwardIterator first, ForwardIterator last, BinaryPredicate pred);

}	// namespace algorithm

using algorithm::unique;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/unique_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_UNIQUE_HPP
