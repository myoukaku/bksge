/**
 *	@file	sph_neumann_impl.hpp
 *
 *	@brief	sph_neumann 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SPH_NEUMANN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SPH_NEUMANN_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/detail/sph_bessel_jn.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
sph_neumann_unchecked(unsigned int n, double x)
{
	return std::sph_neumann(n, x);
}

inline /*BKSGE_CONSTEXPR*/ float
sph_neumann_unchecked(unsigned int n, float x)
{
	return std::sph_neumannf(n, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
sph_neumann_unchecked(unsigned int n, long double x)
{
	return std::sph_neumannl(n, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
sph_neumann_unchecked_2(unsigned int n, T x)
{
	T j_n, n_n, jp_n, np_n;
	bksge::detail::sph_bessel_jn(n, x, j_n, n_n, jp_n, np_n);
	return n_n;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
sph_neumann_unchecked(unsigned int n, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(sph_neumann_unchecked_2(n, static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
sph_neumann_impl(unsigned int n, T x)
{
	if (bksge::isnan(x))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	if (x == T(0))
	{
		return -bksge::numeric_limits<T>::infinity();
	}

	return sph_neumann_unchecked(n, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SPH_NEUMANN_IMPL_HPP
