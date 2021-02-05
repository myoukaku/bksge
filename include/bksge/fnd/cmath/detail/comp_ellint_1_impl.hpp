/**
 *	@file	comp_ellint_1_impl.hpp
 *
 *	@brief	comp_ellint_1 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_COMP_ELLINT_1_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_COMP_ELLINT_1_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>


#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/algorithm/max.hpp>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
comp_ellint_1_unchecked(double k)
{
	return std::comp_ellint_1(k);
}

inline /*BKSGE_CONSTEXPR*/ float
comp_ellint_1_unchecked(float k)
{
	return std::comp_ellint_1f(k);
}

inline /*BKSGE_CONSTEXPR*/ long double
comp_ellint_1_unchecked(long double k)
{
	return std::comp_ellint_1l(k);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_rf(T x, T y, T z)
{
	const T lolim = T(5) * bksge::numeric_limits<T>::min();

	if (x < T(0) || y < T(0) || z < T(0))
	{
		//bksge::throw_domain_error("Argument less than zero in ellint_rf.");
		return bksge::numeric_limits<T>::quiet_NaN();
	}
	else if (x + y < lolim || x + z < lolim || y + z < lolim)
	{
		//bksge::throw_domain_error("Argument too small in ellint_rf");
		return bksge::numeric_limits<T>::quiet_NaN();
	}
	else
	{
		const T c0 = T(1) / T(4);
		const T c1 = T(1) / T(24);
		const T c2 = T(1) / T(10);
		const T c3 = T(3) / T(44);
		const T c4 = T(1) / T(14);

		T xn = x;
		T yn = y;
		T zn = z;

		const T eps = bksge::numeric_limits<T>::epsilon();
		const T errtol = bksge::pow(eps, T(1) / T(6));
		T mu;
		T xndev, yndev, zndev;

		const unsigned int max_iter = 100;
		for (unsigned int iter = 0; iter < max_iter; ++iter)
		{
			mu = (xn + yn + zn) / T(3);
			xndev = 2 - (mu + xn) / mu;
			yndev = 2 - (mu + yn) / mu;
			zndev = 2 - (mu + zn) / mu;
			T const epsilon = bksge::max({bksge::abs(xndev), bksge::abs(yndev), bksge::abs(zndev)});
			if (epsilon < errtol)
			{
				break;
			}
			const T xnroot = bksge::sqrt(xn);
			const T ynroot = bksge::sqrt(yn);
			const T znroot = bksge::sqrt(zn);
			const T lambda = xnroot * (ynroot + znroot) + ynroot * znroot;
			xn = c0 * (xn + lambda);
			yn = c0 * (yn + lambda);
			zn = c0 * (zn + lambda);
		}

		const T e2 = xndev * yndev - zndev * zndev;
		const T e3 = xndev * yndev * zndev;
		const T s  = T(1) + (c1 * e2 - c2 - c3 * e3) * e2 + c4 * e3;

		return s / bksge::sqrt(mu);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
comp_ellint_1_unchecked_2(T k)
{
	return ellint_rf(T(0), T(1) - k * k, T(1));
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
comp_ellint_1_unchecked(T k)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(comp_ellint_1_unchecked_2(static_cast<value_type>(k)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
comp_ellint_1_impl(T k)
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
		return bksge::numeric_limits<T>::infinity();
	}

	return comp_ellint_1_unchecked(k);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_COMP_ELLINT_1_IMPL_HPP
