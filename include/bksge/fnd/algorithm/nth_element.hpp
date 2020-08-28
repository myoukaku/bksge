/**
 *	@file	nth_element.hpp
 *
 *	@brief	nth_element の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_NTH_ELEMENT_HPP
#define BKSGE_FND_ALGORITHM_NTH_ELEMENT_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		基準となる要素よりも小さい要素が前に来るよう並べ替える。
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		nth
 *	@param		last
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		nth_element() を呼び出した後、nth が指している位置の要素は、
 *				全ての範囲がソートされた場合の位置にある要素になる。
 *				そして、[first,nth) にあるイテレータ i と、[nth,last) にあるイテレータ j について、
 *				!(*j < *i) になる。
 *
 *	@complexity	平均で線形時間
 */
template <typename RandomAccessIterator>
BKSGE_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last);

/**
 *	@brief		基準となる要素よりも小さい要素が前に来るよう並べ替える。
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		nth
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		nth_element() を呼び出した後、nth が指している位置の要素は、
 *				全ての範囲がソートされた場合の位置にある要素になる。
 *				そして、[first,nth) にあるイテレータ i と、[nth,last) にあるイテレータ j について、
 *				comp(*j, *i) == false になる。
 *
 *	@complexity	平均で線形時間
 */
template <typename RandomAccessIterator, typename Compare>
BKSGE_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Compare comp);

}	// namespace algorithm

using algorithm::nth_element;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/nth_element_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_NTH_ELEMENT_HPP
