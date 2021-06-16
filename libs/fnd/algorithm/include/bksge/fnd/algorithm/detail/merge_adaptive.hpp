/**
 *	@file	merge_adaptive.hpp
 *
 *	@brief	merge_adaptive の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_MERGE_ADAPTIVE_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_MERGE_ADAPTIVE_HPP

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/algorithm/detail/move_merge_adaptive.hpp>
#include <bksge/fnd/algorithm/detail/move_merge_adaptive_backward.hpp>
#include <bksge/fnd/algorithm/detail/lower_bound.hpp>
#include <bksge/fnd/algorithm/detail/upper_bound.hpp>
#include <bksge/fnd/algorithm/detail/rotate_adaptive.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/iterator/distance.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename BidirectionalIterator,
	typename Distance,
	typename Pointer,
	typename Compare
>
void merge_adaptive(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	Distance len1,
	Distance len2,
	Pointer buffer,
	Distance buffer_size,
	Compare comp)
{
	if (len1 <= len2 && len1 <= buffer_size)
	{
		Pointer buffer_end = bksge::move(first, middle, buffer);
		detail::move_merge_adaptive(buffer, buffer_end, middle, last, first, comp);
	}
	else if (len2 <= buffer_size)
	{
		Pointer buffer_end = bksge::move(middle, last, buffer);
		detail::move_merge_adaptive_backward(first, middle, buffer, buffer_end, last, comp);
	}
	else
	{
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

		auto new_middle = detail::rotate_adaptive(
			first_cut, middle, second_cut,
			len1 - len11, len22, buffer,
			buffer_size);
		detail::merge_adaptive(first, first_cut, new_middle, len11,
			len22, buffer, buffer_size, comp);
		detail::merge_adaptive(new_middle, second_cut, last,
			len1 - len11,
			len2 - len22, buffer,
			buffer_size, comp);
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_MERGE_ADAPTIVE_HPP
