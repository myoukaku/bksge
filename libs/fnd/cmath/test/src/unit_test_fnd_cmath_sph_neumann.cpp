﻿/**
 *	@file	unit_test_fnd_cmath_sph_neumann.cpp
 *
 *	@brief	sph_neumann のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/sph_neumann.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4305);	// 'initializing': truncation from 'double' to 'T1'

namespace bksge_cmath_test
{

namespace sph_neumann_test
{

static_assert(bksge::is_same<float,       decltype(bksge::sph_neumann(0u, 0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::sph_neumann(0u, 0.0))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::sph_neumann(0u, 0.0l))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::sph_neumann(0u, 0))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::sph_neumannf(0u, 0.0f))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::sph_neumannl(0u, 0.0l))>::value, "");

template <typename T>
void SphNeumannTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = std::numeric_limits<T>::min();

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sph_neumann(0u, nan)));

	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::sph_neumann(0u, T(0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-inf, bksge::sph_neumann(1u, T(0)));

	struct testcase
	{
		double expected;
		unsigned int n;
		T x;
	};

	testcase const testcases[] =
	{
		{-3.8756496868425789, 0, 0.25000000000000000},
		{-1.7551651237807455, 0, 0.50000000000000000},
		{-0.97558515849842786, 0, 0.75000000000000000},
		{-0.54030230586813977, 0, 1.0000000000000000},
		{-0.25225788991621495, 0, 1.2500000000000000},
		{-0.047158134445135273, 0, 1.5000000000000000},
		{ 0.10185488894256690, 0, 1.7500000000000000},
		{ 0.20807341827357120, 0, 2.0000000000000000},
		{ 0.27918827676566177, 0, 2.2500000000000000},
		{ 0.32045744621877348, 0, 2.5000000000000000},
		{ 0.33610995586635040, 0, 2.7500000000000000},
		{ 0.32999749886681512, 0, 3.0000000000000000},
		{ 0.30588605417862963, 0, 3.2500000000000000},
		{ 0.26755905351165610, 0, 3.5000000000000000},
		{ 0.21881582862388288, 0, 3.7500000000000000},
		{ 0.16341090521590299, 0, 4.0000000000000000},
		{ 0.10496176233265714, 0, 4.2500000000000000},
		{ 0.046843510984617719, 0, 4.5000000000000000},
		{-0.0079162427132582220, 0, 4.7500000000000000},
		{-0.056732437092645263, 0, 5.0000000000000000},

		{-16.492214584388407, 1, 0.25000000000000000},
		{-4.4691813247698970, 1, 0.50000000000000000},
		{-2.2096318913623492, 1, 0.75000000000000000},
		{-1.3817732906760363, 1, 1.0000000000000000},
		{-0.96099400741744090, 1, 1.2500000000000000},
		{-0.69643541403279308, 1, 1.5000000000000000},
		{-0.50407489024649721, 1, 1.7500000000000000},
		{-0.35061200427605527, 1, 2.0000000000000000},
		{-0.22172663116544869, 1, 2.2500000000000000},
		{-0.11120587915407318, 1, 2.5000000000000000},
		{-0.016564013158538646, 1, 2.7500000000000000},
		{ 0.062959163602315973, 1, 3.0000000000000000},
		{ 0.12740959652576553, 1, 3.2500000000000000},
		{ 0.17666922320036457, 1, 3.5000000000000000},
		{ 0.21076723929766045, 1, 3.7500000000000000},
		{ 0.23005335013095779, 1, 4.0000000000000000},
		{ 0.23528261660264485, 1, 4.2500000000000000},
		{ 0.22763858414438104, 1, 4.5000000000000000},
		{ 0.20871085184465679, 1, 4.7500000000000000},
		{ 0.18043836751409864, 1, 5.0000000000000000},

		{-194.03092532581832, 2, 0.25000000000000000},
		{-25.059922824838637, 2, 0.50000000000000000},
		{-7.8629424069509692, 2, 0.75000000000000000},
		{-3.6050175661599688, 2, 1.0000000000000000},
		{-2.0541277278856431, 2, 1.2500000000000000},
		{-1.3457126936204509, 2, 1.5000000000000000},
		{-0.96598327222227631, 2, 1.7500000000000000},
		{-0.73399142468765399, 2, 2.0000000000000000},
		{-0.57482378498626008, 2, 2.2500000000000000},
		{-0.45390450120366133, 2, 2.5000000000000000},
		{-0.35417978840293796, 2, 2.7500000000000000},
		{-0.26703833526449916, 2, 3.0000000000000000},
		{-0.18827719584715374, 2, 3.2500000000000000},
		{-0.11612829076848646, 2, 3.5000000000000000},
		{-0.050202037185754500, 2, 3.7500000000000000},
		{ 0.0091291073823153435, 2, 4.0000000000000000},
		{ 0.061120084680974532, 2, 4.2500000000000000},
		{ 0.10491554511163632, 2, 4.5000000000000000},
		{ 0.13973362282567303, 2, 4.7500000000000000},
		{ 0.16499545760110443, 2, 5.0000000000000000},

		{-3884190.0626637731, 5, 0.25000000000000000},
		{-61327.563166980639, 5, 0.50000000000000000},
		{-5478.9529323190836, 5, 0.75000000000000000},
		{-999.44034339223640, 5, 1.0000000000000000},
		{-270.49720502942358, 5, 1.2500000000000000},
		{-94.236110085232468, 5, 1.5000000000000000},
		{-39.182827786584333, 5, 1.7500000000000000},
		{-18.591445311190984, 5, 2.0000000000000000},
		{-9.7821420203182274, 5, 2.2500000000000000},
		{-5.5991001548063233, 5, 2.5000000000000000},
		{-3.4400655233636823, 5, 2.7500000000000000},
		{-2.2470233284653904, 5, 3.0000000000000000},
		{-1.5491439945779160, 5, 3.2500000000000000},
		{-1.1205896325654248, 5, 3.5000000000000000},
		{-0.84592255605194844, 5, 3.7500000000000000},
		{-0.66280126645045878, 5, 4.0000000000000000},
		{-0.53589374436038528, 5, 4.2500000000000000},
		{-0.44430324229090551, 5, 4.5000000000000000},
		{-0.37520157232899892, 5, 4.7500000000000000},
		{-0.32046504674973919, 5, 5.0000000000000000},

		{-2750653598174213.5, 10, 0.25000000000000000},
		{-1349739281107.0554, 10, 0.50000000000000000},
		{-15733380424.953760, 10, 0.75000000000000000},
		{-672215008.25620842, 10, 1.0000000000000000},
		{-58607405.988679446, 10, 1.2500000000000000},
		{-8032728.8148234813, 10, 1.5000000000000000},
		{-1505955.5720640516, 10, 1.7500000000000000},
		{-355414.72008543846, 10, 2.0000000000000000},
		{-100086.80374425423, 10, 2.2500000000000000},
		{-32423.794085334419, 10, 2.5000000000000000},
		{-11772.863161809979, 10, 2.7500000000000000},
		{-4699.8591888113924, 10, 3.0000000000000000},
		{-2033.0183273853759, 10, 3.2500000000000000},
		{-942.19075028425493, 10, 3.5000000000000000},
		{-463.65206971202474, 10, 3.7500000000000000},
		{-240.53552987988931, 10, 4.0000000000000000},
		{-130.78478404631085, 10, 4.2500000000000000},
		{-74.170665501737531, 10, 4.5000000000000000},
		{-43.698249898184983, 10, 4.7500000000000000},
		{-26.656114405718711, 10, 5.0000000000000000},

		{-1.4077591402542251e+36, 20, 0.25000000000000000},
		{-6.7288761838234712e+29, 20, 0.50000000000000000},
		{-1.3544611382105945e+26, 20, 0.75000000000000000},
		{-3.2395922185789833e+23, 20, 1.0000000000000000},
		{-3.0096416715953060e+21, 20, 1.2500000000000000},
		{-6.5999646851668173e+19, 20, 1.5000000000000000},
		{-2.6193364753070735e+18, 20, 1.7500000000000000},
		{-1.6054364928152224e+17, 20, 2.0000000000000000},
		{-13719071872797762., 20, 2.2500000000000000},
		{-1524247248298953.8, 20, 2.5000000000000000},
		{-209484650509384.06, 20, 2.7500000000000000},
		{-34327545666696.488, 20, 3.0000000000000000},
		{-6522260876203.3174, 20, 3.2500000000000000},
		{-1406018871897.2307, 20, 3.5000000000000000},
		{-338025193731.78882, 20, 3.7500000000000000},
		{-89381690326.018677, 20, 4.0000000000000000},
		{-25701805899.474934, 20, 4.2500000000000000},
		{-7961859734.2407761, 20, 4.5000000000000000},
		{-2636237230.0850010, 20, 4.7500000000000000},
		{-926795140.30575466, 20, 5.0000000000000000},

		{-1.3823742808004061e+109, 50, 0.25000000000000000},
		{-6.1447912922121694e+93, 50, 0.50000000000000000},
		{-6.4348494908900529e+84, 50, 0.75000000000000000},
		{-2.7391922846297569e+78, 50, 1.0000000000000000},
		{-3.1365037573299931e+73, 50, 1.2500000000000000},
		{-2.8821098528635756e+69, 50, 1.5000000000000000},
		{-1.1148255024189452e+66, 50, 1.7500000000000000},
		{-1.2350219443670970e+63, 50, 2.0000000000000000},
		{-3.0565226939717125e+60, 50, 2.2500000000000000},
		{-1.4262702131152733e+58, 50, 2.5000000000000000},
		{-1.1118745474840939e+56, 50, 2.7500000000000000},
		{-1.3243260716629503e+54, 50, 3.0000000000000000},
		{-2.2519472094129329e+52, 50, 3.2500000000000000},
		{-5.1861507201103288e+50, 50, 3.5000000000000000},
		{-1.5513212909462263e+49, 50, 3.7500000000000000},
		{-5.8276471407900649e+47, 50, 4.0000000000000000},
		{-2.6745414086543416e+46, 50, 4.2500000000000000},
		{-1.4657308996352946e+45, 50, 4.5000000000000000},
		{-9.4102674366690647e+43, 50, 4.7500000000000000},
		{-6.9641091882701322e+42, 50, 5.0000000000000000},

		{-4.2856109460516407e+247, 100, 0.25000000000000000},
		{-1.6911720011753781e+217, 100, 0.50000000000000000},
		{-2.7753107402139484e+199, 100, 0.75000000000000000},
		{-6.6830794632586774e+186, 100, 1.0000000000000000},
		{-1.0906342369729277e+177, 100, 1.2500000000000000},
		{-1.0993184254131119e+169, 100, 1.5000000000000000},
		{-1.9071480498141315e+162, 100, 1.7500000000000000},
		{-2.6559558301924957e+156, 100, 2.0000000000000000},
		{-1.8154136926485787e+151, 100, 2.2500000000000000},
		{-4.3527631662111383e+146, 100, 2.5000000000000000},
		{-2.8809537014100589e+142, 100, 2.7500000000000000},
		{-4.4102229953025611e+138, 100, 3.0000000000000000},
		{-1.3651904154044740e+135, 100, 3.2500000000000000},
		{-7.6980749101063267e+131, 100, 3.5000000000000000},
		{-7.2790553499246662e+128, 100, 3.7500000000000000},
		{-1.0796647795891517e+126, 100, 4.0000000000000000},
		{-2.3785795774441247e+123, 100, 4.2500000000000000},
		{-7.4391596631947432e+120, 100, 4.5000000000000000},
		{-3.1802258278275794e+118, 100, 4.7500000000000000},
		{-1.7997139826255660e+116, 100, 5.0000000000000000},

		{-0.056732437092645263, 0, 5.0000000000000000},
		{ 0.083907152907645249, 0, 10.000000000000000},
		{ 0.050645860857254747, 0, 15.000000000000000},
		{-0.020404103090669597, 0, 20.000000000000000},
		{-0.039648112474538942, 0, 25.000000000000000},
		{-0.0051417149962528020, 0, 30.000000000000000},
		{ 0.025819777288328762, 0, 35.000000000000000},
		{ 0.016673451541306544, 0, 40.000000000000000},
		{-0.011673821973727327, 0, 45.000000000000000},
		{-0.019299320569842265, 0, 50.000000000000000},
		{-0.00040230465930828606, 0, 55.000000000000000},
		{ 0.015873549673585938, 0, 60.000000000000000},
		{ 0.0086531361728949541, 0, 65.000000000000000},
		{-0.0090474171869471404, 0, 70.000000000000000},
		{-0.012290016929663325, 0, 75.000000000000000},
		{ 0.0013798405479880944, 0, 80.000000000000000},
		{ 0.011580901686988727, 0, 85.000000000000000},
		{ 0.0049785957347685574, 0, 90.000000000000000},
		{-0.0076860374841559963, 0, 95.000000000000000},
		{-0.0086231887228768404, 0, 100.00000000000000},

		{ 0.18043836751409864, 1, 5.0000000000000000},
		{ 0.062792826379701502, 1, 10.000000000000000},
		{-0.039976131953324147, 1, 15.000000000000000},
		{-0.046667467690914864, 1, 20.000000000000000},
		{ 0.0037081455049293634, 1, 25.000000000000000},
		{ 0.032762996969886965, 1, 30.000000000000000},
		{ 0.012971498479556563, 1, 35.000000000000000},
		{-0.018210992723451058, 1, 40.000000000000000},
		{-0.019168385477952129, 1, 45.000000000000000},
		{ 0.0048615106626817301, 1, 50.000000000000000},
		{ 0.018170052158169303, 1, 55.000000000000000},
		{ 0.0053447361795967109, 1, 60.000000000000000},
		{-0.012587316051033977, 1, 65.000000000000000},
		{-0.011184829982069090, 1, 70.000000000000000},
		{ 0.0050065549130635621, 1, 75.000000000000000},
		{ 0.012440856180892041, 1, 80.000000000000000},
		{ 0.0022077237839479508, 1, 85.000000000000000},
		{-0.0098779785318421041, 1, 90.000000000000000},
		{-0.0072731342338976518, 1, 95.000000000000000},
		{ 0.0049774245238688201, 1, 100.00000000000000},

		{ 0.16499545760110443, 2, 5.0000000000000000},
		{-0.065069304993734783, 2, 10.000000000000000},
		{-0.058641087247919575, 2, 15.000000000000000},
		{ 0.013403982937032370, 2, 20.000000000000000},
		{ 0.040093089935130458, 2, 25.000000000000000},
		{ 0.0084180146932414986, 2, 30.000000000000000},
		{-0.024707934561509628, 2, 35.000000000000000},
		{-0.018039275995565374, 2, 40.000000000000000},
		{ 0.010395929608530518, 2, 45.000000000000000},
		{ 0.019591011209603170, 2, 50.000000000000000},
		{ 0.0013933984133902479, 2, 55.000000000000000},
		{-0.015606312864606101, 2, 60.000000000000000},
		{-0.0092340892214042153, 2, 65.000000000000000},
		{ 0.0085680673305727519, 2, 70.000000000000000},
		{ 0.012490279126185866, 2, 75.000000000000000},
		{-0.00091330844120464274, 2, 80.000000000000000},
		{-0.011502982024025860, 2, 85.000000000000000},
		{-0.0053078616858299611, 2, 90.000000000000000},
		{ 0.0074563595609802797, 2, 95.000000000000000},
		{ 0.0087725114585929052, 2, 100.00000000000000},

		{-0.32046504674973919, 5, 5.0000000000000000},
		{ 0.093833541678691818, 5, 10.000000000000000},
		{ 0.020475698281859061, 5, 15.000000000000000},
		{-0.048172347757372780, 5, 20.000000000000000},
		{-0.018309489232548347, 5, 25.000000000000000},
		{ 0.026639390496569996, 5, 30.000000000000000},
		{ 0.022006038985576210, 5, 35.000000000000000},
		{-0.011268975348057965, 5, 40.000000000000000},
		{-0.021770388372274858, 5, 45.000000000000000},
		{-0.00069711319645853701, 5, 50.000000000000000},
		{ 0.017439589450220901, 5, 55.000000000000000},
		{ 0.0088699170919343089, 5, 60.000000000000000},
		{-0.010421334444951861, 5, 65.000000000000000},
		{-0.012746769858008553, 5, 70.000000000000000},
		{ 0.0026282888028967737, 5, 75.000000000000000},
		{ 0.012477658581324189, 5, 80.000000000000000},
		{ 0.0040771816818182642, 5, 85.000000000000000},
		{-0.0089777759570579818, 5, 90.000000000000000},
		{-0.0083184557896676149, 5, 95.000000000000000},
		{ 0.0037206784862748965, 5, 100.00000000000000},

		{-26.656114405718711, 10, 5.0000000000000000},
		{-0.17245367208805784, 10, 10.000000000000000},
		{ 0.078461689849642580, 10, 15.000000000000000},
		{-0.036843410496289961, 10, 20.000000000000000},
		{-0.021158339301097475, 10, 25.000000000000000},
		{ 0.031219591064754939, 10, 30.000000000000000},
		{ 0.012840593422414807, 10, 35.000000000000000},
		{-0.021803068636888072, 10, 40.000000000000000},
		{-0.014071636804469044, 10, 45.000000000000000},
		{ 0.013524687511158758, 10, 50.000000000000000},
		{ 0.015684932653180595, 10, 55.000000000000000},
		{-0.0056356895567262122, 10, 60.000000000000000},
		{-0.015364490270315362, 10, 65.000000000000000},
		{-0.0014525575672261295, 10, 70.000000000000000},
		{ 0.012648951699549433, 10, 75.000000000000000},
		{ 0.0068571608061120367, 10, 80.000000000000000},
		{-0.0080151152941401460, 10, 85.000000000000000},
		{-0.0098139742219019149, 10, 90.000000000000000},
		{ 0.0025002854072314951, 10, 95.000000000000000},
		{ 0.010025777373636155, 10, 100.00000000000000},

		{-926795140.30575466, 20, 5.0000000000000000},
		{-1211.2106053526036, 20, 10.000000000000000},
		{-1.5559965765652175, 20, 15.000000000000000},
		{-0.093401132250914398, 20, 20.000000000000000},
		{ 0.044031985675276462, 20, 25.000000000000000},
		{-0.036078033606613907, 20, 30.000000000000000},
		{ 0.029828405631319645, 20, 35.000000000000000},
		{-0.0048414810986760759, 20, 40.000000000000000},
		{-0.020504694681516944, 20, 45.000000000000000},
		{ 0.013759531302541216, 20, 50.000000000000000},
		{ 0.012783038861734196, 20, 55.000000000000000},
		{-0.013117009421906418, 20, 60.000000000000000},
		{-0.010338106075674407, 20, 65.000000000000000},
		{ 0.010538610814111244, 20, 70.000000000000000},
		{ 0.010200029094273744, 20, 75.000000000000000},
		{-0.0073123450945617122, 20, 80.000000000000000},
		{-0.010581510354950906, 20, 85.000000000000000},
		{ 0.0036866374015298723, 20, 90.000000000000000},
		{ 0.010498384318338270, 20, 95.000000000000000},
		{ 5.6317293788334978e-05, 20, 100.00000000000000},

		{-6.9641091882701322e+42, 50, 5.0000000000000000},
		{-4.5282272723513309e+27, 50, 10.000000000000000},
		{-9.0004902645887672e+18, 50, 15.000000000000000},
		{-9542541667002.5762, 50, 20.000000000000000},
		{-363518140.71027178, 50, 25.000000000000000},
		{-152551.57233157742, 50, 30.000000000000000},
		{-386.26599186208688, 50, 35.000000000000000},
		{-4.3290507947291097, 50, 40.000000000000000},
		{-0.19968460851503717, 50, 45.000000000000000},
		{-0.041900001504607758, 50, 50.000000000000000},
		{ 0.010696040672421926, 50, 55.000000000000000},
		{ 0.0078198768555268281, 50, 60.000000000000000},
		{-0.010088474938191183, 50, 65.000000000000000},
		{ 0.0062423671279823656, 50, 70.000000000000000},
		{ 0.0011284242794942282, 50, 75.000000000000000},
		{-0.0093934266037486308, 50, 80.000000000000000},
		{ 0.013108079602843421, 50, 85.000000000000000},
		{-0.0075396607225721932, 50, 90.000000000000000},
		{-0.0042605703552837304, 50, 95.000000000000000},
		{ 0.010747822973682467, 50, 100.00000000000000},

		{-1.7997139826255660e+116, 100, 5.0000000000000000},
		{-8.5732263093288939e+85, 100, 10.000000000000000},
		{-1.9270658593710037e+68, 100, 15.000000000000000},
		{-7.2208893582950327e+55, 100, 20.000000000000000},
		{-2.0868752613007361e+46, 100, 25.000000000000000},
		{-4.2496124023610848e+38, 100, 30.000000000000000},
		{-1.7042898348910030e+32, 100, 35.000000000000000},
		{-6.3021565260722767e+26, 100, 40.000000000000000},
		{-1.3199917400493998e+22, 100, 45.000000000000000},
		{-1.1256928913265911e+18, 100, 50.000000000000000},
		{-309801083340345.56, 100, 55.000000000000000},
		{-232585620046.64404, 100, 60.000000000000000},
		{-421135935.93755186, 100, 65.000000000000000},
		{-1680637.4531202628, 100, 70.000000000000000},
		{-13868.302591128748, 100, 75.000000000000000},
		{-227.24385709173205, 100, 80.000000000000000},
		{-7.2807038787138563, 100, 85.000000000000000},
		{-0.46648154448250850, 100, 90.000000000000000},
		{-0.067270772720654515, 100, 95.000000000000000},
		{-0.022983850491562270, 100, 100.00000000000000},
	};

	for (auto data : testcases)
	{
		auto const r = bksge::sph_neumann(data.n, data.x);

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

GTEST_TEST(CMathTest, SphNeumannTest)
{
	SphNeumannTestFloat<float>      (0.0000001);
	SphNeumannTestFloat<double>     (0.0000000001);
	SphNeumannTestFloat<long double>(0.0000000001);

	BKSGE_CONSTEXPR auto nanf = std::numeric_limits<float>::quiet_NaN();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sph_neumannf(0u, nanf)));

	BKSGE_CONSTEXPR auto nanl = std::numeric_limits<long double>::quiet_NaN();
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::sph_neumannl(0u, nanl)));
}

}	// namespace sph_neumann_test

}	// namespace bksge_cmath_test

BKSGE_WARNING_POP();
