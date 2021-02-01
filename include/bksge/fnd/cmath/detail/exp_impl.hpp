/**
 *	@file	exp_impl.hpp
 *
 *	@brief	exp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXP_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_EXP_IMPL_HPP

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
exp_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_expf(x);
}

inline BKSGE_CONSTEXPR double
exp_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_exp(x);
}

inline BKSGE_CONSTEXPR long double
exp_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_expl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
exp_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::exp(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
exp_impl(FloatType x) BKSGE_NOEXCEPT
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
		exp_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXP_IMPL_HPP
