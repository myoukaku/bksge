/**
 *	@file	merge_without_buffer.hpp
 *
 *	@brief	merge_without_buffer の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_MERGE_WITHOUT_BUFFER_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_MERGE_WITHOUT_BUFFER_HPP

#include <bksge/fnd/algorithm/iter_swap.hpp>
#include <bksge/fnd/algorithm/rotate.hpp>
#include <bksge/fnd/algorithm/detail/lower_bound.hpp>
#include <bksge/fnd/algorithm/detail/upper_bound.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/iterator/distance.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename BidirectionalIterator, typename Distance, typename Compare>
void merge_without_buffer(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	Distance len1,
	Distance len2,
	Compare comp)
{
	if (len1 == 0 || len2 == 0)
	{
		return;
	}

	if (len1 + len2 == 2)
	{
		if (comp(*middle, *first))
		{
			bksge::iter_swap(first, middle);
		}
		return;
	}

	auto first_cut = first;
	auto second_cut = middle;
	Distance len11 = 0;
	Distance len22 = 0;

	if (len1 > len2)
	{
		len11 = len1 / 2;
		bksge::advance(first_cut, len11);
		second_cut = detail::lower_bound(middle, last, *first_cut, comp);
		len22 = bksge::distance(middle, second_cut);
	}
	else
	{
		len22 = len2 / 2;
		bksge::advance(second_cut, len22);
		first_cut = detail::upper_bound(first, middle, *second_cut, comp);
		len11 = bksge::distance(first, first_cut);
	}

	auto new_middle = bksge::rotate(first_cut, middle, second_cut);
	detail::merge_without_buffer(first, first_cut, new_middle, len11, len22, comp);
	detail::merge_without_buffer(new_middle, second_cut, last, len1 - len11, len2 - len22, comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_MERGE_WITHOUT_BUFFER_HPP
