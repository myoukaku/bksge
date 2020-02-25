/**
 *	@file	partial_sort_copy_inl.hpp
 *
 *	@brief	partial_sort_copy の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_COPY_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_COPY_INL_HPP

#include <bksge/fnd/algorithm/partial_sort_copy.hpp>
#include <bksge/fnd/algorithm/make_heap.hpp>
#include <bksge/fnd/algorithm/pop_heap.hpp>
#include <bksge/fnd/algorithm/sort_heap.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename Compare,
	typename InputIterator,
	typename RandomAccessIterator
>
inline RandomAccessIterator
partial_sort_copy(
	InputIterator first,
	InputIterator last,
	RandomAccessIterator result_first,
	RandomAccessIterator result_last,
	Compare comp)
{
	auto r = result_first;

	if (r != result_last)
	{
		for (; first != last && r != result_last; ++first, ++r)
		{
			*r = *first;
		}

		detail::make_heap<Compare>(result_first, r, comp);
		
		auto const len = r - result_first;
		
		for (; first != last; ++first)
		{
			if (comp(*first, *result_first))
			{
				*result_first = *first;
				detail::sift_down<Compare>(
					result_first, r, comp, len, result_first);
			}
		}

		detail::sort_heap<Compare>(result_first, r, comp);
	}

	return r;
}

}	// namespace detail

template <
	typename InputIterator,
	typename RandomAccessIterator,
	typename
>
inline RandomAccessIterator
partial_sort_copy(
	InputIterator first,
	InputIterator last,
	RandomAccessIterator result_first,
	RandomAccessIterator result_last)
{
	return bksge::algorithm::partial_sort_copy(
		first, last, result_first, result_last, bksge::less<>());
}

template <
	typename InputIterator,
	typename RandomAccessIterator,
	typename Compare,
	typename
>
inline RandomAccessIterator
partial_sort_copy(
	InputIterator first,
	InputIterator last,
	RandomAccessIterator result_first,
	RandomAccessIterator result_last,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	return detail::partial_sort_copy<CompRef>(
		first, last, result_first, result_last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_COPY_INL_HPP
