/**
 *	@file	nexttoward.hpp
 *
 *	@brief	nexttoward 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_NEXTTOWARD_HPP
#define BKSGE_FND_CMATH_NEXTTOWARD_HPP

#include <bksge/fnd/cmath/detail/nexttoward_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

inline BKSGE_CONSTEXPR float
nexttoward(float from, long double to) BKSGE_NOEXCEPT
{
	return detail::nexttoward_impl(from, to);
}

inline BKSGE_CONSTEXPR float
nexttowardf(float from, long double to) BKSGE_NOEXCEPT
{
	return detail::nexttoward_impl(from, to);
}

inline BKSGE_CONSTEXPR double
nexttoward(double from, long double to) BKSGE_NOEXCEPT
{
	return detail::nexttoward_impl(from, to);
}

inline BKSGE_CONSTEXPR long double
nexttoward(long double from, long double to) BKSGE_NOEXCEPT
{
	return detail::nexttoward_impl(from, to);
}

inline BKSGE_CONSTEXPR long double
nexttowardl(long double from, long double to) BKSGE_NOEXCEPT
{
	return detail::nexttoward_impl(from, to);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
nexttoward(IntegralType from, long double to) BKSGE_NOEXCEPT
{
	return detail::nexttoward_impl(static_cast<double>(from), to);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_NEXTTOWARD_HPP
