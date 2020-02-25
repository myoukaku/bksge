﻿/**
 *	@file	distance_inl.hpp
 *
 *	@brief	distance 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_INL_DISTANCE_INL_HPP
#define BKSGE_FND_ITERATOR_INL_DISTANCE_INL_HPP

#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_category.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>

namespace bksge
{

namespace detail
{

template <typename Distance, typename InputIterator>
inline BKSGE_CXX14_CONSTEXPR Distance
distance_impl(InputIterator first, InputIterator last, std::input_iterator_tag*)
{
	Distance n = 0;
	for (; first != last; ++first)
	{
		++n;
	}
	return n;
}

template <typename Distance, typename RandomAccessIterator>
inline BKSGE_CONSTEXPR Distance
distance_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag*)
{
	return last - first;
}

}	// namespace detail

template <typename InputIterator, typename>
inline BKSGE_CONSTEXPR bksge::iterator_difference_type<InputIterator>
distance(InputIterator first, InputIterator last)
{
	using Distance = bksge::iterator_difference_type<InputIterator>;
	using Category = bksge::iterator_category<InputIterator>*;
	return bksge::detail::distance_impl<Distance>(first, last, Category());
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_INL_DISTANCE_INL_HPP