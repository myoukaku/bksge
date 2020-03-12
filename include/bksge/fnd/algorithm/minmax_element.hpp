/**
 *	@file	minmax_element.hpp
 *
 *	@brief	minmax_element の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_MINMAX_ELEMENT_HPP
#define BKSGE_FND_ALGORITHM_MINMAX_ELEMENT_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		[first, last)の範囲において、最小要素を指すイテレータと最大要素を指すイテレータの組を取得する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		operator< を比較基準とした際の、最小の要素を指すイテレータを first、
 *				最大の要素を指すイテレータを second に持つ pair オブジェクトを返す。
 *				ただし、first == last の場合には、make_pair(first, first)を返す。
 *
 *	@complexity	n を範囲の要素数とする場合、max(3(n / 2) - 1, 0) 回の述語適用を行う。
 *
 *	@note		最小の要素が複数ある場合、min_element と同様、
 *				最も左側（first に近い方）にある要素を指すイテレータを返す。
 *				一方、最大の要素が複数ある場合、max_element と異なり、
 *				最も右側（last に近い方）にあるイテレータを返す。
 *
 *				最小の要素と最大の要素の両方が必要な場合には、
 *				min_element と max_element をそれぞれ呼び出すよりも本関数を呼び出した方が、
 *				計算量の点で効率的である。
 *				ただし、上記の通り最大の要素に関しては max_element と結果が異なる可能性があるため、
 *				注意する必要がある。
 */
template <
	typename ForwardIterator,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR std::pair<ForwardIterator, ForwardIterator>
minmax_element(ForwardIterator first, ForwardIterator last);

/**
 *	@brief		[first, last)の範囲において、最小要素を指すイテレータと最大要素を指すイテレータの組を取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		comp を比較基準とした際の、最小の要素を指すイテレータを first、
 *				最大の要素を指すイテレータを second に持つ pair オブジェクトを返す。
 *				ただし、first == last の場合には、make_pair(first, first)を返す。
 *
 *	@complexity	n を範囲の要素数とする場合、max(3(n / 2) - 1, 0) 回の述語適用を行う。
 *
 *	@note		comp は 2 引数の関数オブジェクトで、
 *				1 番目の引数が 2 番目の引数「より小さい」場合に true を、
 *				そうでない場合に false を返すものとして扱われる。
 *
 *				最小の要素が複数ある場合、min_element と同様、
 *				最も左側（first に近い方）にある要素を指すイテレータを返す。
 *				一方、最大の要素が複数ある場合、max_element と異なり、
 *				最も右側（last に近い方）にあるイテレータを返す。
 *
 *				最小の要素と最大の要素の両方が必要な場合には、
 *				min_element と max_element をそれぞれ呼び出すよりも本関数を呼び出した方が、
 *				計算量の点で効率的である。
 *				ただし、上記の通り最大の要素に関しては max_element と結果が異なる可能性があるため、
 *				注意する必要がある。
 */
template <
	typename ForwardIterator,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR std::pair<ForwardIterator, ForwardIterator>
minmax_element(ForwardIterator first, ForwardIterator last, Compare comp);

}	// namespace algorithm

using algorithm::minmax_element;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/minmax_element_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_MINMAX_ELEMENT_HPP
