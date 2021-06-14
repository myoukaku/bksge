/**
 *	@file	sinh_impl.hpp
 *
 *	@brief	sinh 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SINH_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SINH_IMPL_HPP

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
sinh_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_sinhf(x);
}

inline BKSGE_CONSTEXPR double
sinh_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_sinh(x);
}

inline BKSGE_CONSTEXPR long double
sinh_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_sinhl(x);
}

#else

//template <typename T>
//inline BKSGE_CONSTEXPR T
//sinh_unchecked_1(T x) BKSGE_NOEXCEPT
//{
//	return T(0.5) * x - T(0.5) / x;
//}

template <typename T>
inline BKSGE_CONSTEXPR T
sinh_unchecked(T x) BKSGE_NOEXCEPT
{
	//return sinh_unchecked_1(bksge::exp(x));
	return std::sinh(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
sinh_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) || bksge::isinf(x) || bksge::isnan(x) ?
			x :
		sinh_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SINH_IMPL_HPP
