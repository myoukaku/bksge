/**
 *	@file	scalbln_impl.hpp
 *
 *	@brief	scalbln 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SCALBLN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SCALBLN_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <cmath>	// TODO

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
scalbln_unchecked(float x, long exp) BKSGE_NOEXCEPT
{
	return __builtin_scalblnf(x, exp);
}

inline BKSGE_CONSTEXPR double
scalbln_unchecked(double x, long exp) BKSGE_NOEXCEPT
{
	return __builtin_scalbln(x, exp);
}

inline BKSGE_CONSTEXPR long double
scalbln_unchecked(long double x, long exp) BKSGE_NOEXCEPT
{
	return __builtin_scalblnl(x, exp);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
scalbln_unchecked(T x, long exp) BKSGE_NOEXCEPT
{
	return std::scalbln(x, exp);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
scalbln_impl(FloatType x, long exp) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) || bksge::isinf(x) || (exp == 0) || bksge::isnan(x) ?
			x :
		scalbln_unchecked(x, exp);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SCALBLN_IMPL_HPP
