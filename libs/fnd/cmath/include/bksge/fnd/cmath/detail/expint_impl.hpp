/**
 *	@file	expint_impl.hpp
 *
 *	@brief	expint 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXPINT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_EXPINT_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/detail/expint_ei.hpp>
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
expint_unchecked(double x)
{
	return std::expint(x);
}

inline /*BKSGE_CONSTEXPR*/ float
expint_unchecked(float x)
{
	return std::expintf(x);
}

inline /*BKSGE_CONSTEXPR*/ long double
expint_unchecked(long double x)
{
	return std::expintl(x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
expint_unchecked_2(T x)
{
	return bksge::detail::expint_Ei(x);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
expint_unchecked(T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(expint_unchecked_2(static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
expint_impl(T x)
{
	if (bksge::isnan(x))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::iszero(x))
	{
		return -std::numeric_limits<T>::infinity();
	}

	return expint_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXPINT_IMPL_HPP
