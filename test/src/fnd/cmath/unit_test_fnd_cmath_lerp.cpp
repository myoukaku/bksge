/**
 *	@file	unit_test_fnd_cmath_lerp.cpp
 *
 *	@brief	lerp のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/lerp.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
//#include <bksge/fnd/cmath/isfinite.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace lerp_test
{

template <typename T>
void LerpTest(void)
{
	//BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	//BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	// When isfinite(a) && isfinite(b):
	// ・If t == 0, the result is equal to a.
	// ・If t == 1, the result is equal to b.
	// ・If t >= 0 && t <= 1, the result is finite.
	// ・If isfinite(t) && a == b, the result is equal to a.
	// ・If isfinite(t) || (!isnan(t) && b-a != 0), the result is not NaN.

	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T(-20.0), bksge::lerp(T( 0.0), T(10.0), T(-2.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T(-10.0), bksge::lerp(T( 0.0), T(10.0), T(-1.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T(  0.0), bksge::lerp(T( 0.0), T(10.0), T( 0.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T(  2.5), bksge::lerp(T( 0.0), T(10.0), T( 0.25)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T(  5.0), bksge::lerp(T( 0.0), T(10.0), T( 0.5)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T(  7.5), bksge::lerp(T( 0.0), T(10.0), T( 0.75)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T( 10.0), bksge::lerp(T( 0.0), T(10.0), T( 1.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T( 20.0), bksge::lerp(T( 0.0), T(10.0), T( 2.0)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(min, bksge::lerp(min, max, T(0.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(max, bksge::lerp(min, max, T(1.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(max, bksge::lerp(max, min, T(0.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(min, bksge::lerp(max, min, T(1.0)));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(std::isfinite(bksge::lerp(min, max, T(0.1))));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(std::isfinite(bksge::lerp(min, max, T(0.5))));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(std::isfinite(bksge::lerp(min, max, T(0.9))));

	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::lerp(T( 0.0), T( 0.0), min));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T( 0.0), bksge::lerp(T( 0.0), T( 0.0), max));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T(10.0), bksge::lerp(T(10.0), T(10.0), min));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(T(10.0), bksge::lerp(T(10.0), T(10.0), max));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(min, bksge::lerp(min, min, T(0.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(min, bksge::lerp(min, min, T(0.5)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(min, bksge::lerp(min, min, T(1.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(min, bksge::lerp(min, min, min));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(min, bksge::lerp(min, min, max));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(max, bksge::lerp(max, max, T(0.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(max, bksge::lerp(max, max, T(0.5)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(max, bksge::lerp(max, max, T(1.0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(max, bksge::lerp(max, max, min));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(max, bksge::lerp(max, max, max));

	// TODO
	//BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(bksge::lerp(T(0.0), T(1.0), inf)));
	//BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(bksge::lerp(min,    max,    inf)));
	//BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::isnan(bksge::lerp(max,    min,    inf)));
}

GTEST_TEST(CMathTest, LerpTest)
{
	LerpTest<float>();
	LerpTest<double>();
	LerpTest<long double>();
}

}	// namespace lerp_test

}	// namespace bksge_cmath_test
