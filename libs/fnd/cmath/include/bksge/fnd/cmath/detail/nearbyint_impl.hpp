/**
 *	@file	nearbyint_impl.hpp
 *
 *	@brief	nearbyint 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_NEARBYINT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_NEARBYINT_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
nearbyint_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::nearbyint(x);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
nearbyint_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isinf(x) || bksge::iszero(x) ?
			x :
		nearbyint_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_NEARBYINT_IMPL_HPP
