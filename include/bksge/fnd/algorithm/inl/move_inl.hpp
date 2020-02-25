﻿/**
 *	@file	move_inl.hpp
 *
 *	@brief	move の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MOVE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MOVE_INL_HPP

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/iterator/unwrap_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <cstddef>
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
move(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	while (first != last)
	{
		*result++ = std::move(*first++);
	}

	return result;
}

template <typename T, typename U>
inline
bksge::enable_if_t<
	std::is_same<bksge::remove_const_t<T>, U>::value &&
	std::is_trivially_copy_assignable<U>::value,
	U*
>
move(T* first, T* last, U* result)
{
	auto const n = static_cast<std::size_t>(last - first);

	if (n > 0)
	{
		std::memmove(result, first, n * sizeof(U));
	}

	return result + n;
}

}	// namespace detail

template <
	typename InputIterator,
	typename OutputIterator,
	typename
>
inline OutputIterator
move(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	return detail::move(
		bksge::unwrap_iterator(first),
		bksge::unwrap_iterator(last),
		bksge::unwrap_iterator(result));
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MOVE_INL_HPP