/**
 *	@file	move_backward_inl.hpp
 *
 *	@brief	move_backward の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MOVE_BACKWARD_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MOVE_BACKWARD_INL_HPP

#include <bksge/fnd/algorithm/move_backward.hpp>
#include <bksge/fnd/iterator/unwrap_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
#include <bksge/fnd/cstring/memmove.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <cstddef>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename InputIterator, typename OutputIterator>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
move_backward(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	while (first != last)
	{
		*--result = bksge::move(*--last);
	}

	return result;
}

#if 0
template <typename T, typename U>
inline bksge::enable_if_t<
	bksge::is_same<bksge::remove_const_t<T>, U>::value &&
	bksge::is_trivially_copy_assignable<U>::value,
	U*
>
move_backward(T* first, T* last, U* result)
{
	auto const n = static_cast<std::size_t>(last - first);

	if (n > 0)
	{
		result -= n;
		bksge::memmove(result, first, n * sizeof(U));
	}

	return result;
}
#endif

}	// namespace detail

template <typename BidirectionalIterator1, typename BidirectionalIterator2>
inline BKSGE_CXX14_CONSTEXPR BidirectionalIterator2
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
