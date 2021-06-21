/**
 *	@file	unit_test_fnd_cmath_expint.cpp
 *
 *	@brief	expint のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/expint.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace expint_test
{

static_assert(bksge::is_same<float,       decltype(bksge::expint(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::expint(0.0))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::expint(0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::expint(0))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::expintf(0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::expintl(0.0l))>::value, "");

template <typename T>
void ExpintTest(double error)
{
	using Promoted = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<Promoted>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<Promoted>::infinity();

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::expint(nan)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::expint(T( 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::expint(T(-0)));

	struct testcase
	{
		double expected;
		T arg;
	};

	testcase const testcases[] =
	{
		{-3.7832640295504591e-24, -50},
		{-1.0489811642368024e-23, -49},
		{-2.9096641904058423e-23, -48},
		{-8.0741978427258127e-23, -47},
		{-2.2415317597442998e-22, -46},
		{-6.2256908094623848e-22, -45},
		{-1.7299598742816476e-21, -44},
		{-4.8094965569500181e-21, -43},
		{-1.3377908810011775e-20, -42},
		{-3.7231667764599780e-20, -41},
		{-1.0367732614516570e-19, -40},
		{-2.8887793015227007e-19, -39},
		{-8.0541069142907499e-19, -38},
		{-2.2470206975885710e-18, -37},
		{-6.2733390097622421e-18, -36},
		{-1.7527059389947371e-17, -35},
		{-4.9006761183927874e-17, -34},
		{-1.3713843484487468e-16, -33},
		{-3.8409618012250671e-16, -32},
		{-1.0767670386162381e-15, -31},
		{-3.0215520106888124e-15, -30},
		{-8.4877597783535634e-15, -29},
		{-2.3869415119337330e-14, -28},
		{-6.7206374352620390e-14, -27},
		{-1.8946858856749785e-13, -26},
		{-5.3488997553402167e-13, -25},
		{-1.5123058939997059e-12, -24},
		{-4.2826847956656722e-12, -23},
		{-1.2149378956204371e-11, -22},
		{-3.4532012671467559e-11, -21},
		{-9.8355252906498815e-11, -20},
		{-2.8078290970607954e-10, -19},
		{-8.0360903448286769e-10, -18},
		{-2.3064319898216543e-09, -17},
		{-6.6404872494410427e-09, -16},
		{-1.9186278921478670e-08, -15},
		{-5.5656311111451816e-08, -14},
		{-1.6218662188014328e-07, -13},
		{-4.7510818246724931e-07, -12},
		{-1.4003003042474418e-06, -11},
		{-4.1569689296853246e-06, -10},
		{-1.2447354178006272e-05,  -9},
		{-3.7665622843924906e-05,  -8},
		{-0.00011548173161033820,  -7},
		{-0.00036008245216265862,  -6},
		{-0.0011482955912753257,   -5},
		{-0.0037793524098489063,   -4},
		{-0.013048381094197037,    -3},
		{-0.048900510708061125,    -2},
		{-0.21938393439552029,     -1},
		{ 1.8951178163559366,       1},
		{ 4.9542343560018907,       2},
		{ 9.9338325706254160,       3},
		{ 19.630874470056217,       4},
		{ 40.185275355803178,       5},
		{ 85.989762142439204,       6},
		{ 191.50474333550136,       7},
		{ 440.37989953483833,       8},
		{ 1037.8782907170896,       9},
		{ 2492.2289762418782,      10},
		{ 6071.4063740986112,      11},
		{ 14959.532666397528,      12},
		{ 37197.688490689041,      13},
		{ 93192.513633965369,      14},
		{ 234955.85249076830,      15},
		{ 595560.99867083691,      16},
		{ 1516637.8940425171,      17},
		{ 3877904.3305974435,      18},
		{ 9950907.2510468438,      19},
		{ 25615652.664056588,      20},
		{ 66127186.355484933,      21},
		{ 171144671.30036369,      22},
		{ 443966369.83027118,      23},
		{ 1154115391.8491828,      24},
		{ 3005950906.5255494,      25},
		{ 7842940991.8981876,      26},
		{ 20496497119.880810,      27},
		{ 53645118592.314682,      28},
		{ 140599195758.40689,      29},
		{ 368973209407.27417,      30},
		{ 969455575968.39392,      31},
		{ 2550043566357.7871,      32},
		{ 6714640184076.4971,      33},
		{ 17698037244116.266,      34},
		{ 46690550144661.602,      35},
		{ 123285207991209.75,      36},
		{ 325798899867226.50,      37},
		{ 861638819996578.75,      38},
		{ 2280446200301902.5,      39},
		{ 6039718263611242.0,      40},
		{ 16006649143245042.,      41},
		{ 42447960921368512.,      42},
		{ 1.1263482901669666e+17,  43},
		{ 2.9904447186323366e+17,  44},
		{ 7.9439160357044531e+17,  45},
		{ 2.1113423886478239e+18,  46},
		{ 5.6143296808103424e+18,  47},
		{ 1.4936302131129930e+19,  48},
		{ 3.9754427479037444e+19,  49},
		{ 1.0585636897131690e+20,  50},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::expint(data.arg);
		double const tole = bksge::abs(data.expected) * error;
		EXPECT_NEAR(data.expected, (double)r, tole);
	}
}

GTEST_TEST(CMathTest, ExpintTest)
{
	ExpintTest<float>      (0.0000001);
	ExpintTest<double>     (0.00000000000001);
	ExpintTest<long double>(0.00000000000001);
	ExpintTest<int>        (0.00000000000001);

	BKSGE_CONSTEXPR auto nanf = std::numeric_limits<float>::quiet_NaN();
	BKSGE_CONSTEXPR auto inff = std::numeric_limits<float>::infinity();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::expintf(nanf)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inff, bksge::expintf( 0.0f));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inff, bksge::expintf(-0.0f));

	BKSGE_CONSTEXPR auto nanl = std::numeric_limits<long double>::quiet_NaN();
	BKSGE_CONSTEXPR auto infl = std::numeric_limits<long double>::infinity();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::expintl(nanl)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-infl, bksge::expintl( 0.0l));
	BKSGE_CONSTEXPR_EXPECT_EQ(-infl, bksge::expintl(-0.0l));
}

}	// namespace expint_test

}	// namespace bksge_cmath_test
