/**
 *	@file	scalbn_impl.hpp
 *
 *	@brief	scalbn 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SCALBN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SCALBN_IMPL_HPP

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
scalbn_unchecked(float x, int exp) BKSGE_NOEXCEPT
{
	return __builtin_scalbnf(x, exp);
}

inline BKSGE_CONSTEXPR double
scalbn_unchecked(double x, int exp) BKSGE_NOEXCEPT
{
	return __builtin_scalbn(x, exp);
}

inline BKSGE_CONSTEXPR long double
scalbn_unchecked(long double x, int exp) BKSGE_NOEXCEPT
{
	return __builtin_scalbnl(x, exp);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
scalbn_unchecked(T x, int exp) BKSGE_NOEXCEPT
{
	return std::scalbn(x, exp);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
scalbn_impl(FloatType x, int exp) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) || bksge::isinf(x) || (exp == 0) || bksge::isnan(x) ?
			x :
		scalbn_unchecked(x, exp);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SCALBN_IMPL_HPP
