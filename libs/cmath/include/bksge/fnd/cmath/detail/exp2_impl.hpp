/**
 *	@file	exp2_impl.hpp
 *
 *	@brief	exp2 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXP2_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_EXP2_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <cmath>	// TODO

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
exp2_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_exp2f(x);
}

inline BKSGE_CONSTEXPR double
exp2_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_exp2(x);
}

inline BKSGE_CONSTEXPR long double
exp2_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_exp2l(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
exp2_unchecked(T x) BKSGE_NOEXCEPT
{
//	return bksge::exp(x * bksge::ln_two<T>());
	return std::exp2(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
exp2_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			FloatType(1) :
		bksge::isinf(x) ?
			bksge::signbit(x) ?
				FloatType(0) :
			x :
		bksge::isnan(x) ?
			x :
		exp2_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXP2_IMPL_HPP
