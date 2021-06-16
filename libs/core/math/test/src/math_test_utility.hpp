/**
 *	@file	math_test_utility.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_CORE_MATH_MATH_TEST_UTILITY_HPP
#define UNIT_TEST_CORE_MATH_MATH_TEST_UTILITY_HPP

#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge_math_test
{

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CXX14_CONSTEXPR bool
IsNear(T lhs, T rhs, double error)
{
	return bksge::fabs(lhs - rhs) <= error;
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
IsNear(bksge::math::detail::VectorBase<T, N> const& lhs, bksge::math::detail::VectorBase<T, N> const& rhs, double error)
{
	for (bksge::size_t i = 0; i < N; ++i)
	{
		if (!IsNear(lhs[i], rhs[i], error))
		{
			return false;
		}
	}
	return true;
}

}	// namespace bksge_math_test

#endif // UNIT_TEST_CORE_MATH_MATH_TEST_UTILITY_HPP
