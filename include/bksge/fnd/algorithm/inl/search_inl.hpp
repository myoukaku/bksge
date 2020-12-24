/**
 *	@file	search_inl.hpp
 *
 *	@brief	search の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_SEARCH_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_SEARCH_INL_HPP

#include <bksge/fnd/algorithm/search.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/iterator/iterator_category.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename BinaryPredicate,
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator1
search(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred,
	bksge::forward_iterator_tag*,
	bksge::forward_iterator_tag*)
{
	if (first2 == last2)
	{
		return first1;  // Everything matches an empty sequence
	}

	for (;;)
	{
		// Find first element in sequence 1 that matchs *first2, with a mininum of loop checks
		for (;;)
		{
			if (first1 == last1)  // return last1 if no element matches *first2
			{
				return last1;
			}

			if (pred(*first1, *first2))
			{
				break;
			}

			++first1;
		}

		// *first1 matches *first2, now match elements after here
		auto m1 = first1;
		auto m2 = first2;

		for (;;)
		{
			// If pattern exhausted, first1 is the answer (works for 1 element pattern)
			if (++m2 == last2)
			{
				return first1;
			}

			// Otherwise if source exhaused, pattern not found
			if (++m1 == last1)
			{
				return last1;
			}

			// if there is a mismatch, restart with a new first1
			if (!pred(*m1, *m2))
			{
				++first1;
				break;
			}  // else there is a match, check next elements
		}
	}
}

template <
	typename BinaryPredicate,
	typename RandomAccessIterator1,
	typename RandomAccessIterator2
>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator1
search(
	RandomAccessIterator1 first1, RandomAccessIterator1 last1,
	RandomAccessIterator2 first2, RandomAccessIterator2 last2,
	BinaryPredicate pred,
	bksge::random_access_iterator_tag*,
	bksge::random_access_iterator_tag*)
{
	// Take advantage of knowing source and pattern lengths.
	// Stop short when source is smaller than pattern
	auto const len2 = last2 - first2;
	if (len2 == 0)
	{
		return first1;
	}

	auto const len1 = last1 - first1;
	if (len1 < len2)
	{
		return last1;
	}

	// Start of pattern match can't go beyond here
	auto const s = last1 - (len2 - 1);

	for (;;)
	{
		for (;;)
		{
			if (first1 == s)
			{
				return last1;
			}

			if (pred(*first1, *first2))
			{
				break;
			}

			++first1;
		}

		auto m1 = first1;
		auto m2 = first2;

		for (;;)
		{
			if (++m2 == last2)
			{
				return first1;
			}

			// no need to check range on m1 because s guarantees we have enough source
			++m1;

			if (!pred(*m1, *m2))
			{
				++first1;
				break;
			}
		}
	}
}

}	// namespace detail

template <typename ForwardIterator1, typename ForwardIterator2>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator1
search(
	ForwardIterator1 first1,
	ForwardIterator1 last1,
	ForwardIterator2 first2,
	ForwardIterator2 last2)
{
	return bksge::algorithm::search(
		first1, last1, first2, last2, bksge::equal_to<>());
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator1
search(
	ForwardIterator1 first1,
	ForwardIterator1 last1,
	ForwardIterator2 first2,
	ForwardIterator2 last2,
	BinaryPredicate pred)
{
	using Category1 = bksge::iterator_category<ForwardIterator1>*;
	using Category2 = bksge::iterator_category<ForwardIterator2>*;
	return bksge::algorithm::detail::search(
		first1, last1, first2, last2, pred, Category1(), Category2());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_SEARCH_INL_HPP
