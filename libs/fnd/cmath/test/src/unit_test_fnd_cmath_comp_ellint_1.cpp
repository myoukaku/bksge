/**
 *	@file	unit_test_fnd_cmath_comp_ellint_1.cpp
 *
 *	@brief	comp_ellint_1 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/comp_ellint_1.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace comp_ellint_1_test
{

static_assert(bksge::is_same<float,       decltype(bksge::comp_ellint_1(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_1(0.0))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_1(0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_1(0))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::comp_ellint_1f(0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_1l(0.0l))>::value, "");

template <typename T>
void CompEllint1TestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1(nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1(T( 1) + eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1(T(-1) - eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1(max)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1(lowest)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1(+inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1(-inf)));

	struct testcase
	{
		double expected;
		T k;
	};

	testcase const testcases[] =
	{
		{inf,                T(-1.0)},
		{2.2805491384227703, T(-0.9)},
		{1.9953027776647294, T(-0.8)},
		{1.8456939983747234, T(-0.7)},
		{1.7507538029157526, T(-0.6)},
		{1.6857503548125961, T(-0.5)},
		{1.6399998658645112, T(-0.4)},
		{1.6080486199305128, T(-0.3)},
		{1.5868678474541662, T(-0.2)},
		{1.5747455615173560, T(-0.1)},
		{1.5707963267948966, T( 0.0)},
		{1.5747455615173560, T( 0.1)},
		{1.5868678474541662, T( 0.2)},
		{1.6080486199305128, T( 0.3)},
		{1.6399998658645112, T( 0.4)},
		{1.6857503548125961, T( 0.5)},
		{1.7507538029157526, T( 0.6)},
		{1.8456939983747238, T( 0.7)},
		{1.9953027776647294, T( 0.8)},
		{2.2805491384227707, T( 0.9)},
		{inf,                T( 1.0)},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::comp_ellint_1(data.k);

		if (bksge::isinf(data.expected))
		{
			EXPECT_EQ(data.expected, r);
		}
		else
		{
			double tole = bksge::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

template <typename T>
void CompEllint1TestInt()
{
	double const error = 0.000000000000001;

	BKSGE_CONSTEXPR auto inf = std::numeric_limits<double>::infinity();

	EXPECT_EQ  (inf,                bksge::comp_ellint_1(T(-1)));
	EXPECT_NEAR(1.5707963267948966, bksge::comp_ellint_1(T( 0)), error);
	EXPECT_EQ  (inf,                bksge::comp_ellint_1(T( 1)));
}

GTEST_TEST(CMathTest, CompEllint1Test)
{
	CompEllint1TestFloat<float>      (0.0000001);
	CompEllint1TestFloat<double>     (0.000000000000001);
	CompEllint1TestFloat<long double>(0.000000000000001);

	CompEllint1TestInt<int>();
	CompEllint1TestInt<short>();

	BKSGE_CONSTEXPR auto nanf = std::numeric_limits<float>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsf = std::numeric_limits<float>::epsilon();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1f(nanf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1f( 1.0f + epsf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1f(-1.0f - epsf)));

	BKSGE_CONSTEXPR auto nanl = std::numeric_limits<long double>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsl = std::numeric_limits<long double>::epsilon();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1l(nanl)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1l( 1.0l + epsl)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_1l(-1.0l - epsl)));
}

}	// namespace comp_ellint_1_test

}	// namespace bksge_cmath_test
