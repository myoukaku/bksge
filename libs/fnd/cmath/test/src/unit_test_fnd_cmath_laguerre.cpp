/**
 *	@file	unit_test_fnd_cmath_laguerre.cpp
 *
 *	@brief	laguerre のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/laguerre.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace laguerre_test
{

static_assert(bksge::is_same<float,       decltype(bksge::laguerre(0u, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::laguerref(0u, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::laguerre(0u, 0.0))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::laguerre(0u, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::laguerrel(0u, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::laguerre(0u, 0))>::value, "");

template <typename T>
void LaguerreTest(double error)
{
	using Promoted = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<Promoted>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<Promoted>::infinity();
	BKSGE_CONSTEXPR auto min = std::numeric_limits<Promoted>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<Promoted>::max();

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerre(0, nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerre(1, nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerre(0, T(-1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerre(1, T(-1))));

	struct testcase
	{
		double expected;
		unsigned int n;
		T x;
	};

	testcase const testcases[] =
	{
		{ 1.0000000000000000, 0,   0},
		{ 1.0000000000000000, 0,  10},
		{ 1.0000000000000000, 0,  20},
		{ 1.0000000000000000, 0,  30},
		{ 1.0000000000000000, 0,  40},
		{ 1.0000000000000000, 0,  50},
		{ 1.0000000000000000, 0,  60},
		{ 1.0000000000000000, 0,  70},
		{ 1.0000000000000000, 0,  80},
		{ 1.0000000000000000, 0,  90},
		{ 1.0000000000000000, 0, 100},

		{ 1.0000000000000000, 1,   0},
		{-9.0000000000000000, 1,  10},
		{-19.000000000000000, 1,  20},
		{-29.000000000000000, 1,  30},
		{-39.000000000000000, 1,  40},
		{-49.000000000000000, 1,  50},
		{-59.000000000000000, 1,  60},
		{-69.000000000000000, 1,  70},
		{-79.000000000000000, 1,  80},
		{-89.000000000000000, 1,  90},
		{-99.000000000000000, 1, 100},

		{ 1.0000000000000000, 2,   0},
		{ 31.000000000000000, 2,  10},
		{ 161.00000000000000, 2,  20},
		{ 391.00000000000000, 2,  30},
		{ 721.00000000000000, 2,  40},
		{ 1151.0000000000000, 2,  50},
		{ 1681.0000000000000, 2,  60},
		{ 2311.0000000000000, 2,  70},
		{ 3041.0000000000000, 2,  80},
		{ 3871.0000000000000, 2,  90},
		{ 4801.0000000000000, 2, 100},

		{ 1.0000000000000000, 5,   0},
		{ 34.333333333333333, 5,  10},
		{-4765.6666666666666, 5,  20},
		{-74399.000000000000, 5,  30},
		{-418865.66666666666, 5,  40},
		{-1498165.6666666666, 5,  50},
		{-4122299.0000000000, 5,  60},
		{-9551265.6666666666, 5,  70},
		{-19595065.666666666, 5,  80},
		{-36713699.000000000, 5,  90},
		{-64117165.666666666, 5, 100},

		{ 1.0000000000000000, 10,   0},
		{ 27.984126984126977, 10,  10},
		{ 3227.8077601410932, 10,  20},
		{ 15129.571428571455, 10,  30},
		{ 79724066.608465582, 10,  40},
		{ 2037190065.3738980, 10,  50},
		{ 21804200401.000000, 10,  60},
		{ 144688291819.51855, 10,  70},
		{ 703324772760.08276, 10,  80},
		{ 2741055412243.8569, 10,  90},
		{ 9051283795429.5723, 10, 100},

		{ 1.0000000000000000, 20,   0},
		{-11.961333867812119, 20,  10},
		{ 2829.4728613531743, 20,  20},
		{-18439.424502520938, 20,  30},
		{ 24799805.877530713, 20,  40},
		{ 7551960453.7672548, 20,  50},
		{-1379223608444.9155, 20,  60},
		{ 165423821874449.94, 20,  70},
		{ 29500368536981676., 20,  80},
		{ 1.1292309514432901e+18, 20,  90},
		{ 2.2061882785931735e+19, 20, 100},

		{ 1.0000000000000000, 50,   0},
		{ 17.534183446338233, 50,  10},
		{ 980.26961889791028, 50,  20},
		{ 293000.50735962362, 50,  30},
		{-14896937.968694873, 50,  40},
		{ 2513677852.6916871, 50,  50},
		{-883876565337.99219, 50,  60},
		{-80967880733583.234, 50,  70},
		{-8217471769564841.0, 50,  80},
		{-2.1140031308048891e+18, 50,  90},
		{-3.9710103487094692e+20, 50, 100},

		{ 1.0000000000000000, 100,   0},
		{ 13.277662844303450, 100,  10},
		{ 1854.0367283243388, 100,  20},
		{ 170141.86987046551, 100,  30},
		{-7272442.3156006960, 100,  40},
		{ 4847420871.2690506, 100,  50},
		{ 693492765740.29688, 100,  60},
		{ 17125518672239.770, 100,  70},
		{-13763178176383768., 100,  80},
		{ 2.1307220490380173e+18, 100,  90},
		{-2.6292260693068916e+20, 100, 100},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::laguerre(data.n, data.x);

		if (data.expected > max)
		{
			EXPECT_EQ(+inf, r);
		}
		else if (data.expected < min)
		{
			EXPECT_EQ(-inf, r);
		}
		else
		{
			double tole = bksge::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

GTEST_TEST(CMathTest, LaguerreTest)
{
	LaguerreTest<float>      (0.0000001);
	LaguerreTest<double>     (0.0000000000001);
	LaguerreTest<long double>(0.0000000000001);
	LaguerreTest<int>        (0.0000000000001);

	BKSGE_CONSTEXPR auto nanf = std::numeric_limits<float>::quiet_NaN();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerref(0, nanf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerref(1, nanf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerref(0, -1.0f)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerref(1, -1.0f)));

	BKSGE_CONSTEXPR auto nanl = std::numeric_limits<long double>::quiet_NaN();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerrel(0, nanl)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerrel(1, nanl)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerrel(0, -1.0l)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::laguerrel(1, -1.0l)));
}

}	// namespace laguerre_test

}	// namespace bksge_cmath_test
