/**
 *	@file	pop_heap_inl.hpp
 *
 *	@brief	pop_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_POP_HEAP_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_POP_HEAP_INL_HPP

#include <bksge/fnd/algorithm/pop_heap.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Compare, typename RandomAccessIterator, typename DifferenceType>
inline BKSGE_CXX14_CONSTEXPR void
sift_down(
	RandomAccessIterator first,
	RandomAccessIterator /*last*/,
	Compare comp,
	DifferenceType len,
	RandomAccessIterator start)
{
	using value_type = bksge::iter_value_t<RandomAccessIterator>;

	// left-child of start is at 2 * start + 1
	// right-child of start is at 2 * start + 2
	auto child = start - first;

	if (len < 2 || (len - 2) / 2 < child)
	{
		return;
	}

	child = 2 * child + 1;
	auto child_i = first + child;

	if ((child + 1) < len && comp(*child_i, *(child_i + 1)))
	{
		// right-child exists and is greater than left-child
		++child_i;
		++child;
	}

	// check if we are in heap-order
	if (comp(*child_i, *start))
	{
		// we are, start is larger than it's largest child
		return;
	}

	value_type top(bksge::move(*start));

	do
	{
		// we are not in heap-order, swap the parent with it's largest child
		*start = bksge::move(*child_i);
		start = child_i;

		if ((len - 2) / 2 < child)
		{
			break;
		}

		// recompute the child based off of the updated parent
		child = 2 * child + 1;
		child_i = first + child;

		if ((child + 1) < len && comp(*child_i, *(child_i + 1)))
		{
			// right-child exists and is greater than left-child
			++child_i;
			++child;
		}

		// check if we are in heap-order
	}
	while (!comp(*child_i, top));

	*start = bksge::move(top);
}

template <typename Compare, typename RandomAccessIterator, typename DifferenceType>
inline BKSGE_CXX14_CONSTEXPR void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp,
	DifferenceType len)
{
	if (len > 1)
	{
		swap(*first, *--last);
		detail::sift_down<Compare>(first, last, comp, len - 1, first);
	}
}

}	// namespace detail

template <typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	bksge::algorithm::pop_heap(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	detail::pop_heap<CompRef>(first, last, comp, last - first);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_POP_HEAP_INL_HPP
