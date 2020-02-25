/**
 *	@file	remove_if.hpp
 *
 *	@brief	remove_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_REMOVE_IF_HPP
#define BKSGE_FND_ALGORITHM_REMOVE_IF_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		条件を満たす要素を取り除く
 *
 *	@tparam		ForwardIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	*first の型は MoveAssignable の要件を満たす必要がある
 *
 *	@return		有効な要素の末尾の次を指すイテレータを返す。
 *
 *	@effect		[first,last) 内にあるイテレータ i について、
 *				pred(*i) != false である要素を取り除き、有効な要素を範囲の前に寄せる。
 *
 *	@complexity	正確に last - first 回の述語の適用を行う
 *
 *	@note		有効な要素を範囲の前方に集める処理には、ムーブを使用する。
 *				取り除いた要素の先頭を指すイテレータをretとし、
 *				範囲[ret, last)の各要素には、有効な要素からムーブされた値が設定される。
 *				それらの値は、「有効だが未規定な値」となる。
 *
 *	@see	remove_if_erase
 */
template <
	typename ForwardIterator,
	typename Predicate,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
remove_if(ForwardIterator first, ForwardIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::remove_if;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/remove_if_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_REMOVE_IF_HPP
