﻿/**
 *	@file	unit_test_fnd_cmath_riemann_zeta.cpp
 *
 *	@brief	riemann_zeta のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/riemann_zeta.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4305);	// 'initializing': truncation from 'double' to 'T1'

namespace bksge_cmath_test
{

namespace riemann_zeta_test
{

static_assert(bksge::is_same<float,       decltype(bksge::riemann_zeta(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::riemann_zeta(0.0))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::riemann_zeta(0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::riemann_zeta(0))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::riemann_zetaf(0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::riemann_zetal(0.0l))>::value, "");

template <typename T>
void RiemannZetaTestFloat(double error)
{
	using Promoted = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<Promoted>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<Promoted>::infinity();

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::riemann_zeta(nan)));

	BKSGE_CONSTEXPR_EXPECT_EQ(inf, bksge::riemann_zeta(T(1)));

	struct testcase
	{
		double expected;
		T arg;
	};

	testcase const testcases[] =
	{
		{ 0.0000000000000000000, -10.0},
		{-0.0033669820451019570, -9.8},
		{-0.0058129517767319012, -9.6},
		{-0.0072908732290556961, -9.4},
		{-0.0078420910654484390, -9.2},
		{-0.0075757575757575760, -9.0},
		{-0.0066476555677551889, -8.8},
		{-0.0052400095350859403, -8.6},
		{-0.0035434308017674907, -8.4},
		{-0.0017417330388368587, -8.2},
		{ 0.0000000000000000000, -8.0},
		{ 0.0015440036789213937, -7.8},
		{ 0.0027852131086497402, -7.6},
		{ 0.0036537321227995885, -7.4},
		{ 0.0041147930817053528, -7.2},
		{ 0.0041666666666666666, -7.0},
		{ 0.0038369975032738362, -6.8},
		{ 0.0031780270571782998, -6.6},
		{ 0.0022611282027338573, -6.4},
		{ 0.0011710237049390457, -6.2},
		{ 0.0000000000000000000, -6.0},
		{-0.0011576366649881868, -5.8},
		{-0.0022106784318564332, -5.6},
		{-0.0030755853460586913, -5.4},
		{-0.0036804380477934761, -5.2},
		{-0.0039682539682539680, -5.0},
		{-0.0038996891301999771, -4.8},
		{-0.0034551830834302698, -4.6},
		{-0.0026366345018725037, -4.4},
		{-0.0014687209305056920, -4.2},
		{ 0.0000000000000000000, -4.0},
		{ 0.0016960463875825209, -3.8},
		{ 0.0035198355903356634, -3.6},
		{ 0.0053441503206513464, -3.4},
		{ 0.0070119720770910566, -3.2},
		{ 0.0083333333333333332, -3.0},
		{ 0.0090807294856852499, -2.8},
		{ 0.0089824623788396559, -2.6},
		{ 0.0077130239874243379, -2.4},
		{ 0.0048792123593035816, -2.2},
		{ 0.0000000000000000000, -2.0},
		{-0.0075229347765968738, -1.8},
		{-0.018448986678963719, -1.6},
		{-0.033764987694047545, -1.4},
		{-0.054788441243880513, -1.2},
		{-0.083333333333333329, -1.0},
		{-0.12198707766977138, -0.8},
		{-0.17459571193801349, -0.6},
		{-0.24716546083171545, -0.4},
		{-0.34966628059831456, -0.2},
		{-0.50000000000000000, 0.0},
		{-0.73392092489634220, 0.2},
		{-1.1347977838669825, 0.4},
		{-1.9526614482240094, 0.6},
		{-4.4375384158955686, 0.8},

		{5.5915824411777519, 1.2},
		{3.1055472779775810, 1.4},
		{2.2857656656801297, 1.6},
		{1.8822296181028220, 1.8},
		{1.6449340668482264, 2.0},
		{1.4905432565068935, 2.2},
		{1.3833428588407355, 2.4},
		{1.3054778090727805, 2.6},
		{1.2470314223172534, 2.8},
		{1.2020569031595942, 3.0},
		{1.1667733709844670, 3.2},
		{1.1386637757280416, 3.4},
		{1.1159890791233376, 3.6},
		{1.0975105764590043, 3.8},
		{1.0823232337111381, 4.0},
		{1.0697514772338095, 4.2},
		{1.0592817259798355, 4.4},
		{1.0505173825665735, 4.6},
		{1.0431480133351789, 4.8},
		{1.0369277551433700, 5.0},
		{1.0316598766779166, 5.2},
		{1.0271855389203539, 5.4},
		{1.0233754792270300, 5.6},
		{1.0201237683883446, 5.8},
		{1.0173430619844492, 6.0},
		{1.0149609451852231, 6.2},
		{1.0129170887121841, 6.4},
		{1.0111610141542711, 6.6},
		{1.0096503223447120, 6.8},
		{1.0083492773819229, 7.0},
		{1.0072276664807172, 7.2},
		{1.0062598756930512, 7.4},
		{1.0054241359879634, 7.6},
		{1.0047019048164696, 7.8},
		{1.0040773561979444, 8.0},
		{1.0035369583062013, 8.2},
		{1.0030691220374448, 8.4},
		{1.0026639074861505, 8.6},
		{1.0023127779098220, 8.8},
		{1.0020083928260821, 9.0},
		{1.0017444334995897, 9.2},
		{1.0015154553480514, 9.4},
		{1.0013167628052648, 9.6},
		{1.0011443029840295, 9.8},
		{1.0009945751278180, 10.0},
		{1.0008645533615088, 10.2},
		{1.0007516206744651, 10.4},
		{1.0006535124140850, 10.6},
		{1.0005682678503411, 10.8},
		{1.0004941886041194, 11.0},
		{1.0004298029239942, 11.2},
		{1.0003738349551166, 11.4},
		{1.0003251782761946, 11.6},
		{1.0002828730909989, 11.8},
		{1.0002460865533080, 12.0},
		{1.0002140957818750, 12.2},
		{1.0001862731874054, 12.4},
		{1.0001620737887460, 12.6},
		{1.0001410242422091, 12.8},
		{1.0001227133475785, 13.0},
		{1.0001067838280169, 13.2},
		{1.0000929252097515, 13.4},
		{1.0000808676518720, 13.6},
		{1.0000703765974504, 13.8},
		{1.0000612481350588, 14.0},
		{1.0000533049750668, 14.2},
		{1.0000463929582293, 14.4},
		{1.0000403780253397, 14.6},
		{1.0000351435864272, 14.8},
		{1.0000305882363070, 15.0},
		{1.0000266237704787, 15.2},
		{1.0000231734615617, 15.4},
		{1.0000201705617975, 15.6},
		{1.0000175570017611, 15.8},
		{1.0000152822594086, 16.0},
		{1.0000133023770335, 16.2},
		{1.0000115791066833, 16.4},
		{1.0000100791671644, 16.6},
		{1.0000087735980012, 16.8},
		{1.0000076371976379, 17.0},
		{1.0000066480348633, 17.2},
		{1.0000057870238737, 17.4},
		{1.0000050375546610, 17.6},
		{1.0000043851715013, 17.8},
		{1.0000038172932650, 18.0},
		{1.0000033229700953, 18.2},
		{1.0000028926717150, 18.4},
		{1.0000025181032419, 18.6},
		{1.0000021920449285, 18.8},
		{1.0000019082127165, 19.0},
		{1.0000016611368951, 19.2},
		{1.0000014460565094, 19.4},
		{1.0000012588274738, 19.6},
		{1.0000010958426055, 19.8},
		{1.0000009539620338, 20.0},
		{1.0000008304526344, 20.2},
		{1.0000007229353187, 20.4},
		{1.0000006293391575, 20.6},
		{1.0000005478614529, 20.8},
		{1.0000004769329869, 21.0},
		{1.0000004151877719, 21.2},
		{1.0000003614367252, 21.4},
		{1.0000003146447527, 21.6},
		{1.0000002739108020, 21.8},
		{1.0000002384505027, 22.0},
		{1.0000002075810521, 22.2},
		{1.0000001807080625, 22.4},
		{1.0000001573141093, 22.6},
		{1.0000001369487659, 22.8},
		{1.0000001192199259, 23.0},
		{1.0000001037862518, 23.2},
		{1.0000000903506006, 23.4},
		{1.0000000786543011, 23.6},
		{1.0000000684721728, 23.8},
		{1.0000000596081891, 24.0},
		{1.0000000518917020, 24.2},
		{1.0000000451741575, 24.4},
		{1.0000000393262332, 24.6},
		{1.0000000342353501, 24.8},
		{1.0000000298035034, 25.0},
		{1.0000000259453767, 25.2},
		{1.0000000225866978, 25.4},
		{1.0000000196628109, 25.6},
		{1.0000000171174297, 25.8},
		{1.0000000149015549, 26.0},
		{1.0000000129725302, 26.2},
		{1.0000000112932221, 26.4},
		{1.0000000098313035, 26.6},
		{1.0000000085586331, 26.8},
		{1.0000000074507118, 27.0},
		{1.0000000064862125, 27.2},
		{1.0000000056465688, 27.4},
		{1.0000000049156179, 27.6},
		{1.0000000042792894, 27.8},
		{1.0000000037253340, 28.0},
		{1.0000000032430887, 28.2},
		{1.0000000028232703, 28.4},
		{1.0000000024577975, 28.6},
		{1.0000000021396356, 28.8},
		{1.0000000018626598, 29.0},
		{1.0000000016215385, 29.2},
		{1.0000000014116304, 29.4},
		{1.0000000012288950, 29.6},
		{1.0000000010698147, 29.8},
		{1.0000000009313275, 30.0},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::riemann_zeta(data.arg);
		double const tole = bksge::abs(data.expected) * error;
		EXPECT_NEAR(data.expected, (double)r, tole);
	}
}

template <typename T>
void RiemannZetaTestInt(double error)
{
	struct testcase
	{
		double expected;
		T arg;
	};

	testcase const testcases[] =
	{
		{ 0.0000000000000000000, -10},
		{-0.0075757575757575760,  -9},
		{ 0.0000000000000000000,  -8},
		{ 0.0041666666666666666,  -7},
		{ 0.0000000000000000000,  -6},
		{-0.0039682539682539680,  -5},
		{ 0.0000000000000000000,  -4},
		{ 0.0083333333333333332,  -3},
		{ 0.0000000000000000000,  -2},
		{-0.083333333333333329,   -1},
		{-0.50000000000000000,     0},

		{ 1.6449340668482264,      2},
		{ 1.2020569031595942,      3},
		{ 1.0823232337111381,      4},
		{ 1.0369277551433700,      5},
		{ 1.0173430619844492,      6},
		{ 1.0083492773819229,      7},
		{ 1.0040773561979444,      8},
		{ 1.0020083928260821,      9},
		{ 1.0009945751278180,     10},
		{ 1.0004941886041194,     11},
		{ 1.0002460865533080,     12},
		{ 1.0001227133475785,     13},
		{ 1.0000612481350588,     14},
		{ 1.0000305882363070,     15},
		{ 1.0000152822594086,     16},
		{ 1.0000076371976379,     17},
		{ 1.0000038172932650,     18},
		{ 1.0000019082127165,     19},
		{ 1.0000009539620338,     20},
		{ 1.0000004769329869,     21},
		{ 1.0000002384505027,     22},
		{ 1.0000001192199259,     23},
		{ 1.0000000596081891,     24},
		{ 1.0000000298035034,     25},
		{ 1.0000000149015549,     26},
		{ 1.0000000074507118,     27},
		{ 1.0000000037253340,     28},
		{ 1.0000000018626598,     29},
		{ 1.0000000009313275,     30},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::riemann_zeta(data.arg);
		double const tole = bksge::abs(data.expected) * error;
		EXPECT_NEAR(data.expected, (double)r, tole);
	}
}

GTEST_TEST(CMathTest, RiemannZetaTest)
{
	RiemannZetaTestFloat<float>      (0.000001);
	RiemannZetaTestFloat<double>     (0.00000000000001);
	RiemannZetaTestFloat<long double>(0.00000000000001);

	RiemannZetaTestInt<int>          (0.00000000000001);

	BKSGE_CONSTEXPR auto nanf = bksge::numeric_limits<float>::quiet_NaN();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::riemann_zetaf(nanf)));

	BKSGE_CONSTEXPR auto nanl = bksge::numeric_limits<long double>::quiet_NaN();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::riemann_zetal(nanl)));
}

}	// namespace riemann_zeta_test

}	// namespace bksge_cmath_test

BKSGE_WARNING_POP();