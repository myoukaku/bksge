/**
 *	@file	fill_inl.hpp
 *
 *	@brief	fill の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_FILL_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_FILL_INL_HPP

#include <bksge/fnd/algorithm/fill.hpp>
#include <bksge/fnd/algorithm/fill_n.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_category.hpp>
#include <iterator>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR void
fill(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	std::forward_iterator_tag*)
{
	while (first != last)
	{
		*first++ = value;
	}
}

template <typename RandomAccessIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR void
fill(
	RandomAccessIterator first,
	RandomAccessIterator last,
	T const& value,
	std::random_access_iterator_tag*)
{
	bksge::fill_n(first, last - first, value);
}

}	// namespace detail

template <typename ForwardIterator, typename T, typename>
inline BKSGE_CXX14_CONSTEXPR void
fill(ForwardIterator first, ForwardIterator last, T const& value)
{
	using Category = bksge::iterator_category<ForwardIterator>*;
	detail::fill(first, last, value, Category());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_FILL_INL_HPP
