/**
 *	@file	mismatch.hpp
 *
 *	@brief	mismatch の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_MISMATCH_HPP
#define BKSGE_FND_ALGORITHM_MISMATCH_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		2つのシーケンスが一致していない場所を検索する
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
 *	@return		last2が渡されなかった場合は、last2 = first2 + (last1 - first1)とする。
 *				[first1,last1) 内にあるイテレータ i と、
 *				j == first2 + (i - first1) であるイテレータ j について、
 *				jが範囲[first2, last2)に含まれており、
 *				!(*i == *j) もしくは pred(*i, *j) == false であるような、最初のイテレータのペアを返す。
 *				そのようなイテレータが見つからなかった場合は
 *				last1 と first2 + (last1 - first1) のペアを返す。
 *
 *	@complexity	最大で last1 - first1 回の対応する比較もしくは述語が適用される。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR bksge::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2);

/**
 *	@overload
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
BKSGE_CXX14_CONSTEXPR bksge::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	BinaryPredicate pred);

/**
 *	@overload
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR bksge::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2);

/**
 *	@overload
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
BKSGE_CXX14_CONSTEXPR bksge::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	BinaryPredicate pred);

}	// namespace algorithm

using algorithm::mismatch;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/mismatch_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_MISMATCH_HPP
