/**
 *	@file	erf_impl.hpp
 *
 *	@brief	erf 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ERF_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ERF_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
erf_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::erf(x);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
erf_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) || bksge::isnan(x)?
			x :
		bksge::isinf(x) ?
			bksge::copysign(FloatType(1), x) :
		erf_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ERF_IMPL_HPP
