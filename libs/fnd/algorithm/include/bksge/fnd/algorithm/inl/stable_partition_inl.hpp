/**
 *	@file	stable_partition_inl.hpp
 *
 *	@brief	stable_partition の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_STABLE_PARTITION_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_STABLE_PARTITION_INL_HPP

#include <bksge/fnd/algorithm/stable_partition.hpp>
#include <bksge/fnd/algorithm/find_if_not.hpp>
#include <bksge/fnd/algorithm/detail/temporary_buffer.hpp>
#include <bksge/fnd/algorithm/detail/stable_partition_adaptive.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/distance.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename ForwardIterator, typename Predicate>
inline ForwardIterator
stable_partition(ForwardIterator first, ForwardIterator last, Predicate pred)
{
	first = bksge::find_if_not(first, last, pred);

	if (first == last)
	{
		return first;
	}

	using value_t = bksge::iter_value_t<ForwardIterator>;
	using difference_t = bksge::iter_difference_t<ForwardIterator>;

	using TmpBuf = detail::temporary_buffer<ForwardIterator, value_t>;
	TmpBuf buf(first, bksge::distance(first, last));

	return
		detail::stable_partition_adaptive(
			first,
			last,
			pred,
			difference_t(buf.requested_size()),
			buf.begin(),
			difference_t(buf.size()));
}

}	// namespace detail

template <typename BidirectionalIterator, typename Predicate>
inline BidirectionalIterator
stable_partition(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Predicate pred)
{
	return detail::stable_partition(first, last, pred);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_STABLE_PARTITION_INL_HPP
