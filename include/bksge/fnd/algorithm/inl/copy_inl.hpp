/**
 *	@file	copy_inl.hpp
 *
 *	@brief	copy の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_COPY_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_COPY_INL_HPP

#include <bksge/fnd/algorithm/copy.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/iterator/unwrap_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/config.hpp>
#include <cstring>
#include <type_traits>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename InputIterator, typename OutputIterator>
inline OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator result)
{
	while (first != last)
	{
		*result++ = *first++;
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
copy(T* first, T* last, U* result)
{
	auto const n = static_cast<bksge::size_t>(last - first);

	if (n > 0)
	{
		std::memmove(result, first, n * sizeof(U));
	}

	return result + n;
}

template <typename InputIterator, typename OutputIterator>
inline OutputIterator
copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result_first,
	OutputIterator result_last)
{
	while (first != last && result_first != result_last)
	{
		*result_first++ = *first++;
	}

	return result_first;
}

template <typename T, typename U>
inline
bksge::enable_if_t<
	std::is_same<bksge::remove_const_t<T>, U>::value &&
	std::is_trivially_copy_assignable<U>::value,
	U*
>
copy(T* first, T* last, U* result_first, U* result_last)
{
	auto const n = bksge::min(
		static_cast<bksge::size_t>(last - first),
		static_cast<bksge::size_t>(result_last - result_first));

	if (n > 0)
	{
		std::memmove(result_first, first, n * sizeof(U));
	}

	return result_first + n;
}

}	// namespace detail

template <
	typename InputIterator,
	typename OutputIterator,
	typename
>
inline OutputIterator
copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	return detail::copy(
		bksge::unwrap_iterator(first),
		bksge::unwrap_iterator(last),
		bksge::unwrap_iterator(result));
}

template <
	typename InputIterator,
	typename OutputIterator,
	typename
>
inline OutputIterator
copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result_first,
	OutputIterator result_last)
{
	return detail::copy(
		bksge::unwrap_iterator(first),
		bksge::unwrap_iterator(last),
		bksge::unwrap_iterator(result_first),
		bksge::unwrap_iterator(result_last));
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_COPY_INL_HPP
