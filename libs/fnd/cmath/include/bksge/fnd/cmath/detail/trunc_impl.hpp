/**
 *	@file	trunc_impl.hpp
 *
 *	@brief	trunc 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_TRUNC_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_TRUNC_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cstdint/uintmax_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
trunc_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_truncf(x);
}

inline BKSGE_CONSTEXPR double
trunc_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_trunc(x);
}

inline BKSGE_CONSTEXPR long double
trunc_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_truncl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
trunc_unchecked(T x) BKSGE_NOEXCEPT
{
	return x < 0 ?
		-static_cast<T>(static_cast<bksge::uintmax_t>(-x)) :
		 static_cast<T>(static_cast<bksge::uintmax_t>( x));
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
trunc_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isinf(x) || bksge::iszero(x) ?
			x :
		trunc_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_TRUNC_IMPL_HPP
