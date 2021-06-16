/**
 *	@file	partition_inl.hpp
 *
 *	@brief	partition の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_PARTITION_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_PARTITION_INL_HPP

#include <bksge/fnd/algorithm/partition.hpp>
#include <bksge/fnd/iterator/iterator_category.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Predicate, typename ForwardIterator>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
partition(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred,
	bksge::forward_iterator_tag*)
{
	for (;;)
	{
		if (first == last)
		{
			return first;
		}

		if (!pred(*first))
		{
			break;
		}

		++first;
	}

	for (auto p = first; ++p != last;)
	{
		if (pred(*p))
		{
			swap(*first, *p);
			++first;
		}
	}

	return first;
}

template <typename Predicate, typename BidirectionalIterator>
inline BKSGE_CXX14_CONSTEXPR BidirectionalIterator
partition(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Predicate pred,
	bksge::bidirectional_iterator_tag*)
{
	for (;;)
	{
		for (;;)
		{
			if (first == last)
			{
				return first;
			}

			if (!pred(*first))
			{
				break;
			}

			++first;
		}
		do
		{
			if (first == --last)
			{
				return first;
			}
		}
		while (!pred(*last));

		swap(*first, *last);
		++first;
	}
}

}	// namespace detail

template <typename ForwardIterator, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
partition(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred)
{
	using Category = bksge::iterator_category<ForwardIterator>*;
	return bksge::algorithm::detail::partition(
		first, last, pred, Category());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PARTITION_INL_HPP
