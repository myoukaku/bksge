/**
 *	@file	unit_test_input_mouse_state.cpp
 *
 *	@brief	MouseStateのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/input/mouse_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(InputTest, MouseState_ConstructTest)
{
	// デフォルトコンストラクタ
	bksge::MouseState d;

	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k7));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kTilt));

	d.pressed(bksge::MouseButton::kLeft)	= true;
	d.pressed(bksge::MouseButton::kMiddle)	= true;
	d.pressed(bksge::MouseButton::k4)		= true;
	d.pressed(bksge::MouseButton::k7)		= true;
	d.velocity(bksge::MouseAxis::kX)		= 0.5;
	d.velocity(bksge::MouseAxis::kY)		= 1.0;
	d.velocity(bksge::MouseAxis::kWheel)	= 1.5;
	d.velocity(bksge::MouseAxis::kTilt)		= 2.0;

	// コピーコンストラクタ
	bksge::MouseState d2(d);
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k7));
	EXPECT_EQ( 0.5f, d2.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 1.0f, d2.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ( 1.5f, d2.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 2.0f, d2.velocity(bksge::MouseAxis::kTilt));
	EXPECT_TRUE(d.buttons() == d2.buttons());

	// MouseStateはディープコピーされるので、dを変更してもd2には影響がない
	d.pressed(bksge::MouseButton::kLeft)	= false;
	d.pressed(bksge::MouseButton::kRight)	= true;
	d.pressed(bksge::MouseButton::k4)		= false;
	d.pressed(bksge::MouseButton::k6)		= true;
	d.velocity(bksge::MouseAxis::kX)		= -0.5;
	d.velocity(bksge::MouseAxis::kY)		=  2.0;
	d.velocity(bksge::MouseAxis::kWheel)	= -3.0;
	d.velocity(bksge::MouseAxis::kTilt)		=  5.0;

	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k7));
	EXPECT_EQ(-0.5f, d.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 2.0f, d.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ(-3.0f, d.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 5.0f, d.velocity(bksge::MouseAxis::kTilt));

	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k7));
	EXPECT_EQ( 0.5f, d2.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 1.0f, d2.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ( 1.5f, d2.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 2.0f, d2.velocity(bksge::MouseAxis::kTilt));
	EXPECT_TRUE(d.buttons() != d2.buttons());

	// 同様にd2を変更してもdには影響がない
	d2.pressed(bksge::MouseButton::kLeft)	= false;
	d2.pressed(bksge::MouseButton::kMiddle)	= false;
	d2.pressed(bksge::MouseButton::k5)		= true;
	d2.pressed(bksge::MouseButton::k6)		= true;
	d2.velocity(bksge::MouseAxis::kX)		= 6.0;
	d2.velocity(bksge::MouseAxis::kY)		= 7.0;
	d2.velocity(bksge::MouseAxis::kWheel)	= 8.0;
	d2.velocity(bksge::MouseAxis::kTilt)	= 9.0;

	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k7));
	EXPECT_EQ(-0.5f, d.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 2.0f, d.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ(-3.0f, d.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 5.0f, d.velocity(bksge::MouseAxis::kTilt));

	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k7));
	EXPECT_EQ( 6.0f, d2.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 7.0f, d2.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ( 8.0f, d2.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 9.0f, d2.velocity(bksge::MouseAxis::kTilt));
	EXPECT_TRUE(d.buttons() != d2.buttons());

	bksge::MouseState const d3(d);
	EXPECT_EQ(false, d3.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(true,  d3.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(true,  d3.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d3.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(false, d3.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(false, d3.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(true,  d3.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(true,  d3.pressed(bksge::MouseButton::k7));
	EXPECT_EQ(-0.5f, d3.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 2.0f, d3.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ(-3.0f, d3.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 5.0f, d3.velocity(bksge::MouseAxis::kTilt));
	EXPECT_TRUE(d.buttons() == d3.buttons());
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

GTEST_TEST(InputTest, MouseState_AssignTest)
{
	bksge::MouseState d;

	bksge::MouseState d2;
	d2.pressed(bksge::MouseButton::kRight)	= true;
	d2.pressed(bksge::MouseButton::kMiddle)	= true;
	d2.pressed(bksge::MouseButton::k3)		= true;
	d2.pressed(bksge::MouseButton::k4)		= true;
	d2.velocity(bksge::MouseAxis::kX)		= 0;
	d2.velocity(bksge::MouseAxis::kY)		= 1;
	d2.velocity(bksge::MouseAxis::kWheel)	= 2;
	d2.velocity(bksge::MouseAxis::kTilt)	= 3;

	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k7));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kTilt));

	d = d2;

	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k7));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 1.0f, d.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ( 2.0f, d.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 3.0f, d.velocity(bksge::MouseAxis::kTilt));

	// 自己代入
	d = d;
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k7));
	EXPECT_EQ( 0.0f, d.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 1.0f, d.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ( 2.0f, d.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 3.0f, d.velocity(bksge::MouseAxis::kTilt));

	// 多重代入
	bksge::MouseState d3;
	d3.pressed(bksge::MouseButton::kLeft)	= true;
	d3.pressed(bksge::MouseButton::kMiddle)	= true;
	d3.pressed(bksge::MouseButton::k5)		= true;
	d3.pressed(bksge::MouseButton::k7)		= true;
	d3.velocity(bksge::MouseAxis::kX)		= 4;
	d3.velocity(bksge::MouseAxis::kY)		= 5;
	d3.velocity(bksge::MouseAxis::kWheel)	= 6;
	d3.velocity(bksge::MouseAxis::kTilt)	= 7;

	d = d2 = d3;

	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(false, d.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(true,  d.pressed(bksge::MouseButton::k7));
	EXPECT_EQ( 4.0f, d.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 5.0f, d.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ( 6.0f, d.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 7.0f, d.velocity(bksge::MouseAxis::kTilt));

	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::kLeft));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::kRight));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::kMiddle));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k3));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k4));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k5));
	EXPECT_EQ(false, d2.pressed(bksge::MouseButton::k6));
	EXPECT_EQ(true,  d2.pressed(bksge::MouseButton::k7));
	EXPECT_EQ( 4.0f, d2.velocity(bksge::MouseAxis::kX));
	EXPECT_EQ( 5.0f, d2.velocity(bksge::MouseAxis::kY));
	EXPECT_EQ( 6.0f, d2.velocity(bksge::MouseAxis::kWheel));
	EXPECT_EQ( 7.0f, d2.velocity(bksge::MouseAxis::kTilt));
}

BKSGE_WARNING_POP()

GTEST_TEST(InputTest, MouseState_CompareTest)
{
	bksge::MouseState d01;
	bksge::MouseState d02;
	bksge::MouseState d03;
	bksge::MouseState d04;
	bksge::MouseState d05;
	bksge::MouseState d06;
	bksge::MouseState d07;
	bksge::MouseState d08;
	bksge::MouseState d09;
	bksge::MouseState d10;
	bksge::MouseState d11;
	bksge::MouseState d12;
	bksge::MouseState d13;
	bksge::MouseState d14;
	d03.pressed(bksge::MouseButton::kLeft)		= true;
	d04.pressed(bksge::MouseButton::kRight)		= true;
	d05.pressed(bksge::MouseButton::kMiddle)	= true;
	d06.pressed(bksge::MouseButton::k3)			= true;
	d07.pressed(bksge::MouseButton::k4)			= true;
	d08.pressed(bksge::MouseButton::k5)			= true;
	d09.pressed(bksge::MouseButton::k6)			= true;
	d10.pressed(bksge::MouseButton::k7)			= true;
	d11.velocity(bksge::MouseAxis::kX)			= 1;
	d12.velocity(bksge::MouseAxis::kY)			= 1;
	d13.velocity(bksge::MouseAxis::kWheel)		= 1;
	d14.velocity(bksge::MouseAxis::kTilt)		= 1;

	EXPECT_TRUE (d01 == d01);
	EXPECT_TRUE (d01 == d02);
	EXPECT_FALSE(d01 == d03);
	EXPECT_FALSE(d01 == d04);
	EXPECT_FALSE(d01 == d05);
	EXPECT_FALSE(d01 == d06);
	EXPECT_FALSE(d01 == d07);
	EXPECT_FALSE(d01 == d08);
	EXPECT_FALSE(d01 == d09);
	EXPECT_FALSE(d01 == d10);
	EXPECT_FALSE(d01 == d11);
	EXPECT_FALSE(d01 == d12);
	EXPECT_FALSE(d01 == d13);
	EXPECT_FALSE(d01 == d14);

	EXPECT_FALSE(d01 != d01);
	EXPECT_FALSE(d01 != d02);
	EXPECT_TRUE (d01 != d03);
	EXPECT_TRUE (d01 != d04);
	EXPECT_TRUE (d01 != d05);
	EXPECT_TRUE (d01 != d06);
	EXPECT_TRUE (d01 != d07);
	EXPECT_TRUE (d01 != d08);
	EXPECT_TRUE (d01 != d09);
	EXPECT_TRUE (d01 != d10);
	EXPECT_TRUE (d01 != d11);
	EXPECT_TRUE (d01 != d12);
	EXPECT_TRUE (d01 != d13);
	EXPECT_TRUE (d01 != d14);
}

// TODO
//GTEST_TEST(InputTest, MouseState_OutputStreamTest)
//{
//}

// TODO
//GTEST_TEST(InputTest, MouseState_SerializeTest)
//{
//}
