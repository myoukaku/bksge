/**
 *	@file	equal.hpp
 *
 *	@brief	equal の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_EQUAL_HPP
#define BKSGE_FND_ALGORITHM_EQUAL_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief	2つの範囲を等値比較する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		BinaryPredicate
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		pred
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	BinaryPredicate pred);

/**
 *	@brief	2つの範囲を等値比較する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2);

/**
 *	@brief	2つの範囲を等値比較する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		BinaryPredicate
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		pred
 *
 *	@return		もしlast1 - first1 != last2 - first2 であれば、falseを返す。
 *				そうでない場合、[first1, last1)のイテレータi、[first2, last2)のイテレータjについて、
 *				pred(*i, *j) が全て満たされるのであればtrueを返す。
 *				そうでない場合はfalseを返す。
 *
 *	@complexity	もし InputIterator1 と InputIterator2 が共にランダムアクセスイテレータの要件を満たす場合で、
 *				かつ、last1 - first1 != last2 - first2 の場合、1 度も述語は適用されない。
 *				そうでない場合、最大で min(last1 - first1, last2 - first2) 回の述語が適用される。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	BinaryPredicate pred);

/**
 *	@brief		2つの範囲を等値比較する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *
 *	@return		もしlast1 - first1 != last2 - first2 であれば、falseを返す。
 *				そうでない場合、[first1, last1)のイテレータi、[first2, last2)のイテレータjについて、
 *				*i == *j が全て満たされるのであればtrueを返す。
 *				そうでない場合はfalseを返す。
 *
 *	@complexity	もし InputIterator1 と InputIterator2 が共にランダムアクセスイテレータの要件を満たす場合で、
 *				かつ、last1 - first1 != last2 - first2 の場合、1 度も比較は適用されない。
 *				そうでない場合、最大で min(last1 - first1, last2 - first2) 回の比較が適用される。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2);

}	// namespace algorithm

using algorithm::equal;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/equal_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_EQUAL_HPP
