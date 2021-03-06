﻿/**
 *	@file	adjacent_find_inl.hpp
 *
 *	@brief	adjacent_find の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_ADJACENT_FIND_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_ADJACENT_FIND_INL_HPP

#include <bksge/fnd/algorithm/adjacent_find.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename ForwardIterator>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
adjacent_find(ForwardIterator first, ForwardIterator last)
{
	return bksge::adjacent_find(
		first, last, bksge::equal_to<>());
}

template <typename ForwardIterator, typename BinaryPredicate>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
adjacent_find(
	ForwardIterator first,
	ForwardIterator last,
	BinaryPredicate pred)
{
	if (first != last)
	{
		auto next_it = first;

		while (++next_it != last)
		{
			if (pred(*first, *next_it))
			{
				return first;
			}

			first = next_it;
		}
	}

	return last;
}

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_ADJACENT_FIND_INL_HPP
