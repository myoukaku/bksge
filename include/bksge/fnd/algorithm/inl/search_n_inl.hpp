/**
 *	@file	search_n_inl.hpp
 *
 *	@brief	search_n の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_SEARCH_N_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_SEARCH_N_INL_HPP

#include <bksge/fnd/algorithm/search_n.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/iterator/iterator_category.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename BinaryPredicate,
	typename ForwardIterator,
	typename Size,
	typename T
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
search_n(
	ForwardIterator first,
	ForwardIterator last,
	Size count,
	T const& value,
	BinaryPredicate pred,
	std::forward_iterator_tag*)
{
	if (count <= 0)
	{
		return first;
	}

	for (;;)
	{
		// Find first element in sequence that matchs value, with a mininum of loop checks
		for (;;)
		{
			if (first == last)  // return last if no element matches value
			{
				return last;
			}

			if (pred(*first, value))
			{
				break;
			}

			++first;
		}

		// *first matches value, now match elements after here
		auto m = first;
		Size c(0);

		for (;;)
		{
			// If pattern exhausted, first is the answer (works for 1 element pattern)
			if (++c == count)
			{
				return first;
			}

			// Otherwise if source exhaused, pattern not found
			if (++m == last)
			{
				return last;
			}

			// if there is a mismatch, restart with a new first
			if (!pred(*m, value))
			{
				first = m;
				++first;
				break;
			}  // else there is a match, check next elements
		}
	}
}

template <
	typename BinaryPredicate,
	typename RandomAccessIterator,
	typename Size,
	typename T
>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator
search_n(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Size count,
	T const& value,
	BinaryPredicate pred,
	std::random_access_iterator_tag*)
{
	if (count <= 0)
	{
		return first;
	}

	auto const len = static_cast<Size>(last - first);
	if (len < count)
	{
		return last;
	}

	// Start of pattern match can't go beyond here
	auto const s = last - (count - 1);

	for (;;)
	{
		// Find first element in sequence that matchs value, with a mininum of loop checks
		for (;;)
		{
			if (first >= s)  // return last if no element matches value
			{
				return last;
			}

			if (pred(*first, value))
			{
				break;
			}

			++first;
		}

		// *first matches value, now match elements after here
		auto m = first;
		Size c(0);

		for (;;)
		{
			// If pattern exhausted, first is the answer (works for 1 element pattern)
			if (++c == count)
			{
				return first;
			}

			++m;	// no need to check range on m because s guarantees we have enough source

			// if there is a mismatch, restart with a new first
			if (!pred(*m, value))
			{
				first = m;
				++first;
				break;
			}  // else there is a match, check next elements
		}
	}
}

}	// namespace detail

template <
	typename ForwardIterator,
	typename Size,
	typename T
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
search_n(
	ForwardIterator first,
	ForwardIterator last,
	Size count,
	T const& value)
{
	return bksge::algorithm::search_n(
		first, last, count, value, bksge::equal_to<>());
}

template <
	typename ForwardIterator,
	typename Size,
	typename T,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
search_n(
	ForwardIterator first,
	ForwardIterator last,
	Size count,
	T const& value,
	BinaryPredicate pred)
{
	using Category = bksge::iterator_category<ForwardIterator>*;
	return bksge::algorithm::detail::search_n(
		first, last, count, value, pred, Category());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_SEARCH_N_INL_HPP
