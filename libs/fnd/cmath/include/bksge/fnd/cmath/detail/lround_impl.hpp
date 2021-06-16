/**
 *	@file	lround_impl.hpp
 *
 *	@brief	lround 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LROUND_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LROUND_IMPL_HPP

#include <bksge/fnd/cmath/round.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR long
lround_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_lroundf(x);
}

inline BKSGE_CONSTEXPR long
lround_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_lround(x);
}

inline BKSGE_CONSTEXPR long
lround_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_lroundl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR long
lround_unchecked(T x) BKSGE_NOEXCEPT
{
	return static_cast<long>(round_unchecked(x));
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR long
lround_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			bksge::numeric_limits<long>::min() :
		x < (FloatType)bksge::numeric_limits<long>::min() ?
			bksge::numeric_limits<long>::min() :
		x > (FloatType)bksge::numeric_limits<long>::max() ?
			bksge::numeric_limits<long>::max() :
		lround_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LROUND_IMPL_HPP
