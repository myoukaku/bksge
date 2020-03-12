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
#include <bksge/fnd/algorithm/min_element.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_value_type.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

// stable, 2-3 compares, 0-2 swaps

template <typename Compare, typename ForwardIterator>
inline unsigned
sort3(
	ForwardIterator x,
	ForwardIterator y,
	ForwardIterator z,
	Compare c)
{
	unsigned r = 0;

	if (!c(*y, *x))          // if x <= y
	{
		if (!c(*z, *y))      // if y <= z
		{
			return r;        // x <= y && y <= z
		}
							 // x <= y && y > z

		swap(*y, *z);        // x <= z && y < z
		r = 1;

		if (c(*y, *x))       // if x > y
		{
			swap(*x, *y);    // x < y && y <= z
			r = 2;
		}

		return r;            // x <= y && y < z
	}

	if (c(*z, *y))           // x > y, if y > z
	{
		swap(*x, *z);        // x < y && y < z
		r = 1;
		return r;
	}

	swap(*x, *y);            // x > y && y <= z
	r = 1;                   // x < y && x <= z

	if (c(*z, *y))           // if y > z
	{
		swap(*y, *z);        // x <= y && y < z
		r = 2;
	}

	return r;
}                            // x <= y && y <= z

// stable, 3-6 compares, 0-5 swaps

template <typename Compare, typename ForwardIterator>
inline unsigned
sort4(
	ForwardIterator x1,
	ForwardIterator x2,
	ForwardIterator x3,
	ForwardIterator x4,
	Compare c)
{
	auto r = detail::sort3<Compare>(x1, x2, x3, c);

	if (c(*x4, *x3))
	{
		swap(*x3, *x4);
		++r;

		if (c(*x3, *x2))
		{
			swap(*x2, *x3);
			++r;

			if (c(*x2, *x1))
			{
				swap(*x1, *x2);
				++r;
			}
		}
	}

	return r;
}

// stable, 4-10 compares, 0-9 swaps

template <typename Compare, typename ForwardIterator>
inline unsigned
sort5(
	ForwardIterator x1,
	ForwardIterator x2,
	ForwardIterator x3,
	ForwardIterator x4,
	ForwardIterator x5,
	Compare c)
{
	auto r = detail::sort4<Compare>(x1, x2, x3, x4, c);

	if (c(*x5, *x4))
	{
		swap(*x4, *x5);
		++r;

		if (c(*x4, *x3))
		{
			swap(*x3, *x4);
			++r;

			if (c(*x3, *x2))
			{
				swap(*x2, *x3);
				++r;

				if (c(*x2, *x1))
				{
					swap(*x1, *x2);
					++r;
				}
			}
		}
	}

	return r;
}

template <typename Compare, typename RandomAccessIterator>
inline void
insertion_sort_3(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	using value_type = bksge::iterator_value_type<RandomAccessIterator>;

	auto j = first+2;
	detail::sort3<Compare>(first, first+1, j, comp);
	
	for (auto i = j+1; i != last; ++i)
	{
		if (comp(*i, *j))
		{
			value_type t(bksge::move(*i));
			auto k = j;
			j = i;

			do
			{
				*j = bksge::move(*k);
				j = k;
			}
			while (j != first && comp(t, *--k));

			*j = bksge::move(t);
		}

		j = i;
	}
}

