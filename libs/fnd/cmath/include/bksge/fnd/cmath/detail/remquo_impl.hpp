/**
 *	@file	remquo_impl.hpp
 *
 *	@brief	remquo 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_REMQUO_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_REMQUO_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
remquo_unchecked(T x, T y, int* quo) BKSGE_NOEXCEPT
{
	return std::remquo(x, y, quo);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
remquo_impl(FloatType x, FloatType y, int* quo) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ||
		bksge::isnan(y) ||
		bksge::isinf(x) ||
		bksge::iszero(y) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		remquo_unchecked(x, y, quo);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_REMQUO_IMPL_HPP
