/**
 *	@file	merge_inl.hpp
 *
 *	@brief	merge の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MERGE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MERGE_INL_HPP

#include <bksge/fnd/algorithm/merge.hpp>
#include <bksge/fnd/algorithm/copy.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename Compare,
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator
>
OutputIterator
merge(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result,
	Compare comp)
{
	for (; first1 != last1; ++result)
	{
		if (first2 == last2)
		{
			return bksge::copy(first1, last1, result);
		}

		if (comp(*first2, *first1))
		{
			*result = *first2;
			++first2;
		}
		else
		{
			*result = *first1;
			++first1;
		}
	}

	return bksge::copy(first2, last2, result);
}

}	// namespace detail

template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename
>
inline OutputIterator
merge(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	OutputIterator result)
{
	return bksge::algorithm::merge(
		first1, last1, first2, last2, result, bksge::less<>());
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename Compare,
	typename
>
inline OutputIterator
merge(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	OutputIterator result,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	return detail::merge<CompRef>(
		first1, last1, first2, last2, result, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MERGE_INL_HPP
