/**
 *	@file	find_end_inl.hpp
 *
 *	@brief	find_end の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_FIND_END_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_FIND_END_INL_HPP

#include <bksge/fnd/algorithm/find_end.hpp>
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
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator1
find_end(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred,
	std::forward_iterator_tag*,
	std::forward_iterator_tag*)
{
	// modeled after search algorithm
	auto r = last1;  // last1 is the "default" answer

	if (first2 == last2)
	{
		return r;
	}

	for (;;)
	{
		for (;;)
		{
			// if source exhausted return last correct answer
			if (first1 == last1)
			{
				return r;	//    (or last1 if never found)
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
			// Pattern exhaused, record answer and search for another one
			if (++m2 == last2)
			{
				r = first1;
				++first1;
				break;
			}

			// Source exhausted, return last answer
			if (++m1 == last1)
			{
				return r;
			}

			// mismatch, restart with a new first
			if (!pred(*m1, *m2))
			{
				++first1;
				break;
			}  // else there is a match, check next elements
		}
	}
}

template <
	typename BidirectionalIterator1,
	typename BidirectionalIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR BidirectionalIterator1
find_end(
	BidirectionalIterator1 first1, BidirectionalIterator1 last1,
	BidirectionalIterator2 first2, BidirectionalIterator2 last2,
	BinaryPredicate pred,
	std::bidirectional_iterator_tag*,
	std::bidirectional_iterator_tag*)
{
	// modeled after search algorithm (in reverse)
	if (first2 == last2)
	{
		return last1;  // Everything matches an empty sequence
	}

	auto l1 = last1;
	auto l2 = last2;
	--l2;

	for (;;)
	{
		// Find last element in sequence 1 that matchs *(last2-1), with a mininum of loop checks
		for (;;)
		{
			if (first1 == l1)  // return last1 if no element matches *first2
			{
				return last1;
			}

			if (pred(*--l1, *l2))
			{
				break;
			}
		}

		// *l1 matches *l2, now match elements before here
		auto m1 = l1;
		auto m2 = l2;

		for (;;)
		{
			// If pattern exhausted, m1 is the answer (works for 1 element pattern)
			if (m2 == first2)
			{
				return m1;
			}

			// Otherwise if source exhaused, pattern not found
			if (m1 == first1)
			{
				return last1;
			}

			// if there is a mismatch, restart with a new l1
			if (!pred(*--m1, *--m2))
			{
				break;
			}  // else there is a match, check next elements
		}
	}
}

template <
	typename RandomAccessIterator1,
	typename RandomAccessIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator1
find_end(
	RandomAccessIterator1 first1, RandomAccessIterator1 last1,
	RandomAccessIterator2 first2, RandomAccessIterator2 last2,
	BinaryPredicate pred,
	std::random_access_iterator_tag*,
	std::random_access_iterator_tag*)
{
	// Take advantage of knowing source and pattern lengths.
	// Stop short when source is smaller than pattern
	auto const len2 = last2 - first2;
	if (len2 == 0)
	{
		return last1;
	}

	auto const len1 = last1 - first1;
	if (len1 < len2)
	{
		return last1;
	}

	// End of pattern match can't go before here
	auto const s = first1 + (len2 - 1);
	auto l1 = last1;
	auto l2 = last2;
	--l2;

	for (;;)
	{
		for (;;)
		{
			if (s == l1)
			{
				return last1;
			}

			if (pred(*--l1, *l2))
			{
				break;
			}
		}

		auto m1 = l1;
		auto m2 = l2;

		for (;;)
		{
			if (m2 == first2)
			{
				return m1;
			}

			// no need to check range on m1 because s guarantees we have enough source
			if (!pred(*--m1, *--m2))
			{
				break;
			}
		}
	}
}

}	// namespace detail

template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator1
find_end(
	ForwardIterator1 first1,
	ForwardIterator1 last1,
	ForwardIterator2 first2,
	ForwardIterator2 last2)
{
	return bksge::algorithm::find_end(
		first1, last1, first2, last2, bksge::equal_to<>());
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator1
find_end(
	ForwardIterator1 first1,
	ForwardIterator1 last1,
	ForwardIterator2 first2,
	ForwardIterator2 last2,
	BinaryPredicate pred)
{
	using Category1 = bksge::iterator_category<ForwardIterator1>*;
	using Category2 = bksge::iterator_category<ForwardIterator2>*;
	return bksge::algorithm::detail::find_end(
		first1, last1, first2, last2, pred, Category1(), Category2());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_FIND_END_INL_HPP
