/**
 *	@file	unit_test_fnd_cmath_comp_ellint_3.cpp
 *
 *	@brief	comp_ellint_3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/comp_ellint_3.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace comp_ellint_3_test
{

static_assert(bksge::is_same<float,       decltype(bksge::comp_ellint_3(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_3(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_3(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_3(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_3(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_3(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_3(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_3(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_3(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_3(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_3(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_3(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_3(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_3(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_3(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::comp_ellint_3(0   , 0   ))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::comp_ellint_3f(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::comp_ellint_3l(0.0l, 0.0l))>::value, "");

template <typename T1, typename T2>
void CompEllint3TestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	BKSGE_CONSTEXPR auto max1 = std::numeric_limits<T1>::max();
	BKSGE_CONSTEXPR auto lowest1 = std::numeric_limits<T1>::lowest();
	BKSGE_CONSTEXPR auto eps1 = std::numeric_limits<T1>::epsilon();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<double>::infinity();

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(nan1, nan2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(nan1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(T1(0), nan2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(T1( 1) + eps1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(T1(-1) - eps1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(max1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(lowest1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(+inf1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(-inf1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(inf, bksge::comp_ellint_3(T1( 1), T2(0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(inf, bksge::comp_ellint_3(T1(-1), T2(0)));

	struct testcase
	{
		double expected;
		T1 k;
		T2 nu;
	};

	testcase const testcases[] =
	{
		{1.5536420236310947, T1(-0.9), T2(-0.9)},
		{1.6044591960982202, T1(-0.9), T2(-0.8)},
		{1.6600480747670936, T1(-0.9), T2(-0.7)},
		{1.7211781128919522, T1(-0.9), T2(-0.6)},
		{1.7888013241937861, T1(-0.9), T2(-0.5)},
		{1.8641114227238348, T1(-0.9), T2(-0.4)},
		{1.9486280260314424, T1(-0.9), T2(-0.3)},
		{2.0443194576468892, T1(-0.9), T2(-0.2)},
		{2.1537868513875286, T1(-0.9), T2(-0.1)},

		{2.2805491384227703, T1(-0.9), T2( 0.0)},
		{2.4295011187834885, T1(-0.9), T2( 0.1)},
		{2.6076835743348412, T1(-0.9), T2( 0.2)},
		{2.8256506968858512, T1(-0.9), T2( 0.3)},
		{3.1000689868578619, T1(-0.9), T2( 0.4)},
		{3.4591069002104677, T1(-0.9), T2( 0.5)},
		{3.9549939883570229, T1(-0.9), T2( 0.6)},
		{4.6985482312992435, T1(-0.9), T2( 0.7)},
		{5.9820740813645710, T1(-0.9), T2( 0.8)},
		{8.9942562031858699, T1(-0.9), T2( 0.9)},

		{1.9953027776647294, T1(-0.8), T2( 0.0)},
		{2.1172616484005085, T1(-0.8), T2( 0.1)},
		{2.2624789434186798, T1(-0.8), T2( 0.2)},
		{2.4392042002725698, T1(-0.8), T2( 0.3)},
		{2.6604037035529728, T1(-0.8), T2( 0.4)},
		{2.9478781158239751, T1(-0.8), T2( 0.5)},
		{3.3418121892288055, T1(-0.8), T2( 0.6)},
		{3.9268876980046397, T1(-0.8), T2( 0.7)},
		{4.9246422058196071, T1(-0.8), T2( 0.8)},
		{7.2263259298637132, T1(-0.8), T2( 0.9)},

		{1.8456939983747234, T1(-0.7), T2( 0.0)},
		{1.9541347343119564, T1(-0.7), T2( 0.1)},
		{2.0829290325820202, T1(-0.7), T2( 0.2)},
		{2.2392290510988535, T1(-0.7), T2( 0.3)},
		{2.4342502915307880, T1(-0.7), T2( 0.4)},
		{2.6868019968236996, T1(-0.7), T2( 0.5)},
		{3.0314573496746742, T1(-0.7), T2( 0.6)},
		{3.5408408771788564, T1(-0.7), T2( 0.7)},
		{4.4042405729076961, T1(-0.7), T2( 0.8)},
		{6.3796094177887754, T1(-0.7), T2( 0.9)},

		{1.7507538029157526, T1(-0.6), T2( 0.0)},
		{1.8508766487100685, T1(-0.6), T2( 0.1)},
		{1.9695980282802217, T1(-0.6), T2( 0.2)},
		{2.1134154405060599, T1(-0.6), T2( 0.3)},
		{2.2925036420985130, T1(-0.6), T2( 0.4)},
		{2.5239007084492711, T1(-0.6), T2( 0.5)},
		{2.8388723099514972, T1(-0.6), T2( 0.6)},
		{3.3029735898397159, T1(-0.6), T2( 0.7)},
		{4.0867036409261832, T1(-0.6), T2( 0.8)},
		{5.8709993116265604, T1(-0.6), T2( 0.9)},

		{1.6857503548125961, T1(-0.5), T2( 0.0)},
		{1.7803034946545482, T1(-0.5), T2( 0.1)},
		{1.8922947612264021, T1(-0.5), T2( 0.2)},
		{2.0277924458111314, T1(-0.5), T2( 0.3)},
		{2.1962905366178065, T1(-0.5), T2( 0.4)},
		{2.4136715042011945, T1(-0.5), T2( 0.5)},
		{2.7090491861753558, T1(-0.5), T2( 0.6)},
		{3.1433945297859229, T1(-0.5), T2( 0.7)},
		{3.8750701888108070, T1(-0.5), T2( 0.8)},
		{5.5355132096026463, T1(-0.5), T2( 0.9)},

		{1.6399998658645112, T1(-0.4), T2( 0.0)},
		{1.7306968836847190, T1(-0.4), T2( 0.1)},
		{1.8380358826317627, T1(-0.4), T2( 0.2)},
		{1.9677924132520139, T1(-0.4), T2( 0.3)},
		{2.1289968719280026, T1(-0.4), T2( 0.4)},
		{2.3367461373176512, T1(-0.4), T2( 0.5)},
		{2.6186940209850191, T1(-0.4), T2( 0.6)},
		{3.0327078743873246, T1(-0.4), T2( 0.7)},
		{3.7289548002199902, T1(-0.4), T2( 0.8)},
		{5.3055535102872513, T1(-0.4), T2( 0.9)},

		{1.6080486199305128, T1(-0.3), T2( 0.0)},
		{1.6960848815118226, T1(-0.3), T2( 0.1)},
		{1.8002173372290500, T1(-0.3), T2( 0.2)},
		{1.9260216862473254, T1(-0.3), T2( 0.3)},
		{2.0822121773175533, T1(-0.3), T2( 0.4)},
		{2.2833505881933971, T1(-0.3), T2( 0.5)},
		{2.5560975528589065, T1(-0.3), T2( 0.6)},
		{2.9562123549913877, T1(-0.3), T2( 0.7)},
		{3.6283050484567170, T1(-0.3), T2( 0.8)},
		{5.1479514944016795, T1(-0.3), T2( 0.9)},

		{1.5868678474541662, T1(-0.2), T2( 0.0)},
		{1.6731552050562593, T1(-0.2), T2( 0.1)},
		{1.7751816279738935, T1(-0.2), T2( 0.2)},
		{1.8983924169967101, T1(-0.2), T2( 0.3)},
		{2.0512956926676806, T1(-0.2), T2( 0.4)},
		{2.2481046259421302, T1(-0.2), T2( 0.5)},
		{2.5148333891629315, T1(-0.2), T2( 0.6)},
		{2.9058704854500967, T1(-0.2), T2( 0.7)},
		{3.5622166386422633, T1(-0.2), T2( 0.8)},
		{5.0448269356200370, T1(-0.2), T2( 0.9)},

		{1.5747455615173560, T1(-0.1), T2( 0.0)},
		{1.6600374067558428, T1(-0.1), T2( 0.1)},
		{1.7608656115083421, T1(-0.1), T2( 0.2)},
		{1.8826015946315438, T1(-0.1), T2( 0.3)},
		{2.0336367403076760, T1(-0.1), T2( 0.4)},
		{2.2279868912966849, T1(-0.1), T2( 0.5)},
		{2.4913004919173827, T1(-0.1), T2( 0.6)},
		{2.8771910188009744, T1(-0.1), T2( 0.7)},
		{3.5246199613295617, T1(-0.1), T2( 0.8)},
		{4.9862890417305508, T1(-0.1), T2( 0.9)},

		{1.5707963267948966, T1( 0.0), T2( 0.0)},
		{1.6557647109660170, T1( 0.0), T2( 0.1)},
		{1.7562036827601817, T1( 0.0), T2( 0.2)},
		{1.8774607092226381, T1( 0.0), T2( 0.3)},
		{2.0278893379868062, T1( 0.0), T2( 0.4)},
		{2.2214414690791831, T1( 0.0), T2( 0.5)},
		{2.4836470664490258, T1( 0.0), T2( 0.6)},
		{2.8678686047727386, T1( 0.0), T2( 0.7)},
		{3.5124073655203634, T1( 0.0), T2( 0.8)},
		{4.9672941328980516, T1( 0.0), T2( 0.9)},

		{1.5747455615173560, T1( 0.1), T2( 0.0)},
		{1.6600374067558428, T1( 0.1), T2( 0.1)},
		{1.7608656115083421, T1( 0.1), T2( 0.2)},
		{1.8826015946315440, T1( 0.1), T2( 0.3)},
		{2.0336367403076760, T1( 0.1), T2( 0.4)},
		{2.2279868912966849, T1( 0.1), T2( 0.5)},
		{2.4913004919173827, T1( 0.1), T2( 0.6)},
		{2.8771910188009744, T1( 0.1), T2( 0.7)},
		{3.5246199613295617, T1( 0.1), T2( 0.8)},
		{4.9862890417305508, T1( 0.1), T2( 0.9)},

		{1.5868678474541662, T1( 0.2), T2( 0.0)},
		{1.6731552050562593, T1( 0.2), T2( 0.1)},
		{1.7751816279738935, T1( 0.2), T2( 0.2)},
		{1.8983924169967101, T1( 0.2), T2( 0.3)},
		{2.0512956926676806, T1( 0.2), T2( 0.4)},
		{2.2481046259421302, T1( 0.2), T2( 0.5)},
		{2.5148333891629315, T1( 0.2), T2( 0.6)},
		{2.9058704854500967, T1( 0.2), T2( 0.7)},
		{3.5622166386422633, T1( 0.2), T2( 0.8)},
		{5.0448269356200370, T1( 0.2), T2( 0.9)},

		{1.6080486199305128, T1( 0.3), T2( 0.0)},
		{1.6960848815118228, T1( 0.3), T2( 0.1)},
		{1.8002173372290500, T1( 0.3), T2( 0.2)},
		{1.9260216862473254, T1( 0.3), T2( 0.3)},
		{2.0822121773175533, T1( 0.3), T2( 0.4)},
		{2.2833505881933975, T1( 0.3), T2( 0.5)},
		{2.5560975528589065, T1( 0.3), T2( 0.6)},
		{2.9562123549913877, T1( 0.3), T2( 0.7)},
		{3.6283050484567174, T1( 0.3), T2( 0.8)},
		{5.1479514944016795, T1( 0.3), T2( 0.9)},

		{1.6399998658645112, T1( 0.4), T2( 0.0)},
		{1.7306968836847190, T1( 0.4), T2( 0.1)},
		{1.8380358826317629, T1( 0.4), T2( 0.2)},
		{1.9677924132520141, T1( 0.4), T2( 0.3)},
		{2.1289968719280030, T1( 0.4), T2( 0.4)},
		{2.3367461373176512, T1( 0.4), T2( 0.5)},
		{2.6186940209850196, T1( 0.4), T2( 0.6)},
		{3.0327078743873246, T1( 0.4), T2( 0.7)},
		{3.7289548002199906, T1( 0.4), T2( 0.8)},
		{5.3055535102872522, T1( 0.4), T2( 0.9)},

		{1.6857503548125961, T1( 0.5), T2( 0.0)},
		{1.7803034946545482, T1( 0.5), T2( 0.1)},
		{1.8922947612264021, T1( 0.5), T2( 0.2)},
		{2.0277924458111314, T1( 0.5), T2( 0.3)},
		{2.1962905366178065, T1( 0.5), T2( 0.4)},
		{2.4136715042011945, T1( 0.5), T2( 0.5)},
		{2.7090491861753558, T1( 0.5), T2( 0.6)},
		{3.1433945297859229, T1( 0.5), T2( 0.7)},
		{3.8750701888108070, T1( 0.5), T2( 0.8)},
		{5.5355132096026463, T1( 0.5), T2( 0.9)},

		{1.7507538029157526, T1( 0.6), T2( 0.0)},
		{1.8508766487100687, T1( 0.6), T2( 0.1)},
		{1.9695980282802217, T1( 0.6), T2( 0.2)},
		{2.1134154405060599, T1( 0.6), T2( 0.3)},
		{2.2925036420985130, T1( 0.6), T2( 0.4)},
		{2.5239007084492711, T1( 0.6), T2( 0.5)},
		{2.8388723099514976, T1( 0.6), T2( 0.6)},
		{3.3029735898397159, T1( 0.6), T2( 0.7)},
		{4.0867036409261832, T1( 0.6), T2( 0.8)},
		{5.8709993116265613, T1( 0.6), T2( 0.9)},

		{1.8456939983747238, T1( 0.7), T2( 0.0)},
		{1.9541347343119566, T1( 0.7), T2( 0.1)},
		{2.0829290325820207, T1( 0.7), T2( 0.2)},
		{2.2392290510988540, T1( 0.7), T2( 0.3)},
		{2.4342502915307880, T1( 0.7), T2( 0.4)},
		{2.6868019968237000, T1( 0.7), T2( 0.5)},
		{3.0314573496746746, T1( 0.7), T2( 0.6)},
		{3.5408408771788569, T1( 0.7), T2( 0.7)},
		{4.4042405729076970, T1( 0.7), T2( 0.8)},
		{6.3796094177887763, T1( 0.7), T2( 0.9)},

		{1.9953027776647294, T1( 0.8), T2( 0.0)},
		{2.1172616484005085, T1( 0.8), T2( 0.1)},
		{2.2624789434186798, T1( 0.8), T2( 0.2)},
		{2.4392042002725698, T1( 0.8), T2( 0.3)},
		{2.6604037035529728, T1( 0.8), T2( 0.4)},
		{2.9478781158239751, T1( 0.8), T2( 0.5)},
		{3.3418121892288055, T1( 0.8), T2( 0.6)},
		{3.9268876980046397, T1( 0.8), T2( 0.7)},
		{4.9246422058196071, T1( 0.8), T2( 0.8)},
		{7.2263259298637132, T1( 0.8), T2( 0.9)},

		{2.2805491384227707, T1( 0.9), T2( 0.0)},
		{2.4295011187834890, T1( 0.9), T2( 0.1)},
		{2.6076835743348421, T1( 0.9), T2( 0.2)},
		{2.8256506968858521, T1( 0.9), T2( 0.3)},
		{3.1000689868578628, T1( 0.9), T2( 0.4)},
		{3.4591069002104686, T1( 0.9), T2( 0.5)},
		{3.9549939883570242, T1( 0.9), T2( 0.6)},
		{4.6985482312992453, T1( 0.9), T2( 0.7)},
		{5.9820740813645727, T1( 0.9), T2( 0.8)},
		{8.9942562031858735, T1( 0.9), T2( 0.9)},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::comp_ellint_3(data.k, data.nu);

		{
			double tole = bksge::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

template <typename T>
void CompEllint3TestInt()
{
	double const error = 0.000000000001;

	BKSGE_CONSTEXPR auto nan = std::numeric_limits<double>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<double>::infinity();

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(T(0), nan)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(nan, T(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(T( 2), T(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3(T(-2), T(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(inf, bksge::comp_ellint_3(T( 1), 0.0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(inf, bksge::comp_ellint_3(T(-1), 0.0));

	struct testcase
	{
		double expected;
		T      k;
		double nu;
	};

	testcase const testcases[] =
	{
		{0.6412749150809320, T(0), -5.0},
		{0.7024814731040726, T(0), -4.0},
		{0.7853981633974483, T(0), -3.0},
		{0.9068996821171089, T(0), -2.0},
		{0.9224033638333891, T(0), -1.9},
		{0.9387303546113190, T(0), -1.8},
		{0.9559562015909127, T(0), -1.7},
		{0.9741665274385427, T(0), -1.6},
		{0.9934588265796101, T(0), -1.5},
		{1.0139446689934029, T(0), -1.4},
		{1.0357524255703822, T(0), -1.3},
		{1.0590306674828851, T(0), -1.2},
		{1.0839524458626357, T(0), -1.1},
		{1.1107207345395915, T(0), -1.0},
		{1.1395754288497420, T(0), -0.9},
		{1.1708024551734543, T(0), -0.8},
		{1.2047457872617383, T(0), -0.7},
		{1.2418235332245126, T(0), -0.6},
		{1.2825498301618640, T(0), -0.5},
		{1.3275651989026322, T(0), -0.4},
		{1.3776795151134890, T(0), -0.3},
		{1.4339343023863691, T(0), -0.2},
		{1.4976955329233277, T(0), -0.1},
		{1.5707963267948966, T(0),  0.0},
		{1.6557647109660170, T(0),  0.1},
		{1.7562036827601817, T(0),  0.2},
		{1.8774607092226381, T(0),  0.3},
		{2.0278893379868062, T(0),  0.4},
		{2.2214414690791831, T(0),  0.5},
		{2.4836470664490258, T(0),  0.6},
		{2.8678686047727386, T(0),  0.7},
		{3.5124073655203634, T(0),  0.8},
		{4.9672941328980516, T(0),  0.9},
	};

	for (auto data : testcases)
	{
		double const tole = bksge::abs(data.expected) * error;
		double const r = bksge::comp_ellint_3(data.k, data.nu);
		EXPECT_NEAR(data.expected, r, tole);
	}
}

GTEST_TEST(CMathTest, CompEllint3Test)
{
	CompEllint3TestFloat<float,       float>      (0.000001);
	CompEllint3TestFloat<float,       double>     (0.000001);
	CompEllint3TestFloat<float,       long double>(0.000001);
	CompEllint3TestFloat<double,      float>      (0.000001);
	CompEllint3TestFloat<double,      double>     (0.000000000001);
	CompEllint3TestFloat<double,      long double>(0.000000000001);
	CompEllint3TestFloat<long double, float>      (0.000001);
	CompEllint3TestFloat<long double, double>     (0.000000000001);
	CompEllint3TestFloat<long double, long double>(0.000000000001);

	CompEllint3TestInt<int>();
	CompEllint3TestInt<short>();

	BKSGE_CONSTEXPR auto nanf = std::numeric_limits<float>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsf = std::numeric_limits<float>::epsilon();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3f(nanf, nanf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3f(nanf, 0.0f)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3f(0.0f, nanf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3f( 1.0f + epsf, 0.0f)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3f(-1.0f - epsf, 0.0f)));

	BKSGE_CONSTEXPR auto nanl = std::numeric_limits<long double>::quiet_NaN();
	BKSGE_CONSTEXPR auto epsl = std::numeric_limits<long double>::epsilon();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3l(nanl, nanl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3l(nanl, 0.0l)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3l(0.0l, nanl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3l( 1.0l + epsl, 0.0l)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::comp_ellint_3l(-1.0l - epsl, 0.0l)));
}

}	// namespace comp_ellint_3_test

}	// namespace bksge_cmath_test
