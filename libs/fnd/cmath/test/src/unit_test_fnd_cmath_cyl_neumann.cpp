﻿/**
 *	@file	unit_test_fnd_cmath_cyl_neumann.cpp
 *
 *	@brief	cyl_neumann のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/cyl_neumann.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4305);	// 'initializing': truncation from 'double' to 'T1'

namespace bksge_cmath_test
{

namespace cyl_neumann_test
{

static_assert(bksge::is_same<float,       decltype(bksge::cyl_neumann(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_neumann(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_neumann(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_neumann(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_neumann(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_neumann(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_neumann(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_neumann(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_neumann(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_neumann(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_neumann(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_neumann(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_neumann(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_neumann(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_neumann(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_neumann(0   , 0   ))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::cyl_neumannf(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_neumannl(0.0l, 0.0l))>::value, "");

template <typename T1, typename T2>
void CylNeumannTest(double error)
{
	using Promoted = bksge::float_promote_t<T1, T2>;
	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<Promoted>::infinity();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<Promoted>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<Promoted>::max();
	BKSGE_CONSTEXPR auto min = std::numeric_limits<Promoted>::min();

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_neumann(nan1, nan2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_neumann(nan1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_neumann(T1(0), nan2)));

	struct testcase
	{
		double expected;
		T1 nu;
		T2 x;
	};

	testcase const testcases[] =
	{
		{-0.93157302493005878,  0.0000000000000000, 0.25000000000000000},
		{-0.44451873350670656,  0.0000000000000000, 0.50000000000000000},
		{-0.13717276938577236,  0.0000000000000000, 0.75000000000000000},
		{ 0.088256964215676942, 0.0000000000000000, 1.0000000000000000},
		{ 0.25821685159454072,  0.0000000000000000, 1.2500000000000000},
		{ 0.38244892379775886,  0.0000000000000000, 1.5000000000000000},
		{ 0.46549262864690610,  0.0000000000000000, 1.7500000000000000},
		{ 0.51037567264974493,  0.0000000000000000, 2.0000000000000000},
		{ 0.52006476245727862,  0.0000000000000000, 2.2500000000000000},
		{ 0.49807035961523194,  0.0000000000000000, 2.5000000000000000},
		{ 0.44865872156913222,  0.0000000000000000, 2.7500000000000000},
		{ 0.37685001001279045,  0.0000000000000000, 3.0000000000000000},
		{ 0.28828690267308710,  0.0000000000000000, 3.2500000000000000},
		{ 0.18902194392082688,  0.0000000000000000, 3.5000000000000000},
		{ 0.085256756977362638, 0.0000000000000000, 3.7500000000000000},
		{-0.016940739325064763, 0.0000000000000000, 4.0000000000000000},
		{-0.11191885116160770,  0.0000000000000000, 4.2500000000000000},
		{-0.19470500862950454,  0.0000000000000000, 4.5000000000000000},
		{-0.26123250323497549,  0.0000000000000000, 4.7500000000000000},
		{-0.30851762524903359,  0.0000000000000000, 5.0000000000000000},

		{-1.3461842332051073,   0.33333333333333333, 0.25000000000000000},
		{-0.84062782604337771,  0.33333333333333333, 0.50000000000000000},
		{-0.52488281484097088,  0.33333333333333333, 0.75000000000000000},
		{-0.27880164127599216,  0.33333333333333333, 1.0000000000000000},
		{-0.074321349727836453, 0.33333333333333333, 1.2500000000000000},
		{ 0.096610087766627981, 0.33333333333333333, 1.5000000000000000},
		{ 0.23582564494922068,  0.33333333333333333, 1.7500000000000000},
		{ 0.34319996626034494,  0.33333333333333333, 2.0000000000000000},
		{ 0.41835668452349323,  0.33333333333333333, 2.2500000000000000},
		{ 0.46145947419129157,  0.33333333333333333, 2.5000000000000000},
		{ 0.47358926135786023,  0.33333333333333333, 2.7500000000000000},
		{ 0.45689303457230640,  0.33333333333333333, 3.0000000000000000},
		{ 0.41458485697347386,  0.33333333333333333, 3.2500000000000000},
		{ 0.35084133277859947,  0.33333333333333333, 3.5000000000000000},
		{ 0.27061914527820891,  0.33333333333333333, 3.7500000000000000},
		{ 0.17941676634394862,  0.33333333333333333, 4.0000000000000000},
		{ 0.083000434191526043, 0.33333333333333333, 4.2500000000000000},
		{-0.012886361627105348, 0.33333333333333333, 4.5000000000000000},
		{-0.10281143123935124,  0.33333333333333333, 4.7500000000000000},
		{-0.18192321129343850,  0.33333333333333333, 5.0000000000000000},

		{-1.5461605241060765,   0.50000000000000000, 0.25000000000000000},
		{-0.99024588024340454,  0.50000000000000000, 0.50000000000000000},
		{-0.67411792914454438,  0.50000000000000000, 0.75000000000000000},
		{-0.43109886801837571,  0.50000000000000000, 1.0000000000000000},
		{-0.22502969244466481,  0.50000000000000000, 1.2500000000000000},
		{-0.046083165893097265, 0.50000000000000000, 1.5000000000000000},
		{ 0.10750804524368722,  0.50000000000000000, 1.7500000000000000},
		{ 0.23478571040624849,  0.50000000000000000, 2.0000000000000000},
		{ 0.33414002338271825,  0.50000000000000000, 2.2500000000000000},
		{ 0.40427830223905686,  0.50000000000000000, 2.5000000000000000},
		{ 0.44472115119490507,  0.50000000000000000, 2.7500000000000000},
		{ 0.45604882079463316,  0.50000000000000000, 3.0000000000000000},
		{ 0.43998859501924370,  0.50000000000000000, 3.2500000000000000},
		{ 0.39938682536304909,  0.50000000000000000, 3.5000000000000000},
		{ 0.33809163836693340,  0.50000000000000000, 3.7500000000000000},
		{ 0.26076607667717877,  0.50000000000000000, 4.0000000000000000},
		{ 0.17264962544644955,  0.50000000000000000, 4.2500000000000000},
		{ 0.079285862862978548, 0.50000000000000000, 4.5000000000000000},
		{-0.013765943019498003, 0.50000000000000000, 4.7500000000000000},
		{-0.10121770918510846,  0.50000000000000000, 5.0000000000000000},

		{-1.8021638417426857,   0.66666666666666666, 0.25000000000000000},
		{-1.1316060101031435,   0.66666666666666666, 0.50000000000000000},
		{-0.80251156358450748,  0.66666666666666666, 0.75000000000000000},
		{-0.56270321497463327,  0.66666666666666666, 1.0000000000000000},
		{-0.36007453643432208,  0.66666666666666666, 1.2500000000000000},
		{-0.18017937469615020,  0.66666666666666666, 1.5000000000000000},
		{-0.019885608758103752, 0.66666666666666666, 1.7500000000000000},
		{ 0.11989345361903521,  0.66666666666666666, 2.0000000000000000},
		{ 0.23690889836358039,  0.66666666666666666, 2.2500000000000000},
		{ 0.32882045742954535,  0.66666666666666666, 2.5000000000000000},
		{ 0.39385133784531856,  0.66666666666666666, 2.7500000000000000},
		{ 0.43115101690935642,  0.66666666666666666, 3.0000000000000000},
		{ 0.44098127351445843,  0.66666666666666666, 3.2500000000000000},
		{ 0.42477631413456485,  0.66666666666666666, 3.5000000000000000},
		{ 0.38510384155620386,  0.66666666666666666, 3.7500000000000000},
		{ 0.32554526794354366,  0.66666666666666666, 4.0000000000000000},
		{ 0.25051080073878446,  0.66666666666666666, 4.2500000000000000},
		{ 0.16500507211842136,  0.66666666666666666, 4.5000000000000000},
		{ 0.074359649728861360, 0.66666666666666666, 4.7500000000000000},
		{-0.016050662643389627, 0.66666666666666666, 5.0000000000000000},

		{-2.7041052293152825,   1.0000000000000000, 0.25000000000000000},
		{-1.4714723926702433,   1.0000000000000000, 0.50000000000000000},
		{-1.0375945507692856,   1.0000000000000000, 0.75000000000000000},
		{-0.78121282130028891,  1.0000000000000000, 1.0000000000000000},
		{-0.58436403661500824,  1.0000000000000000, 1.2500000000000000},
		{-0.41230862697391119,  1.0000000000000000, 1.5000000000000000},
		{-0.25397298594624573,  1.0000000000000000, 1.7500000000000000},
		{-0.10703243154093699,  1.0000000000000000, 2.0000000000000000},
		{ 0.027192057738017056, 1.0000000000000000, 2.2500000000000000},
		{ 0.14591813796678599,  1.0000000000000000, 2.5000000000000000},
		{ 0.24601900149738354,  1.0000000000000000, 2.7500000000000000},
		{ 0.32467442479180003,  1.0000000000000000, 3.0000000000000000},
		{ 0.37977777371708382,  1.0000000000000000, 3.2500000000000000},
		{ 0.41018841788751170,  1.0000000000000000, 3.5000000000000000},
		{ 0.41586877934522715,  1.0000000000000000, 3.7500000000000000},
		{ 0.39792571055709991,  1.0000000000000000, 4.0000000000000000},
		{ 0.35856889308385076,  1.0000000000000000, 4.2500000000000000},
		{ 0.30099732306965449,  1.0000000000000000, 4.5000000000000000},
		{ 0.22922559673872217,  1.0000000000000000, 4.7500000000000000},
		{ 0.14786314339122700,  1.0000000000000000, 5.0000000000000000},

		{-20.701268809592200,   2.0000000000000000, 0.25000000000000000},
		{-5.4413708371742668,   2.0000000000000000, 0.50000000000000000},
		{-2.6297460326656559,   2.0000000000000000, 0.75000000000000000},
		{-1.6506826068162548,   2.0000000000000000, 1.0000000000000000},
		{-1.1931993101785539,   2.0000000000000000, 1.2500000000000000},
		{-0.93219375976297369,  2.0000000000000000, 1.5000000000000000},
		{-0.75574746972832973,  2.0000000000000000, 1.7500000000000000},
		{-0.61740810419068193,  2.0000000000000000, 2.0000000000000000},
		{-0.49589404446793012,  2.0000000000000000, 2.2500000000000000},
		{-0.38133584924180314,  2.0000000000000000, 2.5000000000000000},
		{-0.26973581138921693,  2.0000000000000000, 2.7500000000000000},
		{-0.16040039348492377,  2.0000000000000000, 3.0000000000000000},
		{-0.054577503462573951, 2.0000000000000000, 3.2500000000000000},
		{ 0.045371437729179787, 2.0000000000000000, 3.5000000000000000},
		{ 0.13653992534009185,  2.0000000000000000, 3.7500000000000000},
		{ 0.21590359460361472,  2.0000000000000000, 4.0000000000000000},
		{ 0.28065715378930217,  2.0000000000000000, 4.2500000000000000},
		{ 0.32848159666046206,  2.0000000000000000, 4.5000000000000000},
		{ 0.35774854396706901,  2.0000000000000000, 4.7500000000000000},
		{ 0.36766288260552438,  2.0000000000000000, 5.0000000000000000},

		{-251309.48151852371,  5.0000000000000000, 0.25000000000000000},
		{-7946.3014788074752,  5.0000000000000000, 0.50000000000000000},
		{-1067.2468952289760,  5.0000000000000000, 0.75000000000000000},
		{-260.40586662581228,  5.0000000000000000, 1.0000000000000000},
		{-88.474252441880395,  5.0000000000000000, 1.2500000000000000},
		{-37.190308395498064,  5.0000000000000000, 1.5000000000000000},
		{-18.165774988201832,  5.0000000000000000, 1.7500000000000000},
		{-9.9359891284819675,  5.0000000000000000, 2.0000000000000000},
		{-5.9446343848076424,  5.0000000000000000, 2.2500000000000000},
		{-3.8301760007407522,  5.0000000000000000, 2.5000000000000000},
		{-2.6287042009459087,  5.0000000000000000, 2.7500000000000000},
		{-1.9059459538286738,  5.0000000000000000, 3.0000000000000000},
		{-1.4498157389142654,  5.0000000000000000, 3.2500000000000000},
		{-1.1494603169763686,  5.0000000000000000, 3.5000000000000000},
		{-0.94343105151431672, 5.0000000000000000, 3.7500000000000000},
		{-0.79585142111419982, 5.0000000000000000, 4.0000000000000000},
		{-0.68479288173907016, 5.0000000000000000, 4.2500000000000000},
		{-0.59631936513587558, 5.0000000000000000, 4.5000000000000000},
		{-0.52130838331747587, 5.0000000000000000, 4.7500000000000000},
		{-0.45369482249110193, 5.0000000000000000, 5.0000000000000000},

		{-124241617095379.48, 10.000000000000000, 0.25000000000000000},
		{-121963623349.56966, 10.000000000000000, 0.50000000000000000},
		{-2133501638.9057348, 10.000000000000000, 0.75000000000000000},
		{-121618014.27868921, 10.000000000000000, 1.0000000000000000},
		{-13265210.158452792, 10.000000000000000, 1.2500000000000000},
		{-2183993.0260864049, 10.000000000000000, 1.5000000000000000},
		{-478274.82386541169, 10.000000000000000, 1.7500000000000000},
		{-129184.54220803917, 10.000000000000000, 2.0000000000000000},
		{-40993.254794381690, 10.000000000000000, 2.2500000000000000},
		{-14782.847716021070, 10.000000000000000, 2.5000000000000000},
		{-5916.5330998776262, 10.000000000000000, 2.7500000000000000},
		{-2582.6071294842995, 10.000000000000000, 3.0000000000000000},
		{-1213.3423564023892, 10.000000000000000, 3.2500000000000000},
		{-607.27437834125760, 10.000000000000000, 3.5000000000000000},
		{-321.17461059752202, 10.000000000000000, 3.7500000000000000},
		{-178.33055590796428, 10.000000000000000, 4.0000000000000000},
		{-103.40496587570090, 10.000000000000000, 4.2500000000000000},
		{-62.345024619781434, 10.000000000000000, 4.5000000000000000},
		{-38.944510430296937, 10.000000000000000, 4.7500000000000000},
		{-25.129110095610095, 10.000000000000000, 5.0000000000000000},

		{-4.4678815064152581e+34, 20.000000000000000, 0.25000000000000000},
		{-4.2714301215659088e+28, 20.000000000000000, 0.50000000000000000},
		{-1.2898357375834223e+25, 20.000000000000000, 0.75000000000000000},
		{-4.1139703148355065e+22, 20.000000000000000, 1.0000000000000000},
		{-4.7783533372148580e+20, 20.000000000000000, 1.2500000000000000},
		{-1.2577301772964241e+19, 20.000000000000000, 1.5000000000000000},
		{-5.8251041176649626e+17, 20.000000000000000, 1.7500000000000000},
		{-40816513889983640.,     20.000000000000000, 2.0000000000000000},
		{-3925339868516418.5,     20.000000000000000, 2.2500000000000000},
		{-484776559582090.25,     20.000000000000000, 2.5000000000000000},
		{-73320655044814.469,     20.000000000000000, 2.7500000000000000},
		{-13113540041757.449,     20.000000000000000, 3.0000000000000000},
		{-2700669268882.7139,     20.000000000000000, 3.2500000000000000},
		{-627339518240.21240,     20.000000000000000, 3.5000000000000000},
		{-161695236802.71753,     20.000000000000000, 3.7500000000000000},
		{-45637199262.220100,     20.000000000000000, 4.0000000000000000},
		{-13953299213.925377,     20.000000000000000, 4.2500000000000000},
		{-4580215756.5691023,     20.000000000000000, 4.5000000000000000},
		{-1602110715.5159132,     20.000000000000000, 4.7500000000000000},
		{-593396529.69143200,     20.000000000000000, 5.0000000000000000},

		{-2.7643487471155969e+107, 50.000000000000000, 0.25000000000000000},
		{-2.4575848224461092e+92,  50.000000000000000, 0.50000000000000000},
		{-3.8604508467683829e+83,  50.000000000000000, 0.75000000000000000},
		{-2.1911428126053411e+77,  50.000000000000000, 1.0000000000000000},
		{-3.1362926828833165e+72,  50.000000000000000, 1.2500000000000000},
		{-3.4584216846550566e+68,  50.000000000000000, 1.5000000000000000},
		{-1.5607714080312795e+65,  50.000000000000000, 1.7500000000000000},
		{-1.9761505765184128e+62,  50.000000000000000, 2.0000000000000000},
		{-5.5023640499231188e+59,  50.000000000000000, 2.2500000000000000},
		{-2.8530384545826849e+57,  50.000000000000000, 2.5000000000000000},
		{-2.4467169322684809e+55,  50.000000000000000, 2.7500000000000000},
		{-3.1793891461005181e+53,  50.000000000000000, 3.0000000000000000},
		{-5.8573901231568658e+51,  50.000000000000000, 3.2500000000000000},
		{-1.4528262197760965e+50,  50.000000000000000, 3.5000000000000000},
		{-4.6566569870478635e+48,  50.000000000000000, 3.7500000000000000},
		{-1.8661134361400254e+47,  50.000000000000000, 4.0000000000000000},
		{-9.1005883612255402e+45,  50.000000000000000, 4.2500000000000000},
		{-5.2813777542386141e+44,  50.000000000000000, 4.5000000000000000},
		{-3.5795477722116469e+43,  50.000000000000000, 4.7500000000000000},
		{-2.7888370175838930e+42,  50.000000000000000, 5.0000000000000000},

		{-6.0523080585856763e+245, 100.00000000000000, 0.25000000000000000},
		{-4.7766903780412668e+215, 100.00000000000000, 0.50000000000000000},
		{-1.1758283017660654e+198, 100.00000000000000, 0.75000000000000000},
		{-3.7752878101091316e+185, 100.00000000000000, 1.0000000000000000},
		{-7.7013290729995187e+175, 100.00000000000000, 1.2500000000000000},
		{-9.3152624794288802e+167, 100.00000000000000, 1.5000000000000000},
		{-1.8854163374247264e+161, 100.00000000000000, 1.7500000000000000},
		{-3.0008260488566283e+155, 100.00000000000000, 2.0000000000000000},
		{-2.3075650873777408e+150, 100.00000000000000, 2.2500000000000000},
		{-6.1476258561369381e+145, 100.00000000000000, 2.5000000000000000},
		{-4.4758816234829593e+141, 100.00000000000000, 2.7500000000000000},
		{-7.4747961023547862e+137, 100.00000000000000, 3.0000000000000000},
		{-2.5067022766901547e+134, 100.00000000000000, 3.2500000000000000},
		{-1.5222488313432757e+131, 100.00000000000000, 3.5000000000000000},
		{-1.5422392812241399e+128, 100.00000000000000, 3.7500000000000000},
		{-2.4400857387551062e+125, 100.00000000000000, 4.0000000000000000},
		{-5.7118153392422293e+122, 100.00000000000000, 4.2500000000000000},
		{-1.8915420905193392e+120, 100.00000000000000, 4.5000000000000000},
		{-8.5357945104770158e+117, 100.00000000000000, 4.7500000000000000},
		{-5.0848639160196196e+115, 100.00000000000000, 5.0000000000000000},

		{-0.30851762524903359,   0.0000000000000000, 5.0000000000000000},
		{ 0.055671167283599457,  0.0000000000000000, 10.000000000000000},
		{ 0.20546429603891822,   0.0000000000000000, 15.000000000000000},
		{ 0.062640596809384053,  0.0000000000000000, 20.000000000000000},
		{-0.12724943226800617,   0.0000000000000000, 25.000000000000000},
		{-0.11729573168666413,   0.0000000000000000, 30.000000000000000},
		{ 0.045797987195155689,  0.0000000000000000, 35.000000000000000},
		{ 0.12593641705826092,   0.0000000000000000, 40.000000000000000},
		{ 0.027060469763313333,  0.0000000000000000, 45.000000000000000},
		{-0.098064995470077118,  0.0000000000000000, 50.000000000000000},
		{-0.077569178730412594,  0.0000000000000000, 55.000000000000000},
		{ 0.047358952209449426,  0.0000000000000000, 60.000000000000000},
		{ 0.097183557740181920,  0.0000000000000000, 65.000000000000000},
		{ 0.0093096664589409992, 0.0000000000000000, 70.000000000000000},
		{-0.085369047647775656,  0.0000000000000000, 75.000000000000000},
		{-0.055620339089770016,  0.0000000000000000, 80.000000000000000},
		{ 0.049567884951494251,  0.0000000000000000, 85.000000000000000},
		{ 0.079776475854877751,  0.0000000000000000, 90.000000000000000},
		{-0.0028230995861232107, 0.0000000000000000, 95.000000000000000},
		{-0.077244313365083153,  0.0000000000000000, 100.00000000000000},

		{-0.18192321129343850,  0.33333333333333333, 5.0000000000000000},
		{ 0.17020111788268760,  0.33333333333333333, 10.000000000000000},
		{ 0.18540507541540796,  0.33333333333333333, 15.000000000000000},
		{-0.028777707635715043, 0.33333333333333333, 20.000000000000000},
		{-0.15829741864944163,  0.33333333333333333, 25.000000000000000},
		{-0.058645772316705209, 0.33333333333333333, 30.000000000000000},
		{ 0.10294930308870617,  0.33333333333333333, 35.000000000000000},
		{ 0.10547870367098922,  0.33333333333333333, 40.000000000000000},
		{-0.034334228816010816, 0.33333333333333333, 45.000000000000000},
		{-0.11283489933031279,  0.33333333333333333, 50.000000000000000},
		{-0.030007358986895105, 0.33333333333333333, 55.000000000000000},
		{ 0.086699173295718121, 0.33333333333333333, 60.000000000000000},
		{ 0.074875579668878658, 0.33333333333333333, 65.000000000000000},
		{-0.039323246374552680, 0.33333333333333333, 70.000000000000000},
		{-0.091263539574475236, 0.33333333333333333, 75.000000000000000},
		{-0.013358849535984318, 0.33333333333333333, 80.000000000000000},
		{ 0.078373575537830198, 0.33333333333333333, 85.000000000000000},
		{ 0.055812482883955940, 0.33333333333333333, 90.000000000000000},
		{-0.043310380106990683, 0.33333333333333333, 95.000000000000000},
		{-0.076900504962136559, 0.33333333333333333, 100.00000000000000},

		{-0.10121770918510846,   0.50000000000000000, 5.0000000000000000},
		{ 0.21170886633139810,   0.50000000000000000, 10.000000000000000},
		{ 0.15650551590730855,   0.50000000000000000, 15.000000000000000},
		{-0.072806904785061938,  0.50000000000000000, 20.000000000000000},
		{-0.15817308404205055,   0.50000000000000000, 25.000000000000000},
		{-0.022470290598831138,  0.50000000000000000, 30.000000000000000},
		{ 0.12187835265849535,   0.50000000000000000, 35.000000000000000},
		{ 0.084138655676395377,  0.50000000000000000, 40.000000000000000},
		{-0.062482641933003201,  0.50000000000000000, 45.000000000000000},
		{-0.10888475635053954,   0.50000000000000000, 50.000000000000000},
		{-0.0023805454010949376, 0.50000000000000000, 55.000000000000000},
		{ 0.098104683735037918,  0.50000000000000000, 60.000000000000000},
		{ 0.055663470218594434,  0.50000000000000000, 65.000000000000000},
		{-0.060396767883824871,  0.50000000000000000, 70.000000000000000},
		{-0.084922578922046868,  0.50000000000000000, 75.000000000000000},
		{ 0.0098472271924441284, 0.50000000000000000, 80.000000000000000},
		{ 0.085190643574343625,  0.50000000000000000, 85.000000000000000},
		{ 0.037684970437156268,  0.50000000000000000, 90.000000000000000},
		{-0.059772904856097500,  0.50000000000000000, 95.000000000000000},
		{-0.068803091468728109,  0.50000000000000000, 100.00000000000000},

		{-0.016050662643389627, 0.66666666666666666, 5.0000000000000000},
		{ 0.23937232657540733,  0.66666666666666666, 10.000000000000000},
		{ 0.11762106604241235,  0.66666666666666666, 15.000000000000000},
		{-0.11182254014899558,  0.66666666666666666, 20.000000000000000},
		{-0.14756582982938804,  0.66666666666666666, 25.000000000000000},
		{ 0.015078692908077713, 0.66666666666666666, 30.000000000000000},
		{ 0.13260911815705795,  0.66666666666666666, 35.000000000000000},
		{ 0.057217565989652698, 0.66666666666666666, 40.000000000000000},
		{-0.086373755152382006, 0.66666666666666666, 45.000000000000000},
		{-0.097624139208051616, 0.66666666666666666, 50.000000000000000},
		{ 0.025354902147023392, 0.66666666666666666, 55.000000000000000},
		{ 0.10288136476351206,  0.66666666666666666, 60.000000000000000},
		{ 0.032728379560128203, 0.66666666666666666, 65.000000000000000},
		{-0.077363672735747818, 0.66666666666666666, 70.000000000000000},
		{-0.072855870458293961, 0.66666666666666666, 75.000000000000000},
		{ 0.032358106046953543, 0.66666666666666666, 80.000000000000000},
		{ 0.086240651537394228, 0.66666666666666666, 85.000000000000000},
		{ 0.017029601697285190, 0.66666666666666666, 90.000000000000000},
		{-0.072173520560584681, 0.66666666666666666, 95.000000000000000},
		{-0.056057339204073887, 0.66666666666666666, 100.00000000000000},

		{ 0.14786314339122700,   1.0000000000000000, 5.0000000000000000},
		{ 0.24901542420695386,   1.0000000000000000, 10.000000000000000},
		{ 0.021073628036873522,  1.0000000000000000, 15.000000000000000},
		{-0.16551161436252115,   1.0000000000000000, 20.000000000000000},
		{-0.098829964783237412,  1.0000000000000000, 25.000000000000000},
		{ 0.084425570661747135,  1.0000000000000000, 30.000000000000000},
		{ 0.12751273354559009,   1.0000000000000000, 35.000000000000000},
		{-0.0057935058215497536, 1.0000000000000000, 40.000000000000000},
		{-0.11552517964639945,   1.0000000000000000, 45.000000000000000},
		{-0.056795668562014692,  1.0000000000000000, 50.000000000000000},
		{ 0.073846265432577926,  1.0000000000000000, 55.000000000000000},
		{ 0.091869609369866892,  1.0000000000000000, 60.000000000000000},
		{-0.017940374275377362,  1.0000000000000000, 65.000000000000000},
		{-0.094844652625716230,  1.0000000000000000, 70.000000000000000},
		{-0.035213785160580421,  1.0000000000000000, 75.000000000000000},
		{ 0.069395913784588037,  1.0000000000000000, 80.000000000000000},
		{ 0.071233187582749768,  1.0000000000000000, 85.000000000000000},
		{-0.026187238607768244,  1.0000000000000000, 90.000000000000000},
		{-0.081827958724501215,  1.0000000000000000, 95.000000000000000},
		{-0.020372312002759834,  1.0000000000000000, 100.00000000000000},

		{ 0.36766288260552438,   2.0000000000000000, 5.0000000000000000},
		{-0.0058680824422086830, 2.0000000000000000, 10.000000000000000},
		{-0.20265447896733507,   2.0000000000000000, 15.000000000000000},
		{-0.079191758245636165,  2.0000000000000000, 20.000000000000000},
		{ 0.11934303508534717,   2.0000000000000000, 25.000000000000000},
		{ 0.12292410306411394,   2.0000000000000000, 30.000000000000000},
		{-0.038511545278264829,  2.0000000000000000, 35.000000000000000},
		{-0.12622609234933840,   2.0000000000000000, 40.000000000000000},
		{-0.032194922192042195,  2.0000000000000000, 45.000000000000000},
		{ 0.095793168727596537,  2.0000000000000000, 50.000000000000000},
		{ 0.080254497473415426,  2.0000000000000000, 55.000000000000000},
		{-0.044296631897120527,  2.0000000000000000, 60.000000000000000},
		{-0.097735569256347382,  2.0000000000000000, 65.000000000000000},
		{-0.012019513676818605,  2.0000000000000000, 70.000000000000000},
		{ 0.084430013376826846,  2.0000000000000000, 75.000000000000000},
		{ 0.057355236934384719,  2.0000000000000000, 80.000000000000000},
		{-0.047891809949547198,  2.0000000000000000, 85.000000000000000},
		{-0.080358414490605934,  2.0000000000000000, 90.000000000000000},
		{ 0.0011004057182389746, 2.0000000000000000, 95.000000000000000},
		{ 0.076836867125027963,  2.0000000000000000, 100.00000000000000},

		{-0.45369482249110193,    5.0000000000000000, 5.0000000000000000},
		{ 0.13540304768936234,    5.0000000000000000, 10.000000000000000},
		{ 0.16717271575940015,    5.0000000000000000, 15.000000000000000},
		{-0.10003576788953220,    5.0000000000000000, 20.000000000000000},
		{-0.14705799311372267,    5.0000000000000000, 25.000000000000000},
		{ 0.031627359289264301,   5.0000000000000000, 30.000000000000000},
		{ 0.13554781474770028,    5.0000000000000000, 35.000000000000000},
		{ 0.031869448780850247,   5.0000000000000000, 40.000000000000000},
		{-0.10426932700176872,    5.0000000000000000, 45.000000000000000},
		{-0.078548413913081594,   5.0000000000000000, 50.000000000000000},
		{ 0.055257033062858375,   5.0000000000000000, 55.000000000000000},
		{ 0.099464632840450887,   5.0000000000000000, 60.000000000000000},
		{ 0.00023860469499595305, 5.0000000000000000, 65.000000000000000},
		{-0.091861802216406052,   5.0000000000000000, 70.000000000000000},
		{-0.048383671296970042,   5.0000000000000000, 75.000000000000000},
		{ 0.060293667104896316,   5.0000000000000000, 80.000000000000000},
		{ 0.077506166682733996,   5.0000000000000000, 85.000000000000000},
		{-0.015338764062239767,   5.0000000000000000, 90.000000000000000},
		{-0.081531504045514361,   5.0000000000000000, 95.000000000000000},
		{-0.029480196281661937,   5.0000000000000000, 100.00000000000000},

		{-25.129110095610095,    10.000000000000000, 5.0000000000000000},
		{-0.35981415218340279,   10.000000000000000, 10.000000000000000},
		{ 0.21997141360195577,   10.000000000000000, 15.000000000000000},
		{-0.043894653515658105,  10.000000000000000, 20.000000000000000},
		{-0.14871839049980651,   10.000000000000000, 25.000000000000000},
		{ 0.075056702122397012,  10.000000000000000, 30.000000000000000},
		{ 0.12222473135000546,   10.000000000000000, 35.000000000000000},
		{-0.046723877232677985,  10.000000000000000, 40.000000000000000},
		{-0.11739339009322181,   10.000000000000000, 45.000000000000000},
		{ 0.0057238971820535930, 10.000000000000000, 50.000000000000000},
		{ 0.10733910125831631,   10.000000000000000, 55.000000000000000},
		{ 0.036290350559545478,  10.000000000000000, 60.000000000000000},
		{-0.083239127691715667,  10.000000000000000, 65.000000000000000},
		{-0.069639384138314858,  10.000000000000000, 70.000000000000000},
		{ 0.045798335061325066,  10.000000000000000, 75.000000000000000},
		{ 0.086269195064844456,  10.000000000000000, 80.000000000000000},
		{-0.0018234674126248740, 10.000000000000000, 85.000000000000000},
		{-0.082067762371231284,  10.000000000000000, 90.000000000000000},
		{-0.038798074754578089,  10.000000000000000, 95.000000000000000},
		{ 0.058331574236414913,  10.000000000000000, 100.00000000000000},

		{-593396529.69143200,    20.000000000000000, 5.0000000000000000},
		{-1597.4838482696259,    20.000000000000000, 10.000000000000000},
		{-3.3087330924737621,    20.000000000000000, 15.000000000000000},
		{-0.28548945860020319,   20.000000000000000, 20.000000000000000},
		{ 0.19804074776289243,   20.000000000000000, 25.000000000000000},
		{-0.16848153948742683,   20.000000000000000, 30.000000000000000},
		{ 0.10102784152594022,   20.000000000000000, 35.000000000000000},
		{ 0.045161820565805755,  20.000000000000000, 40.000000000000000},
		{-0.12556489308015448,   20.000000000000000, 45.000000000000000},
		{ 0.016442633948115834,  20.000000000000000, 50.000000000000000},
		{ 0.10853448778255181,   20.000000000000000, 55.000000000000000},
		{-0.026721408520664701,  20.000000000000000, 60.000000000000000},
		{-0.098780425256324175,  20.000000000000000, 65.000000000000000},
		{ 0.016201957786018233,  20.000000000000000, 70.000000000000000},
		{ 0.093591198265063721,  20.000000000000000, 75.000000000000000},
		{ 0.0040484400737296200, 20.000000000000000, 80.000000000000000},
		{-0.086314929459920531,  20.000000000000000, 85.000000000000000},
		{-0.028274110097231530,  20.000000000000000, 90.000000000000000},
		{ 0.072349520791638741,  20.000000000000000, 95.000000000000000},
		{ 0.051247973076188474,  20.000000000000000, 100.00000000000000},

		{-2.7888370175838930e+42, 50.000000000000000, 5.0000000000000000},
		{-3.6410665018007421e+27, 50.000000000000000, 10.000000000000000},
		{-1.0929732912175415e+19, 50.000000000000000, 15.000000000000000},
		{-15606426801663.734,     50.000000000000000, 20.000000000000000},
		{-753573251.44662738,     50.000000000000000, 25.000000000000000},
		{-386759.32602734759,     50.000000000000000, 30.000000000000000},
		{-1172.8690492895323,     50.000000000000000, 35.000000000000000},
		{-15.615608873419944,     50.000000000000000, 40.000000000000000},
		{-0.87058346204176895,    50.000000000000000, 45.000000000000000},
		{-0.21031655464397747,    50.000000000000000, 50.000000000000000},
		{ 0.093048240412999389,   50.000000000000000, 55.000000000000000},
		{ 0.0086417699626744754,  50.000000000000000, 60.000000000000000},
		{-0.025019788459222037,   50.000000000000000, 65.000000000000000},
		{-0.0014815155191909152,  50.000000000000000, 70.000000000000000},
		{ 0.050335774732164121,   50.000000000000000, 75.000000000000000},
		{-0.092924250967987232,   50.000000000000000, 80.000000000000000},
		{ 0.087332463030205698,   50.000000000000000, 85.000000000000000},
		{-0.016164237701651860,   50.000000000000000, 90.000000000000000},
		{-0.068897613820457934,   50.000000000000000, 95.000000000000000},
		{ 0.076505263944803045,   50.000000000000000, 100.00000000000000},

		{-5.0848639160196196e+115, 100.00000000000000, 5.0000000000000000},
		{-4.8491482711800252e+85,  100.00000000000000, 10.000000000000000},
		{-1.6375955323195320e+68,  100.00000000000000, 15.000000000000000},
		{-8.2002648144679115e+55,  100.00000000000000, 20.000000000000000},
		{-2.9712216432562368e+46,  100.00000000000000, 25.000000000000000},
		{-7.2875284708240751e+38,  100.00000000000000, 30.000000000000000},
		{-3.4251079902107980e+32,  100.00000000000000, 35.000000000000000},
		{-1.4552439438102214e+27,  100.00000000000000, 40.000000000000000},
		{-3.4506612476220073e+22,  100.00000000000000, 45.000000000000000},
		{-3.2938001882025477e+18,  100.00000000000000, 50.000000000000000},
		{-1005686182055520.4,      100.00000000000000, 55.000000000000000},
		{-831892881402.09033,      100.00000000000000, 60.000000000000000},
		{-1650863778.0598392,      100.00000000000000, 65.000000000000000},
		{-7192614.1976097794,      100.00000000000000, 70.000000000000000},
		{-64639.072261231595,      100.00000000000000, 75.000000000000000},
		{-1152.5905185698466,      100.00000000000000, 80.000000000000000},
		{-40.250761402101489,      100.00000000000000, 85.000000000000000},
		{-2.8307771387185294,      100.00000000000000, 90.000000000000000},
		{-0.45762200495904848,     100.00000000000000, 95.000000000000000},
		{-0.16692141141757652,     100.00000000000000, 100.00000000000000},

		{-2.2438688257729954e-02, 100.0000000000000000, 1000.0000000000000000},
		{-2.1077595159819992e-02, 100.0000000000000000, 1100.0000000000000000},
		{-3.5299439206692585e-03, 100.0000000000000000, 1200.0000000000000000},
		{ 1.4250019326536615e-02, 100.0000000000000000, 1300.0000000000000000},
		{ 2.1304679089735663e-02, 100.0000000000000000, 1400.0000000000000000},
		{ 1.5734395077905267e-02, 100.0000000000000000, 1500.0000000000000000},
		{ 2.5544633636137774e-03, 100.0000000000000000, 1600.0000000000000000},
		{-1.0722045524849367e-02, 100.0000000000000000, 1700.0000000000000000},
		{-1.8036919243226864e-02, 100.0000000000000000, 1800.0000000000000000},
		{-1.6958415593079763e-02, 100.0000000000000000, 1900.0000000000000000},
		{-8.8788704566276667e-03, 100.0000000000000000, 2000.0000000000000000},
		{ 2.2504407108413179e-03, 100.0000000000000000, 2100.0000000000000000},
		{ 1.1833215246712251e-02, 100.0000000000000000, 2200.0000000000000000},
		{ 1.6398784536343945e-02, 100.0000000000000000, 2300.0000000000000000},
		{ 1.4675984403642338e-02, 100.0000000000000000, 2400.0000000000000000},
		{ 7.7523920451654229e-03, 100.0000000000000000, 2500.0000000000000000},
		{-1.5759822576003489e-03, 100.0000000000000000, 2600.0000000000000000},
		{-9.9314877404787089e-03, 100.0000000000000000, 2700.0000000000000000},
		{-1.4534495161704743e-02, 100.0000000000000000, 2800.0000000000000000},
		{-1.4059273497237509e-02, 100.0000000000000000, 2900.0000000000000000},
		{-8.9385158149605185e-03, 100.0000000000000000, 3000.0000000000000000},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::cyl_neumann(data.nu, data.x);

		if (data.expected > max)
		{
			if (!bksge::isnan(r))
			{
				EXPECT_EQ(+inf, r);
			}
		}
		else if (data.expected < lowest)
		{
			if (!bksge::isnan(r))
			{
				EXPECT_EQ(-inf, r);
			}
		}
		else if (0 <= data.expected && data.expected < min)
		{
			EXPECT_GT(min, r);
		}
		else
		{
			double tole = bksge::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

GTEST_TEST(CMathTest, CylNeumannTest)
{
	CylNeumannTest<float,       float>      (0.01);
	CylNeumannTest<float,       double>     (0.000001);
	CylNeumannTest<float,       long double>(0.000001);
	CylNeumannTest<double,      float>      (0.0000000001);
	CylNeumannTest<double,      double>     (0.0000000001);
	CylNeumannTest<double,      long double>(0.0000000001);
	CylNeumannTest<long double, float>      (0.0000000001);
	CylNeumannTest<long double, double>     (0.0000000001);
	CylNeumannTest<long double, long double>(0.0000000001);

	BKSGE_CONSTEXPR auto nanf = std::numeric_limits<float>::quiet_NaN();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_neumannf(nanf, nanf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_neumannf(nanf, 0.0f)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_neumannf(0.0f, nanf)));

	BKSGE_CONSTEXPR auto nanl = std::numeric_limits<long double>::quiet_NaN();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_neumannl(nanl, nanl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_neumannl(nanl, 0.0l)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_neumannl(0.0l, nanl)));
}

}	// namespace cyl_neumann_test

}	// namespace bksge_cmath_test

BKSGE_WARNING_POP();
