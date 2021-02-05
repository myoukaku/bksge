﻿/**
 *	@file	unit_test_fnd_cmath_ellint_2.cpp
 *
 *	@brief	ellint_2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/ellint_2.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
//#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4305);	// 'initializing': truncation from 'double' to 'T1'

namespace bksge_cmath_test
{

namespace ellint_2_test
{

static_assert(bksge::is_same<float,       decltype(bksge::ellint_2(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ellint_2(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ellint_2(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ellint_2(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ellint_2(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ellint_2(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ellint_2(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ellint_2(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ellint_2(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ellint_2(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ellint_2(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ellint_2(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ellint_2(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ellint_2(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ellint_2(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::ellint_2(0   , 0   ))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::ellint_2f(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::ellint_2l(0.0l, 0.0l))>::value, "");

template <typename T1, typename T2>
void Ellint2TestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan1 = bksge::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = bksge::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto eps1 = bksge::numeric_limits<T1>::epsilon();

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2(nan1, nan2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2(nan1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2(T1(0), nan2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2(T1( 1) + eps1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2(T1(-1) - eps1, T2(0))));

	struct testcase
	{
		double expected;
		T1 k;
		T2 phi;
	};

	testcase const testcases[] =
	{
		{0.0000000000000000, -1.0, 0.0000000000000000},
		{0.1736481776669303, -1.0, 0.17453292519943295},
		{0.3420201433256687, -1.0, 0.34906585039886590},
		{0.4999999999999999, -1.0, 0.52359877559829882},
		{0.6427876096865392, -1.0, 0.69813170079773179},
		{0.7660444431189780, -1.0, 0.87266462599716477},
		{0.8660254037844385, -1.0, 1.0471975511965976},
		{0.9396926207859083, -1.0, 1.2217304763960306},
		{0.9848077530122080, -1.0, 1.3962634015954636},
		{1.0000000000000000, -1.0, 1.5707963267948966},

		{0.0000000000000000, -0.9, 0.0000000000000000},
		{0.1738169060616796, -0.9, 0.17453292519943295},
		{0.3433791918697205, -0.9, 0.34906585039886590},
		{0.5046426865985633, -0.9, 0.52359877559829882},
		{0.6540000384236859, -0.9, 0.69813170079773179},
		{0.7885492841990463, -0.9, 0.87266462599716477},
		{0.9064569862631539, -0.9, 1.0471975511965976},
		{1.0075154899135927, -0.9, 1.2217304763960306},
		{1.0940135583194071, -0.9, 1.3962634015954636},
		{1.1716970527816142, -0.9, 1.5707963267948966},

		{0.0000000000000000, -0.8, 0.0000000000000000},
		{0.1739676227453480, -0.8, 0.17453292519943295},
		{0.3445868522696932, -0.8, 0.34906585039886590},
		{0.5087292365450243, -0.8, 0.52359877559829882},
		{0.6637201653917622, -0.8, 0.69813170079773179},
		{0.8076034441016740, -0.8, 0.87266462599716477},
		{0.9394548037249507, -0.8, 1.0471975511965976},
		{1.0597473310395040, -0.8, 1.2217304763960306},
		{1.1706981862452359, -0.8, 1.3962634015954636},
		{1.2763499431699064, -0.8, 1.5707963267948966},

		{0.0000000000000000, -0.7, 0.0000000000000000},
		{0.1741004124270254, -0.7, 0.17453292519943295},
		{0.3456460508576476, -0.7, 0.34906585039886590},
		{0.5122849569331465, -0.7, 0.52359877559829882},
		{0.6720765409879953, -0.7, 0.69813170079773179},
		{0.8237093263155649, -0.7, 0.87266462599716477},
		{0.9667231330945280, -0.7, 1.0471975511965976},
		{1.1017090644949501, -0.7, 1.2217304763960306},
		{1.2304180097292916, -0.7, 1.3962634015954636},
		{1.3556611355719554, -0.7, 1.5707963267948966},

		{0.0000000000000000, -0.6, 0.0000000000000000},
		{0.1742153491959912, -0.6, 0.17453292519943295},
		{0.3465592778717409, -0.6, 0.34906585039886590},
		{0.5153303453843214, -0.6, 0.52359877559829882},
		{0.6791655059745301, -0.6, 0.69813170079773179},
		{0.8372021818034988, -0.6, 0.87266462599716477},
		{0.9892215935493775, -0.6, 1.0471975511965976},
		{1.1357478470419362, -0.6, 1.2217304763960306},
		{1.2780617372844061, -0.6, 1.3962634015954636},
		{1.4180833944487241, -0.6, 1.5707963267948966},

		{0.0000000000000000, -0.5, 0.0000000000000000},
		{0.1743124967731590, -0.5, 0.17453292519943295},
		{0.3473286253777080, -0.5, 0.34906585039886590},
		{0.5178819348599379, -0.5, 0.52359877559829882},
		{0.6850602295416454, -0.5, 0.69813170079773179},
		{0.8483166280334720, -0.5, 0.87266462599716477},
		{1.0075555551444719, -0.5, 1.0471975511965976},
		{1.1631768599287302, -0.5, 1.2217304763960306},
		{1.3160584048772548, -0.5, 1.3962634015954636},
		{1.4674622093394272, -0.5, 1.5707963267948966},

		{0.0000000000000000, -0.4, 0.0000000000000000},
		{0.1743919087248126, -0.4, 0.17453292519943295},
		{0.3479558176709921, -0.4, 0.34906585039886590},
		{0.5199529068380446, -0.4, 0.52359877559829882},
		{0.6898163846443152, -0.4, 0.69813170079773179},
		{0.8572208885993603, -0.4, 0.87266462599716477},
		{1.0221301327876993, -0.4, 1.0471975511965976},
		{1.1848138019818375, -0.4, 1.2217304763960306},
		{1.3458259266501533, -0.4, 1.3962634015954636},
		{1.5059416123600404, -0.4, 1.5707963267948966},

		{0.0000000000000000, -0.3, 0.0000000000000000},
		{0.1744536286404891, -0.3, 0.17453292519943295},
		{0.3484422353571347, -0.3, 0.34906585039886590},
		{0.5215535387741175, -0.3, 0.52359877559829882},
		{0.6934758441836989, -0.3, 0.69813170079773179},
		{0.8640360992823765, -0.3, 0.87266462599716477},
		{1.0332234514065408, -0.3, 1.0471975511965976},
		{1.2011943182068923, -0.3, 1.2217304763960306},
		{1.3682566113689625, -0.3, 1.3962634015954636},
		{1.5348334649232489, -0.3, 1.5707963267948966},

		{0.0000000000000000, -0.2, 0.0000000000000000},
		{0.1744976902765280, -0.2, 0.17453292519943295},
		{0.3487889340076209, -0.2, 0.34906585039886590},
		{0.5226915285605741, -0.2, 0.52359877559829882},
		{0.6960691336015757, -0.2, 0.69813170079773179},
		{0.8688478237486337, -0.2, 0.87266462599716477},
		{1.0410255369689567, -0.2, 1.0471975511965976},
		{1.2126730391631364, -0.2, 1.2217304763960306},
		{1.3839259540325151, -0.2, 1.3962634015954636},
		{1.5549685462425293, -0.2, 1.5707963267948966},

		{0.0000000000000000, -0.1, 0.0000000000000000},
		{0.1745241176664994, -0.1, 0.17453292519943295},
		{0.3489966580544240, -0.1, 0.34906585039886590},
		{0.5233722240050878, -0.1, 0.52359877559829882},
		{0.6976170521728486, -0.1, 0.69813170079773179},
		{0.8717130927300749, -0.1, 0.87266462599716477},
		{1.0456602197056326, -0.1, 1.0471975511965976},
		{1.2194762899272027, -0.1, 1.2217304763960306},
		{1.3931950229892747, -0.1, 1.3962634015954636},
		{1.5668619420216683, -0.1, 1.5707963267948966},

		{0.0000000000000000, 0.0, 0.0000000000000000},
		{0.1745329251994329, 0.0, 0.17453292519943295},
		{0.3490658503988659, 0.0, 0.34906585039886590},
		{0.5235987755982988, 0.0, 0.52359877559829882},
		{0.6981317007977317, 0.0, 0.69813170079773179},
		{0.8726646259971647, 0.0, 0.87266462599716477},
		{1.0471975511965976, 0.0, 1.0471975511965976},
		{1.2217304763960306, 0.0, 1.2217304763960306},
		{1.3962634015954636, 0.0, 1.3962634015954636},
		{1.5707963267948966, 0.0, 1.5707963267948966},

		{0.0000000000000000, 0.1, 0.0000000000000000},
		{0.1745241176664994, 0.1, 0.17453292519943295},
		{0.3489966580544240, 0.1, 0.34906585039886590},
		{0.5233722240050878, 0.1, 0.52359877559829882},
		{0.6976170521728486, 0.1, 0.69813170079773179},
		{0.8717130927300749, 0.1, 0.87266462599716477},
		{1.0456602197056326, 0.1, 1.0471975511965976},
		{1.2194762899272027, 0.1, 1.2217304763960306},
		{1.3931950229892747, 0.1, 1.3962634015954636},
		{1.5668619420216683, 0.1, 1.5707963267948966},

		{0.0000000000000000, 0.2, 0.0000000000000000},
		{0.1744976902765280, 0.2, 0.17453292519943295},
		{0.3487889340076209, 0.2, 0.34906585039886590},
		{0.5226915285605741, 0.2, 0.52359877559829882},
		{0.6960691336015757, 0.2, 0.69813170079773179},
		{0.8688478237486337, 0.2, 0.87266462599716477},
		{1.0410255369689567, 0.2, 1.0471975511965976},
		{1.2126730391631364, 0.2, 1.2217304763960306},
		{1.3839259540325151, 0.2, 1.3962634015954636},
		{1.5549685462425291, 0.2, 1.5707963267948966},

		{0.0000000000000000, 0.3, 0.0000000000000000},
		{0.1744536286404891, 0.3, 0.17453292519943295},
		{0.3484422353571347, 0.3, 0.34906585039886590},
		{0.5215535387741175, 0.3, 0.52359877559829882},
		{0.6934758441836989, 0.3, 0.69813170079773179},
		{0.8640360992823765, 0.3, 0.87266462599716477},
		{1.0332234514065408, 0.3, 1.0471975511965976},
		{1.2011943182068923, 0.3, 1.2217304763960306},
		{1.3682566113689625, 0.3, 1.3962634015954636},
		{1.5348334649232489, 0.3, 1.5707963267948966},

		{0.0000000000000000, 0.4, 0.0000000000000000},
		{0.1743919087248126, 0.4, 0.17453292519943295},
		{0.3479558176709921, 0.4, 0.34906585039886590},
		{0.5199529068380446, 0.4, 0.52359877559829882},
		{0.6898163846443152, 0.4, 0.69813170079773179},
		{0.8572208885993603, 0.4, 0.87266462599716477},
		{1.0221301327876993, 0.4, 1.0471975511965976},
		{1.1848138019818375, 0.4, 1.2217304763960306},
		{1.3458259266501531, 0.4, 1.3962634015954636},
		{1.5059416123600402, 0.4, 1.5707963267948966},

		{0.0000000000000000, 0.5, 0.0000000000000000},
		{0.1743124967731590, 0.5, 0.17453292519943295},
		{0.3473286253777080, 0.5, 0.34906585039886590},
		{0.5178819348599379, 0.5, 0.52359877559829882},
		{0.6850602295416454, 0.5, 0.69813170079773179},
		{0.8483166280334720, 0.5, 0.87266462599716477},
		{1.0075555551444719, 0.5, 1.0471975511965976},
		{1.1631768599287302, 0.5, 1.2217304763960306},
		{1.3160584048772548, 0.5, 1.3962634015954636},
		{1.4674622093394272, 0.5, 1.5707963267948966},

		{0.0000000000000000, 0.6, 0.0000000000000000},
		{0.1742153491959912, 0.6, 0.17453292519943295},
		{0.3465592778717409, 0.6, 0.34906585039886590},
		{0.5153303453843214, 0.6, 0.52359877559829882},
		{0.6791655059745301, 0.6, 0.69813170079773179},
		{0.8372021818034988, 0.6, 0.87266462599716477},
		{0.9892215935493775, 0.6, 1.0471975511965976},
		{1.1357478470419360, 0.6, 1.2217304763960306},
		{1.2780617372844061, 0.6, 1.3962634015954636},
		{1.4180833944487241, 0.6, 1.5707963267948966},

		{0.0000000000000000, 0.7, 0.0000000000000000},
		{0.1741004124270254, 0.7, 0.17453292519943295},
		{0.3456460508576476, 0.7, 0.34906585039886590},
		{0.5122849569331465, 0.7, 0.52359877559829882},
		{0.6720765409879951, 0.7, 0.69813170079773179},
		{0.8237093263155649, 0.7, 0.87266462599716477},
		{0.9667231330945280, 0.7, 1.0471975511965976},
		{1.1017090644949501, 0.7, 1.2217304763960306},
		{1.2304180097292916, 0.7, 1.3962634015954636},
		{1.3556611355719552, 0.7, 1.5707963267948966},

		{0.0000000000000000, 0.8, 0.0000000000000000},
		{0.1739676227453480, 0.8, 0.17453292519943295},
		{0.3445868522696932, 0.8, 0.34906585039886590},
		{0.5087292365450243, 0.8, 0.52359877559829882},
		{0.6637201653917622, 0.8, 0.69813170079773179},
		{0.8076034441016740, 0.8, 0.87266462599716477},
		{0.9394548037249507, 0.8, 1.0471975511965976},
		{1.0597473310395040, 0.8, 1.2217304763960306},
		{1.1706981862452359, 0.8, 1.3962634015954636},
		{1.2763499431699064, 0.8, 1.5707963267948966},

		{0.0000000000000000, 0.9, 0.0000000000000000},
		{0.1738169060616796, 0.9, 0.17453292519943295},
		{0.3433791918697205, 0.9, 0.34906585039886590},
		{0.5046426865985633, 0.9, 0.52359877559829882},
		{0.6540000384236859, 0.9, 0.69813170079773179},
		{0.7885492841990463, 0.9, 0.87266462599716477},
		{0.9064569862631538, 0.9, 1.0471975511965976},
		{1.0075154899135927, 0.9, 1.2217304763960306},
		{1.0940135583194068, 0.9, 1.3962634015954636},
		{1.1716970527816140, 0.9, 1.5707963267948966},

		{0.0000000000000000, 1.0, 0.0000000000000000},
		{0.1736481776669303, 1.0, 0.17453292519943295},
		{0.3420201433256687, 1.0, 0.34906585039886590},
		{0.4999999999999999, 1.0, 0.52359877559829882},
		{0.6427876096865392, 1.0, 0.69813170079773179},
		{0.7660444431189780, 1.0, 0.87266462599716477},
		{0.8660254037844385, 1.0, 1.0471975511965976},
		{0.9396926207859083, 1.0, 1.2217304763960306},
		{0.9848077530122080, 1.0, 1.3962634015954636},
		{1.0000000000000000, 1.0, 1.5707963267948966},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::ellint_2(data.k, data.phi);
		double const tole = bksge::abs(data.expected) * error;
		EXPECT_NEAR(data.expected, (double)r, tole);
	}
}

template <typename T>
void Ellint2TestInt()
{
	double const error = 0.000000000001;

	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<double>::quiet_NaN();

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2(T(0), nan)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2(nan, T(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2(T( 2), T(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2(T(-2), T(0))));

	struct testcase
	{
		double expected;
		T      k;
		double phi;
	};

	testcase const testcases[] =
	{
		{0.0000000000000000, 0, 0.0000000000000000},
		{0.1745329251994329, 0, 0.17453292519943295},
		{0.3490658503988659, 0, 0.34906585039886590},
		{0.5235987755982988, 0, 0.52359877559829882},
		{0.6981317007977317, 0, 0.69813170079773179},
		{0.8726646259971647, 0, 0.87266462599716477},
		{1.0471975511965976, 0, 1.0471975511965976},
		{1.2217304763960306, 0, 1.2217304763960306},
		{1.3962634015954636, 0, 1.3962634015954636},
		{1.5707963267948966, 0, 1.5707963267948966},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::ellint_2(data.k, data.phi);
		double const tole = bksge::abs(data.expected) * error;
		EXPECT_NEAR(data.expected, (double)r, tole);
	}
}

GTEST_TEST(CMathTest, Ellint2Test)
{
	Ellint2TestFloat<float,       float>      (0.000001);
	Ellint2TestFloat<float,       double>     (0.000001);
	Ellint2TestFloat<float,       long double>(0.000001);
	Ellint2TestFloat<double,      float>      (0.000001);
	Ellint2TestFloat<double,      double>     (0.000000000001);
	Ellint2TestFloat<double,      long double>(0.000000000001);
	Ellint2TestFloat<long double, float>      (0.000001);
	Ellint2TestFloat<long double, double>     (0.000000000001);
	Ellint2TestFloat<long double, long double>(0.000000000001);

	Ellint2TestInt<int>();
	Ellint2TestInt<short>();

	BKSGE_CONSTEXPR auto nanf = bksge::numeric_limits<float>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsf = bksge::numeric_limits<float>::epsilon();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2f(nanf, nanf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2f(nanf, 0.0f)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2f(0.0f, nanf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2f( 1.0f + epsf, 0.0f)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2f(-1.0f - epsf, 0.0f)));

	BKSGE_CONSTEXPR auto nanl = bksge::numeric_limits<long double>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsl = bksge::numeric_limits<long double>::epsilon();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2l(nanl, nanl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2l(nanl, 0.0l)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2l(0.0l, nanl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2l( 1.0l + epsl, 0.0l)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::ellint_2l(-1.0l - epsl, 0.0l)));
}

}	// namespace ellint_2_test

}	// namespace bksge_cmath_test

BKSGE_WARNING_POP();
