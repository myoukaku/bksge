/**
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
#include <bksge/fnd/iterator/iterator_category.hpp>
#include <bksge/fnd/iterator/tag.hpp>

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
inline BKSGE_CXX14_CONSTEXPR OutputIterator
copy_n(
	InputIterator first,
	Size n,
	OutputIterator result,
	bksge::input_iterator_tag*)
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
inline BKSGE_CXX14_CONSTEXPR OutputIterator
copy_n(
	RandomAccessIterator first,
	Size n,
	OutputIterator result,
	bksge::random_access_iterator_tag*)
{
	return bksge::copy(first, first + n, result);
}

}	// namespace detail

template <
	typename InputIterator,
	typename Size,
	typename OutputIterator
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
copy_n(InputIterator first, Size n, OutputIterator result)
{
	using Category = bksge::iterator_category<InputIterator>*;
	return detail::copy_n(first, n, result, Category());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_COPY_N_INL_HPP
