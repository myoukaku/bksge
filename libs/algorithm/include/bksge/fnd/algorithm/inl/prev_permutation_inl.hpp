/**
 *	@file	prev_permutation_inl.hpp
 *
 *	@brief	prev_permutation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_PREV_PERMUTATION_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_PREV_PERMUTATION_INL_HPP

#include <bksge/fnd/algorithm/prev_permutation.hpp>
#include <bksge/fnd/algorithm/reverse.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Compare, typename BidirectionalIterator>
inline bool
prev_permutation(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Compare comp)
{
	auto i = last;

	if (first == last || first == --i)
	{
		return false;
	}

	for (;;)
	{
		auto ip1 = i;

		if (comp(*ip1, *--i))
		{
			auto j = last;

			while (!comp(*--j, *i))
			{
				;
			}

			swap(*i, *j);
			bksge::reverse(ip1, last);
			return true;
		}

		if (i == first)
		{
			bksge::reverse(first, last);
			return false;
		}
	}
}

}	// namespace detail

template <typename BidirectionalIterator>
inline bool
prev_permutation(
	BidirectionalIterator first,
	BidirectionalIterator last)
{
	return bksge::algorithm::prev_permutation(
		first, last, bksge::less<>());
}

template <typename BidirectionalIterator, typename Compare>
inline bool
prev_permutation(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	return detail::prev_permutation<CompRef>(first, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PREV_PERMUTATION_INL_HPP
