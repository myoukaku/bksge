/**
 *	@file	nth_element_inl.hpp
 *
 *	@brief	nth_element の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_NTH_ELEMENT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_NTH_ELEMENT_INL_HPP

#include <bksge/fnd/algorithm/nth_element.hpp>
#include <bksge/fnd/algorithm/detail/introselect.hpp>
#include <bksge/fnd/algorithm/detail/lg.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Compare comp)
{
	if (first == last || nth == last)
	{
		return;
	}

	detail::introselect(first, nth, last, detail::lg(last - first) * 2, comp);
}

}	// namespace detail

template <typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last)
{
	return bksge::algorithm::nth_element(first, nth, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Compare comp)
{
	detail::nth_element(first, nth, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_NTH_ELEMENT_INL_HPP
