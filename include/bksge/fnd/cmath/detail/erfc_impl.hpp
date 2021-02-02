/**
 *	@file	erfc_impl.hpp
 *
 *	@brief	erfc 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ERFC_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ERFC_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
erfc_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::erfc(x);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
erfc_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x)?
			x :
		bksge::isinf(x) ?
			bksge::signbit(x) ?
				FloatType(+2.0) :
				FloatType(+0.0) :
		erfc_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ERFC_IMPL_HPP
