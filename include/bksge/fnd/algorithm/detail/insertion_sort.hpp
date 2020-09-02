/**
 *	@file	insertion_sort.hpp
 *
 *	@brief	insertion_sort の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_INSERTION_SORT_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_INSERTION_SORT_HPP

#include <bksge/fnd/algorithm/move_backward.hpp>
#include <bksge/fnd/algorithm/detail/unguarded_linear_insert.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	if (first == last)
	{
		return;
	}

	for (auto i = first + 1; i != last; ++i)
	{
		if (comp(*i, *first))
		{
			bksge::iter_value_t<RandomAccessIterator> val = bksge::move(*i);
			bksge::move_backward(first, i, i + 1);
			*first = bksge::move(val);
		}
		else
		{
			detail::unguarded_linear_insert(i, comp);
		}
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_INSERTION_SORT_HPP
