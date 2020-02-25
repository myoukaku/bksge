/**
 *	@file	partial_sort_inl.hpp
 *
 *	@brief	partial_sort の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_INL_HPP

#include <bksge/fnd/algorithm/partial_sort.hpp>
#include <bksge/fnd/algorithm/make_heap.hpp>
#include <bksge/fnd/algorithm/pop_heap.hpp>
#include <bksge/fnd/algorithm/sort_heap.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Compare, typename RandomAccessIterator>
inline void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	Compare comp)
{
	detail::make_heap<Compare>(first, middle, comp);

	auto const len = middle - first;
	
	for (auto i = middle; i != last; ++i)
	{
		if (comp(*i, *first))
		{
			swap(*i, *first);
			detail::sift_down<Compare>(first, middle, comp, len, first);
		}
	}

	detail::sort_heap<Compare>(first, middle, comp);
}

}	// namespace detail

template <typename RandomAccessIterator, typename>
inline void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last)
{
	return bksge::algorithm::partial_sort(
		first, middle, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare, typename>
inline void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	detail::partial_sort<CompRef>(
		first, middle, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_INL_HPP
