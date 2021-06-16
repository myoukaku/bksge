/**
 *	@file	inplace_merge_inl.hpp
 *
 *	@brief	inplace_merge の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_INPLACE_MERGE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_INPLACE_MERGE_INL_HPP

#include <bksge/fnd/algorithm/inplace_merge.hpp>
#include <bksge/fnd/algorithm/detail/temporary_buffer.hpp>
#include <bksge/fnd/algorithm/detail/merge_without_buffer.hpp>
#include <bksge/fnd/algorithm/detail/merge_adaptive.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/functional/less.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename BidirectionalIterator, typename Compare>
inline void
inplace_merge(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	Compare comp)
{
	using value_t = bksge::iter_value_t<BidirectionalIterator>;
	using difference_t = bksge::iter_difference_t<BidirectionalIterator>;

	if (first == middle || middle == last)
	{
		return;
	}

	const difference_t len1 = bksge::distance(first, middle);
	const difference_t len2 = bksge::distance(middle, last);

	typedef detail::temporary_buffer<BidirectionalIterator, value_t> TmpBuf;
	TmpBuf buf(first, len1 + len2);

	if (buf.begin() == 0)
	{
		detail::merge_without_buffer(first, middle, last, len1, len2, comp);
	}
	else
	{
		detail::merge_adaptive(first, middle, last, len1, len2, buf.begin(), difference_t(buf.size()), comp);
	}
}

}	// namespace detail

template <typename BidirectionalIterator>
inline void
inplace_merge(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last)
{
	return bksge::algorithm::inplace_merge(first, middle, last, bksge::less<>());
}

template <typename BidirectionalIterator, typename Compare>
inline void
inplace_merge(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	Compare comp)
{
	return detail::inplace_merge(first, middle, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_INPLACE_MERGE_INL_HPP
