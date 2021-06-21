/**
 *	@file	sph_bessel_impl.hpp
 *
 *	@brief	sph_bessel 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SPH_BESSEL_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SPH_BESSEL_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/detail/sph_bessel_jn.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
sph_bessel_unchecked(unsigned int n, double x)
{
	return std::sph_bessel(n, x);
}

inline /*BKSGE_CONSTEXPR*/ float
sph_bessel_unchecked(unsigned int n, float x)
{
	return std::sph_besself(n, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
sph_bessel_unchecked(unsigned int n, long double x)
{
	return std::sph_bessell(n, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
sph_bessel_unchecked_2(unsigned int n, T x)
{
	if (x == T(0))
	{
		if (n == 0)
		{
			return T(1);
		}
		else
		{
			return T(0);
		}
	}
	else
	{
		T j_n, n_n, jp_n, np_n;
		bksge::detail::sph_bessel_jn(n, x, j_n, n_n, jp_n, np_n);
		return j_n;
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
sph_bessel_unchecked(unsigned int n, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(sph_bessel_unchecked_2(n, static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
sph_bessel_impl(unsigned int n, T x)
{
	if (bksge::isnan(x))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	return sph_bessel_unchecked(n, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SPH_BESSEL_IMPL_HPP
