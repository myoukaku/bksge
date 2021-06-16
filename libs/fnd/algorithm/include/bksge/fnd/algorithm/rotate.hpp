/**
 *	@file	rotate.hpp
 *
 *	@brief	rotate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_ROTATE_HPP
#define BKSGE_FND_ALGORITHM_ROTATE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		要素の並びを回転させる。
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *
 *	@require	[first,middle) と [middle,last) は有効な範囲である必要がある。
 *				ForwardIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		0 以上 last - first 未満の整数 i について、
 *				first + i の要素を first + (i + (last - middle)) % (last - first) の位置へ移動させる。
 *
 *	@return		first + (last - middle)
 *
 *	@complexity	最大で last - first 回 swap する。
 *
 *	@note		これは左への回転である
 */
template <typename ForwardIterator>
ForwardIterator
rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last);
	
}	// namespace algorithm

using algorithm::rotate;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/rotate_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_ROTATE_HPP
