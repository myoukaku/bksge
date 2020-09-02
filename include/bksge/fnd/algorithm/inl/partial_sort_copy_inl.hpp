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
#include <bksge/fnd/algorithm/detail/make_heap.hpp>
#include <bksge/fnd/algorithm/detail/adjust_heap.hpp>
#include <bksge/fnd/algorithm/detail/sort_heap.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename InputIterator, typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator
partial_sort_copy(
	InputIterator first,
	InputIterator last,
	RandomAccessIterator result_first,
	RandomAccessIterator result_last,
	Compare comp)
{
	using input_value_t = bksge::iter_value_t<InputIterator>;
	using difference_t = bksge::iter_difference_t<RandomAccessIterator>;

	if (result_first == result_last)
	{
		return result_last;
	}

	auto result_real_last = result_first;
	while (first != last && result_real_last != result_last)
	{
		*result_real_last = *first;
		++result_real_last;
		++first;
	}

	detail::make_heap(result_first, result_real_last, comp);

	while (first != last)
	{
		if (comp(*first, *result_first))
		{
			detail::adjust_heap(
				result_first,
				difference_t(0),
				difference_t(result_real_last - result_first),
				input_value_t(*first),
				comp);
		}

		++first;
	}

	detail::sort_heap(result_first, result_real_last, comp);
	return result_real_last;
}

}	// namespace detail

template <typename InputIterator, typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator
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
	typename Compare
>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator
partial_sort_copy(
	InputIterator first,
	InputIterator last,
	RandomAccessIterator result_first,
	RandomAccessIterator result_last,
	Compare comp)
{
	return detail::partial_sort_copy(
		first, last, result_first, result_last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_COPY_INL_HPP
