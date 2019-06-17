/**
 *	@file	unit_test_units_angle.cpp
 *
 *	@brief	angle のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/units/radian.hpp>
#include <bksge/units/degree.hpp>
#include <bksge/cmath/constants.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace units_angle_test
{

template <typename T>
class AngleTest : public ::testing::Test {};

using AngleTestTypes = ::testing::Types<float, double, long double>;

TYPED_TEST_SUITE(AngleTest, AngleTestTypes);

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
