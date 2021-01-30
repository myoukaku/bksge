/**
 *	@file	nextafter.hpp
 *
 *	@brief	nextafter 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_NEXTAFTER_HPP
#define BKSGE_FND_CMATH_NEXTAFTER_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
nextafter_impl(FloatType from, FloatType to) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(from) || bksge::isnan(to) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		std::nextafter(from, to);
}

}	// namespace detail

inline BKSGE_CONSTEXPR float
nextafter(float from, float to) BKSGE_NOEXCEPT
{
	return detail::nextafter_impl(from, to);
}

inline BKSGE_CONSTEXPR float
nextafterf(float from, float to) BKSGE_NOEXCEPT
{
	return detail::nextafter_impl(from, to);
}

inline BKSGE_CONSTEXPR double
nextafter(double from, double to) BKSGE_NOEXCEPT
{
	return detail::nextafter_impl(from, to);
}

inline BKSGE_CONSTEXPR long double
nextafter(long double from, long double to) BKSGE_NOEXCEPT
{
	return detail::nextafter_impl(from, to);
}

inline BKSGE_CONSTEXPR long double
nextafterl(long double from, long double to) BKSGE_NOEXCEPT
{
	return detail::nextafter_impl(from, to);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
nextafter(Arithmetic1 from, Arithmetic2 to) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::nextafter_impl(static_cast<type>(from), static_cast<type>(to));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_NEXTAFTER_HPP
