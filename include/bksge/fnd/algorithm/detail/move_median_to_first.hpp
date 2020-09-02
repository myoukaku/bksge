/**
 *	@file	move_median_to_first.hpp
 *
 *	@brief	move_median_to_first の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_MOVE_MEDIAN_TO_FIRST_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_MOVE_MEDIAN_TO_FIRST_HPP

#include <bksge/fnd/algorithm/iter_swap.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Iterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
move_median_to_first(
	Iterator result,
	Iterator a,
	Iterator b,
	Iterator c,
	Compare comp)
{
	if (comp(*a, *b))
	{
		if (comp(*b, *c))
		{
			bksge::iter_swap(result, b);
		}
		else if (comp(*a, *c))
		{
			bksge::iter_swap(result, c);
		}
		else
		{
			bksge::iter_swap(result, a);
		}
	}
	else if (comp(*a, *c))
	{
		bksge::iter_swap(result, a);
	}
	else if (comp(*b, *c))
	{
		bksge::iter_swap(result, c);
	}
	else
	{
		bksge::iter_swap(result, b);
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_MOVE_MEDIAN_TO_FIRST_HPP
