/**
 *	@file	max_inl.hpp
 *
 *	@brief	max の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MAX_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MAX_INL_HPP

#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/functional/less.hpp>

namespace bksge
{

namespace algorithm
{

template <typename T>
inline BKSGE_CONSTEXPR T const&
max(T const& a, T const& b)
{
	return bksge::max(a, b, bksge::less<>());
}

template <typename T, typename Compare>
inline BKSGE_CONSTEXPR T const&
max(T const& a, T const& b, Compare comp)
{
	return comp(b, a) ? a : b;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MAX_INL_HPP
