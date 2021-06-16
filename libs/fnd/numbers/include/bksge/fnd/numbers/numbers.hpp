/**
 *	@file	numbers.hpp
 *
 *	@brief	数学定数
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMBERS_NUMBERS_HPP
#define BKSGE_FND_NUMBERS_NUMBERS_HPP

#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/// e
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T e_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(2.718281828459045235360287471352662498L);
}

/// log_2 e
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T log2e_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(1.442695040888963407359924681001892137L);
}

/// log_10 e
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T log10e_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(0.434294481903251827651128918916605082L);
}

/// pi
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T pi_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(3.141592653589793238462643383279502884L);
}

/// 1/pi
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T inv_pi_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(0.318309886183790671537767526745028724L);
}

/// 1/sqrt(pi)
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T inv_sqrtpi_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(0.564189583547756286948079451560772586L);
}

/// log_e 2
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T ln2_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(0.693147180559945309417232121458176568L);
}

/// log_e 10
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T ln10_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(2.302585092994045684017991454684364208L);
}

/// sqrt(2)
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T sqrt2_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(1.414213562373095048801688724209698079L);
}

/// sqrt(3)
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T sqrt3_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(1.732050807568877293527446341505872367L);
}

/// 1/sqrt(3)
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T inv_sqrt3_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(0.577350269189625764509148780501957456L);
}

/// The Euler-Mascheroni constant
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T egamma_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(0.577215664901532860606512090082402431L);
}

/// The golden ratio, (1+sqrt(5))/2
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T phi_t() BKSGE_NOEXCEPT
{
	return static_cast<T>(1.618033988749894848204586834365638118L);
}

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T e_v = e_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T log2e_v = log2e_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T log10e_v = log10e_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T pi_v = pi_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T inv_pi_v = inv_pi_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T inv_sqrtpi_v = inv_sqrtpi_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T ln2_v = ln2_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T ln10_v = ln10_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T sqrt2_v = sqrt2_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T sqrt3_v = sqrt3_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T inv_sqrt3_v = inv_sqrt3_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T egamma_v = egamma_t<T>();

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR T phi_v = phi_t<T>();

#endif

BKSGE_INLINE_VAR BKSGE_CONSTEXPR double e          = e_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double log2e      = log2e_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double log10e     = log10e_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double pi         = pi_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double inv_pi     = inv_pi_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double inv_sqrtpi = inv_sqrtpi_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double ln2        = ln2_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double ln10       = ln10_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double sqrt2      = sqrt2_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double sqrt3      = sqrt3_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double inv_sqrt3  = inv_sqrt3_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double egamma     = egamma_t<double>();
BKSGE_INLINE_VAR BKSGE_CONSTEXPR double phi        = phi_t<double>();

}	// namespace bksge

#endif // BKSGE_FND_NUMBERS_NUMBERS_HPP
