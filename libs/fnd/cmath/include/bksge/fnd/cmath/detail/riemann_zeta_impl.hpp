/**
 *	@file	riemann_zeta_impl.hpp
 *
 *	@brief	riemann_zeta 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/cmath/lgamma.hpp>
#include <bksge/fnd/cmath/tgamma.hpp>
#include <bksge/fnd/cmath/detail/riemann_zeta_product.hpp>
#include <bksge/fnd/cmath/detail/riemann_zeta_glob.hpp>
#include <bksge/fnd/cmath/detail/riemann_zeta_sum.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
riemann_zeta_unchecked(double x)
{
	return std::riemann_zeta(x);
}

inline /*BKSGE_CONSTEXPR*/ float
riemann_zeta_unchecked(float x)
{
	return std::riemann_zetaf(x);
}

inline /*BKSGE_CONSTEXPR*/ long double
riemann_zeta_unchecked(long double x)
{
	return std::riemann_zetal(x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
riemann_zeta_unchecked_2(T x)
{
	if (x < -T(19))
	{
		return
			bksge::detail::riemann_zeta_product(T(1) - x) *
			bksge::pow(T(2) * bksge::pi_t<T>(), x) *
			bksge::sin((bksge::pi_t<T>() / 2) * x) *
			bksge::exp(bksge::lgamma(T(1) - x)) /
			bksge::pi_t<T>();
	}
	else if (x < T(20))
	{
		//  Global double sum or McLaurin?
		bool glob = true;
		if (glob)
		{
			return bksge::detail::riemann_zeta_glob(x);
		}
		else
		{
			if (x > T(1))
			{
				return bksge::detail::riemann_zeta_sum(x);
			}
			else
			{
				return
					bksge::pow(T(2) *
					bksge::pi_t<T>(), x) *
					bksge::sin((bksge::pi_t<T>() / 2) * x) *
					bksge::tgamma(T(1) - x) *
					bksge::detail::riemann_zeta_sum(T(1) - x);
			}
		}
	}
	else
	{
		return bksge::detail::riemann_zeta_product(x);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
riemann_zeta_unchecked(T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(riemann_zeta_unchecked_2(static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
riemann_zeta_impl(T x)
{
	if (bksge::isnan(x))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	if (x == T(1))
	{
		return std::numeric_limits<T>::infinity();
	}

	return riemann_zeta_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_IMPL_HPP
