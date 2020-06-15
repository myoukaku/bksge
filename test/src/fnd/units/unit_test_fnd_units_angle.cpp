/**
 *	@file	unit_test_fnd_units_angle.cpp
 *
 *	@brief	angle のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/units/radian.hpp>
#include <bksge/fnd/units/degree.hpp>
#include <bksge/fnd/cmath/constants.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace units_angle_test
{

template <typename T>
class AngleTest : public ::testing::Test {};

using AngleTestTypes = ::testing::Types<float, double, long double>;

TYPED_TEST_SUITE(AngleTest, AngleTestTypes);

template <typename T>
struct angle_accuracy;
template <> struct angle_accuracy<float>       { static BKSGE_CONSTEXPR double get() { return 0.0001; } };
template <> struct angle_accuracy<double>      { static BKSGE_CONSTEXPR double get() { return 0.000000000000000000000000000001; } };
template <> struct angle_accuracy<long double> { static BKSGE_CONSTEXPR double get() { return 0.000000000000000000000000000001; } };

TYPED_TEST(AngleTest, AccuracyTest)
{
	using T = TypeParam;
	using radians = bksge::units::radians<T>;
	using degrees = bksge::units::degrees<T>;

	BKSGE_CONSTEXPR auto p = bksge::pi<T>();

	BKSGE_CONSTEXPR double error = angle_accuracy<T>::get();

	BKSGE_CONSTEXPR_EXPECT_NEAR(  0.0, (double)degrees(radians(p * T(0.00))).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 45.0, (double)degrees(radians(p * T(0.25))).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 90.0, (double)degrees(radians(p * T(0.50))).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(135.0, (double)degrees(radians(p * T(0.75))).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(180.0, (double)degrees(radians(p * T(1.00))).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(225.0, (double)degrees(radians(p * T(1.25))).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(270.0, (double)degrees(radians(p * T(1.50))).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(315.0, (double)degrees(radians(p * T(1.75))).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(360.0, (double)degrees(radians(p * T(2.00))).value(), error);

	BKSGE_CONSTEXPR_EXPECT_NEAR(p * 0.00, (double)radians(degrees(  0.0)).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(p * 0.25, (double)radians(degrees( 45.0)).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(p * 0.50, (double)radians(degrees( 90.0)).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(p * 0.75, (double)radians(degrees(135.0)).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(p * 1.00, (double)radians(degrees(180.0)).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(p * 1.25, (double)radians(degrees(225.0)).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(p * 1.50, (double)radians(degrees(270.0)).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(p * 1.75, (double)radians(degrees(315.0)).value(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(p * 2.00, (double)radians(degrees(360.0)).value(), error);
}

TYPED_TEST(AngleTest, SinTest)
{
	using radians = bksge::units::radians<TypeParam>;
	using degrees = bksge::units::degrees<TypeParam>;

	BKSGE_CONSTEXPR auto p = bksge::pi<TypeParam>();

	const double error = 0.000001;

	EXPECT_NEAR( 0.00000000000, (double)sin(radians(p * TypeParam(0.000))), error);
	EXPECT_NEAR( 0.70710678118, (double)sin(radians(p * TypeParam(0.250))), error);
	EXPECT_NEAR( 1.00000000000, (double)sin(radians(p * TypeParam(0.500))), error);
	EXPECT_NEAR( 0.70710678118, (double)sin(radians(p * TypeParam(0.750))), error);
	EXPECT_NEAR( 0.00000000000, (double)sin(radians(p * TypeParam(1.000))), error);
	EXPECT_NEAR(-0.70710678118, (double)sin(radians(p * TypeParam(1.250))), error);
	EXPECT_NEAR(-1.00000000000, (double)sin(radians(p * TypeParam(1.500))), error);
	EXPECT_NEAR(-0.70710678118, (double)sin(radians(p * TypeParam(1.750))), error);
	EXPECT_NEAR( 0.00000000000, (double)sin(radians(p * TypeParam(2.000))), error);

	EXPECT_NEAR( 0.00000000000, (double)sin(degrees(  0)), error);
	EXPECT_NEAR( 0.50000000000, (double)sin(degrees( 30)), error);
	EXPECT_NEAR( 0.70710678118, (double)sin(degrees( 45)), error);
	EXPECT_NEAR( 0.86602540378, (double)sin(degrees( 60)), error);
	EXPECT_NEAR( 1.00000000000, (double)sin(degrees( 90)), error);
	EXPECT_NEAR( 0.86602540378, (double)sin(degrees(120)), error);
	EXPECT_NEAR( 0.70710678118, (double)sin(degrees(135)), error);
	EXPECT_NEAR( 0.50000000000, (double)sin(degrees(150)), error);
	EXPECT_NEAR( 0.00000000000, (double)sin(degrees(180)), error);
	EXPECT_NEAR(-0.50000000000, (double)sin(degrees(210)), error);
	EXPECT_NEAR(-0.70710678118, (double)sin(degrees(225)), error);
	EXPECT_NEAR(-0.86602540378, (double)sin(degrees(240)), error);
	EXPECT_NEAR(-1.00000000000, (double)sin(degrees(270)), error);
	EXPECT_NEAR(-0.86602540378, (double)sin(degrees(300)), error);
	EXPECT_NEAR(-0.70710678118, (double)sin(degrees(315)), error);
	EXPECT_NEAR(-0.50000000000, (double)sin(degrees(330)), error);
	EXPECT_NEAR( 0.00000000000, (double)sin(degrees(360)), error);
}

TYPED_TEST(AngleTest, CosTest)
{
	using radians = bksge::units::radians<TypeParam>;
	using degrees = bksge::units::degrees<TypeParam>;

	BKSGE_CONSTEXPR auto p = bksge::pi<TypeParam>();

	const double error = 0.000001;

	EXPECT_NEAR( 1.00000000000, (double)cos(radians(p * TypeParam(0.000))), error);
	EXPECT_NEAR( 0.70710678118, (double)cos(radians(p * TypeParam(0.250))), error);
	EXPECT_NEAR( 0.00000000000, (double)cos(radians(p * TypeParam(0.500))), error);
	EXPECT_NEAR(-0.70710678118, (double)cos(radians(p * TypeParam(0.750))), error);
	EXPECT_NEAR(-1.00000000000, (double)cos(radians(p * TypeParam(1.000))), error);
	EXPECT_NEAR(-0.70710678118, (double)cos(radians(p * TypeParam(1.250))), error);
	EXPECT_NEAR( 0.00000000000, (double)cos(radians(p * TypeParam(1.500))), error);
	EXPECT_NEAR( 0.70710678118, (double)cos(radians(p * TypeParam(1.750))), error);
	EXPECT_NEAR( 1.00000000000, (double)cos(radians(p * TypeParam(2.000))), error);

	EXPECT_NEAR( 1.00000000000, (double)cos(degrees(  0)), error);
	EXPECT_NEAR( 0.86602540378, (double)cos(degrees( 30)), error);
	EXPECT_NEAR( 0.70710678118, (double)cos(degrees( 45)), error);
	EXPECT_NEAR( 0.50000000000, (double)cos(degrees( 60)), error);
	EXPECT_NEAR( 0.00000000000, (double)cos(degrees( 90)), error);
	EXPECT_NEAR(-0.50000000000, (double)cos(degrees(120)), error);
	EXPECT_NEAR(-0.70710678118, (double)cos(degrees(135)), error);
	EXPECT_NEAR(-0.86602540378, (double)cos(degrees(150)), error);
	EXPECT_NEAR(-1.00000000000, (double)cos(degrees(180)), error);
	EXPECT_NEAR(-0.86602540378, (double)cos(degrees(210)), error);
	EXPECT_NEAR(-0.70710678118, (double)cos(degrees(225)), error);
	EXPECT_NEAR(-0.50000000000, (double)cos(degrees(240)), error);
	EXPECT_NEAR( 0.00000000000, (double)cos(degrees(270)), error);
	EXPECT_NEAR( 0.50000000000, (double)cos(degrees(300)), error);
	EXPECT_NEAR( 0.70710678118, (double)cos(degrees(315)), error);
	EXPECT_NEAR( 0.86602540378, (double)cos(degrees(330)), error);
	EXPECT_NEAR( 1.00000000000, (double)cos(degrees(360)), error);
}

TYPED_TEST(AngleTest, TanTest)
{
	using radians = bksge::units::radians<TypeParam>;
	using degrees = bksge::units::degrees<TypeParam>;

	BKSGE_CONSTEXPR auto p = bksge::pi<TypeParam>();

	const double error = 0.000001;

	EXPECT_NEAR( 0.00000000000, (double)tan(radians(p * TypeParam(0.000))), error);
	EXPECT_NEAR( 1.00000000000, (double)tan(radians(p * TypeParam(0.250))), error);
//	EXPECT_NEAR( 1.6331239e+16, (double)tan(radians(p * TypeParam(0.500))), error);
	EXPECT_NEAR(-1.00000000000, (double)tan(radians(p * TypeParam(0.750))), error);
	EXPECT_NEAR( 0.00000000000, (double)tan(radians(p * TypeParam(1.000))), error);
	EXPECT_NEAR( 1.00000000000, (double)tan(radians(p * TypeParam(1.250))), error);
//	EXPECT_NEAR( 5.4437465e+15, (double)tan(radians(p * TypeParam(1.500))), error);
	EXPECT_NEAR(-1.00000000000, (double)tan(radians(p * TypeParam(1.750))), error);
	EXPECT_NEAR( 0.00000000000, (double)tan(radians(p * TypeParam(2.000))), error);

	EXPECT_NEAR( 0.00000000000, (double)tan(degrees(  0)), error);
	EXPECT_NEAR( 0.57735026919, (double)tan(degrees( 30)), error);
	EXPECT_NEAR( 1.00000000000, (double)tan(degrees( 45)), error);
	EXPECT_NEAR( 1.73205080757, (double)tan(degrees( 60)), error);
//	EXPECT_NEAR( 1.6331239e+16, (double)tan(degrees( 90)), error);
	EXPECT_NEAR(-1.73205080757, (double)tan(degrees(120)), error);
	EXPECT_NEAR(-1.00000000000, (double)tan(degrees(135)), error);
	EXPECT_NEAR(-0.57735026919, (double)tan(degrees(150)), error);
	EXPECT_NEAR( 0.00000000000, (double)tan(degrees(180)), error);
	EXPECT_NEAR( 0.57735026919, (double)tan(degrees(210)), error);
	EXPECT_NEAR( 1.00000000000, (double)tan(degrees(225)), error);
	EXPECT_NEAR( 1.73205080757, (double)tan(degrees(240)), error);
//	EXPECT_NEAR( 5.4437465e+15, (double)tan(degrees(270)), error);
	EXPECT_NEAR(-1.73205080757, (double)tan(degrees(300)), error);
	EXPECT_NEAR(-1.00000000000, (double)tan(degrees(315)), error);
	EXPECT_NEAR(-0.57735026919, (double)tan(degrees(330)), error);
	EXPECT_NEAR( 0.00000000000, (double)tan(degrees(360)), error);
}

}	// namespace units_angle_test
