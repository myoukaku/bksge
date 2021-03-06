﻿/**
 *	@file	unit_test_fnd_cmath_legendre.cpp
 *
 *	@brief	legendre のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/legendre.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4305);	// 'initializing': truncation from 'double' to 'T'

namespace bksge_cmath_test
{

namespace legendre_test
{

static_assert(bksge::is_same<float,       decltype(bksge::legendre(0u, 0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::legendref(0u, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::legendre(0u, 0.0))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::legendre(0u, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::legendrel(0u, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::legendre(0u, 0))>::value, "");

template <typename T>
void LegendreTest(double error)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendre(0, nan)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendre(1, nan)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendre(2, T( 1) + eps)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendre(3, T(-1) - eps)));

	struct testcase
	{
		double expected;
		unsigned int n;
		T x;
	};

	testcase const testcases[] =
	{
		{ 1.0000000000000000, 0, -1.0},
		{ 1.0000000000000000, 0, -0.9},
		{ 1.0000000000000000, 0, -0.8},
		{ 1.0000000000000000, 0, -0.7},
		{ 1.0000000000000000, 0, -0.6},
		{ 1.0000000000000000, 0, -0.5},
		{ 1.0000000000000000, 0, -0.4},
		{ 1.0000000000000000, 0, -0.3},
		{ 1.0000000000000000, 0, -0.2},
		{ 1.0000000000000000, 0, -0.1},
		{ 1.0000000000000000, 0,  0.0},
		{ 1.0000000000000000, 0,  0.1},
		{ 1.0000000000000000, 0,  0.2},
		{ 1.0000000000000000, 0,  0.3},
		{ 1.0000000000000000, 0,  0.4},
		{ 1.0000000000000000, 0,  0.5},
		{ 1.0000000000000000, 0,  0.6},
		{ 1.0000000000000000, 0,  0.7},
		{ 1.0000000000000000, 0,  0.8},
		{ 1.0000000000000000, 0,  0.9},
		{ 1.0000000000000000, 0,  1.0},

		{-1.0000000000000000, 1, -1.0},
		{-0.9000000000000000, 1, -0.9},
		{-0.8000000000000000, 1, -0.8},
		{-0.7000000000000000, 1, -0.7},
		{-0.6000000000000000, 1, -0.6},
		{-0.5000000000000000, 1, -0.5},
		{-0.4000000000000000, 1, -0.4},
		{-0.3000000000000000, 1, -0.3},
		{-0.2000000000000000, 1, -0.2},
		{-0.1000000000000000, 1, -0.1},
		{ 0.0000000000000000, 1,  0.0},
		{ 0.1000000000000000, 1,  0.1},
		{ 0.2000000000000000, 1,  0.2},
		{ 0.3000000000000000, 1,  0.3},
		{ 0.4000000000000000, 1,  0.4},
		{ 0.5000000000000000, 1,  0.5},
		{ 0.6000000000000000, 1,  0.6},
		{ 0.7000000000000000, 1,  0.7},
		{ 0.8000000000000000, 1,  0.8},
		{ 0.9000000000000000, 1,  0.9},
		{ 1.0000000000000000, 1,  1.0},

		{ 1.0000000000000000, 2, -1.0},
		{ 0.7150000000000000, 2, -0.9},
		{ 0.4600000000000001, 2, -0.8},
		{ 0.2349999999999998, 2, -0.7},
		{ 0.0399999999999999, 2, -0.6},
		{-0.1250000000000000, 2, -0.5},
		{-0.2600000000000001, 2, -0.4},
		{-0.3650000000000000, 2, -0.3},
		{-0.4400000000000000, 2, -0.2},
		{-0.4849999999999999, 2, -0.1},
		{-0.5000000000000000, 2,  0.0},
		{-0.4849999999999999, 2,  0.1},
		{-0.4399999999999998, 2,  0.2},
		{-0.3649999999999999, 2,  0.3},
		{-0.2599999999999998, 2,  0.4},
		{-0.1250000000000000, 2,  0.5},
		{ 0.0400000000000001, 2,  0.6},
		{ 0.2350000000000003, 2,  0.7},
		{ 0.4600000000000001, 2,  0.8},
		{ 0.7150000000000003, 2,  0.9},
		{ 1.0000000000000000, 2,  1.0},

		{-1.0000000000000000, 5, -1.0},
		{ 0.0411412500000000, 5, -0.9},
		{ 0.3995199999999999, 5, -0.8},
		{ 0.3651987499999999, 5, -0.7},
		{ 0.1526399999999999, 5, -0.6},
		{-0.0898437500000000, 5, -0.5},
		{-0.2706400000000001, 5, -0.4},
		{-0.3453862499999999, 5, -0.3},
		{-0.3075199999999999, 5, -0.2},
		{-0.1788287499999999, 5, -0.1},
		{ 0.0000000000000000, 5,  0.0},
		{ 0.1788287500000001, 5,  0.1},
		{ 0.3075200000000001, 5,  0.2},
		{ 0.3453862500000000, 5,  0.3},
		{ 0.2706399999999998, 5,  0.4},
		{ 0.0898437500000000, 5,  0.5},
		{-0.1526400000000001, 5,  0.6},
		{-0.3651987500000002, 5,  0.7},
		{-0.3995199999999999, 5,  0.8},
		{-0.0411412499999991, 5,  0.9},
		{ 1.0000000000000000, 5,  1.0},

		{ 1.0000000000000000, 10, -1.0},
		{-0.2631456178558596, 10, -0.9},
		{ 0.3005297956000000, 10, -0.8},
		{ 0.0858057955316403, 10, -0.7},
		{-0.2436627456000000, 10, -0.6},
		{-0.1882286071777343, 10, -0.5},
		{ 0.0968390644000002, 10, -0.4},
		{ 0.2514763495160156, 10, -0.3},
		{ 0.1290720255999998, 10, -0.2},
		{-0.1221249973871094, 10, -0.1},
		{-0.2460937500000000, 10,  0.0},
		{-0.1221249973871092, 10,  0.1},
		{ 0.1290720256000004, 10,  0.2},
		{ 0.2514763495160156, 10,  0.3},
		{ 0.0968390643999996, 10,  0.4},
		{-0.1882286071777343, 10,  0.5},
		{-0.2436627455999998, 10,  0.6},
		{ 0.0858057955316412, 10,  0.7},
		{ 0.3005297956000000, 10,  0.8},
		{-0.2631456178558601, 10,  0.9},
		{ 1.0000000000000000, 10,  1.0},

		{ 1.0000000000000000, 20, -1.0},
		{-0.1493082353098483, 20, -0.9},
		{ 0.2242046054174134, 20, -0.8},
		{-0.2045739446383417, 20, -0.7},
		{ 0.1591675291009810, 20, -0.6},
		{-0.0483583810673735, 20, -0.5},
		{-0.1015926155862811, 20, -0.4},
		{ 0.1802871594799804, 20, -0.3},
		{-0.0980421943445947, 20, -0.2},
		{-0.0820771309445276, 20, -0.1},
		{ 0.1761970520019531, 20,  0.0},
		{-0.0820771309445280, 20,  0.1},
		{-0.0980421943445940, 20,  0.2},
		{ 0.1802871594799804, 20,  0.3},
		{-0.1015926155862819, 20,  0.4},
		{-0.0483583810673735, 20,  0.5},
		{ 0.1591675291009807, 20,  0.6},
		{-0.2045739446383413, 20,  0.7},
		{ 0.2242046054174134, 20,  0.8},
		{-0.1493082353098475, 20,  0.9},
		{ 1.0000000000000000, 20,  1.0},

		{ 1.0000000000000000, 50, -1.0},
		{-0.1700376599438367, 50, -0.9},
		{ 0.1387973734509311, 50, -0.8},
		{-0.0145727316458928, 50, -0.7},
		{-0.0588607988440020, 50, -0.6},
		{-0.0310590992396098, 50, -0.5},
		{ 0.0415690333818246, 50, -0.4},
		{ 0.1091105157471479, 50, -0.3},
		{ 0.0834322722041974, 50, -0.2},
		{-0.0382058126613136, 50, -0.1},
		{-0.1122751726592170, 50,  0.0},
		{-0.0382058126613141, 50,  0.1},
		{ 0.0834322722041965, 50,  0.2},
		{ 0.1091105157471479, 50,  0.3},
		{ 0.0415690333818260, 50,  0.4},
		{-0.0310590992396098, 50,  0.5},
		{-0.0588607988440014, 50,  0.6},
		{-0.0145727316458907, 50,  0.7},
		{ 0.1387973734509311, 50,  0.8},
		{-0.1700376599438367, 50,  0.9},
		{ 1.0000000000000000, 50,  1.0},

		{ 1.0000000000000000, 100, -1.0},
		{ 0.1022658205587189, 100, -0.9},
		{ 0.0508611679135842, 100, -0.8},
		{-0.0771325071997786, 100, -0.7},
		{-0.0237470239051331, 100, -0.6},
		{-0.0605180259618611, 100, -0.5},
		{-0.0722582021256850, 100, -0.4},
		{ 0.0571273922028010, 100, -0.3},
		{ 0.0146818353556597, 100, -0.2},
		{-0.0638950984347502, 100, -0.1},
		{ 0.0795892373871787, 100,  0.0},
		{-0.0638950984347497, 100,  0.1},
		{ 0.0146818353556578, 100,  0.2},
		{ 0.0571273922028015, 100,  0.3},
		{-0.0722582021256840, 100,  0.4},
		{-0.0605180259618611, 100,  0.5},
		{-0.0237470239051342, 100,  0.6},
		{-0.0771325071997805, 100,  0.7},
		{ 0.0508611679135842, 100,  0.8},
		{ 0.1022658205587206, 100,  0.9},
		{ 1.0000000000000000, 100,  1.0},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::legendre(data.n, data.x);

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

template <typename T>
void LegendreTestInt(double error)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendre(0, T( 2))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendre(1, T(-2))));

	struct testcase
	{
		double expected;
		unsigned int n;
		T x;
	};

	testcase const testcases[] =
	{
		{ 1.0000000000000000, 0, -1},
		{ 1.0000000000000000, 0,  0},
		{ 1.0000000000000000, 0,  1},

		{-1.0000000000000000, 1, -1},
		{ 0.0000000000000000, 1,  0},
		{ 1.0000000000000000, 1,  1},

		{ 1.0000000000000000, 2, -1},
		{-0.5000000000000000, 2,  0},
		{ 1.0000000000000000, 2,  1},

		{-1.0000000000000000, 5, -1},
		{ 0.0000000000000000, 5,  0},
		{ 1.0000000000000000, 5,  1},

		{ 1.0000000000000000, 10, -1},
		{-0.2460937500000000, 10,  0},
		{ 1.0000000000000000, 10,  1},

		{ 1.0000000000000000, 20, -1},
		{ 0.1761970520019531, 20,  0},
		{ 1.0000000000000000, 20,  1},

		{ 1.0000000000000000, 50, -1},
		{-0.1122751726592170, 50,  0},
		{ 1.0000000000000000, 50,  1},

		{ 1.0000000000000000, 100, -1},
		{ 0.0795892373871787, 100,  0},
		{ 1.0000000000000000, 100,  1},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::legendre(data.n, data.x);

		{
			double tole = bksge::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

GTEST_TEST(CMathTest, LegendreTest)
{
	LegendreTest<float>      (0.001);
	LegendreTest<double>     (0.00000000001);
	LegendreTest<long double>(0.00000000001);

	LegendreTestInt<int>(0.00000000001);

	BKSGE_CONSTEXPR auto nanf = std::numeric_limits<float>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsf = std::numeric_limits<float>::epsilon();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendref(0, nanf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendref(1, nanf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendref(2,  1.0f + epsf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendref(3, -1.0f - epsf)));

	BKSGE_CONSTEXPR auto nanl = std::numeric_limits<long double>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsl = std::numeric_limits<long double>::epsilon();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendrel(0, nanl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendrel(1, nanl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendrel(2,  1.0l + epsl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::legendrel(3, -1.0l - epsl)));
}

}	// namespace legendre_test

}	// namespace bksge_cmath_test

BKSGE_WARNING_POP();
