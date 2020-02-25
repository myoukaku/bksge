/**
 *	@file	is_permutation_inl.hpp
 *
 *	@brief	is_permutation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_IS_PERMUTATION_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_IS_PERMUTATION_INL_HPP

#include <bksge/fnd/algorithm/is_permutation.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_category.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>
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
inline BKSGE_CXX14_CONSTEXPR bool
is_permutation_impl(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred)
{
	using D1 = bksge::iterator_difference_type<ForwardIterator1>;

	// For each element in [f1, l1) see if there are the same number of
	//    equal elements in [f2, l2)
	for (auto i = first1; i != last1; ++i)
	{
		//  Have we already counted the number of *i in [f1, l1)?
		auto match = first1;

		for (; match != i; ++match)
		{
			if (pred(*match, *i))
			{
				break;
			}
		}

		if (match == i)
		{
			// Count number of *i in [f2, l2)
			D1 c2 = 0;
			for (auto j = first2; j != last2; ++j)
			{
				if (pred(*i, *j))
				{
					++c2;
				}
			}

			if (c2 == 0)
			{
				return false;
			}

			// Count number of *i in [i, l1) (we can start with 1)
			D1 c1 = 1;
			for (auto j = bksge::next(i); j != last1; ++j)
			{
				if (pred(*i, *j))
				{
					++c1;
				}
			}

			if (c1 != c2)
			{
				return false;
			}
		}
	}

	return true;
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2,
	BinaryPredicate pred)
{
	//  shorten sequences as much as possible by lopping of any equal prefix
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!pred(*first1, *first2))
		{
			break;
		}
	}

	if (first1 == last1)
	{
		return true;
	}

	//  first1 != last1 && *first1 != *first2
	auto const l1 = bksge::distance(first1, last1);
	if (l1 == 1)
	{
		return false;
	}

	ForwardIterator2 last2 = bksge::next(first2, l1);

	return is_permutation_impl(first1, last1, first2, last2, pred);
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred,
	std::forward_iterator_tag*,
	std::forward_iterator_tag*)
{
	//  shorten sequences as much as possible by lopping of any equal prefix
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (!pred(*first1, *first2))
		{
			break;
		}
	}

	if (first1 == last1)
	{
		return first2 == last2;
	}
	else if (first2 == last2)
	{
		return false;
	}

	auto const l1 = bksge::distance(first1, last1);
	auto const l2 = bksge::distance(first2, last2);

	if (l1 != l2)
	{
		return false;
	}

	return is_permutation_impl(first1, last1, first2, last2, pred);
}

template <
	typename RandomAccessIterator1,
	typename RandomAccessIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	RandomAccessIterator1 first1, RandomAccessIterator2 last1,
	RandomAccessIterator1 first2, RandomAccessIterator2 last2,
	BinaryPredicate pred,
	std::random_access_iterator_tag*,
	std::random_access_iterator_tag*)
{
	if (bksge::distance(first1, last1) != bksge::distance(first2, last2))
	{
		return false;
	}

	return bksge::is_permutation(first1, last1, first2, pred);
}

}	// namespace detail

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename
>
inline BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1,
	ForwardIterator1 last1,
	ForwardIterator2 first2)
{
	return bksge::algorithm::is_permutation(
		first1, last1, first2, bksge::equal_to<>());
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate,
	typename
>
inline BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1,
	ForwardIterator1 last1,
	ForwardIterator2 first2,
	BinaryPredicate pred)
{
	return bksge::algorithm::detail::is_permutation(
		first1, last1, first2, pred);
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename
>
inline BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1,
	ForwardIterator1 last1,
	ForwardIterator2 first2,
	ForwardIterator2 last2)
{
	return bksge::algorithm::is_permutation(
		first1, last1, first2, last2, bksge::equal_to<>());
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate,
	typename
>
inline BKSGE_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1,
	ForwardIterator1 last1,
	ForwardIterator2 first2,
	ForwardIterator2 last2,
	BinaryPredicate pred)
{
	using Category1 = bksge::iterator_category<ForwardIterator1>*;
	using Category2 = bksge::iterator_category<ForwardIterator2>*;
	return bksge::algorithm::detail::is_permutation(
		first1, last1, first2, last2, pred, Category1(), Category2());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_IS_PERMUTATION_INL_HPP
