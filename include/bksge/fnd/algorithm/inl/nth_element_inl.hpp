/**
 *	@file	nth_element_inl.hpp
 *
 *	@brief	nth_element の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_NTH_ELEMENT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_NTH_ELEMENT_INL_HPP

#include <bksge/fnd/algorithm/nth_element.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/utility/swap.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Compare, typename BirdirectionalIterator>
inline BKSGE_CXX14_CONSTEXPR void
selection_sort(
	BirdirectionalIterator first,
	BirdirectionalIterator last,
	Compare comp)
{
	auto lm1 = last;

	for (--lm1; first != lm1; ++first)
	{
		auto i = bksge::min_element<
			BirdirectionalIterator,
			bksge::add_lvalue_reference_t<Compare>
		>(first, last, comp);
		
		if (i != first)
		{
			swap(*first, *i);
		}
	}
}

template <typename Compare, typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Compare comp)
{
	// Compare is known to be a reference type
	using difference_type = bksge::iter_difference_t<RandomAccessIterator>;

	const difference_type limit = 7;

	for (;;)
	{
//RESTART:
		if (nth == last)
		{
			return;
		}

		auto const len = last - first;

		switch (len)
		{
		case 0:
		case 1:
			return;
		case 2:
			if (comp(*--last, *first))
			{
				swap(*first, *last);
			}
			return;
		case 3:
			{
				auto m = first;
				detail::sort3<Compare>(first, ++m, --last, comp);
			}
			return;
		}

		if (len <= limit)
		{
			detail::selection_sort<Compare>(first, last, comp);
			return;
		}

		bool restart = false;

		// len > limit >= 3
		auto m = first + len/2;
		auto lm1 = last;
		auto n_swaps = detail::sort3<Compare>(first, m, --lm1, comp);

		// *m is median
		// partition [first, m) < *m and *m <= [m, last)
		// (this inhibits tossing elements equivalent to m around unnecessarily)
		auto i = first;
		auto j = lm1;
		// j points beyond range to be tested, *lm1 is known to be <= *m
		// The search going up is known to be guarded but the search coming down isn't.
		// Prime the downward search with a guard.
		if (!comp(*i, *m))  // if *first == *m
		{
			// *first == *m, *first doesn't go in first part
			// manually guard downward moving j against i
			for (;;)
			{
				if (i == --j)
				{
					// *first == *m, *m <= all other elements
					// Parition instead into [first, i) == *first and *first < [i, last)
					++i;  // first + 1
					j = last;

					if (!comp(*first, *--j))  // we need a guard if *first == *(last-1)
					{
						for (;;)
						{
							if (i == j)
							{
								return;  // [first, last) all equivalent elements
							}

							if (comp(*first, *i))
							{
								swap(*i, *j);
								++n_swaps;
								++i;
								break;
							}

							++i;
						}
					}
					
					// [first, i) == *first and *first < [j, last) and j == last - 1
					if (i == j)
					{
						return;
					}

					for (;;)
					{
						while (!comp(*first, *i))
						{
							++i;
						}

						while (comp(*first, *--j))
						{
							;
						}

						if (i >= j)
						{
							break;
						}

						swap(*i, *j);
						++n_swaps;
						++i;
					}

					// [first, i) == *first and *first < [i, last)
					// The first part is sorted,
					if (nth < i)
					{
						return;
					}

					// nth_element the secod part
					// nth_element<Compare>(i, nth, last, comp);
					first = i;
					//goto RESTART;
					restart = true;
				}

				if (restart)
				{
					break;
				}

				if (comp(*j, *m))
				{
					swap(*i, *j);
					++n_swaps;
					break;  // found guard for downward moving j, now use unguarded partition
				}
			}
		}

		if (restart)
		{
			continue;
		}

		++i;
		// j points beyond range to be tested, *lm1 is known to be <= *m
		// if not yet partitioned...
		if (i < j)
		{
			// known that *(i - 1) < *m
			for (;;)
			{
				// m still guards upward moving i
				while (comp(*i, *m))
				{
					++i;
				}

				// It is now known that a guard exists for downward moving j
				while (!comp(*--j, *m))
				{
					;
				}

				if (i >= j)
				{
					break;
				}

				swap(*i, *j);
				++n_swaps;
				
				// It is known that m != j
				// If m just moved, follow it
				if (m == i)
				{
					m = j;
				}

				++i;
			}
		}

		// [first, i) < *m and *m <= [i, last)
		if (i != m && comp(*m, *i))
		{
			swap(*i, *m);
			++n_swaps;
		}

		// [first, i) < *i and *i <= [i+1, last)
		if (nth == i)
		{
			return;
		}

		bool sorted = true;

		if (n_swaps == 0)
		{
			// We were given a perfectly partitioned sequence.  Coincidence?
			if (nth < i)
			{
				// Check for [first, i) already sorted
				j = m = first;

				while (++j != i)
				{
					if (comp(*j, *m))
					{
						// not yet sorted, so sort
						//goto NOT_SORTED;
						sorted = false;
						break;
					}

					m = j;
				}

				// [first, i) sorted
				if (sorted)
				{
					return;
				}
			}
			else
			{
				// Check for [i, last) already sorted
				j = m = i;

				while (++j != last)
				{
					if (comp(*j, *m))
					{
						// not yet sorted, so sort
						//goto NOT_SORTED;
						sorted = false;
						break;
					}

					m = j;
				}

				// [i, last) sorted
				if (sorted)
				{
					return;
				}
			}
		}

//NOT_SORTED:
		// nth_element on range containing nth
		if (nth < i)
		{
			// nth_element<Compare>(first, nth, i, comp);
			last = i;
		}
		else
		{
			// nth_element<Compare>(i+1, nth, last, comp);
			first = ++i;
		}
	}
}

}	// namespace detail

template <typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last)
{
	return bksge::algorithm::nth_element(
		first, nth, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	detail::nth_element<CompRef>(first, nth, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_NTH_ELEMENT_INL_HPP
