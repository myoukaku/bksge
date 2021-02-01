/**
 *	@file	ldexp_impl.hpp
 *
 *	@brief	ldexp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LDEXP_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LDEXP_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/limits.hpp>
#include <cmath>	// TODO

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
ldexp_unchecked(float x, int exp) BKSGE_NOEXCEPT
{
	return __builtin_ldexpf(x, exp);
}

inline BKSGE_CONSTEXPR double
ldexp_unchecked(double x, int exp) BKSGE_NOEXCEPT
{
	return __builtin_ldexp(x, exp);
}

inline BKSGE_CONSTEXPR long double
ldexp_unchecked(long double x, int exp) BKSGE_NOEXCEPT
{
	return __builtin_ldexpl(x, exp);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
ldexp_unchecked(T x, int exp) BKSGE_NOEXCEPT
{
	return std::ldexp(x, exp);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
ldexp_impl(FloatType x, int exp) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) || bksge::isinf(x) || (exp == 0) || bksge::isnan(x) ?
			x :
		ldexp_unchecked(x, exp);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LDEXP_IMPL_HPP
