﻿/**
 *	@file	unit_test_fnd_cmath_cyl_bessel_i.cpp
 *
 *	@brief	cyl_bessel_i のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/cyl_bessel_i.hpp>
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

namespace cyl_bessel_i_test
{

static_assert(bksge::is_same<float,       decltype(bksge::cyl_bessel_i(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_bessel_i(0.0f, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_bessel_i(0.0f, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_bessel_i(0.0f, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_bessel_i(0.0 , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_bessel_i(0.0 , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_bessel_i(0.0 , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_bessel_i(0.0 , 0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_bessel_i(0.0l, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_bessel_i(0.0l, 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_bessel_i(0.0l, 0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_bessel_i(0.0l, 0   ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_bessel_i(0   , 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_bessel_i(0   , 0.0 ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_bessel_i(0   , 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::cyl_bessel_i(0   , 0   ))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::cyl_bessel_if(0.0f, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::cyl_bessel_il(0.0l, 0.0l))>::value, "");

template <typename T1, typename T2>
void CylBesselITestFloat(double error)
{
	using Promoted = bksge::float_promote_t<T1, T2>;
	BKSGE_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	BKSGE_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<Promoted>::infinity();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<Promoted>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<Promoted>::max();
	BKSGE_CONSTEXPR auto min = std::numeric_limits<Promoted>::min();

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_bessel_i(nan1, nan2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_bessel_i(nan1, T2(0))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_bessel_i(T1(0), nan2)));

	struct testcase
	{
		double expected;
		T1 nu;
		T2 x;
	};

	testcase const testcases[] =
	{
		{1.0000000000000000, 0.0000000000000000, 0.0000000000000000},
		{1.0156861412236078, 0.0000000000000000, 0.2500000000000000},
		{1.0634833707413236, 0.0000000000000000, 0.5000000000000000},
		{1.1456467780440014, 0.0000000000000000, 0.7500000000000000},
		{1.2660658777520082, 0.0000000000000000, 1.0000000000000000},
		{1.4304687177218294, 0.0000000000000000, 1.2500000000000000},
		{1.6467231897728904, 0.0000000000000000, 1.5000000000000000},
		{1.9252521538585021, 0.0000000000000000, 1.7500000000000000},
		{2.2795853023360668, 0.0000000000000000, 2.0000000000000000},
		{2.7270783071907951, 0.0000000000000000, 2.2500000000000000},
		{3.2898391440501231, 0.0000000000000000, 2.5000000000000000},
		{3.9959131072376550, 0.0000000000000000, 2.7500000000000000},
		{4.8807925858650245, 0.0000000000000000, 3.0000000000000000},
		{5.9893359979395138, 0.0000000000000000, 3.2500000000000000},
		{7.3782034322254750, 0.0000000000000000, 3.5000000000000000},
		{9.1189458608445655, 0.0000000000000000, 3.7500000000000000},
		{11.301921952136325, 0.0000000000000000, 4.0000000000000000},
		{14.041263683000595, 0.0000000000000000, 4.2500000000000000},
		{17.481171855609272, 0.0000000000000000, 4.5000000000000000},
		{21.803898740902120, 0.0000000000000000, 4.7500000000000000},
		{27.239871823604439, 0.0000000000000000, 5.0000000000000000},

		{0.0000000000000000, 0.33333333333333331, 0.0000000000000000},
		{0.5665068655780866, 0.33333333333333331, 0.25000000000000000},
		{0.7389731564251186, 0.33333333333333331, 0.50000000000000000},
		{0.8953232036583681, 0.33333333333333331, 0.75000000000000000},
		{1.0646313978895283, 0.33333333333333331, 1.0000000000000000},
		{1.2623776732605250, 0.33333333333333331, 1.2500000000000000},
		{1.5014290000224382, 0.33333333333333331, 1.5000000000000000},
		{1.7951195525946040, 0.33333333333333331, 1.7500000000000000},
		{2.1587825813728614, 0.33333333333333331, 2.0000000000000000},
		{2.6109134564811405, 0.33333333333333331, 2.2500000000000000},
		{3.1743242297241938, 0.33333333333333331, 2.5000000000000000},
		{3.8774551722182093, 0.33333333333333331, 2.7500000000000000},
		{4.7559569371646946, 0.33333333333333331, 3.0000000000000000},
		{5.8546499652731825, 0.33333333333333331, 3.2500000000000000},
		{7.2299798619171129, 0.33333333333333331, 3.5000000000000000},
		{8.9531114355506318, 0.33333333333333331, 3.7500000000000000},
		{11.113838389991479, 0.33333333333333331, 4.0000000000000000},
		{13.825531136529117, 0.33333333333333331, 4.2500000000000000},
		{17.231403968478318, 0.33333333333333331, 4.5000000000000000},
		{21.512458099556554, 0.33333333333333331, 4.7500000000000000},
		{26.897553069268362, 0.33333333333333331, 5.0000000000000000},

		{0.0000000000000000, 0.50000000000000000, 0.0000000000000000},
		{0.4031109348997589, 0.50000000000000000, 0.25000000000000000},
		{0.5879930867904157, 0.50000000000000000, 0.50000000000000000},
		{0.7576149863899129, 0.50000000000000000, 0.75000000000000000},
		{0.9376748882454869, 0.50000000000000000, 1.0000000000000000},
		{1.1432089853159872, 0.50000000000000000, 1.2500000000000000},
		{1.3871617204034761, 0.50000000000000000, 1.5000000000000000},
		{1.6830217804556813, 0.50000000000000000, 1.7500000000000000},
		{2.0462368630890526, 0.50000000000000000, 2.0000000000000000},
		{2.4953405089360046, 0.50000000000000000, 2.2500000000000000},
		{3.0530935381967175, 0.50000000000000000, 2.5000000000000000},
		{3.7477882494879449, 0.50000000000000000, 2.7500000000000000},
		{4.6148229034075969, 0.50000000000000000, 3.0000000000000000},
		{5.6986505325335486, 0.50000000000000000, 3.2500000000000000},
		{7.0552194086911859, 0.50000000000000000, 3.5000000000000000},
		{8.7550467841188979, 0.50000000000000000, 3.7500000000000000},
		{10.887101798588422, 0.50000000000000000, 4.0000000000000000},
		{13.563718712579764, 0.50000000000000000, 4.2500000000000000},
		{16.926820080158183, 0.50000000000000000, 4.5000000000000000},
		{21.155804306570005, 0.50000000000000000, 4.7500000000000000},
		{26.477547497559065, 0.50000000000000000, 5.0000000000000000},

		{0.0000000000000000, 0.66666666666666663, 0.0000000000000000},
		{0.2795369061320044, 0.66666666666666663, 0.25000000000000000},
		{0.4562832311355689, 0.66666666666666663, 0.50000000000000000},
		{0.6259456983818262, 0.66666666666666663, 0.75000000000000000},
		{0.8075212886061297, 0.66666666666666663, 1.0000000000000000},
		{1.0139484513577173, 0.66666666666666663, 1.2500000000000000},
		{1.2572918396962993, 0.66666666666666663, 1.5000000000000000},
		{1.5505806938325581, 0.66666666666666663, 1.7500000000000000},
		{1.9089492968236210, 0.66666666666666663, 2.0000000000000000},
		{2.3506463490300340, 0.66666666666666663, 2.2500000000000000},
		{2.8981161894224896, 0.66666666666666663, 2.5000000000000000},
		{3.5792654911068724, 0.66666666666666663, 2.7500000000000000},
		{4.4290087213549514, 0.66666666666666663, 3.0000000000000000},
		{5.4911895720097705, 0.66666666666666663, 3.2500000000000000},
		{6.8209918044137305, 0.66666666666666663, 3.5000000000000000},
		{8.4879784249619785, 0.66666666666666663, 3.7500000000000000},
		{10.579932774013004, 0.66666666666666663, 4.0000000000000000},
		{13.207720355482458, 0.66666666666666663, 4.2500000000000000},
		{16.511448404200543, 0.66666666666666663, 4.5000000000000000},
		{20.668274532832392, 0.66666666666666663, 4.7500000000000000},
		{25.902310583215122, 0.66666666666666663, 5.0000000000000000},

		{0.0000000000000000, 1.0000000000000000, 0.0000000000000000},
		{0.1259791089454679, 1.0000000000000000, 0.25000000000000000},
		{0.2578943053908963, 1.0000000000000000, 0.50000000000000000},
		{0.4019924615809222, 1.0000000000000000, 0.75000000000000000},
		{0.5651591039924850, 1.0000000000000000, 1.0000000000000000},
		{0.7552814183407472, 1.0000000000000000, 1.2500000000000000},
		{0.9816664285779072, 1.0000000000000000, 1.5000000000000000},
		{1.2555375122401728, 1.0000000000000000, 1.7500000000000000},
		{1.5906368546373291, 1.0000000000000000, 2.0000000000000000},
		{2.0039674569295931, 1.0000000000000000, 2.2500000000000000},
		{2.5167162452886984, 1.0000000000000000, 2.5000000000000000},
		{3.1554101386190028, 1.0000000000000000, 2.7500000000000000},
		{3.9533702174026097, 1.0000000000000000, 3.0000000000000000},
		{4.9525461659085490, 1.0000000000000000, 3.2500000000000000},
		{6.2058349222583642, 1.0000000000000000, 3.5000000000000000},
		{7.7800152298244170, 1.0000000000000000, 3.7500000000000000},
		{9.7594651537044523, 1.0000000000000000, 4.0000000000000000},
		{12.250874667409304, 1.0000000000000000, 4.2500000000000000},
		{15.389222753735924, 1.0000000000000000, 4.5000000000000000},
		{19.345361447520226, 1.0000000000000000, 4.7500000000000000},
		{24.335642142450524, 1.0000000000000000, 5.0000000000000000},

		{0.0000000000000000, 2.0000000000000000, 0.0000000000000000},
		{0.0078532696598645167, 2.0000000000000000, 0.25000000000000000},
		{0.031906149177738249, 2.0000000000000000, 0.50000000000000000},
		{0.073666880494875436, 2.0000000000000000, 0.75000000000000000},
		{0.13574766976703831, 2.0000000000000000, 1.0000000000000000},
		{0.22201844837663415, 2.0000000000000000, 1.2500000000000000},
		{0.33783461833568068, 2.0000000000000000, 1.5000000000000000},
		{0.49035213986973314, 2.0000000000000000, 1.7500000000000000},
		{0.68894844769873831, 2.0000000000000000, 2.0000000000000000},
		{0.94577390103115722, 2.0000000000000000, 2.2500000000000000},
		{1.2764661478191643, 2.0000000000000000, 2.5000000000000000},
		{1.7010693700601991, 2.0000000000000000, 2.7500000000000000},
		{2.2452124409299512, 2.0000000000000000, 3.0000000000000000},
		{2.9416152804573357, 2.0000000000000000, 3.2500000000000000},
		{3.8320120480778415, 2.0000000000000000, 3.5000000000000000},
		{4.9696044049382113, 2.0000000000000000, 3.7500000000000000},
		{6.4221893752841055, 2.0000000000000000, 4.0000000000000000},
		{8.2761461924550552, 2.0000000000000000, 4.2500000000000000},
		{10.641517298393307, 2.0000000000000000, 4.5000000000000000},
		{13.658483394577813, 2.0000000000000000, 4.7500000000000000},
		{17.505614966624233, 2.0000000000000000, 5.0000000000000000},

		{0.0000000000000000, 5.0000000000000000, 0.0000000000000000},
		{2.5497616449882785e-07, 5.0000000000000000, 0.25000000000000000},
		{8.2231713131092646e-06, 5.0000000000000000, 0.50000000000000000},
		{6.3261122739811725e-05, 5.0000000000000000, 0.75000000000000000},
		{0.00027146315595697195, 5.0000000000000000, 1.0000000000000000},
		{0.00084793613616686856, 5.0000000000000000, 1.2500000000000000},
		{0.0021705595690975554, 5.0000000000000000, 1.5000000000000000},
		{0.0048504513371845385, 5.0000000000000000, 1.7500000000000000},
		{0.0098256793231317023, 5.0000000000000000, 2.0000000000000000},
		{0.018486577941045829, 5.0000000000000000, 2.2500000000000000},
		{0.032843475172023219, 5.0000000000000000, 2.5000000000000000},
		{0.055750882754221943, 5.0000000000000000, 2.7500000000000000},
		{0.091206477661513338, 5.0000000000000000, 3.0000000000000000},
		{0.14474880546308083, 5.0000000000000000, 3.2500000000000000},
		{0.22398495470190780, 5.0000000000000000, 3.5000000000000000},
		{0.33928899170999877, 5.0000000000000000, 3.7500000000000000},
		{0.50472436311316637, 5.0000000000000000, 4.0000000000000000},
		{0.73925961816682961, 5.0000000000000000, 4.2500000000000000},
		{1.0683677743764701, 5.0000000000000000, 4.5000000000000000},
		{1.5261268693599621, 5.0000000000000000, 4.7500000000000000},
		{2.1579745473225476, 5.0000000000000000, 5.0000000000000000},

		{0.0000000000000000, 10.000000000000000, 0.0000000000000000},
		{2.5701232848571186e-16, 10.000000000000000, 0.25000000000000000},
		{2.6430419258812784e-13, 10.000000000000000, 0.50000000000000000},
		{1.5349659676120412e-11, 10.000000000000000, 0.75000000000000000},
		{2.7529480398368732e-10, 10.000000000000000, 1.0000000000000000},
		{2.5967897782035928e-09, 10.000000000000000, 1.2500000000000000},
		{1.6330924437799743e-08, 10.000000000000000, 1.5000000000000000},
		{7.7706676834614079e-08, 10.000000000000000, 1.7500000000000000},
		{3.0169638793506839e-07, 10.000000000000000, 2.0000000000000000},
		{1.0034459057774481e-06, 10.000000000000000, 2.2500000000000000},
		{2.9557436109680578e-06, 10.000000000000000, 2.5000000000000000},
		{7.8955603774082724e-06, 10.000000000000000, 2.7500000000000000},
		{1.9464393470612970e-05, 10.000000000000000, 3.0000000000000000},
		{4.4875369479742435e-05, 10.000000000000000, 3.2500000000000000},
		{9.7760848514528916e-05, 10.000000000000000, 3.5000000000000000},
		{0.00020289011210063496, 10.000000000000000, 3.7500000000000000},
		{0.00040378896132693058, 10.000000000000000, 4.0000000000000000},
		{0.00077478519551669892, 10.000000000000000, 4.2500000000000000},
		{0.0014397060684919682, 10.000000000000000, 4.5000000000000000},
		{0.0026004486016189452, 10.000000000000000, 4.7500000000000000},
		{0.0045800444191760525, 10.000000000000000, 5.0000000000000000},

		{0.0000000000000000, 20.000000000000000, 0.0000000000000000},
		{3.5677858077910353e-37, 20.000000000000000, 0.25000000000000000},
		{3.7494538480790194e-31, 20.000000000000000, 0.50000000000000000},
		{1.2514356342425337e-27, 20.000000000000000, 0.75000000000000000},
		{3.9668359858190197e-25, 20.000000000000000, 1.0000000000000000},
		{3.4637832909868234e-23, 20.000000000000000, 1.2500000000000000},
		{1.3388331839683472e-21, 20.000000000000000, 1.5000000000000000},
		{2.9502376732679751e-20, 20.000000000000000, 1.7500000000000000},
		{4.3105605761095479e-19, 20.000000000000000, 2.0000000000000000},
		{4.6032451406433059e-18, 20.000000000000000, 2.2500000000000000},
		{3.8400317244170310e-17, 20.000000000000000, 2.5000000000000000},
		{2.6239115263043263e-16, 20.000000000000000, 2.7500000000000000},
		{1.5209660019426689e-15, 20.000000000000000, 3.0000000000000000},
		{7.6806450728249953e-15, 20.000000000000000, 3.2500000000000000},
		{3.4495528847222945e-14, 20.000000000000000, 3.5000000000000000},
		{1.4006589294850677e-13, 20.000000000000000, 3.7500000000000000},
		{5.2100734221993054e-13, 20.000000000000000, 4.0000000000000000},
		{1.7946903269488168e-12, 20.000000000000000, 4.2500000000000000},
		{5.7763830562279699e-12, 20.000000000000000, 4.5000000000000000},
		{1.7502433074548735e-11, 20.000000000000000, 4.7500000000000000},
		{5.0242393579718066e-11, 20.000000000000000, 5.0000000000000000},

		{1.0000000000000000, 0.0000000000000000, 0.0000000000000000},
		{27.239871823604439, 0.0000000000000000, 5.0000000000000000},
		{2815.7166284662558, 0.0000000000000000, 10.000000000000000},
		{339649.37329791381, 0.0000000000000000, 15.000000000000000},
		{43558282.559553474, 0.0000000000000000, 20.000000000000000},
		{5774560606.4663124, 0.0000000000000000, 25.000000000000000},
		{781672297823.97925, 0.0000000000000000, 30.000000000000000},
		{107338818494514.42, 0.0000000000000000, 35.000000000000000},
		{14894774793419916., 0.0000000000000000, 40.000000000000000},
		{2.0834140751773164e+18, 0.0000000000000000, 45.000000000000000},
		{2.9325537838493457e+20, 0.0000000000000000, 50.000000000000000},
		{4.1487895607332160e+22, 0.0000000000000000, 55.000000000000000},
		{5.8940770556098216e+24, 0.0000000000000000, 60.000000000000000},
		{8.4030398456255582e+26, 0.0000000000000000, 65.000000000000000},
		{1.2015889579125424e+29, 0.0000000000000000, 70.000000000000000},
		{1.7226390780357976e+31, 0.0000000000000000, 75.000000000000000},
		{2.4751784043341661e+33, 0.0000000000000000, 80.000000000000000},
		{3.5634776304081403e+35, 0.0000000000000000, 85.000000000000000},
		{5.1392383455086475e+37, 0.0000000000000000, 90.000000000000000},
		{7.4233258618752072e+39, 0.0000000000000000, 95.000000000000000},
		{1.0737517071310986e+42, 0.0000000000000000, 100.00000000000000},

		{0.0000000000000000, 0.33333333333333331, 0.0000000000000000},
		{26.897553069268362, 0.33333333333333331, 5.0000000000000000},
		{2799.2396097056790, 0.33333333333333331, 10.000000000000000},
		{338348.63146593666, 0.33333333333333331, 15.000000000000000},
		{43434263.927938424, 0.33333333333333331, 20.000000000000000},
		{5761474759.6213636, 0.33333333333333331, 25.000000000000000},
		{780201111830.30237, 0.33333333333333331, 30.000000000000000},
		{107166066959051.91, 0.33333333333333331, 35.000000000000000},
		{14873836574083762., 0.33333333333333331, 40.000000000000000},
		{2.0808143020217085e+18, 0.33333333333333331, 45.000000000000000},
		{2.9292639365644226e+20, 0.33333333333333331, 50.000000000000000},
		{4.1445621624120489e+22, 0.33333333333333331, 55.000000000000000},
		{5.8885758374365916e+24, 0.33333333333333331, 60.000000000000000},
		{8.3958047021083941e+26, 0.33333333333333331, 65.000000000000000},
		{1.2006287819446431e+29, 0.33333333333333331, 70.000000000000000},
		{1.7213548977150022e+31, 0.33333333333333331, 75.000000000000000},
		{2.4734492458444449e+33, 0.33333333333333331, 80.000000000000000},
		{3.5611354547857122e+35, 0.33333333333333331, 85.000000000000000},
		{5.1360491295551848e+37, 0.33333333333333331, 90.000000000000000},
		{7.4189629097600431e+39, 0.33333333333333331, 95.000000000000000},
		{1.0731523308358370e+42, 0.33333333333333331, 100.00000000000000},

		{0.0000000000000000, 0.50000000000000000, 0.0000000000000000},
		{26.477547497559065, 0.50000000000000000, 5.0000000000000000},
		{2778.7846038745711, 0.50000000000000000, 10.000000000000000},
		{336729.88718706399, 0.50000000000000000, 15.000000000000000},
		{43279746.272428922, 0.50000000000000000, 20.000000000000000},
		{5745159748.3464680, 0.50000000000000000, 25.000000000000000},
		{778366068840.44580, 0.50000000000000000, 30.000000000000000},
		{106950522408567.66, 0.50000000000000000, 35.000000000000000},
		{14847705549021960., 0.50000000000000000, 40.000000000000000},
		{2.0775691824625661e+18, 0.50000000000000000, 45.000000000000000},
		{2.9251568529912984e+20, 0.50000000000000000, 50.000000000000000},
		{4.1392840094781220e+22, 0.50000000000000000, 55.000000000000000},
		{5.8817065760751945e+24, 0.50000000000000000, 60.000000000000000},
		{8.3867695787277245e+26, 0.50000000000000000, 65.000000000000000},
		{1.1994296461653203e+29, 0.50000000000000000, 70.000000000000000},
		{1.7197510246063334e+31, 0.50000000000000000, 75.000000000000000},
		{2.4712895036230794e+33, 0.50000000000000000, 80.000000000000000},
		{3.5582099086757769e+35, 0.50000000000000000, 85.000000000000000},
		{5.1320654031231128e+37, 0.50000000000000000, 90.000000000000000},
		{7.4135128383495239e+39, 0.50000000000000000, 95.000000000000000},
		{1.0724035825423179e+42, 0.50000000000000000, 100.00000000000000},

		{0.0000000000000000, 0.66666666666666663, 0.0000000000000000},
		{25.902310583215122, 0.66666666666666663, 5.0000000000000000},
		{2750.4090423459315, 0.66666666666666663, 10.000000000000000},
		{334476.98138574377, 0.66666666666666663, 15.000000000000000},
		{43064361.686912313, 0.66666666666666663, 20.000000000000000},
		{5722397441.9603882, 0.66666666666666663, 25.000000000000000},
		{775804343498.02661, 0.66666666666666663, 30.000000000000000},
		{106649495512800.88, 0.66666666666666663, 35.000000000000000},
		{14811199896983754., 0.66666666666666663, 40.000000000000000},
		{2.0730345814356961e+18, 0.66666666666666663, 45.000000000000000},
		{2.9194166755257467e+20, 0.66666666666666663, 50.000000000000000},
		{4.1319059569935374e+22, 0.66666666666666663, 55.000000000000000},
		{5.8721031476386222e+24, 0.66666666666666663, 60.000000000000000},
		{8.3741368248217830e+26, 0.66666666666666663, 65.000000000000000},
		{1.1977528777008688e+29, 0.66666666666666663, 70.000000000000000},
		{1.7175081240014333e+31, 0.66666666666666663, 75.000000000000000},
		{2.4682690458513916e+33, 0.66666666666666663, 80.000000000000000},
		{3.5541181975850724e+35, 0.66666666666666663, 85.000000000000000},
		{5.1264933963228892e+37, 0.66666666666666663, 90.000000000000000},
		{7.4058894880134064e+39, 0.66666666666666663, 95.000000000000000},
		{1.0713562154788124e+42, 0.66666666666666663, 100.00000000000000},

		{0.0000000000000000, 1.0000000000000000, 0.0000000000000000},
		{24.335642142450524, 1.0000000000000000, 5.0000000000000000},
		{2670.9883037012560, 1.0000000000000000, 10.000000000000000},
		{328124.92197020649, 1.0000000000000000, 15.000000000000000},
		{42454973.385127783, 1.0000000000000000, 20.000000000000000},
		{5657865129.8787022, 1.0000000000000000, 25.000000000000000},
		{768532038938.95667, 1.0000000000000000, 30.000000000000000},
		{105794126051896.17, 1.0000000000000000, 35.000000000000000},
		{14707396163259352., 1.0000000000000000, 40.000000000000000},
		{2.0601334620815780e+18, 1.0000000000000000, 45.000000000000000},
		{2.9030785901035638e+20, 1.0000000000000000, 50.000000000000000},
		{4.1108986452992812e+22, 1.0000000000000000, 55.000000000000000},
		{5.8447515883904527e+24, 1.0000000000000000, 60.000000000000000},
		{8.3381485471501288e+26, 1.0000000000000000, 65.000000000000000},
		{1.1929750788892366e+29, 1.0000000000000000, 70.000000000000000},
		{1.7111160152965382e+31, 1.0000000000000000, 75.000000000000000},
		{2.4596595795675343e+33, 1.0000000000000000, 80.000000000000000},
		{3.5424536064404024e+35, 1.0000000000000000, 85.000000000000000},
		{5.1106068152566129e+37, 1.0000000000000000, 90.000000000000000},
		{7.3841518091360182e+39, 1.0000000000000000, 95.000000000000000},
		{1.0683693903381569e+42, 1.0000000000000000, 100.00000000000000},

		{0.0000000000000000, 2.0000000000000000, 0.0000000000000000},
		{17.505614966624233, 2.0000000000000000, 5.0000000000000000},
		{2281.5189677260046, 2.0000000000000000, 10.000000000000000},
		{295899.38370188628, 2.0000000000000000, 15.000000000000000},
		{39312785.221040756, 2.0000000000000000, 20.000000000000000},
		{5321931396.0760155, 2.0000000000000000, 25.000000000000000},
		{730436828561.38013, 2.0000000000000000, 30.000000000000000},
		{101293439862977.19, 2.0000000000000000, 35.000000000000000},
		{14159404985256920., 2.0000000000000000, 40.000000000000000},
		{1.9918525879736883e+18, 2.0000000000000000, 45.000000000000000},
		{2.8164306402451938e+20, 2.0000000000000000, 50.000000000000000},
		{3.9993023372677540e+22, 2.0000000000000000, 55.000000000000000},
		{5.6992520026634433e+24, 2.0000000000000000, 60.000000000000000},
		{8.1464814287900364e+26, 2.0000000000000000, 65.000000000000000},
		{1.1675039556585663e+29, 2.0000000000000000, 70.000000000000000},
		{1.6770093176278926e+31, 2.0000000000000000, 75.000000000000000},
		{2.4136869148449879e+33, 2.0000000000000000, 80.000000000000000},
		{3.4801257808448186e+35, 2.0000000000000000, 85.000000000000000},
		{5.0256693051696307e+37, 2.0000000000000000, 90.000000000000000},
		{7.2678700343145818e+39, 2.0000000000000000, 95.000000000000000},
		{1.0523843193243042e+42, 2.0000000000000000, 100.00000000000000},

		{0.0000000000000000, 5.0000000000000000, 0.0000000000000000},
		{2.1579745473225476, 5.0000000000000000, 5.0000000000000000},
		{777.18828640326012, 5.0000000000000000, 10.000000000000000},
		{144572.01120063409, 5.0000000000000000, 15.000000000000000},
		{23018392.213413671, 5.0000000000000000, 20.000000000000000},
		{3472466208.7419176, 5.0000000000000000, 25.000000000000000},
		{512151465476.93494, 5.0000000000000000, 30.000000000000000},
		{74756743552251.547, 5.0000000000000000, 35.000000000000000},
		{10858318337624278., 5.0000000000000000, 40.000000000000000},
		{1.5736087399245911e+18, 5.0000000000000000, 45.000000000000000},
		{2.2785483079112825e+20, 5.0000000000000000, 50.000000000000000},
		{3.2989391052963687e+22, 5.0000000000000000, 55.000000000000000},
		{4.7777652072561732e+24, 5.0000000000000000, 60.000000000000000},
		{6.9232165147172657e+26, 5.0000000000000000, 65.000000000000000},
		{1.0038643002095155e+29, 5.0000000000000000, 70.000000000000000},
		{1.4566328222327073e+31, 5.0000000000000000, 75.000000000000000},
		{2.1151488565944835e+33, 5.0000000000000000, 80.000000000000000},
		{3.0735883450768239e+35, 5.0000000000000000, 85.000000000000000},
		{4.4694790189230327e+37, 5.0000000000000000, 90.000000000000000},
		{6.5037505570430995e+39, 5.0000000000000000, 95.000000000000000},
		{9.4700938730355882e+41, 5.0000000000000000, 100.00000000000000},

		{0.0000000000000000, 10.000000000000000, 0.0000000000000000},
		{0.0045800444191760525, 10.000000000000000, 5.0000000000000000},
		{21.891706163723381, 10.000000000000000, 10.000000000000000},
		{12267.475049806462, 10.000000000000000, 15.000000000000000},
		{3540200.2090195213, 10.000000000000000, 20.000000000000000},
		{771298871.17072666, 10.000000000000000, 25.000000000000000},
		{145831809975.96710, 10.000000000000000, 30.000000000000000},
		{25449470018534.777, 10.000000000000000, 35.000000000000000},
		{4228469210516757.0, 10.000000000000000, 40.000000000000000},
		{6.8049404557505165e+17, 10.000000000000000, 45.000000000000000},
		{1.0715971594776370e+20, 10.000000000000000, 50.000000000000000},
		{1.6618215752886714e+22, 10.000000000000000, 55.000000000000000},
		{2.5486246072566784e+24, 10.000000000000000, 60.000000000000000},
		{3.8764628702155475e+26, 10.000000000000000, 65.000000000000000},
		{5.8592538145409686e+28, 10.000000000000000, 70.000000000000000},
		{8.8135370711317444e+30, 10.000000000000000, 75.000000000000000},
		{1.3207418268325279e+33, 10.000000000000000, 80.000000000000000},
		{1.9732791360862190e+35, 10.000000000000000, 85.000000000000000},
		{2.9411893748384672e+37, 10.000000000000000, 90.000000000000000},
		{4.3754494922439984e+39, 10.000000000000000, 95.000000000000000},
		{6.4989755247201446e+41, 10.000000000000000, 100.00000000000000},

		{0.0000000000000000, 20.000000000000000, 0.0000000000000000},
		{5.0242393579718066e-11, 20.000000000000000, 5.0000000000000000},
		{0.00012507997356449481, 20.000000000000000, 10.000000000000000},
		{1.6470152535015836, 20.000000000000000, 15.000000000000000},
		{3188.7503288536154, 20.000000000000000, 20.000000000000000},
		{2449840.5422952301, 20.000000000000000, 25.000000000000000},
		{1126985104.4483771, 20.000000000000000, 30.000000000000000},
		{379617876611.88580, 20.000000000000000, 35.000000000000000},
		{104459633129479.88, 20.000000000000000, 40.000000000000000},
		{25039579987216524., 20.000000000000000, 45.000000000000000},
		{5.4420084027529984e+18, 20.000000000000000, 50.000000000000000},
		{1.1007498584335495e+21, 20.000000000000000, 55.000000000000000},
		{2.1091734863057236e+23, 20.000000000000000, 60.000000000000000},
		{3.8763618091286891e+25, 20.000000000000000, 65.000000000000000},
		{6.8946130527930870e+27, 20.000000000000000, 70.000000000000000},
		{1.1946319948836447e+30, 20.000000000000000, 75.000000000000000},
		{2.0265314377577587e+32, 20.000000000000000, 80.000000000000000},
		{3.3784665214179985e+34, 20.000000000000000, 85.000000000000000},
		{5.5516089411796646e+36, 20.000000000000000, 90.000000000000000},
		{9.0129310795305151e+38, 20.000000000000000, 95.000000000000000},
		{1.4483461256427176e+41, 20.000000000000000, 100.00000000000000},

		{0.0000000000000000, 50.000000000000000, 0.0000000000000000},
		{2.9314696468108517e-45, 50.000000000000000, 5.0000000000000000},
		{4.7568945607268435e-30, 50.000000000000000, 10.000000000000000},
		{5.5468372730667069e-21, 50.000000000000000, 15.000000000000000},
		{2.2551205757604056e-14, 50.000000000000000, 20.000000000000000},
		{4.5344251866130257e-09, 50.000000000000000, 25.000000000000000},
		{0.00014590106916468940, 50.000000000000000, 30.000000000000000},
		{1.3965549457254882, 50.000000000000000, 35.000000000000000},
		{5726.8656631289887, 50.000000000000000, 40.000000000000000},
		{12672593.113027781, 50.000000000000000, 45.000000000000000},
		{17650802430.016712, 50.000000000000000, 50.000000000000000},
		{17220231607789.926, 50.000000000000000, 55.000000000000000},
		{12704607933652176., 50.000000000000000, 60.000000000000000},
		{7.4989491942193715e+18, 50.000000000000000, 65.000000000000000},
		{3.6944034898904922e+21, 50.000000000000000, 70.000000000000000},
		{1.5691634774370186e+24, 50.000000000000000, 75.000000000000000},
		{5.8927749458163587e+26, 50.000000000000000, 80.000000000000000},
		{1.9958849054749339e+29, 50.000000000000000, 85.000000000000000},
		{6.1946050361781500e+31, 50.000000000000000, 90.000000000000000},
		{1.7845429728697119e+34, 50.000000000000000, 95.000000000000000},
		{4.8219580855940819e+36, 50.000000000000000, 100.00000000000000},

		{0.0000000000000000, 100.00000000000000, 0.0000000000000000},
		{7.0935514885313123e-119, 100.00000000000000, 5.0000000000000000},
		{1.0823442017492015e-88, 100.00000000000000, 10.000000000000000},
		{5.9887888536468904e-71, 100.00000000000000, 15.000000000000000},
		{2.8703193216428771e-58, 100.00000000000000, 20.000000000000000},
		{2.4426896913122370e-48, 100.00000000000000, 25.000000000000000},
		{3.9476420053334271e-40, 100.00000000000000, 30.000000000000000},
		{4.2836596180818780e-33, 100.00000000000000, 35.000000000000000},
		{6.6249380222596129e-27, 100.00000000000000, 40.000000000000000},
		{2.3702587262788900e-21, 100.00000000000000, 45.000000000000000},
		{2.7278879470966917e-16, 100.00000000000000, 50.000000000000000},
		{1.2763258878228082e-11, 100.00000000000000, 55.000000000000000},
		{2.8832770906491972e-07, 100.00000000000000, 60.000000000000000},
		{0.0035805902717061223, 100.00000000000000, 65.000000000000000},
		{27.017219102595387, 100.00000000000000, 70.000000000000000},
		{134001.44891209516, 100.00000000000000, 75.000000000000000},
		{465194832.85060996, 100.00000000000000, 80.000000000000000},
		{1189280653119.4814, 100.00000000000000, 85.000000000000000},
		{2334119331258728.0, 100.00000000000000, 90.000000000000000},
		{3.6399223078502436e+18, 100.00000000000000, 95.000000000000000},
		{4.6415349416162005e+21, 100.00000000000000, 100.00000000000000},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::cyl_bessel_i(data.nu, data.x);

		if (data.expected > max)
		{
			EXPECT_EQ(+inf, r);
		}
		else if (data.expected < lowest)
		{
			EXPECT_EQ(-inf, r);
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

GTEST_TEST(CMathTest, CylBesselITest)
{
	CylBesselITestFloat<float,       float>      (0.000001);
	CylBesselITestFloat<float,       double>     (0.000001);
	CylBesselITestFloat<float,       long double>(0.000001);
	CylBesselITestFloat<double,      float>      (0.000001);
	CylBesselITestFloat<double,      double>     (0.000000000001);
	CylBesselITestFloat<double,      long double>(0.000000000001);
	CylBesselITestFloat<long double, float>      (0.000001);
	CylBesselITestFloat<long double, double>     (0.000000000001);
	CylBesselITestFloat<long double, long double>(0.000000000001);

	BKSGE_CONSTEXPR auto nanf = std::numeric_limits<float>::quiet_NaN();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_bessel_if(nanf, nanf)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_bessel_if(nanf, 0.0f)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_bessel_if(0.0f, nanf)));

	BKSGE_CONSTEXPR auto nanl = std::numeric_limits<long double>::quiet_NaN();
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_bessel_il(nanl, nanl)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_bessel_il(nanl, 0.0l)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::cyl_bessel_il(0.0l, nanl)));
}

}	// namespace cyl_bessel_i_test

}	// namespace bksge_cmath_test

BKSGE_WARNING_POP();
