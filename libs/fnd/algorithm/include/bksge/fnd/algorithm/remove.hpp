/**
 *	@file	remove.hpp
 *
 *	@brief	remove の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_REMOVE_HPP
#define BKSGE_FND_ALGORITHM_REMOVE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された要素を取り除く
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	*first の型は MoveAssignable の要件を満たす必要がある
 *
 *	@return		有効な要素の末尾の次を指すイテレータを返す。
 *
 *	@effect		[first,last) 内にあるイテレータ i について、
 *				*i == value である要素を取り除き、有効な要素を範囲の前に寄せる。
 *
 *	@complexity	正確に last - first 回の比較を行う
 *
 *	@note		有効な要素を範囲の前方に集める処理には、ムーブを使用する。
 *				取り除いた要素の先頭を指すイテレータをretとし、
 *				範囲[ret, last)の各要素には、有効な要素からムーブされた値が設定される。
 *				それらの値は、「有効だが未規定な値」となる。
 *
 *	@see	remove_erase
 */
template <typename ForwardIterator, typename T>
BKSGE_CXX14_CONSTEXPR ForwardIterator
remove(ForwardIterator first, ForwardIterator last, T const& value);

}	// namespace algorithm

using algorithm::remove;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/remove_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_REMOVE_HPP
