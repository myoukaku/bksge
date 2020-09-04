/**
 *	@file	upper_bound_inl.hpp
 *
 *	@brief	upper_bound の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_UPPER_BOUND_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_UPPER_BOUND_INL_HPP

#include <bksge/fnd/algorithm/upper_bound.hpp>
#include <bksge/fnd/algorithm/detail/upper_bound.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
upper_bound(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	return bksge::algorithm::upper_bound(
		first, last, value, bksge::less<>());
}

template <
	typename ForwardIterator,
	typename T,
	typename Compare
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
upper_bound(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	return detail::upper_bound(first, last, value, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_UPPER_BOUND_INL_HPP
