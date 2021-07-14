/**
 *	@file	unit_test_fnd_cmath_comp_ellint_2.cpp
 *
 *	@brief	comp_ellint_2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/comp_ellint_2.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace comp_ellint_2_test
{

static_assert(bksge::is_same<float,       decltype(bksge::comp_ellint_2(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_2(0.0))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_2(0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_2(0))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::comp_ellint_2f(0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_2l(0.0l))>::value, "");

template <typename T>
void CompEllint2TestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2(nan)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2(T( 1) + eps)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2(T(-1) - eps)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2(max)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2(lowest)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2(+inf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2(-inf)));

	struct testcase
	{
		double expected;
		T k;
	};

	testcase const testcases[] =
	{
		{1.0000000000000000, T(-1.0)},
		{1.1716970527816142, T(-0.9)},
		{1.2763499431699064, T(-0.8)},
		{1.3556611355719554, T(-0.7)},
		{1.4180833944487243, T(-0.6)},
		{1.4674622093394272, T(-0.5)},
		{1.5059416123600404, T(-0.4)},
		{1.5348334649232491, T(-0.3)},
		{1.5549685462425293, T(-0.2)},
		{1.5668619420216683, T(-0.1)},
		{1.5707963267948966, T( 0.0)},
		{1.5668619420216683, T( 0.1)},
		{1.5549685462425293, T( 0.2)},
		{1.5348334649232491, T( 0.3)},
		{1.5059416123600402, T( 0.4)},
		{1.4674622093394272, T( 0.5)},
		{1.4180833944487241, T( 0.6)},
		{1.3556611355719554, T( 0.7)},
		{1.2763499431699064, T( 0.8)},
		{1.1716970527816140, T( 0.9)},
		{1.0000000000000000, T( 1.0)},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::comp_ellint_2(data.k);

		{
			double tole = bksge::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

template <typename T>
void CompEllint2TestInt()
{
	double const error = 0.00000000000001;

	EXPECT_EQ  (1.0000000000000000, bksge::comp_ellint_2(T(-1)));
	EXPECT_NEAR(1.5707963267948966, bksge::comp_ellint_2(T( 0)), error);
	EXPECT_EQ  (1.0000000000000000, bksge::comp_ellint_2(T( 1)));
}

GTEST_TEST(CMathTest, CompEllint2Test)
{
	CompEllint2TestFloat<float>      (0.000001);
	CompEllint2TestFloat<double>     (0.00000000000001);
	CompEllint2TestFloat<long double>(0.00000000000001);

	CompEllint2TestInt<int>();
	CompEllint2TestInt<short>();

	BKSGE_CONSTEXPR auto nanf = std::numeric_limits<float>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsf = std::numeric_limits<float>::epsilon();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2f(nanf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2f( 1.0f + epsf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2f(-1.0f - epsf)));

	BKSGE_CONSTEXPR auto nanl = std::numeric_limits<long double>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsl = std::numeric_limits<long double>::epsilon();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2l(nanl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2l( 1.0l + epsl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_2l(-1.0l - epsl)));
}

}	// namespace comp_ellint_2_test

}	// namespace bksge_cmath_test
