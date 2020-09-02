/**
 *	@file	sort_inl.hpp
 *
 *	@brief	sort の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_SORT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_SORT_INL_HPP

#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/algorithm/detail/lg.hpp>
#include <bksge/fnd/algorithm/detail/insertion_sort.hpp>
#include <bksge/fnd/algorithm/detail/unguarded_linear_insert.hpp>
#include <bksge/fnd/algorithm/detail/unguarded_partition_pivot.hpp>
#include <bksge/fnd/algorithm/detail/partial_sort.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
unguarded_insertion_sort(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	for (auto i = first; i != last; ++i)
	{
		detail::unguarded_linear_insert(i, comp);
	}
}

namespace sort_detail
{

enum { s_threshold = 16 };

}	// namespace sort_detail

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
final_insertion_sort(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	if (last - first > int(sort_detail::s_threshold))
	{
		detail::insertion_sort(first, first + int(sort_detail::s_threshold), comp);
		detail::unguarded_insertion_sort(first + int(sort_detail::s_threshold), last, comp);
	}
	else
	{
		detail::insertion_sort(first, last, comp);
	}
}

template <typename RandomAccessIterator, typename Size, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
introsort_loop(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Size depth_limit,
	Compare comp)
{
	while (last - first > int(sort_detail::s_threshold))
	{
		if (depth_limit == 0)
		{
			detail::partial_sort(first, last, last, comp);
			return;
		}

		--depth_limit;
		auto cut = detail::unguarded_partition_pivot(first, last, comp);
		detail::introsort_loop(cut, last, depth_limit, comp);
		last = cut;
	}
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	if (first != last)
	{
		detail::introsort_loop(first, last, detail::lg(last - first) * 2, comp);
		detail::final_insertion_sort(first, last, comp);
	}
}

}	// namespace detail

template <typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR void
sort(RandomAccessIterator first, RandomAccessIterator last)
{
	return bksge::algorithm::sort(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	detail::sort(first, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_SORT_INL_HPP
