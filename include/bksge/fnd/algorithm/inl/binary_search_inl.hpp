/**
 *	@file	binary_search_inl.hpp
 *
 *	@brief	binary_search の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_BINARY_SEARCH_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_BINARY_SEARCH_INL_HPP

#include <bksge/fnd/algorithm/binary_search.hpp>
#include <bksge/fnd/algorithm/lower_bound.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Compare, typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR bool
binary_search(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	first = detail::lower_bound<Compare>(first, last, value, comp);
	return first != last && !comp(value, *first);
}

}	// namespace detail

template <typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR bool
binary_search(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	return bksge::algorithm::binary_search(
		first, last, value, bksge::less<>());
}

template <typename ForwardIterator, typename T, typename Compare>
inline BKSGE_CXX14_CONSTEXPR bool
binary_search(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	return detail::binary_search<CompRef>(first, last, value, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_BINARY_SEARCH_INL_HPP
