﻿/**
 *	@file	move_backward_inl.hpp
 *
 *	@brief	move_backward の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MOVE_BACKWARD_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MOVE_BACKWARD_INL_HPP

#include <bksge/fnd/algorithm/move_backward.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/iterator/unwrap_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <cstring>
#include <type_traits>
#include <utility>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename InputIterator, typename OutputIterator>
inline OutputIterator
move_backward(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	while (first != last)
	{
		*--result = std::move(*--last);
	}

	return result;
}

template <typename T, typename U>
inline bksge::enable_if_t<
	std::is_same<bksge::remove_const_t<T>, U>::value &&
	std::is_trivially_copy_assignable<U>::value,
	U*
>
move_backward(T* first, T* last, U* result)
{
	auto const n = static_cast<bksge::size_t>(last - first);

	if (n > 0)
	{
		result -= n;
		std::memmove(result, first, n * sizeof(U));
	}

	return result;
}

}	// namespace detail

template <
	typename BidirectionalIterator1,
	typename BidirectionalIterator2,
	typename
>
inline BidirectionalIterator2
move_backward(
	BidirectionalIterator1 first,
	BidirectionalIterator1 last,
	BidirectionalIterator2 result)
{
	return detail::move_backward(
		bksge::unwrap_iterator(first),
		bksge::unwrap_iterator(last),
		bksge::unwrap_iterator(result));
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MOVE_BACKWARD_INL_HPP
