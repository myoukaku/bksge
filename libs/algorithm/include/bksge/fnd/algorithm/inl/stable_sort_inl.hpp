/**
 *	@file	stable_sort_inl.hpp
 *
 *	@brief	stable_sort の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_STABLE_SORT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_STABLE_SORT_INL_HPP

#include <bksge/fnd/algorithm/stable_sort.hpp>
#include <bksge/fnd/algorithm/detail/temporary_buffer.hpp>
#include <bksge/fnd/algorithm/detail/inplace_stable_sort.hpp>
#include <bksge/fnd/algorithm/detail/stable_sort_adaptive.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/distance.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline void stable_sort(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	using value_t = bksge::iter_value_t<RandomAccessIterator>;
	using difference_t = bksge::iter_difference_t<RandomAccessIterator>;

	using TmpBuf = detail::temporary_buffer<RandomAccessIterator, value_t>;
	TmpBuf buf(first, bksge::distance(first, last));

	if (buf.begin() == 0)
	{
		detail::inplace_stable_sort(first, last, comp);
	}
	else
	{
		detail::stable_sort_adaptive(first, last, buf.begin(), difference_t(buf.size()), comp);
	}
}

}	// namespace detail

template <typename RandomAccessIterator>
inline void
stable_sort(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	bksge::algorithm::stable_sort(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline void
stable_sort(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	detail::stable_sort(first, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_STABLE_SORT_INL_HPP
