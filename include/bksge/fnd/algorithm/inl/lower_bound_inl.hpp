/**
 *	@file	lower_bound_inl.hpp
 *
 *	@brief	lower_bound の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_LOWER_BOUND_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_LOWER_BOUND_INL_HPP

#include <bksge/fnd/algorithm/lower_bound.hpp>
#include <bksge/fnd/algorithm/detail/lower_bound.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
lower_bound(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	return bksge::algorithm::lower_bound(
		first, last, value, bksge::less<>());
}

template <typename ForwardIterator, typename T, typename Compare>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
lower_bound(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	return detail::lower_bound(first, last, value, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_LOWER_BOUND_INL_HPP
