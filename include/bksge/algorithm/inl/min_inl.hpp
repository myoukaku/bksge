/**
 *	@file	min_inl.hpp
 *
 *	@brief	min の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_ALGORITHM_INL_MIN_INL_HPP
#define BKSGE_ALGORITHM_INL_MIN_INL_HPP

#include <bksge/algorithm/min.hpp>
#include <bksge/functional/less.hpp>

namespace bksge
{

namespace algorithm
{

template <typename T>
inline BKSGE_CONSTEXPR T const&
min(T const& a, T const& b)
{
	return bksge::min(a, b, bksge::less<>());
}

template <typename T, typename Compare>
inline BKSGE_CONSTEXPR T const&
min(T const& a, T const& b, Compare comp)
{
	return comp(a, b) ? a : b;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_ALGORITHM_INL_MIN_INL_HPP
