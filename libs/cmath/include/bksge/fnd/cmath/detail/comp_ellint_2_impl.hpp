/**
 *	@file	comp_ellint_2_impl.hpp
 *
 *	@brief	comp_ellint_2 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_COMP_ELLINT_2_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_COMP_ELLINT_2_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/detail/ellint_rf.hpp>
#include <bksge/fnd/cmath/detail/ellint_rd.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
comp_ellint_2_unchecked(double k)
{
	return std::comp_ellint_2(k);
}

inline /*BKSGE_CONSTEXPR*/ float
comp_ellint_2_unchecked(float k)
{
	return std::comp_ellint_2f(k);
}

inline /*BKSGE_CONSTEXPR*/ long double
comp_ellint_2_unchecked(long double k)
{
	return std::comp_ellint_2l(k);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
comp_ellint_2_unchecked_2(T k)
{
	T const kk = k * k;
	T const x = T(0);
	T const y = T(1) - kk;
	T const z = T(1);

	return bksge::detail::ellint_rf(x, y, z) - kk * bksge::detail::ellint_rd(x, y, z) / T(3);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
comp_ellint_2_unchecked(T k)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(comp_ellint_2_unchecked_2(static_cast<value_type>(k)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
comp_ellint_2_impl(T k)
{
	if (bksge::isnan(k))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::abs(k) > T(1))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::abs(k) == T(1))
	{
		return T(1);
	}

	return comp_ellint_2_unchecked(k);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_COMP_ELLINT_2_IMPL_HPP
