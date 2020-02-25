/**
 *	@file	equal_inl.hpp
 *
 *	@brief	equal の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_EQUAL_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_EQUAL_INL_HPP

#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_category.hpp>
#include <iterator>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	BinaryPredicate pred,
	std::input_iterator_tag*,
	std::input_iterator_tag*)
{
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (!pred(*first1, *first2))
		{
			return false;
		}
	}

	return first1 == last1 && first2 == last2;
}

template <
	typename RandomAccessIterator1,
	typename RandomAccessIterator2,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR bool
equal(
	RandomAccessIterator1 first1, RandomAccessIterator1 last1,
	RandomAccessIterator2 first2, RandomAccessIterator2 last2,
	BinaryPredicate pred,
	std::random_access_iterator_tag*,
	std::random_access_iterator_tag*)
{
	if (bksge::distance(first1, last1) != bksge::distance(first2, last2))
	{
		return false;
	}

	return bksge::equal(first1, last1, first2, pred);
}

}	// namespace detail

template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate,
	typename
>
inline BKSGE_CXX14_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	BinaryPredicate pred)
{
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!pred(*first1, *first2))
		{
			return false;
		}
	}

	return true;
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename
>
inline BKSGE_CXX14_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2)
{
	return bksge::algorithm::equal(
		first1, last1, first2, bksge::equal_to<>());
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate,
	typename
>
inline BKSGE_CXX14_CONSTEXPR bool
equal(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	BinaryPredicate pred)
{
	using Category1 = bksge::iterator_category<InputIterator1>*;
	using Category2 = bksge::iterator_category<InputIterator2>*;
	return bksge::algorithm::detail::equal(
		first1, last1, first2, last2, pred, Category1(), Category2());
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename
>
inline BKSGE_CXX14_CONSTEXPR bool
equal(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2)
{
	return bksge::algorithm::equal(
		first1, last1, first2, last2, bksge::equal_to<>());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_EQUAL_INL_HPP
