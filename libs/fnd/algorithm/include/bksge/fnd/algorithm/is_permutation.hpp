/**
 *	@file	is_permutation.hpp
 *
 *	@brief	is_permutation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_IS_PERMUTATION_HPP
#define BKSGE_FND_ALGORITHM_IS_PERMUTATION_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		first2 で始まる範囲を並べ替えたものが、[first1, last1) の範囲と一致するか判定する。
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *	@tparam		BinaryPredicate
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		pred
 *
 *	@require	decltype(*first1) と decltype(*first2) の型が同じであること。
 *				BinaryPredicate は等価関係を持っていること。
 *
 *	@return		last2 が与えられている形式の場合、last1 - first1 != last2 - first2 であれば false を返す。
 *				そうでなければ、[first1, last1) の範囲と
 *				[first2, first2 + (last1 - first1)) の範囲を並び変えたもので、
 *				equal(first1, last1, first2)、あるいは
 *				equal(first1, last1, first2, pred) が true を返すようなものがあれば true を、
 *				そうでなければ false を返す。
 *				なお、実際に並べ替えが行われるわけではない。
 *
 *	@complexity	last2 が与えられている形式の場合、
 *				ForwardIterator1 と ForwardIterator2 がどちらもランダムアクセスイテレータの要件を満たし、
 *				かつ last1 - first1 != last2 - first2 であれば 1 度も述語の適用を行わない。
 *				そうでなければ、equal(first1, last1, first2, last2) == true
 *				もしくは equal(first1, last1, first2, last2, pred) == true の場合
 *				（last2 が無い形式の場合、equal も last2 の無い形式で置き換える）、
 *				distance(first1, last1) 回の述語適用で完了する。
 *				そうでなければ、distance(first1, last1) をNとした場合に最悪O(N^2)回の述語適用で完了する。
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2);

/**
 *
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2,
	BinaryPredicate pred);

/**
 *
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2);

/**
 *
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred);

}	// namespace algorithm

using algorithm::is_permutation;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/is_permutation_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_IS_PERMUTATION_HPP
