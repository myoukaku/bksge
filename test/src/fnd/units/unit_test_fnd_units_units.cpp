/**
 *	@file	unit_test_fnd_units_units.cpp
 *
 *	@brief	units のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/units.hpp>
#include <bksge/fnd/cmath/constants.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace units_units_test
{

template <typename T>
class UnitsTest : public ::testing::Test {};

using UnitsTestTypes = ::testing::Types<float, double, long double>;

TYPED_TEST_SUITE(UnitsTest, UnitsTestTypes);

TYPED_TEST(UnitsTest, AbsorbedDoseTest)
{
	using joules    = bksge::units::joules<TypeParam>;
	using kilograms = bksge::units::kilograms<TypeParam>;
	using grays     = bksge::units::grays<TypeParam>;
	using metres    = bksge::units::metres<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;

	{
		// J/kg
		BKSGE_CONSTEXPR_OR_CONST auto Gy = joules(20) / kilograms(2);
		static_assert(bksge::is_same<decltype(Gy), const grays>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, Gy.value());
	}
	{
		// m^2・s^-2
		BKSGE_CONSTEXPR_OR_CONST auto Gy = (metres(3) * metres(4)) / (seconds(2) * seconds(3));
		static_assert(bksge::is_same<decltype(Gy), const grays>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(2, Gy.value());
	}
}

TYPED_TEST(UnitsTest, AccelerationTest)
{
	using metres_per_second_squared = bksge::units::metres_per_second_squared<TypeParam>;
	using metres_per_second         = bksge::units::metres_per_second<TypeParam>;
	using seconds                   = bksge::units::seconds<TypeParam>;
	using metres                    = bksge::units::metres<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto x = metres_per_second_squared(10) * seconds(2);
		static_assert(bksge::is_same<decltype(x), const metres_per_second>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, x.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto x = metres_per_second_squared(10) * seconds(2) * seconds(3);
		static_assert(bksge::is_same<decltype(x), const metres>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(60, x.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto x = metres_per_second(10) / seconds(2);
		static_assert(bksge::is_same<decltype(x), const metres_per_second_squared>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, x.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto x = metres(60) / seconds(3) / seconds(2);
		static_assert(bksge::is_same<decltype(x), const metres_per_second_squared>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, x.value());
	}
}

TYPED_TEST(UnitsTest, ActionTest)
{
	using joule_seconds = bksge::units::joule_seconds<TypeParam>;
	using joules        = bksge::units::joules<TypeParam>;
	using seconds       = bksge::units::seconds<TypeParam>;
	using kilograms     = bksge::units::kilograms<TypeParam>;
	using metres        = bksge::units::metres<TypeParam>;

	{
		// J・s
		BKSGE_CONSTEXPR_OR_CONST auto js = joules(4) * seconds(5);
		static_assert(bksge::is_same<decltype(js), const joule_seconds>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, js.value());
	}
	{
		// kg・m^2・s^-1
		BKSGE_CONSTEXPR_OR_CONST auto js = kilograms(2) * metres(3) * metres(4) / seconds(6);
		static_assert(bksge::is_same<decltype(js), const joule_seconds>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(4, js.value());
	}
}

TYPED_TEST(UnitsTest, AmountTest)
{
	{
		BKSGE_CONSTEXPR bksge::units::moles<TypeParam>      mol(2);

		BKSGE_CONSTEXPR bksge::units::kilomoles<TypeParam>  kmol(mol);
		BKSGE_CONSTEXPR bksge::units::megamoles<TypeParam>  Mmol(mol);

		BKSGE_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000,        (double)kmol.value(), 0.0000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000 / 1000, (double)Mmol.value(), 0.00000000000001);
	}
	{
		BKSGE_CONSTEXPR bksge::units::kilomoles<TypeParam>  kmol(3);

		BKSGE_CONSTEXPR bksge::units::moles<TypeParam>      mol(kmol);
		BKSGE_CONSTEXPR bksge::units::megamoles<TypeParam>  Mmol(kmol);

		BKSGE_CONSTEXPR_EXPECT_EQ  ( 3.0 * 1000,         mol.value());
		BKSGE_CONSTEXPR_EXPECT_NEAR( 3.0 / 1000, (double)Mmol.value(), 0.0000000001);
	}
	{
		BKSGE_CONSTEXPR bksge::units::megamoles<TypeParam>  Mmol(4);

		BKSGE_CONSTEXPR bksge::units::moles<TypeParam>      mol(Mmol);
		BKSGE_CONSTEXPR bksge::units::kilomoles<TypeParam>  kmol(Mmol);

		BKSGE_CONSTEXPR_EXPECT_EQ( 4.0 * 1000 * 1000, mol.value());
		BKSGE_CONSTEXPR_EXPECT_EQ( 4.0 * 1000,        kmol.value());
	}
}

TYPED_TEST(UnitsTest, AngleTest)
{
	BKSGE_CONSTEXPR auto p = bksge::pi<double>();
	BKSGE_CONSTEXPR bksge::units::radians<TypeParam> r(1);
	BKSGE_CONSTEXPR bksge::units::degrees<TypeParam> d(2);

	BKSGE_CONSTEXPR bksge::units::radians<TypeParam> r_1(r);
	BKSGE_CONSTEXPR bksge::units::radians<TypeParam> r_2(d);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 1 * 1.0,             r_1.value());
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2 * p / 180, (double)r_2.value(), 0.000000001);

	BKSGE_CONSTEXPR bksge::units::degrees<TypeParam> d_1(r);
	BKSGE_CONSTEXPR bksge::units::degrees<TypeParam> d_2(d);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1 * 180 / p, (double)d_1.value(), 0.000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 2 * 1.0,             d_2.value());
}

TYPED_TEST(UnitsTest, AngularAccelerationTest)
{
	using radians_per_second_squared = bksge::units::radians_per_second_squared<TypeParam>;
	using radians = bksge::units::radians<TypeParam>;
	using seconds = bksge::units::seconds<TypeParam>;

	{
		// rad・s^-2
		BKSGE_CONSTEXPR_OR_CONST auto a = radians(60) / seconds(3) / seconds(4);
		static_assert(bksge::is_same<decltype(a), const radians_per_second_squared>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, AngularMomentumTest)
{
	using newton_metre_seconds = bksge::units::newton_metre_seconds<TypeParam>;
	using newtons              = bksge::units::newtons<TypeParam>;
	using metres               = bksge::units::metres<TypeParam>;
	using seconds              = bksge::units::seconds<TypeParam>;
	using kilograms            = bksge::units::kilograms<TypeParam>;

	{
		// N・m・s
		BKSGE_CONSTEXPR_OR_CONST auto a = newtons(3) * metres(4) * seconds(5);
		static_assert(bksge::is_same<decltype(a), const newton_metre_seconds>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(60, a.value());
	}
	{
		// m^2・kg・s^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(3) * metres(4) * kilograms(5) / seconds(6);
		static_assert(bksge::is_same<decltype(a), const newton_metre_seconds>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
}

TYPED_TEST(UnitsTest, AngularVelocityTest)
{
	using radians_per_second = bksge::units::radians_per_second<TypeParam>;
	using radians = bksge::units::radians<TypeParam>;
	using seconds = bksge::units::seconds<TypeParam>;

	{
		// rad・s^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = radians(60) / seconds(3);
		static_assert(bksge::is_same<decltype(a), const radians_per_second>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
}

TYPED_TEST(UnitsTest, AreaTest)
{
	using square_metres = bksge::units::square_metres<TypeParam>;
	using metres        = bksge::units::metres<TypeParam>;
	using kilometres    = bksge::units::kilometres<TypeParam>;

	{
		// m・m
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(3) * metres(4);
		static_assert(bksge::is_same<decltype(a), const square_metres>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, a.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST square_metres a = metres(5) * kilometres(6);
		BKSGE_CONSTEXPR_EXPECT_EQ(30000, a.value());
	}
}

TYPED_TEST(UnitsTest, CatalyticActivityTest)
{
	using moles   = bksge::units::moles<TypeParam>;
	using seconds = bksge::units::seconds<TypeParam>;
	using katals  = bksge::units::katals<TypeParam>;

	{
		// mol/s
		BKSGE_CONSTEXPR_OR_CONST auto kat = moles(20) / seconds(2);
		static_assert(bksge::is_same<decltype(kat), const katals>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, kat.value());
	}
}

TYPED_TEST(UnitsTest, CurrentTest)
{
	{
		BKSGE_CONSTEXPR bksge::units::amperes<TypeParam>      A(2);

		BKSGE_CONSTEXPR bksge::units::kiloamperes<TypeParam>  kA(A);
		BKSGE_CONSTEXPR bksge::units::megaamperes<TypeParam>  MA(A);

		BKSGE_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000,        (double)kA.value(), 0.0000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000 / 1000, (double)MA.value(), 0.00000000000001);
	}
	{
		BKSGE_CONSTEXPR bksge::units::kiloamperes<TypeParam>  kA(3);

		BKSGE_CONSTEXPR bksge::units::amperes<TypeParam>      A(kA);
		BKSGE_CONSTEXPR bksge::units::megaamperes<TypeParam>  MA(kA);

		BKSGE_CONSTEXPR_EXPECT_EQ  ( 3.0 * 1000,         A.value());
		BKSGE_CONSTEXPR_EXPECT_NEAR( 3.0 / 1000, (double)MA.value(), 0.0000000001);
	}
	{
		BKSGE_CONSTEXPR bksge::units::megaamperes<TypeParam>  MA(4);

		BKSGE_CONSTEXPR bksge::units::amperes<TypeParam>      A(MA);
		BKSGE_CONSTEXPR bksge::units::kiloamperes<TypeParam>  kA(MA);

		BKSGE_CONSTEXPR_EXPECT_EQ( 4.0 * 1000 * 1000, A.value());
		BKSGE_CONSTEXPR_EXPECT_EQ( 4.0 * 1000,        kA.value());
	}
}

TYPED_TEST(UnitsTest, DynamicViscosityTest)
{
	using pascal_seconds = bksge::units::pascal_seconds<TypeParam>;
	using pascals        = bksge::units::pascals<TypeParam>;
	using seconds        = bksge::units::seconds<TypeParam>;
	using kilograms      = bksge::units::kilograms<TypeParam>;
	using metres         = bksge::units::metres<TypeParam>;

	{
		// Pa・s
		BKSGE_CONSTEXPR_OR_CONST auto v = pascals(3) * seconds(4);
		static_assert(bksge::is_same<decltype(v), const pascal_seconds>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		// m^-1・kg・s^-1
		BKSGE_CONSTEXPR_OR_CONST auto v = kilograms(60) / metres(2) / seconds(3);
		static_assert(bksge::is_same<decltype(v), const pascal_seconds>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v.value());
	}
}

TYPED_TEST(UnitsTest, ElectricChargeTest)
{
	using amperes     = bksge::units::amperes<TypeParam>;
	using kiloamperes = bksge::units::kiloamperes<TypeParam>;
	using seconds     = bksge::units::seconds<TypeParam>;
	using coulomb     = bksge::units::coulomb<TypeParam>;
	using kilocoulomb = bksge::units::kilocoulomb<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = amperes(3) * seconds(4);
		static_assert(bksge::is_same<decltype(v), const coulomb>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = kiloamperes(4) * seconds(5);
		static_assert(bksge::is_same<decltype(v), const kilocoulomb>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
}

TYPED_TEST(UnitsTest, ElectricPotentialTest)
{
	using watts        = bksge::units::watts<TypeParam>;
	using kilowatts    = bksge::units::kilowatts<TypeParam>;
	using amperes      = bksge::units::amperes<TypeParam>;
	using milliamperes = bksge::units::milliamperes<TypeParam>;
	using volts        = bksge::units::volts<TypeParam>;
	using kilovolts    = bksge::units::kilovolts<TypeParam>;
	using joules       = bksge::units::joules<TypeParam>;
	using coulombs     = bksge::units::coulombs<TypeParam>;
	using metres       = bksge::units::metres<TypeParam>;
	using kilograms    = bksge::units::kilograms<TypeParam>;
	using seconds      = bksge::units::seconds<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = watts(20) / amperes(4);
		static_assert(bksge::is_same<decltype(v), const volts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = kilowatts(30) / amperes(2);
		static_assert(bksge::is_same<decltype(v), const kilovolts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(15, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = watts(40) / milliamperes(5);
		static_assert(bksge::is_same<decltype(v), const kilovolts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = joules(60) / coulombs(5);
		static_assert(bksge::is_same<decltype(v), const volts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = metres(4) * metres(5) * kilograms(6) / seconds(1) / seconds(2) / seconds(3) / amperes(4);
		static_assert(bksge::is_same<decltype(v), const volts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalCapacitanceTest)
{
	using coulombs  = bksge::units::coulombs<TypeParam>;
	using volts     = bksge::units::volts<TypeParam>;
	using farads    = bksge::units::farads<TypeParam>;
	using joules    = bksge::units::joules<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;
	using amperes   = bksge::units::amperes<TypeParam>;
	using metres    = bksge::units::metres<TypeParam>;
	using kilograms = bksge::units::kilograms<TypeParam>;

	{
		// C/V
		BKSGE_CONSTEXPR_OR_CONST auto F = coulombs(20) / volts(4);
		static_assert(bksge::is_same<decltype(F), const farads>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, F.value());
	}
	{
		// J/V^2
		BKSGE_CONSTEXPR_OR_CONST auto F = joules(60) / volts(2) / volts(3);
		static_assert(bksge::is_same<decltype(F), const farads>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, F.value());
	}
	{
		// C^2/J
		BKSGE_CONSTEXPR_OR_CONST auto F = coulombs(20) * coulombs(10) / joules(4);
		static_assert(bksge::is_same<decltype(F), const farads>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(50, F.value());
	}
	{
		// s^4 A^2 / (m^-2 kg^-1)
		BKSGE_CONSTEXPR_OR_CONST auto s  = seconds(2);
		BKSGE_CONSTEXPR_OR_CONST auto A  = amperes(3);
		BKSGE_CONSTEXPR_OR_CONST auto m  = metres(4);
		BKSGE_CONSTEXPR_OR_CONST auto kg = kilograms(3);
		BKSGE_CONSTEXPR_OR_CONST auto F  = s * s * s * s * A * A / m / m / kg;
		static_assert(bksge::is_same<decltype(F), const farads>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(3, F.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalConductanceTest)
{
	using ohms      = bksge::units::ohms<TypeParam>;
	using siemens   = bksge::units::siemens<TypeParam>;
	using amperes   = bksge::units::amperes<TypeParam>;
	using volts     = bksge::units::volts<TypeParam>;
	using coulombs  = bksge::units::coulombs<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;
	using kilograms = bksge::units::kilograms<TypeParam>;
	using metre     = bksge::units::metre<TypeParam>;

	{
		// Ω^-1
		BKSGE_CONSTEXPR_OR_CONST auto S = TypeParam(10) / ohms(2);
		static_assert(bksge::is_same<decltype(S), const siemens>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, S.value());
	}
	{
		// A V^-1
		BKSGE_CONSTEXPR_OR_CONST auto S = amperes(30) / volts(3);
		static_assert(bksge::is_same<decltype(S), const siemens>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, S.value());
	}
	{
		// C^2 s kg^-1 m^-2
		BKSGE_CONSTEXPR_OR_CONST auto C = coulombs(3);
		BKSGE_CONSTEXPR_OR_CONST auto s = seconds(6);
		BKSGE_CONSTEXPR_OR_CONST auto kg = kilograms(2);
		BKSGE_CONSTEXPR_OR_CONST auto m = metre(3);
		BKSGE_CONSTEXPR_OR_CONST auto S = C * C * s / (kg * m * m);
		static_assert(bksge::is_same<decltype(S), const siemens>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(3, S.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalConductivityTest)
{
	using siemens_per_metre = bksge::units::siemens_per_metre<TypeParam>;
	using siemens           = bksge::units::siemens<TypeParam>;
	using metres            = bksge::units::metres<TypeParam>;
	using kilograms         = bksge::units::kilograms<TypeParam>;
	using seconds           = bksge::units::seconds<TypeParam>;
	using amperes           = bksge::units::amperes<TypeParam>;
	using volts             = bksge::units::volts<TypeParam>;

	{
		// S/m
		BKSGE_CONSTEXPR_OR_CONST auto a = siemens(60) / metres(3);
		static_assert(bksge::is_same<decltype(a), const siemens_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// A・V^-1・m^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = amperes(60) / volts(4) / metres(5);
		static_assert(bksge::is_same<decltype(a), const siemens_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(3, a.value());
	}
	{
		// m^-3・kg^-1・s^3・A^2
		BKSGE_CONSTEXPR_OR_CONST auto m = metres(2);
		BKSGE_CONSTEXPR_OR_CONST auto kg = kilograms(3);
		BKSGE_CONSTEXPR_OR_CONST auto s = seconds(4);
		BKSGE_CONSTEXPR_OR_CONST auto A = amperes(6);
		BKSGE_CONSTEXPR_OR_CONST auto a = s * s * s * A * A / (m * m * m * kg);
		static_assert(bksge::is_same<decltype(a), const siemens_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(96, a.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalResistanceTest)
{
	using volts     = bksge::units::volts<TypeParam>;
	using ampere    = bksge::units::ampere<TypeParam>;
	using ohms      = bksge::units::ohms<TypeParam>;
	using watts     = bksge::units::watts<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;
	using farads    = bksge::units::farads<TypeParam>;
	using kilograms = bksge::units::kilograms<TypeParam>;
	using metre     = bksge::units::metre<TypeParam>;
	using coulombs  = bksge::units::coulombs<TypeParam>;

	{
		// V/A
		BKSGE_CONSTEXPR_OR_CONST auto O = volts(10) / ampere(2);
		static_assert(bksge::is_same<decltype(O), const ohms>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, O.value());
	}
	{
		// W/A^2
		BKSGE_CONSTEXPR_OR_CONST auto O = watts(60) / ampere(2) / ampere(3);
		static_assert(bksge::is_same<decltype(O), const ohms>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, O.value());
	}
	{
		// V^2/W
		BKSGE_CONSTEXPR_OR_CONST auto O = volts(4) * volts(5) / watts(10);
		static_assert(bksge::is_same<decltype(O), const ohms>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(2, O.value());
	}
	{
		// s/F
		BKSGE_CONSTEXPR_OR_CONST auto O = seconds(30) / farads(5);
		static_assert(bksge::is_same<decltype(O), const ohms>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(6, O.value());
	}
	{
		// kg m^2 / s C^2
		BKSGE_CONSTEXPR_OR_CONST auto kg = kilograms(6);
		BKSGE_CONSTEXPR_OR_CONST auto m = metre(4);
		BKSGE_CONSTEXPR_OR_CONST auto s = seconds(3);
		BKSGE_CONSTEXPR_OR_CONST auto C = coulombs(2);
		BKSGE_CONSTEXPR_OR_CONST auto O = (kg * m * m) / (s * C * C);
		static_assert(bksge::is_same<decltype(O), const ohms>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(8, O.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalResistivityTest)
{
	using ohm_metre = bksge::units::ohm_metre<TypeParam>;
	using ohms      = bksge::units::ohms<TypeParam>;
	using metres    = bksge::units::metres<TypeParam>;
	using kilograms = bksge::units::kilograms<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;
	using amperes   = bksge::units::amperes<TypeParam>;

	{
		// Ω・m
		BKSGE_CONSTEXPR_OR_CONST auto v = ohms(3) * metres(4);
		static_assert(bksge::is_same<decltype(v), const ohm_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		// m^3・kg・s^-3・A^-2
		BKSGE_CONSTEXPR_OR_CONST auto m = metres(4);
		BKSGE_CONSTEXPR_OR_CONST auto kg = kilograms(3);
		BKSGE_CONSTEXPR_OR_CONST auto s = seconds(2);
		BKSGE_CONSTEXPR_OR_CONST auto A = amperes(1);
		BKSGE_CONSTEXPR_OR_CONST auto v = m * m * m * kg / (s * s * s * A * A);
		static_assert(bksge::is_same<decltype(v), const ohm_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(24, v.value());
	}
}

TYPED_TEST(UnitsTest, EnergyTest)
{
	using kilograms = bksge::units::kilograms<TypeParam>;
	using metres    = bksge::units::metres<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;
	using newtons   = bksge::units::newtons<TypeParam>;
	using watts     = bksge::units::watts<TypeParam>;
	using joule     = bksge::units::joule<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = kilograms(120) * metres(1) * metres(2) / seconds(3) / seconds(4);
		static_assert(bksge::is_same<decltype(v), const joule>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = newtons(5) * metres(6);
		static_assert(bksge::is_same<decltype(v), const joule>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(30, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = watts(7) * seconds(8);
		static_assert(bksge::is_same<decltype(v), const joule>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(56, v.value());
	}
}

TYPED_TEST(UnitsTest, EnergyDensityTest)
{
	using joules_per_cubic_metre = bksge::units::joules_per_cubic_metre<TypeParam>;
	using joules                 = bksge::units::joules<TypeParam>;
	using metres                 = bksge::units::metres<TypeParam>;
	using kilograms              = bksge::units::kilograms<TypeParam>;
	using seconds                = bksge::units::seconds<TypeParam>;

	{
		// J/m^3
		BKSGE_CONSTEXPR_OR_CONST auto a = joules(60) / metres(1) / metres(2) / metres(3);
		static_assert(bksge::is_same<decltype(a), const joules_per_cubic_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// m^-1・kg・s^-2
		BKSGE_CONSTEXPR_OR_CONST auto a = kilograms(60) / (metres(2) * seconds(3) * seconds(5));
		static_assert(bksge::is_same<decltype(a), const joules_per_cubic_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(2, a.value());
	}
}

TYPED_TEST(UnitsTest, EquivalentDoseTest)
{
	using joules    = bksge::units::joules<TypeParam>;
	using kilograms = bksge::units::kilograms<TypeParam>;
	using sieverts  = bksge::units::sieverts<TypeParam>;
	using metres    = bksge::units::metres<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;

	{
		// J/kg
		BKSGE_CONSTEXPR_OR_CONST auto Sv = joules(20) / kilograms(2);
		static_assert(bksge::is_same<decltype(Sv), const sieverts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, Sv.value());
	}
	{
		// m^2・s^-2
		BKSGE_CONSTEXPR_OR_CONST auto Sv = (metres(3) * metres(4)) / (seconds(2) * seconds(3));
		static_assert(bksge::is_same<decltype(Sv), const sieverts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(2, Sv.value());
	}
}

TYPED_TEST(UnitsTest, ForceTest)
{
	using kilograms   = bksge::units::kilograms<TypeParam>;
	using grams       = bksge::units::grams<TypeParam>;
	using pounds      = bksge::units::pounds<TypeParam>;
	using metres      = bksge::units::metres<TypeParam>;
	using centimetres = bksge::units::centimetres<TypeParam>;
	using feet        = bksge::units::feet<TypeParam>;
	using seconds     = bksge::units::seconds<TypeParam>;
	using newtons     = bksge::units::newtons<TypeParam>;
	using dynes       = bksge::units::dynes<TypeParam>;
	using poundals    = bksge::units::poundals<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = kilograms(120) * metres(2) / seconds(3) / seconds(4);
		static_assert(bksge::is_same<decltype(v), const newtons>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = grams(40) * centimetres(3) / seconds(4) / seconds(5);
		static_assert(bksge::is_same<decltype(v), const dynes>::value, "");
		BKSGE_CONSTEXPR_EXPECT_NEAR(6.0, (double)v.value(), 0.000001);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = pounds(60) * feet(4) / seconds(5) / seconds(6);
		static_assert(bksge::is_same<decltype(v), const poundals>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.value());
	}
}

TYPED_TEST(UnitsTest, FrequencyTest)
{
	using T = TypeParam;
	using hertz   = bksge::units::hertz<T>;
	using seconds = bksge::units::seconds<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = T(120) / seconds(3);
		static_assert(bksge::is_same<decltype(v), const hertz>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(40, v.value());
	}
	{
		BKSGE_CONSTEXPR bksge::units::hertz<TypeParam>      Hz(1);

		BKSGE_CONSTEXPR bksge::units::kilohertz<TypeParam>  kHz(Hz);
		BKSGE_CONSTEXPR bksge::units::megahertz<TypeParam>  MHz(Hz);
		BKSGE_CONSTEXPR bksge::units::gigahertz<TypeParam>	GHz(Hz);
		BKSGE_CONSTEXPR bksge::units::terahertz<TypeParam>  THz(Hz);

		BKSGE_CONSTEXPR_EXPECT_NEAR(1.0 / 1000,          (double)kHz.value(), 0.0000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(1.0 / 1000000,       (double)MHz.value(), 0.00000000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(1.0 / 1000000000,    (double)GHz.value(), 0.0000000000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(1.0 / 1000000000000, (double)THz.value(), 0.0000000000000000001);
	}
	{
		BKSGE_CONSTEXPR bksge::units::kilohertz<TypeParam>  kHz(2);

		BKSGE_CONSTEXPR bksge::units::hertz<TypeParam>      Hz(kHz);
		BKSGE_CONSTEXPR bksge::units::megahertz<TypeParam>  MHz(kHz);
		BKSGE_CONSTEXPR bksge::units::gigahertz<TypeParam>	GHz(kHz);
		BKSGE_CONSTEXPR bksge::units::terahertz<TypeParam>  THz(kHz);

		BKSGE_CONSTEXPR_EXPECT_EQ  (2.0 * 1000,               Hz.value());
		BKSGE_CONSTEXPR_EXPECT_NEAR(2.0 / 1000,       (double)MHz.value(), 0.0000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(2.0 / 1000000,    (double)GHz.value(), 0.0000000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(2.0 / 1000000000, (double)THz.value(), 0.0000000000000001);
	}
}

TYPED_TEST(UnitsTest, HeatCapacityTest)
{
	using joules_per_kelvin = bksge::units::joules_per_kelvin<TypeParam>;
	using joules            = bksge::units::joules<TypeParam>;
	using kelvins           = bksge::units::kelvins<TypeParam>;
	using metres            = bksge::units::metres<TypeParam>;
	using kilograms         = bksge::units::kilograms<TypeParam>;
	using seconds           = bksge::units::seconds<TypeParam>;

	{
		// J/K
		BKSGE_CONSTEXPR_OR_CONST auto a = joules(60) / kelvins(3);
		static_assert(bksge::is_same<decltype(a), const joules_per_kelvin>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// m^2・kg・s^-2・K^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(3) * metres(4) * kilograms(5) / (seconds(2) * seconds(3) * kelvins(1));
		static_assert(bksge::is_same<decltype(a), const joules_per_kelvin>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
}

TYPED_TEST(UnitsTest, IlluminanceTest)
{
	using lumens = bksge::units::lumens<TypeParam>;
	using metres = bksge::units::metres<TypeParam>;
	using lux    = bksge::units::lux<TypeParam>;

	{
		// lm・m^-2
		BKSGE_CONSTEXPR_OR_CONST auto lx = lumens(60) / (metres(4) * metres(5));
		static_assert(bksge::is_same<decltype(lx), const lux>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(3, lx.value());
	}
}

TYPED_TEST(UnitsTest, InductanceTest)
{
	using volts     = bksge::units::volts<TypeParam>;
	using amperes   = bksge::units::amperes<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;
	using henries   = bksge::units::henries<TypeParam>;
	using joules    = bksge::units::joules<TypeParam>;
	using kilograms = bksge::units::kilograms<TypeParam>;
	using metres    = bksge::units::metres<TypeParam>;

	{
		// V/(A/s)
		BKSGE_CONSTEXPR_OR_CONST auto H = volts(30) / (amperes(4) / seconds(2));
		static_assert(bksge::is_same<decltype(H), const henries>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(15, H.value());
	}
	{
		// J・A^-2
		BKSGE_CONSTEXPR_OR_CONST auto H = joules(30) / (amperes(2) * amperes(3));
		static_assert(bksge::is_same<decltype(H), const henries>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, H.value());
	}
	{
		// kg・m^2・s^-2・A^-2
		BKSGE_CONSTEXPR_OR_CONST auto H = (kilograms(30) * metres(6) * metres(8)) / (seconds(2) * seconds(3) * amperes(4) * amperes(5));
		static_assert(bksge::is_same<decltype(H), const henries>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, H.value());
	}
}

TYPED_TEST(UnitsTest, InformationTest)
{
	{
		BKSGE_CONSTEXPR bksge::units::bits<TypeParam>		b(1);

		BKSGE_CONSTEXPR bksge::units::bytes<TypeParam>		B(b);
		BKSGE_CONSTEXPR bksge::units::kilobytes<TypeParam>	kB(b);
		BKSGE_CONSTEXPR bksge::units::megabytes<TypeParam>	MB(b);
		BKSGE_CONSTEXPR bksge::units::gigabytes<TypeParam>	GB(b);
		BKSGE_CONSTEXPR bksge::units::kibibytes<TypeParam>	KiB(b);
		BKSGE_CONSTEXPR bksge::units::mebibytes<TypeParam>	MiB(b);
		BKSGE_CONSTEXPR bksge::units::gibibytes<TypeParam>	GiB(b);

		BKSGE_CONSTEXPR_EXPECT_EQ  (1.0 / 8,                              B.value());
		BKSGE_CONSTEXPR_EXPECT_NEAR(1.0 / 8 / 1000,               (double)kB.value(),  0.00000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(1.0 / 8 / 1000 / 1000,        (double)MB.value(),  0.000000000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(1.0 / 8 / 1000 / 1000 / 1000, (double)GB.value(),  0.00000000000000001);
		BKSGE_CONSTEXPR_EXPECT_EQ  (1.0 / 8 / 1024,                       KiB.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (1.0 / 8 / 1024 / 1024,                MiB.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (1.0 / 8 / 1024 / 1024 / 1024,         GiB.value());
	}
	{
		BKSGE_CONSTEXPR bksge::units::bytes<TypeParam>		B(2);

		BKSGE_CONSTEXPR bksge::units::bits<TypeParam>		b(B);
		BKSGE_CONSTEXPR bksge::units::kilobytes<TypeParam>	kB(B);
		BKSGE_CONSTEXPR bksge::units::megabytes<TypeParam>	MB(B);
		BKSGE_CONSTEXPR bksge::units::gigabytes<TypeParam>	GB(B);
		BKSGE_CONSTEXPR bksge::units::kibibytes<TypeParam>	KiB(B);
		BKSGE_CONSTEXPR bksge::units::mebibytes<TypeParam>	MiB(B);
		BKSGE_CONSTEXPR bksge::units::gibibytes<TypeParam>	GiB(B);

		BKSGE_CONSTEXPR_EXPECT_EQ  (2.0 * 8,                          b.value());
		BKSGE_CONSTEXPR_EXPECT_NEAR(2.0 / 1000,               (double)kB.value(),  0.0000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(2.0 / 1000 / 1000,        (double)MB.value(),  0.00000000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(2.0 / 1000 / 1000 / 1000, (double)GB.value(),  0.0000000000000001);
		BKSGE_CONSTEXPR_EXPECT_EQ  (2.0 / 1024,                       KiB.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (2.0 / 1024 / 1024,                MiB.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (2.0 / 1024 / 1024 / 1024,         GiB.value());
	}
	{
		BKSGE_CONSTEXPR bksge::units::megabytes<TypeParam>	MB(4);

		BKSGE_CONSTEXPR bksge::units::bits<TypeParam>		b(MB);
		BKSGE_CONSTEXPR bksge::units::bytes<TypeParam>		B(MB);
		BKSGE_CONSTEXPR bksge::units::kilobytes<TypeParam>	kB(MB);
		BKSGE_CONSTEXPR bksge::units::gigabytes<TypeParam>	GB(MB);
		BKSGE_CONSTEXPR bksge::units::kibibytes<TypeParam>	KiB(MB);
		BKSGE_CONSTEXPR bksge::units::mebibytes<TypeParam>	MiB(MB);
		BKSGE_CONSTEXPR bksge::units::gibibytes<TypeParam>	GiB(MB);

		BKSGE_CONSTEXPR_EXPECT_EQ  (4.0 * 8 * 1000 * 1000,                  b.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (4.0 * 1000 * 1000,                      B.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (4.0 * 1000,                             kB.value());
		BKSGE_CONSTEXPR_EXPECT_NEAR(4.0 / 1000,                     (double)GB.value(), 0.000000001);
		BKSGE_CONSTEXPR_EXPECT_EQ  (4.0 * 1000 * 1000 / 1024,               KiB.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (4.0 * 1000 * 1000 / 1024 / 1024,        MiB.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (4.0 * 1000 * 1000 / 1024 / 1024 / 1024, GiB.value());
	}
	{
		BKSGE_CONSTEXPR bksge::units::kibibytes<TypeParam>	KiB(6);

		BKSGE_CONSTEXPR bksge::units::bits<TypeParam>		b(KiB);
		BKSGE_CONSTEXPR bksge::units::bytes<TypeParam>		B(KiB);
		BKSGE_CONSTEXPR bksge::units::kilobytes<TypeParam>	kB(KiB);
		BKSGE_CONSTEXPR bksge::units::megabytes<TypeParam>	MB(KiB);
		BKSGE_CONSTEXPR bksge::units::gigabytes<TypeParam>	GB(KiB);
		BKSGE_CONSTEXPR bksge::units::mebibytes<TypeParam>	MiB(KiB);
		BKSGE_CONSTEXPR bksge::units::gibibytes<TypeParam>	GiB(KiB);

		BKSGE_CONSTEXPR_EXPECT_EQ  (6.0 * 8 * 1024,                          b.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (6.0 * 1024,                              B.value());
		BKSGE_CONSTEXPR_EXPECT_NEAR(6.0 * 1024 / 1000,               (double)kB.value(), 0.0000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(6.0 * 1024 / 1000 / 1000,        (double)MB.value(), 0.000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(6.0 * 1024 / 1000 / 1000 / 1000, (double)GB.value(), 0.0000000000001);
		BKSGE_CONSTEXPR_EXPECT_EQ  (6.0 / 1024,                              MiB.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (6.0 / 1024 / 1024,                       GiB.value());
	}
}

TYPED_TEST(UnitsTest, KinematicViscosityTest)
{
	using square_metres_per_second = bksge::units::square_metres_per_second<TypeParam>;
	using seconds                  = bksge::units::seconds<TypeParam>;
	using metres                   = bksge::units::metres<TypeParam>;

	{
		// m^2/s
		BKSGE_CONSTEXPR_OR_CONST auto v = metres(10) * metres(6) / seconds(2);
		static_assert(bksge::is_same<decltype(v), const square_metres_per_second>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(30, v.value());
	}
}

TYPED_TEST(UnitsTest, LengthTest)
{
	BKSGE_CONSTEXPR bksge::units::millimetres<TypeParam> mm(1);
	BKSGE_CONSTEXPR bksge::units::centimetres<TypeParam> cm(2);
	BKSGE_CONSTEXPR bksge::units::metres<TypeParam>      m (3);
	BKSGE_CONSTEXPR bksge::units::kilometres<TypeParam>  km(4);
	BKSGE_CONSTEXPR bksge::units::inches<TypeParam>		 in(5);
	BKSGE_CONSTEXPR bksge::units::feet<TypeParam>		 ft(6);
	BKSGE_CONSTEXPR bksge::units::yards<TypeParam>		 yd(7);
	BKSGE_CONSTEXPR bksge::units::miles<TypeParam>		 mi(8);

	BKSGE_CONSTEXPR bksge::units::metres<float>          m_1(mm);
	BKSGE_CONSTEXPR bksge::units::metres<TypeParam>      m_2(cm);
	BKSGE_CONSTEXPR bksge::units::metres<float>          m_3(m);
	BKSGE_CONSTEXPR bksge::units::metres<TypeParam>      m_4(km);
	BKSGE_CONSTEXPR bksge::units::metres<TypeParam>      m_5(in);
	BKSGE_CONSTEXPR bksge::units::metres<TypeParam>      m_6(ft);
	BKSGE_CONSTEXPR bksge::units::metres<TypeParam>      m_7(yd);
	BKSGE_CONSTEXPR bksge::units::metres<TypeParam>      m_8(mi);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL *    0.001,  (double)m_1.value(), 0.0000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL *    0.01,   (double)m_2.value(), 0.000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 3LL *    1,              m_3.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL * 1000,              m_4.value());
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL *    0.0254, (double)m_5.value(), 0.00000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 6LL *    0.3048, (double)m_6.value(), 0.0000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 7LL *    0.9144, (double)m_7.value(), 0.000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 8LL * 1609.344,  (double)m_8.value(), 0.0001);

	BKSGE_CONSTEXPR bksge::units::kilometres<TypeParam>  km_1(mm);
	BKSGE_CONSTEXPR bksge::units::kilometres<float>      km_2(cm);
	BKSGE_CONSTEXPR bksge::units::kilometres<TypeParam>  km_3(m);
	BKSGE_CONSTEXPR bksge::units::kilometres<float>      km_4(km);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL * 0.000001, (double)km_1.value(), 0.00000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL * 0.00001,  (double)km_2.value(), 0.000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL * 0.001,    (double)km_3.value(), 0.0000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL * 1,                km_4.value());

	BKSGE_CONSTEXPR bksge::units::inches<TypeParam>	in_1(m);
	BKSGE_CONSTEXPR bksge::units::inches<float>		in_2(in);
	BKSGE_CONSTEXPR bksge::units::inches<TypeParam>	in_3(ft);
	BKSGE_CONSTEXPR bksge::units::inches<float>		in_4(yd);
	BKSGE_CONSTEXPR bksge::units::inches<TypeParam>	in_5(mi);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL *    39.3700787402, (double)in_1.value(), 0.000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 5LL *     1,                    in_2.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL *    12,                    in_3.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 7LL *    36,                    in_4.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 8LL * 63360,                    in_5.value());

	BKSGE_CONSTEXPR bksge::units::feet<float>		ft_1(m);
	BKSGE_CONSTEXPR bksge::units::feet<TypeParam>	ft_2(in);
	BKSGE_CONSTEXPR bksge::units::feet<float>		ft_3(ft);
	BKSGE_CONSTEXPR bksge::units::feet<TypeParam>	ft_4(yd);
	BKSGE_CONSTEXPR bksge::units::feet<TypeParam>	ft_5(mi);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL *    3.2808398950, (double)ft_1.value(), 0.0000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL *    0.0833333333, (double)ft_2.value(), 0.00000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL *    1,                    ft_3.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 7LL *    3,                    ft_4.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 8LL * 5280,                    ft_5.value());

	BKSGE_CONSTEXPR bksge::units::yards<TypeParam>	yd_1(m);
	BKSGE_CONSTEXPR bksge::units::yards<TypeParam>	yd_2(in);
	BKSGE_CONSTEXPR bksge::units::yards<float>		yd_3(ft);
	BKSGE_CONSTEXPR bksge::units::yards<float>		yd_4(yd);
	BKSGE_CONSTEXPR bksge::units::yards<float>		yd_5(mi);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL *    1.0936132983, (double)yd_1.value(), 0.0000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL *    0.0277777777, (double)yd_2.value(), 0.00000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 6LL *    0.3333333333, (double)yd_3.value(), 0.000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 7LL *    1,                    yd_4.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 8LL * 1760,                    yd_5.value());

	BKSGE_CONSTEXPR bksge::units::miles<TypeParam>	mi_1(m);
	BKSGE_CONSTEXPR bksge::units::miles<TypeParam>	mi_2(in);
	BKSGE_CONSTEXPR bksge::units::miles<float>		mi_3(ft);
	BKSGE_CONSTEXPR bksge::units::miles<float>		mi_4(yd);
	BKSGE_CONSTEXPR bksge::units::miles<float>		mi_5(mi);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL * 0.000621371, (double)mi_1.value(), 0.000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL * 0.000015783, (double)mi_2.value(), 0.000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 6LL * 0.000189394, (double)mi_3.value(), 0.000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 7LL * 0.000568182, (double)mi_4.value(), 0.00000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 8LL * 1,                   mi_5.value());
}

TYPED_TEST(UnitsTest, LuminanceTest)
{
	using candelas_per_square_metre = bksge::units::candelas_per_square_metre<TypeParam>;
	using candelas                  = bksge::units::candelas<TypeParam>;
	using metres                    = bksge::units::metres<TypeParam>;

	{
		// cd/m^2
		BKSGE_CONSTEXPR_OR_CONST auto a = candelas(60) / (metres(3) * metres(4));
		static_assert(bksge::is_same<decltype(a), const candelas_per_square_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, LuminousFluxTest)
{
	using candelas   = bksge::units::candelas<TypeParam>;
	using steradians = bksge::units::steradians<TypeParam>;
	using lumens     = bksge::units::lumens<TypeParam>;

	{
		// cd・sr
		BKSGE_CONSTEXPR_OR_CONST auto lm = candelas(3) * steradians(4);
		static_assert(bksge::is_same<decltype(lm), const lumens>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, lm.value());
	}
}

TYPED_TEST(UnitsTest, LuminousIntensityTest)
{
	{
		BKSGE_CONSTEXPR bksge::units::candelas<TypeParam>      cd(2);

		BKSGE_CONSTEXPR bksge::units::kilocandelas<TypeParam>  kcd(cd);
		BKSGE_CONSTEXPR bksge::units::megacandelas<TypeParam>  Mcd(cd);

		BKSGE_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000,        (double)kcd.value(), 0.0000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000 / 1000, (double)Mcd.value(), 0.00000000000001);
	}
	{
		BKSGE_CONSTEXPR bksge::units::kilocandelas<TypeParam>  kcd(3);

		BKSGE_CONSTEXPR bksge::units::candelas<TypeParam>      cd(kcd);
		BKSGE_CONSTEXPR bksge::units::megacandelas<TypeParam>  Mcd(kcd);

		BKSGE_CONSTEXPR_EXPECT_EQ  ( 3.0 * 1000,         cd.value());
		BKSGE_CONSTEXPR_EXPECT_NEAR( 3.0 / 1000, (double)Mcd.value(), 0.0000000001);
	}
	{
		BKSGE_CONSTEXPR bksge::units::megacandelas<TypeParam>  Mcd(4);

		BKSGE_CONSTEXPR bksge::units::candelas<TypeParam>      cd(Mcd);
		BKSGE_CONSTEXPR bksge::units::kilocandelas<TypeParam>  kcd(Mcd);

		BKSGE_CONSTEXPR_EXPECT_EQ( 4.0 * 1000 * 1000, cd.value());
		BKSGE_CONSTEXPR_EXPECT_EQ( 4.0 * 1000,        kcd.value());
	}
}

TYPED_TEST(UnitsTest, MagneticFieldIntensityTest)
{
	using amperes_per_metre = bksge::units::amperes_per_metre<TypeParam>;
	using amperes           = bksge::units::amperes<TypeParam>;
	using metres            = bksge::units::metres<TypeParam>;

	{
		// A/m
		BKSGE_CONSTEXPR_OR_CONST auto a = amperes(10) / metres(2);
		static_assert(bksge::is_same<decltype(a), const amperes_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, MagneticFluxTest)
{
	using volts     = bksge::units::volts<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;
	using webers    = bksge::units::webers<TypeParam>;
	using joules    = bksge::units::joules<TypeParam>;
	using amperes   = bksge::units::amperes<TypeParam>;
	using kilograms = bksge::units::kilograms<TypeParam>;
	using metres    = bksge::units::metres<TypeParam>;

	{
		// V・s
		BKSGE_CONSTEXPR_OR_CONST auto Wb = volts(3) * seconds(4);
		static_assert(bksge::is_same<decltype(Wb), const webers>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, Wb.value());
	}
	{
		// J/A
		BKSGE_CONSTEXPR_OR_CONST auto Wb = joules(60) / amperes(4);
		static_assert(bksge::is_same<decltype(Wb), const webers>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(15, Wb.value());
	}
	{
		// kg m^2 s^-2 A^-1
		BKSGE_CONSTEXPR_OR_CONST auto kg = kilograms(10);
		BKSGE_CONSTEXPR_OR_CONST auto m = metres(12);
		BKSGE_CONSTEXPR_OR_CONST auto s = seconds(3);
		BKSGE_CONSTEXPR_OR_CONST auto A = amperes(2);
		BKSGE_CONSTEXPR_OR_CONST auto Wb = (kg * m * m) / (s * s * A);
		static_assert(bksge::is_same<decltype(Wb), const webers>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(80, Wb.value());
	}
}

TYPED_TEST(UnitsTest, MagneticFluxDensityTest)
{
	using webers        = bksge::units::webers<TypeParam>;
	using square_metres = bksge::units::square_metres<TypeParam>;
	using teslas        = bksge::units::teslas<TypeParam>;
	using volts         = bksge::units::volts<TypeParam>;
	using seconds       = bksge::units::seconds<TypeParam>;
	using metres        = bksge::units::metres<TypeParam>;
	using newtons       = bksge::units::newtons<TypeParam>;
	using amperes       = bksge::units::amperes<TypeParam>;
	using kilograms     = bksge::units::kilograms<TypeParam>;

	{
		// Wb・m^-2
		BKSGE_CONSTEXPR_OR_CONST auto T = webers(30) / square_metres(3);
		static_assert(bksge::is_same<decltype(T), const teslas>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, T.value());
	}
	{
		// V・s・m^-2
		BKSGE_CONSTEXPR_OR_CONST auto T = volts(10) * seconds(3) / (metres(2) * metres(3));
		static_assert(bksge::is_same<decltype(T), const teslas>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, T.value());
	}
	{
		// N・A^-1・m^-1
		BKSGE_CONSTEXPR_OR_CONST auto T = newtons(18) / amperes(3) / metres(2);
		static_assert(bksge::is_same<decltype(T), const teslas>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(3, T.value());
	}
	{
		// kg・A^-1・s^-2
		BKSGE_CONSTEXPR_OR_CONST auto T = kilograms(120) / amperes(3) / seconds(2) / seconds(5);
		static_assert(bksge::is_same<decltype(T), const teslas>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(4, T.value());
	}
}

TYPED_TEST(UnitsTest, MagneticPermeabilityTest)
{
	using henries_per_metre = bksge::units::henries_per_metre<TypeParam>;
	using henries           = bksge::units::henries<TypeParam>;
	using metres            = bksge::units::metres<TypeParam>;
	using kilograms         = bksge::units::kilograms<TypeParam>;
	using seconds           = bksge::units::seconds<TypeParam>;
	using amperes           = bksge::units::amperes<TypeParam>;

	{
		// H/m
		BKSGE_CONSTEXPR_OR_CONST auto a = henries(10) / metres(2);
		static_assert(bksge::is_same<decltype(a), const henries_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
	{
		// m・kg・s^-2・A^-2
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(6) * kilograms(10) / (seconds(1) * seconds(2) * amperes(3) * amperes(5));
		static_assert(bksge::is_same<decltype(a), const henries_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(2, a.value());
	}
}

TYPED_TEST(UnitsTest, MagneticReluctanceTest)
{
	using amperes_per_weber  = bksge::units::amperes_per_weber<TypeParam>;
	using reciprocal_henries = bksge::units::reciprocal_henries<TypeParam>;
	using amperes            = bksge::units::amperes<TypeParam>;
	using webers             = bksge::units::webers<TypeParam>;
	using henries            = bksge::units::henries<TypeParam>;
	using seconds            = bksge::units::seconds<TypeParam>;
	using metres             = bksge::units::metres<TypeParam>;
	using kilograms          = bksge::units::kilograms<TypeParam>;

	{
		// A/Wb
		BKSGE_CONSTEXPR_OR_CONST auto a = amperes(60) / webers(2);
		static_assert(bksge::is_same<decltype(a), const amperes_per_weber>::value, "");
		static_assert(bksge::is_same<decltype(a), const reciprocal_henries>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(30, a.value());
	}
	{
		// H^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = TypeParam(10) / henries(2);
		static_assert(bksge::is_same<decltype(a), const amperes_per_weber>::value, "");
		static_assert(bksge::is_same<decltype(a), const reciprocal_henries>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
	{
		// m^-2・kg^-1・s^2・A^2
		BKSGE_CONSTEXPR_OR_CONST auto a = seconds(2) * seconds(3) * amperes(4) * amperes(5) / (metres(2) * metres(3) * kilograms(4));
		static_assert(bksge::is_same<decltype(a), const amperes_per_weber>::value, "");
		static_assert(bksge::is_same<decltype(a), const reciprocal_henries>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, MassTest)
{
	BKSGE_CONSTEXPR bksge::units::milligrams<TypeParam> mg(1);
	BKSGE_CONSTEXPR bksge::units::grams<TypeParam>      g(2);
	BKSGE_CONSTEXPR bksge::units::kilograms<TypeParam>  kg(3);
	BKSGE_CONSTEXPR bksge::units::tonnes<TypeParam>	    t(4);
	BKSGE_CONSTEXPR bksge::units::grains<TypeParam>	    gr(5);
	BKSGE_CONSTEXPR bksge::units::ounces<TypeParam>	    oz(6);
	BKSGE_CONSTEXPR bksge::units::pounds<TypeParam>	    lb(7);

	BKSGE_CONSTEXPR bksge::units::milligrams<TypeParam> mg_1(mg);
	BKSGE_CONSTEXPR bksge::units::milligrams<TypeParam> mg_2(g);
	BKSGE_CONSTEXPR bksge::units::milligrams<TypeParam> mg_3(kg);
	BKSGE_CONSTEXPR bksge::units::milligrams<TypeParam> mg_4(t);
	BKSGE_CONSTEXPR bksge::units::milligrams<TypeParam> mg_5(gr);
	BKSGE_CONSTEXPR bksge::units::milligrams<TypeParam> mg_6(oz);
	BKSGE_CONSTEXPR bksge::units::milligrams<TypeParam> mg_7(lb);

	BKSGE_CONSTEXPR_EXPECT_EQ  ( 1LL * 1.0            *    1.0,                           mg_1.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 2LL * 1.0            * 1000.0,                           mg_2.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 3LL * 1.0            * 1000.0 * 1000.0,                  mg_3.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL * 1.0            * 1000.0 * 1000.0 * 1000.0,         mg_4.value());
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL * 0.00006479891  * 1000.0 * 1000.0,          (double)mg_5.value(), 0.0001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 6LL * 0.028349523125 * 1000.0 * 1000.0,          (double)mg_6.value(), 0.01);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 7LL * 0.45359237     * 1000.0 * 1000.0,          (double)mg_7.value(), 0.1);

	BKSGE_CONSTEXPR bksge::units::grams<TypeParam> g_1(mg);
	BKSGE_CONSTEXPR bksge::units::grams<TypeParam> g_2(g);
	BKSGE_CONSTEXPR bksge::units::grams<TypeParam> g_3(kg);
	BKSGE_CONSTEXPR bksge::units::grams<TypeParam> g_4(t);
	BKSGE_CONSTEXPR bksge::units::grams<TypeParam> g_5(gr);
	BKSGE_CONSTEXPR bksge::units::grams<TypeParam> g_6(oz);
	BKSGE_CONSTEXPR bksge::units::grams<TypeParam> g_7(lb);

	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL * 1.0            *    0.001,        (double)g_1.value(), 0.0000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 2LL * 1.0            *    1.0,                  g_2.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 3LL * 1.0            * 1000.0,                  g_3.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL * 1.0            * 1000.0 * 1000.0,         g_4.value());
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL * 0.00006479891  * 1000.0,          (double)g_5.value(), 0.00000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 6LL * 0.028349523125 * 1000.0,          (double)g_6.value(), 0.00001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 7LL * 0.45359237     * 1000.0,          (double)g_7.value(), 0.001);

	BKSGE_CONSTEXPR bksge::units::kilograms<TypeParam> kg_1(mg);
	BKSGE_CONSTEXPR bksge::units::kilograms<TypeParam> kg_2(g);
	BKSGE_CONSTEXPR bksge::units::kilograms<TypeParam> kg_3(kg);
	BKSGE_CONSTEXPR bksge::units::kilograms<TypeParam> kg_4(t);
	BKSGE_CONSTEXPR bksge::units::kilograms<TypeParam> kg_5(gr);
	BKSGE_CONSTEXPR bksge::units::kilograms<TypeParam> kg_6(oz);
	BKSGE_CONSTEXPR bksge::units::kilograms<TypeParam> kg_7(lb);

	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL * 1.0            *    0.001 * 0.001, (double)kg_1.value(), 0.0000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL * 1.0            *    0.001,         (double)kg_2.value(), 0.0000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 3LL * 1.0            *    1.0,                   kg_3.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL * 1.0            * 1000.0,                   kg_4.value());
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL * 0.00006479891  *    1.0,           (double)kg_5.value(), 0.0000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 6LL * 0.028349523125 *    1.0,           (double)kg_6.value(), 0.00000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 7LL * 0.45359237     *    1.0,           (double)kg_7.value(), 0.0000001);

	BKSGE_CONSTEXPR bksge::units::tonnes<TypeParam> t_1(mg);
	BKSGE_CONSTEXPR bksge::units::tonnes<TypeParam> t_2(g);
	BKSGE_CONSTEXPR bksge::units::tonnes<TypeParam> t_3(kg);
	BKSGE_CONSTEXPR bksge::units::tonnes<TypeParam> t_4(t);
	BKSGE_CONSTEXPR bksge::units::tonnes<TypeParam> t_5(gr);
	BKSGE_CONSTEXPR bksge::units::tonnes<TypeParam> t_6(oz);
	BKSGE_CONSTEXPR bksge::units::tonnes<TypeParam> t_7(lb);

	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL * 1.0            *    0.001 * 0.001 * 0.001, (double)t_1.value(), 0.0000000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL * 1.0            *    0.001 * 0.001,         (double)t_2.value(), 0.00000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL * 1.0            *    0.001,                 (double)t_3.value(), 0.0000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL * 1.0            *    1.0,                           t_4.value());
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL * 0.00006479891  *    0.001,                 (double)t_5.value(), 0.00000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 6LL * 0.028349523125 *    0.001,                 (double)t_6.value(), 0.00000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 7LL * 0.45359237     *    0.001,                 (double)t_7.value(), 0.0000000001);

	BKSGE_CONSTEXPR bksge::units::grains<TypeParam> gr_1(mg);
	BKSGE_CONSTEXPR bksge::units::grains<TypeParam> gr_2(g);
	BKSGE_CONSTEXPR bksge::units::grains<TypeParam> gr_3(kg);
	BKSGE_CONSTEXPR bksge::units::grains<TypeParam> gr_4(t);
	BKSGE_CONSTEXPR bksge::units::grains<TypeParam> gr_5(gr);
	BKSGE_CONSTEXPR bksge::units::grains<TypeParam> gr_6(oz);
	BKSGE_CONSTEXPR bksge::units::grains<TypeParam> gr_7(lb);

	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL /    0.00006479891 *    0.001 * 0.001, (double)gr_1.value(),  0.000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL /    0.00006479891 *    0.001,         (double)gr_2.value(),  0.000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL /    0.00006479891 *    1.0,           (double)gr_3.value(),  0.001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 4LL /    0.00006479891 * 1000.0,           (double)gr_4.value(), 10.0);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 5LL *    1.0           *    1.0,                   gr_5.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL *  437.5           *    1.0,                   gr_6.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 7LL * 7000.0           *    1.0,                   gr_7.value());

	BKSGE_CONSTEXPR bksge::units::ounces<TypeParam> oz_1(mg);
	BKSGE_CONSTEXPR bksge::units::ounces<TypeParam> oz_2(g);
	BKSGE_CONSTEXPR bksge::units::ounces<TypeParam> oz_3(kg);
	BKSGE_CONSTEXPR bksge::units::ounces<TypeParam> oz_4(t);
	BKSGE_CONSTEXPR bksge::units::ounces<TypeParam> oz_5(gr);
	BKSGE_CONSTEXPR bksge::units::ounces<TypeParam> oz_6(oz);
	BKSGE_CONSTEXPR bksge::units::ounces<TypeParam> oz_7(lb);

	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL /   0.028349523125 *    0.001 * 0.001, (double)oz_1.value(),  0.000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL /   0.028349523125 *    0.001,         (double)oz_2.value(),  0.000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL /   0.028349523125 *    1.0,           (double)oz_3.value(),  0.00001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 4LL /   0.028349523125 * 1000.0,           (double)oz_4.value(),  0.01);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL / 437.5            *    1.0,           (double)oz_5.value(),  0.000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL *   1.0            *    1.0,                   oz_6.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 7LL *  16.0            *    1.0,                   oz_7.value());

	BKSGE_CONSTEXPR bksge::units::pounds<TypeParam> lb_1(mg);
	BKSGE_CONSTEXPR bksge::units::pounds<TypeParam> lb_2(g);
	BKSGE_CONSTEXPR bksge::units::pounds<TypeParam> lb_3(kg);
	BKSGE_CONSTEXPR bksge::units::pounds<TypeParam> lb_4(t);
	BKSGE_CONSTEXPR bksge::units::pounds<TypeParam> lb_5(gr);
	BKSGE_CONSTEXPR bksge::units::pounds<TypeParam> lb_6(oz);
	BKSGE_CONSTEXPR bksge::units::pounds<TypeParam> lb_7(lb);

	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL /   0.45359237 *    0.001 * 0.001, (double)lb_1.value(),  0.0000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL /   0.45359237 *    0.001,         (double)lb_2.value(),  0.0000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL /   0.45359237 *    1.0,           (double)lb_3.value(),  0.000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 4LL /   0.45359237 * 1000.0,           (double)lb_4.value(),  0.001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 5LL / 7000.0       *    1.0,           (double)lb_5.value(),  0.00000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL /   16.0       *    1.0,                   lb_6.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 7LL *    1.0       *    1.0,                   lb_7.value());
}

TYPED_TEST(UnitsTest, MassDensityTest)
{
	using kilograms                  = bksge::units::kilograms<TypeParam>;
	using grams                      = bksge::units::grams<TypeParam>;
	using pounds                     = bksge::units::pounds<TypeParam>;

	using metres                     = bksge::units::metres<TypeParam>;
	using centimetres                = bksge::units::centimetres<TypeParam>;
	using feet                       = bksge::units::feet<TypeParam>;

	using kilograms_per_cubic_metre  = bksge::units::kilograms_per_cubic_metre<TypeParam>;
	using grams_per_cubic_centimetre = bksge::units::grams_per_cubic_centimetre<TypeParam>;
	using pounds_per_cubic_foot      = bksge::units::pounds_per_cubic_foot<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = kilograms(120) / metres(2) / metres(3) / metres(4);
		static_assert(bksge::is_same<decltype(v), const kilograms_per_cubic_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = grams(120) / centimetres(1) / centimetres(2) / centimetres(3);
		static_assert(bksge::is_same<decltype(v), const grams_per_cubic_centimetre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = pounds(120) / feet(3) / feet(4) / feet(5);
		static_assert(bksge::is_same<decltype(v), const pounds_per_cubic_foot>::value, "");
		BKSGE_CONSTEXPR_EXPECT_NEAR(2.0, (double)v.value(), 0.000001);
	}
}

TYPED_TEST(UnitsTest, MolarEnergyTest)
{
	using joules_per_mole = bksge::units::joules_per_mole<TypeParam>;
	using joules          = bksge::units::joules<TypeParam>;
	using mole            = bksge::units::mole<TypeParam>;
	using metres          = bksge::units::metres<TypeParam>;
	using kilograms       = bksge::units::kilograms<TypeParam>;
	using seconds         = bksge::units::seconds<TypeParam>;

	{
		// J/mol
		BKSGE_CONSTEXPR_OR_CONST auto a = joules(60) / mole(2);
		static_assert(bksge::is_same<decltype(a), const joules_per_mole>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(30, a.value());
	}
	{
		// m^2・kg・s^-2・mol^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(2) * metres(3) * kilograms(4) / (seconds(1) * seconds(2) * mole(3));
		static_assert(bksge::is_same<decltype(a), const joules_per_mole>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(4, a.value());
	}
}

TYPED_TEST(UnitsTest, MolarHeatCapacityTest)
{
	using joules_per_kelvin_mole = bksge::units::joules_per_kelvin_mole<TypeParam>;
	using joules                 = bksge::units::joules<TypeParam>;
	using kelvins                = bksge::units::kelvins<TypeParam>;
	using mole                   = bksge::units::mole<TypeParam>;
	using metres                 = bksge::units::metres<TypeParam>;
	using kilograms              = bksge::units::kilograms<TypeParam>;
	using seconds                = bksge::units::seconds<TypeParam>;

	{
		// J/(K・mol)
		BKSGE_CONSTEXPR_OR_CONST auto a = joules(60) / (kelvins(3) * mole(2));
		static_assert(bksge::is_same<decltype(a), const joules_per_kelvin_mole>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// m^2・kg・s^-2・K^-1・mol^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(2) * metres(3) * kilograms(4) / (seconds(1) * seconds(2) * kelvins(2) * mole(3));
		static_assert(bksge::is_same<decltype(a), const joules_per_kelvin_mole>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(2, a.value());
	}
}

TYPED_TEST(UnitsTest, MomentOfInertiaTest)
{
	using kilograms_square_metre = bksge::units::kilograms_square_metre<TypeParam>;
	using kilograms              = bksge::units::kilograms<TypeParam>;
	using metres                 = bksge::units::metres<TypeParam>;

	{
		// kg・m^2
		BKSGE_CONSTEXPR_OR_CONST auto a = kilograms(2) * metres(3) * metres(4);
		static_assert(bksge::is_same<decltype(a), const kilograms_square_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(24, a.value());
	}
}

TYPED_TEST(UnitsTest, MomentumTest)
{
	using newton_seconds = bksge::units::newton_seconds<TypeParam>;
	using newtons        = bksge::units::newtons<TypeParam>;
	using seconds        = bksge::units::seconds<TypeParam>;
	using metres         = bksge::units::metres<TypeParam>;
	using kilograms      = bksge::units::kilograms<TypeParam>;

	{
		// N・s
		BKSGE_CONSTEXPR_OR_CONST auto a = newtons(4) * seconds(5);
		static_assert(bksge::is_same<decltype(a), const newton_seconds>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// m・kg・s^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(4) * kilograms(3) / seconds(2);
		static_assert(bksge::is_same<decltype(a), const newton_seconds>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(6, a.value());
	}
}

TYPED_TEST(UnitsTest, PermittivityTest)
{
	using farads_per_metre = bksge::units::farads_per_metre<TypeParam>;
	using farads           = bksge::units::farads<TypeParam>;
	using metres           = bksge::units::metres<TypeParam>;
	using kilograms        = bksge::units::kilograms<TypeParam>;
	using seconds          = bksge::units::seconds<TypeParam>;
	using amperes          = bksge::units::amperes<TypeParam>;

	{
		// F/m
		BKSGE_CONSTEXPR_OR_CONST auto a = farads(60) / metres(3);
		static_assert(bksge::is_same<decltype(a), const farads_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// m^-3・kg^-1・s^4・A^2
		BKSGE_CONSTEXPR_OR_CONST auto m = metres(2);
		BKSGE_CONSTEXPR_OR_CONST auto kg = kilograms(3);
		BKSGE_CONSTEXPR_OR_CONST auto s = seconds(2);
		BKSGE_CONSTEXPR_OR_CONST auto A = amperes(3);
		BKSGE_CONSTEXPR_OR_CONST auto a = s * s * s * s * A * A / (m * m * m * kg);
		static_assert(bksge::is_same<decltype(a), const farads_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(6, a.value());
	}
}

TYPED_TEST(UnitsTest, PowerTest)
{
	using metres    = bksge::units::metres<TypeParam>;
	using joules    = bksge::units::joules<TypeParam>;
	using seconds   = bksge::units::seconds<TypeParam>;
	using watts     = bksge::units::watts<TypeParam>;
	using newtons   = bksge::units::newtons<TypeParam>;
	using kilograms = bksge::units::kilograms<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = joules(60) / seconds(4);
		static_assert(bksge::is_same<decltype(v), const watts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(15, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = newtons(10) * metres(6) / seconds(5);
		static_assert(bksge::is_same<decltype(v), const watts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = metres(10) * metres(6) * kilograms(8) / seconds(2) / seconds(3) / seconds(4);
		static_assert(bksge::is_same<decltype(v), const watts>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
}

TYPED_TEST(UnitsTest, PressureTest)
{
	using square_metre = bksge::units::square_metre<TypeParam>;
	using metre        = bksge::units::metre<TypeParam>;
	using newtons      = bksge::units::newtons<TypeParam>;
	using kilograms    = bksge::units::kilograms<TypeParam>;
	using seconds      = bksge::units::seconds<TypeParam>;
	using pascals      = bksge::units::pascals<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = newtons(10) / square_metre(2);
		static_assert(bksge::is_same<decltype(v), const pascals>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = newtons(60) / metre(2) / metre(3);
		static_assert(bksge::is_same<decltype(v), const pascals>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = kilograms(120) / metre(2) / seconds(3) / seconds(4);
		static_assert(bksge::is_same<decltype(v), const pascals>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
}

TYPED_TEST(UnitsTest, RadioactivityTest)
{
	using seconds = bksge::units::seconds<TypeParam>;
	using becquerels = bksge::units::becquerels<TypeParam>;

	{
		// s^-1
		BKSGE_CONSTEXPR_OR_CONST auto Bq = TypeParam(10) / seconds(2);
		static_assert(bksge::is_same<decltype(Bq), const becquerels>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, Bq.value());
	}
}

TYPED_TEST(UnitsTest, SolidAngleTest)
{
	BKSGE_CONSTEXPR bksge::units::steradians<TypeParam> s(42);
	BKSGE_CONSTEXPR_EXPECT_EQ(42, s.value());
}

TYPED_TEST(UnitsTest, SpecificEnergyTest)
{
	using joules_per_kilogram = bksge::units::joules_per_kilogram<TypeParam>;
	using joules              = bksge::units::joules<TypeParam>;
	using kilograms           = bksge::units::kilograms<TypeParam>;
	using metres              = bksge::units::metres<TypeParam>;
	using seconds             = bksge::units::seconds<TypeParam>;

	{
		// J/kg
		BKSGE_CONSTEXPR_OR_CONST auto a = joules(60) / kilograms(2);
		static_assert(bksge::is_same<decltype(a), const joules_per_kilogram>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(30, a.value());
	}
	{
		// m^2・s^-2
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(6) * metres(50) / (seconds(2) * seconds(3));
		static_assert(bksge::is_same<decltype(a), const joules_per_kilogram>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(50, a.value());
	}
}

TYPED_TEST(UnitsTest, SpecificHeatCapacityTest)
{
	using joules_per_kilogram_kelvin = bksge::units::joules_per_kilogram_kelvin<TypeParam>;
	using joules                     = bksge::units::joules<TypeParam>;
	using kelvins                    = bksge::units::kelvins<TypeParam>;
	using kilograms                  = bksge::units::kilograms<TypeParam>;
	using metres                     = bksge::units::metres<TypeParam>;
	using seconds                    = bksge::units::seconds<TypeParam>;

	{
		// J/(K・kg)
		BKSGE_CONSTEXPR_OR_CONST auto a = joules(60) / (kelvins(3) * kilograms(2));
		static_assert(bksge::is_same<decltype(a), const joules_per_kilogram_kelvin>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// m^2・s^-2・K^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(6) * metres(50) / (seconds(2) * seconds(3) * kelvins(10));
		static_assert(bksge::is_same<decltype(a), const joules_per_kilogram_kelvin>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, SpecificVolumeTest)
{
	using cubic_metres_per_kilogram = bksge::units::cubic_metres_per_kilogram<TypeParam>;
	using metres                    = bksge::units::metres<TypeParam>;
	using kilograms                 = bksge::units::kilograms<TypeParam>;

	{
		// m^3/kg
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(2) * metres(3) * metres(4) / kilograms(2);
		static_assert(bksge::is_same<decltype(a), const cubic_metres_per_kilogram>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(12, a.value());
	}
}

TYPED_TEST(UnitsTest, SurfaceDensityTest)
{
	using kilograms                  = bksge::units::kilograms<TypeParam>;
	using grams                      = bksge::units::grams<TypeParam>;
	using pounds                     = bksge::units::pounds<TypeParam>;

	using metres                     = bksge::units::metres<TypeParam>;
	using centimetres                = bksge::units::centimetres<TypeParam>;
	using feet                       = bksge::units::feet<TypeParam>;

	using kilograms_per_square_metre  = bksge::units::kilograms_per_square_metre<TypeParam>;
	using grams_per_square_centimetre = bksge::units::grams_per_square_centimetre<TypeParam>;
	using pounds_per_square_foot      = bksge::units::pounds_per_square_foot<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = kilograms(120) / metres(2) / metres(3);
		static_assert(bksge::is_same<decltype(v), const kilograms_per_square_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = grams(120) / centimetres(1) / centimetres(2);
		static_assert(bksge::is_same<decltype(v), const grams_per_square_centimetre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(60, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = pounds(120) / feet(3) / feet(4);
		static_assert(bksge::is_same<decltype(v), const pounds_per_square_foot>::value, "");
		BKSGE_CONSTEXPR_EXPECT_NEAR(10.0, (double)v.value(), 0.000001);
	}
}

TYPED_TEST(UnitsTest, SurfaceTensionTest)
{
	using newtons_per_metre = bksge::units::newtons_per_metre<TypeParam>;
	using newtons           = bksge::units::newtons<TypeParam>;
	using metres            = bksge::units::metres<TypeParam>;
	using joules            = bksge::units::joules<TypeParam>;
	using kilograms         = bksge::units::kilograms<TypeParam>;
	using seconds           = bksge::units::seconds<TypeParam>;

	{
		// N / m
		BKSGE_CONSTEXPR_OR_CONST auto a = newtons(60) / metres(2);
		static_assert(bksge::is_same<decltype(a), const newtons_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(30, a.value());
	}
	{
		// J / m^2
		BKSGE_CONSTEXPR_OR_CONST auto a = joules(60) / (metres(2) * metres(3));
		static_assert(bksge::is_same<decltype(a), const newtons_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// kg・s^-2
		BKSGE_CONSTEXPR_OR_CONST auto a = kilograms(30) / (seconds(2) * seconds(3));
		static_assert(bksge::is_same<decltype(a), const newtons_per_metre>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, TemperatureTest)
{
	using kelvins            = bksge::units::kelvins<TypeParam>;
	using kilokelvins        = bksge::units::kilokelvins<TypeParam>;
	using megakelvins        = bksge::units::megakelvins<TypeParam>;
	using degrees_celsius    = bksge::units::degrees_celsius<TypeParam>;
	using degrees_fahrenheit = bksge::units::degrees_fahrenheit<TypeParam>;

	{
		BKSGE_CONSTEXPR kelvins            k(0);
		BKSGE_CONSTEXPR kilokelvins        kk(k);
		BKSGE_CONSTEXPR megakelvins        Mk(k);
		BKSGE_CONSTEXPR degrees_celsius	   c(k);
		BKSGE_CONSTEXPR degrees_fahrenheit f(k);
		BKSGE_CONSTEXPR_EXPECT_EQ  (   0.0,          kk.value());
		BKSGE_CONSTEXPR_EXPECT_EQ  (   0.0,          Mk.value());
		BKSGE_CONSTEXPR_EXPECT_NEAR(-273.15, (double)c.value(),  0.00001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(-459.67, (double)f.value(),  0.0001);
	}
	{
		BKSGE_CONSTEXPR kelvins            k(TypeParam(255.3722222222));
		BKSGE_CONSTEXPR kilokelvins        kk(k);
		BKSGE_CONSTEXPR megakelvins        Mk(k);
		BKSGE_CONSTEXPR degrees_celsius	   c(k);
		BKSGE_CONSTEXPR degrees_fahrenheit f(k);
		BKSGE_CONSTEXPR_EXPECT_NEAR(255.3722222222 * 0.001,         (double)kk.value(), 0.00000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(255.3722222222 * 0.001 * 0.001, (double)Mk.value(), 0.0000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(-17.7777777778,                 (double)c.value(),  0.00001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(  0.0,                          (double)f.value(),  0.00001);
	}
	{
		BKSGE_CONSTEXPR kelvins            k(TypeParam(273.15));
		BKSGE_CONSTEXPR kilokelvins        kk(k);
		BKSGE_CONSTEXPR megakelvins        Mk(k);
		BKSGE_CONSTEXPR degrees_celsius	   c(k);
		BKSGE_CONSTEXPR degrees_fahrenheit f(k);
		BKSGE_CONSTEXPR_EXPECT_NEAR(273.15 * 0.001,         (double)kk.value(), 0.00000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(273.15 * 0.001 * 0.001, (double)Mk.value(), 0.0000000001);
		BKSGE_CONSTEXPR_EXPECT_NEAR(  0.0,                  (double)c.value(),  0.00001);
		BKSGE_CONSTEXPR_EXPECT_NEAR( 32.0,                  (double)f.value(),  0.0001);
	}
	// celsius + celsius -> kelvins
	{
		// ※ 7 ℃ + 5 ℃ = 12 ℃　ではない
		// ケルビンに変換してから計算される
		// 280.15 K + 278.15 K = 558.30 K
		BKSGE_CONSTEXPR kelvins k = degrees_celsius(7) + degrees_celsius(5);
		BKSGE_CONSTEXPR_EXPECT_NEAR(558.30, (double)k.value(), 0.0001);
	}
	// fahrenheit + fahrenheit -> kelvins
	{
		// ※ 7 °F + 5 °F = 12 °F　ではない
		// ケルビンに変換してから計算される
		// 259.2611111 K + 258.15 K = 517.41111 K
		BKSGE_CONSTEXPR kelvins k = degrees_fahrenheit(7) + degrees_fahrenheit(5);
		BKSGE_CONSTEXPR_EXPECT_NEAR(517.41111111111111111111111111111, (double)k.value(), 0.0001);
	}
	// celsius - celsius -> kelvins
	{
		// ※ 7 ℃ - 5 ℃ = 2 ℃　ではない
		// ケルビンに変換してから計算される
		// 280.15 K - 278.15 K = 2.0 K
		BKSGE_CONSTEXPR kelvins k = degrees_celsius(7) - degrees_celsius(5);
		BKSGE_CONSTEXPR_EXPECT_NEAR(2.0, (double)k.value(), 0.0001);
	}
	// fahrenheit - fahrenheit -> kelvins
	{
		// ※ 7 °F - 5 °F = 2 °F　ではない
		// ケルビンに変換してから計算される
		// 259.2611111 K - 258.15 K = 1.11111 K
		BKSGE_CONSTEXPR kelvins k = degrees_fahrenheit(7) - degrees_fahrenheit(5);
		BKSGE_CONSTEXPR_EXPECT_NEAR(1.11111111111111111111111111111, (double)k.value(), 0.0001);
	}
}

TYPED_TEST(UnitsTest, ThermalConductivityTest)
{
	using watts_per_metre_kelvin = bksge::units::watts_per_metre_kelvin<TypeParam>;
	using watts                  = bksge::units::watts<TypeParam>;
	using metres                 = bksge::units::metres<TypeParam>;
	using kelvins                = bksge::units::kelvins<TypeParam>;
	using kilograms              = bksge::units::kilograms<TypeParam>;
	using seconds                = bksge::units::seconds<TypeParam>;

	{
		// W/(m・K)
		BKSGE_CONSTEXPR_OR_CONST auto a = watts(60) / (metres(2) * kelvins(3));
		static_assert(bksge::is_same<decltype(a), const watts_per_metre_kelvin>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// m・kg・s^-3・K^-1
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(8) * kilograms(6) / (seconds(1) * seconds(2) * seconds(3) * kelvins(4));
		static_assert(bksge::is_same<decltype(a), const watts_per_metre_kelvin>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(2, a.value());
	}
}

TYPED_TEST(UnitsTest, TimeTest)
{
	BKSGE_CONSTEXPR bksge::units::milliseconds<TypeParam> ms (1);
	BKSGE_CONSTEXPR bksge::units::seconds<TypeParam>      s  (2);
	BKSGE_CONSTEXPR bksge::units::minutes<TypeParam>      min(3);
	BKSGE_CONSTEXPR bksge::units::hours<TypeParam>		  h  (4);
	BKSGE_CONSTEXPR bksge::units::days<TypeParam>		  d  (5);
	BKSGE_CONSTEXPR bksge::units::years<TypeParam>		  y  (6);

	BKSGE_CONSTEXPR bksge::units::seconds<float>          s_1(ms);
	BKSGE_CONSTEXPR bksge::units::seconds<float>          s_2(s);
	BKSGE_CONSTEXPR bksge::units::seconds<TypeParam>      s_3(min);
	BKSGE_CONSTEXPR bksge::units::seconds<TypeParam>      s_4(h);
	BKSGE_CONSTEXPR bksge::units::seconds<TypeParam>      s_5(d);
	BKSGE_CONSTEXPR bksge::units::seconds<TypeParam>      s_6(y);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL *        0.001, (double)s_1.value(), 0.0000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 2LL *        1,             s_2.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 3LL *       60,             s_3.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL *     3600,             s_4.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 5LL *    86400,             s_5.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL * 31557600,             s_6.value());

	BKSGE_CONSTEXPR bksge::units::milliseconds<TypeParam>  ms_1(ms);
	BKSGE_CONSTEXPR bksge::units::milliseconds<TypeParam>  ms_2(s);
	BKSGE_CONSTEXPR bksge::units::milliseconds<TypeParam>  ms_3(min);
	BKSGE_CONSTEXPR bksge::units::milliseconds<TypeParam>  ms_4(h);
	BKSGE_CONSTEXPR bksge::units::milliseconds<TypeParam>  ms_5(d);
	BKSGE_CONSTEXPR bksge::units::milliseconds<TypeParam>  ms_6(y);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 1LL *               1, ms_1.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 2LL *            1000, ms_2.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 3LL *       60 * 1000, ms_3.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL *     3600 * 1000, ms_4.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 5LL *    86400 * 1000, ms_5.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL * 31557600 * 1000, ms_6.value());

	BKSGE_CONSTEXPR bksge::units::minutes<TypeParam>	min_1(ms);
	BKSGE_CONSTEXPR bksge::units::minutes<TypeParam>	min_2(s);
	BKSGE_CONSTEXPR bksge::units::minutes<float>		min_3(min);
	BKSGE_CONSTEXPR bksge::units::minutes<TypeParam>	min_4(h);
	BKSGE_CONSTEXPR bksge::units::minutes<float>		min_5(d);
	BKSGE_CONSTEXPR bksge::units::minutes<TypeParam>	min_6(y);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL *      0.000016666666, (double)min_1.value(), 0.000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL *      0.016666666666, (double)min_2.value(), 0.00000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 3LL *      1,                      min_3.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL *     60,                      min_4.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 5LL *   1440,                      min_5.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL * 525960,                      min_6.value());

	BKSGE_CONSTEXPR bksge::units::hours<TypeParam>	h_1(ms);
	BKSGE_CONSTEXPR bksge::units::hours<float>		h_2(s);
	BKSGE_CONSTEXPR bksge::units::hours<TypeParam>	h_3(min);
	BKSGE_CONSTEXPR bksge::units::hours<float>		h_4(h);
	BKSGE_CONSTEXPR bksge::units::hours<TypeParam>	h_5(d);
	BKSGE_CONSTEXPR bksge::units::hours<TypeParam>	h_6(y);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL *    0.0000002777777, (double)h_1.value(), 0.0000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL *    0.0002777777777, (double)h_2.value(), 0.0000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL *    0.0166666666666, (double)h_3.value(), 0.000000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 4LL *    1,                       h_4.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 5LL *   24,                       h_5.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL * 8766,                       h_6.value());

	BKSGE_CONSTEXPR bksge::units::days<TypeParam>	d_1(ms);
	BKSGE_CONSTEXPR bksge::units::days<TypeParam>	d_2(s);
	BKSGE_CONSTEXPR bksge::units::days<TypeParam>	d_3(min);
	BKSGE_CONSTEXPR bksge::units::days<float>		d_4(h);
	BKSGE_CONSTEXPR bksge::units::days<float>		d_5(d);
	BKSGE_CONSTEXPR bksge::units::days<float>		d_6(y);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 1LL *   0.00000001157407, (double)d_1.value(), 0.00000000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 2LL *   0.00001157407,    (double)d_2.value(), 0.00000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 3LL *   0.00069444444,    (double)d_3.value(), 0.000000001);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 4LL *   0.04166666666,    (double)d_4.value(), 0.00000001);
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 5LL *   1,                        d_5.value());
	BKSGE_CONSTEXPR_EXPECT_EQ  ( 6LL * 365.25,                     d_6.value());
}

TYPED_TEST(UnitsTest, TorqueTest)
{
	using newton_metres = bksge::units::newton_metres<TypeParam>;
	using newtons       = bksge::units::newtons<TypeParam>;
	using metres        = bksge::units::metres<TypeParam>;
	using kilograms     = bksge::units::kilograms<TypeParam>;
	using seconds       = bksge::units::seconds<TypeParam>;

	{
		// N・m
		BKSGE_CONSTEXPR_OR_CONST auto a = newtons(4) * metres(5);
		static_assert(bksge::is_same<decltype(a), const newton_metres>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// m^2・kg・s^-2
		BKSGE_CONSTEXPR_OR_CONST auto a = metres(2) * metres(3) * kilograms(4) / (seconds(2) * seconds(3));
		static_assert(bksge::is_same<decltype(a), const newton_metres>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(4, a.value());
	}
}

TYPED_TEST(UnitsTest, VelocityTest)
{
	using metres                 = bksge::units::metres<TypeParam>;
	using centimetres            = bksge::units::centimetres<TypeParam>;
	using kilometres             = bksge::units::kilometres<TypeParam>;
	using feet                   = bksge::units::feet<TypeParam>;
	using miles                  = bksge::units::miles<TypeParam>;

	using seconds                = bksge::units::seconds<TypeParam>;
	using hours                  = bksge::units::hours<TypeParam>;
	
	using metres_per_second      = bksge::units::metres_per_second<TypeParam>;
	using centimetres_per_second = bksge::units::centimetres_per_second<TypeParam>;
	using kilometres_per_hour    = bksge::units::kilometres_per_hour<TypeParam>;
	using feet_per_second        = bksge::units::feet_per_second<TypeParam>;
	using miles_per_hour         = bksge::units::miles_per_hour<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = metres(10) / seconds(2);
		static_assert(bksge::is_same<decltype(v), const metres_per_second>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = centimetres(10) / seconds(5);
		static_assert(bksge::is_same<decltype(v), const centimetres_per_second>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = kilometres(120) / hours(2);
		static_assert(bksge::is_same<decltype(v), const kilometres_per_hour>::value, "");
		BKSGE_CONSTEXPR_EXPECT_NEAR(60, (double)v.value(), 0.00001);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = feet(12) / seconds(4);
		static_assert(bksge::is_same<decltype(v), const feet_per_second>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = miles(60) / hours(3);
		static_assert(bksge::is_same<decltype(v), const miles_per_hour>::value, "");
		BKSGE_CONSTEXPR_EXPECT_NEAR(20, (double)v.value(), 0.00000000000001);
	}
}

TYPED_TEST(UnitsTest, VolumeTest)
{
	using metres       = bksge::units::metres<TypeParam>;
	using inches       = bksge::units::inches<TypeParam>;
	using decimetre    = bksge::units::decimetre<TypeParam>;
	using cubic_metres = bksge::units::cubic_metres<TypeParam>;
	using cubic_inches = bksge::units::cubic_inches<TypeParam>;
	using litres       = bksge::units::litres<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = metres(2) * metres(3) * metres(4);
		static_assert(bksge::is_same<decltype(v), const cubic_metres>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(24, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = inches(3) * inches(4) * inches(5);
		static_assert(bksge::is_same<decltype(v), const cubic_inches>::value, "");
		BKSGE_CONSTEXPR_EXPECT_NEAR(60, (double)v.value(), 0.0001);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = decimetre(7) * decimetre(4) * decimetre(2);
		static_assert(bksge::is_same<decltype(v), const litres>::value, "");
		BKSGE_CONSTEXPR_EXPECT_NEAR(56, (double)v.value(), 0.00000000000001);
	}
}

TYPED_TEST(UnitsTest, WavenumberTest)
{
	using metres                = bksge::units::metres<TypeParam>;
	using kilometres            = bksge::units::kilometres<TypeParam>;
	using centimetres           = bksge::units::centimetres<TypeParam>;

	using reciprocal_metres     = bksge::units::reciprocal_metres<TypeParam>;
	using reciprocal_kilometres = bksge::units::reciprocal_kilometres<TypeParam>;
	using kaysers               = bksge::units::kaysers<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = TypeParam(50) / metres(10);
		static_assert(bksge::is_same<decltype(v), const reciprocal_metres>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = 100 / kilometres(2);
		static_assert(bksge::is_same<decltype(v), const reciprocal_kilometres>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(50, v.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto v = 22.5f / centimetres(5);
		static_assert(bksge::is_same<decltype(v), const kaysers>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(4.5, v.value());
	}
}

}	// namespace units_units_test
