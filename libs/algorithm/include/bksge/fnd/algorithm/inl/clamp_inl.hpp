/**
 *	@file	clamp_inl.hpp
 *
 *	@brief	clamp の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_CLAMP_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_CLAMP_INL_HPP

#include <bksge/fnd/algorithm/clamp.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename T>
inline BKSGE_CONSTEXPR T const&
clamp(T const& v, T const& lo, T const& hi)
{
	return clamp(v, lo, hi, bksge::less<T>());
}

template <typename T, typename Compare>
inline BKSGE_CONSTEXPR T const&
clamp(T const& v, T const& lo, T const& hi, Compare comp)
{
	return BKSGE_ASSERT(!comp(hi, lo)),
        comp(v, lo) ? lo : comp(hi, v) ? hi : v;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_CLAMP_INL_HPP