template <typename Compare, typename RandomAccessIterator>
inline bool
insertion_sort_incomplete(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	switch (last - first)
	{
	case 0:
	case 1:
		return true;
	case 2:
		if (comp(*--last, *first))
		{
			swap(*first, *last);
		}
		return true;
	case 3:
		detail::sort3<Compare>(first, first+1, --last, comp);
		return true;
	case 4:
		detail::sort4<Compare>(first, first+1, first+2, --last, comp);
		return true;
	case 5:
		detail::sort5<Compare>(first, first+1, first+2, first+3, --last, comp);
		return true;
	}

	using value_type = bksge::iterator_value_type<RandomAccessIterator>;
	auto j = first+2;
	detail::sort3<Compare>(first, first+1, j, comp);
	unsigned const limit = 8;
	unsigned count = 0;

	for (auto i = j+1; i != last; ++i)
	{
		if (comp(*i, *j))
		{
			value_type t(bksge::move(*i));
			auto k = j;
			j = i;

			do
			{
				*j = bksge::move(*k);
				j = k;
			}
			while (j != first && comp(t, *--k));

			*j = bksge::move(t);
			
			if (++count == limit)
			{
				return ++i == last;
			}
		}

		j = i;
	}

	return true;
}

template <typename Compare, typename RandomAccessIterator>
inline void
sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	// Compare is known to be a reference type
	using difference_type = bksge::iterator_difference_type<RandomAccessIterator>;
	using value_type      = bksge::iterator_value_type<RandomAccessIterator>;

	const difference_type limit =
		bksge::is_trivially_copy_constructible<value_type>::value &&
		bksge::is_trivially_copy_assignable<value_type>::value ? 30 : 6;

	for (;;)
	{
RESTART:
		auto len = last - first;

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
			detail::sort3<Compare>(first, first+1, --last, comp);
			return;
		case 4:
			detail::sort4<Compare>(first, first+1, first+2, --last, comp);
			return;
		case 5:
			detail::sort5<Compare>(first, first+1, first+2, first+3, --last, comp);
			return;
		}

		if (len <= limit)
		{
			detail::insertion_sort_3<Compare>(first, last, comp);
			return;
		}

		// len > 5
		auto m = first;
		auto lm1 = last;
		--lm1;
		unsigned n_swaps;

		{
			difference_type delta;
			if (len >= 1000)
			{
				delta = len/2;
				m += delta;
				delta /= 2;
				n_swaps = detail::sort5<Compare>(first, first + delta, m, m+delta, lm1, comp);
			}
			else
			{
				delta = len/2;
				m += delta;
				n_swaps = detail::sort3<Compare>(first, m, lm1, comp);
			}
		}

		// *m is median
		// partition [first, m) < *m and *m <= [m, last)
		// (this inhibits tossing elements equivalent to m around unnecessarily)
		auto i = first;
		auto j = lm1;
		// j points beyond range to be tested, *m is known to be <= *lm1
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
					// The first part is sorted, sort the secod part
					// detail::sort<Compare>(i, last, comp);
					first = i;
					goto RESTART;
				}

				if (comp(*j, *m))
				{
					swap(*i, *j);
					++n_swaps;
					break;  // found guard for downward moving j, now use unguarded partition
				}
			}
		}

		// It is known that *i < *m
		++i;
		// j points beyond range to be tested, *m is known to be <= *lm1
		// if not yet partitioned...
		if (i < j)
		{
			// known that *(i - 1) < *m
			// known that i <= m
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

				if (i > j)
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
		// If we were given a perfect partition, see if insertion sort is quick...
		if (n_swaps == 0)
		{
			bool fs = detail::insertion_sort_incomplete<Compare>(first, i, comp);
			if (detail::insertion_sort_incomplete<Compare>(i+1, last, comp))
			{
				if (fs)
				{
					return;
				}

				last = i;
				continue;
			}
			else
			{
				if (fs)
				{
					first = ++i;
					continue;
				}
			}
		}

		// sort smaller range with recursive call and larger with tail recursion elimination
		if (i - first < last - i)
		{
			detail::sort<Compare>(first, i, comp);
			first = ++i;
		}
		else
		{
			detail::sort<Compare>(i+1, last, comp);
			last = i;
		}
	}
}

}	// namespace detail

template <typename RandomAccessIterator, typename>
inline void
sort(RandomAccessIterator first, RandomAccessIterator last)
{
	return bksge::algorithm::sort(
		first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare, typename>
inline void
sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	detail::sort<CompRef>(first, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_SORT_INL_HPP
