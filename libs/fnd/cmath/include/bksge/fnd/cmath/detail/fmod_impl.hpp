/**
 *	@file	fmod_impl.hpp
 *
 *	@brief	fmod 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_FMOD_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_FMOD_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/trunc.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
fmod_unchecked(T x, T y) BKSGE_NOEXCEPT
{
	return x - (bksge::trunc(x / y) * y);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
fmod_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isnan(y) || bksge::isinf(x) || bksge::iszero(y) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::iszero(x) || bksge::isinf(y) ?
			x :
		fmod_unchecked(x, y);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_FMOD_IMPL_HPP
