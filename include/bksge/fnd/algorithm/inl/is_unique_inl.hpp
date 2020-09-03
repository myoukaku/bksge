/**
 *	@file	is_unique_inl.hpp
 *
 *	@brief	is_unique の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_IS_UNIQUE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_IS_UNIQUE_INL_HPP

#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/adjacent_find.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator>
inline BKSGE_CONSTEXPR bool
is_unique(
	ForwardIterator first,
	ForwardIterator last)
{
	return bksge::adjacent_find(first, last) == last;
}

template <typename ForwardIterator, typename Compare>
inline BKSGE_CONSTEXPR bool
is_unique(
	ForwardIterator first,
	ForwardIterator last,
	Compare			comp)
{
	return bksge::adjacent_find(first, last, comp) == last;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_IS_UNIQUE_INL_HPP
