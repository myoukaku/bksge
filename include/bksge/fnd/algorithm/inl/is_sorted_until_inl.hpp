﻿/**
 *	@file	is_sorted_until_inl.hpp
 *
 *	@brief	is_sorted_until の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_IS_SORTED_UNTIL_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_IS_SORTED_UNTIL_INL_HPP

#include <bksge/fnd/algorithm/is_sorted_until.hpp>
#include <bksge/fnd/functional/less.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
is_sorted_until(
	ForwardIterator first,
	ForwardIterator last)
{
	return bksge::algorithm::is_sorted_until(first, last, bksge::less<>());
}

template <typename ForwardIterator, typename Compare, typename>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
is_sorted_until(
	ForwardIterator first,
	ForwardIterator last,
	Compare comp)
{
	if (first != last)
	{
		auto next = first;

		while (++next != last)
		{
			if (comp(*next, *first))
			{
				return next;
			}

			first = next;
		}
	}

	return last;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_IS_SORTED_UNTIL_INL_HPP
