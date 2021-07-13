/**
 *	@file	complex_test_utility.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_COMPLEX_COMPLEX_TEST_UTILITY_HPP
#define UNIT_TEST_FND_COMPLEX_COMPLEX_TEST_UTILITY_HPP

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge_complex_test
{

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CXX14_CONSTEXPR bool
IsNear(T lhs, T rhs, double error)
{
	return
		(bksge::isnan(lhs) && bksge::isnan(rhs)) ||
		(bksge::isinf(lhs) && bksge::isinf(rhs) && bksge::signbit(lhs) == bksge::signbit(rhs)) ||
		bksge::fabs(lhs - rhs) <= error;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
IsNear(bksge::complex<T> const& lhs, bksge::complex<T> const& rhs, double error)
{
	return
		IsNear(lhs.real(), rhs.real(), error) &&
		IsNear(lhs.imag(), rhs.imag(), error);
}

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CXX14_CONSTEXPR bool
IsEqual(T lhs, T rhs)
{
	return
		(bksge::isnan(lhs) && bksge::isnan(rhs)) ||
		lhs == rhs;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
IsEqual(bksge::complex<T> const& lhs, bksge::complex<T> const& rhs)
{
	return
		IsEqual(lhs.real(), rhs.real()) &&
		IsEqual(lhs.imag(), rhs.imag());
}

}	// namespace bksge_complex_test

#endif // UNIT_TEST_FND_COMPLEX_COMPLEX_TEST_UTILITY_HPP
