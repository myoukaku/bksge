/**
 *	@file	issubnormal_impl.hpp
 *
 *	@brief	issubnormal 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ISSUBNORMAL_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ISSUBNORMAL_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR bool
issubnormal_or_zero(T x) BKSGE_NOEXCEPT
{
	return
		x > 0 ?
			x <  (bksge::numeric_limits<T>::min)():
			x > -(bksge::numeric_limits<T>::min)();
}

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
issubnormal_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		!bksge::isnan(x) &&
		!bksge::iszero(x) &&
		issubnormal_or_zero(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ISSUBNORMAL_IMPL_HPP
