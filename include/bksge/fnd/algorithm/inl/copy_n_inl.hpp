﻿/**
 *	@file	copy_n_inl.hpp
 *
 *	@brief	copy_n の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_COPY_N_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_COPY_N_INL_HPP

#include <bksge/fnd/algorithm/copy_n.hpp>
#include <bksge/fnd/algorithm/copy.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_category.hpp>
#include <iterator>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename InputIterator,
	typename Size,
	typename OutputIterator
>
inline OutputIterator
copy_n(
	InputIterator first,
	Size n,
	OutputIterator result,
	std::input_iterator_tag*)
{
	for (Size i = 0; i < n; i++)
	{
		*result++ = *first++;
	}

	return result;
}

template <
	typename RandomAccessIterator,
	typename Size,
	typename OutputIterator
>
inline OutputIterator
copy_n(
	RandomAccessIterator first,
	Size n,
	OutputIterator result,
	std::random_access_iterator_tag*)
{
	return bksge::copy(first, first + n, result);
}

}	// namespace detail

template <
	typename InputIterator,
	typename Size,
	typename OutputIterator,
	typename
>
inline OutputIterator
copy_n(InputIterator first, Size n, OutputIterator result)
{
	using Category = bksge::iterator_category<InputIterator>*;
	return detail::copy_n(first, n, result, Category());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_COPY_N_INL_HPP