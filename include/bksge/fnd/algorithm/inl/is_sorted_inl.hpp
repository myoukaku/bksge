/**
 *	@file	is_sorted_inl.hpp
 *
 *	@brief	is_sorted の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_IS_SORTED_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_IS_SORTED_INL_HPP

#include <bksge/fnd/algorithm/is_sorted.hpp>
#include <bksge/fnd/algorithm/is_sorted_until.hpp>
#include <bksge/fnd/functional/less.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename>
inline BKSGE_CXX14_CONSTEXPR bool
is_sorted(
	ForwardIterator first,
	ForwardIterator last)
{
	return bksge::algorithm::is_sorted(first, last, bksge::less<>());
}

template <typename ForwardIterator, typename Compare, typename>
inline BKSGE_CXX14_CONSTEXPR bool
is_sorted(
	ForwardIterator first,
	ForwardIterator last,
	Compare comp)
{
	return bksge::is_sorted_until(first, last, comp) == last;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_IS_SORTED_INL_HPP
