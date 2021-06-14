/**
 *	@file	signbit_impl.hpp
 *
 *	@brief	signbit 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SIGNBIT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SIGNBIT_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
signbit_impl(FloatType x) BKSGE_NOEXCEPT
{
	return __builtin_signbit(x);
}

#else

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
signbit_impl(FloatType x) BKSGE_NOEXCEPT
{
	return (bksge::iszero(x) || bksge::isnan(x)) ?
		false :
		(x < FloatType(0));
}

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SIGNBIT_IMPL_HPP
