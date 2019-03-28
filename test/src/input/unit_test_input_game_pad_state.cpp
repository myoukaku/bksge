/**
 *	@file	unit_test_input_game_pad_state.cpp
 *
 *	@brief	GamePadStateのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/input/game_pad_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(InputTest, GamePadState_ConstructTest)
{
	// デフォルトコンストラクタ
	bksge::GamePadState s;

	EXPECT_EQ(false, s.pressed(0));
	EXPECT_EQ(false, s.pressed(1));
	EXPECT_EQ(false, s.pressed(2));
	EXPECT_EQ(false, s.pressed(3));
	EXPECT_EQ(false, s.pressed(4));
	EXPECT_EQ(false, s.pressed(5));
	EXPECT_EQ(0.0f, s.analog_button(0));
	EXPECT_EQ(0.0f, s.analog_button(1));
	EXPECT_EQ(bksge::Vector2f(0, 0), s.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f(0, 0), s.analog_stick(1));

	s.pressed(1)		= true;
	s.pressed(4)		= true;
	s.analog_button(0)	= 0.5f;
	s.analog_stick(0)	= bksge::Vector2f(1, -1);

	// コピーコンストラクタ
	bksge::GamePadState s2(s);
	EXPECT_EQ(false, s2.pressed(0));
	EXPECT_EQ(true,  s2.pressed(1));
	EXPECT_EQ(false, s2.pressed(2));
	EXPECT_EQ(false, s2.pressed(3));
	EXPECT_EQ(true,  s2.pressed(4));
	EXPECT_EQ(false, s2.pressed(5));
	EXPECT_EQ(0.5f, s.analog_button(0));
	EXPECT_EQ(0.0f, s.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 1, -1), s.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s.analog_stick(1));

	// GamePadStateはディープコピーされるので、sを変更してもs2には影響がない
	s.pressed(1)		= false;
	s.pressed(2)		= true;
	s.analog_button(1)	= 1.0f;
	s.analog_stick(0)	= bksge::Vector2f(2, 3);

	EXPECT_EQ(false, s.pressed(0));
	EXPECT_EQ(false, s.pressed(1));
	EXPECT_EQ(true,  s.pressed(2));
	EXPECT_EQ(false, s.pressed(3));
	EXPECT_EQ(true,  s.pressed(4));
	EXPECT_EQ(false, s.pressed(5));
	EXPECT_EQ(0.5f, s.analog_button(0));
	EXPECT_EQ(1.0f, s.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 2,  3), s.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s.analog_stick(1));

	EXPECT_EQ(false, s2.pressed(0));
	EXPECT_EQ(true,  s2.pressed(1));
	EXPECT_EQ(false, s2.pressed(2));
	EXPECT_EQ(false, s2.pressed(3));
	EXPECT_EQ(true,  s2.pressed(4));
	EXPECT_EQ(false, s2.pressed(5));
	EXPECT_EQ(0.5f, s2.analog_button(0));
	EXPECT_EQ(0.0f, s2.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 1, -1), s2.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s2.analog_stick(1));

	// 同様にs2を変更してもsには影響がない
	s2.pressed(3)		= true;
	s2.pressed(4)	    = false;
	s2.analog_button(0)	= 2.0f;
	s2.analog_stick(1)	= bksge::Vector2f(4, 5);

	EXPECT_EQ(false, s.pressed(0));
	EXPECT_EQ(false, s.pressed(1));
	EXPECT_EQ(true,  s.pressed(2));
	EXPECT_EQ(false, s.pressed(3));
	EXPECT_EQ(true,  s.pressed(4));
	EXPECT_EQ(false, s.pressed(5));
	EXPECT_EQ(0.5f, s.analog_button(0));
	EXPECT_EQ(1.0f, s.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 2,  3), s.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s.analog_stick(1));

	EXPECT_EQ(false, s2.pressed(0));
	EXPECT_EQ(true,  s2.pressed(1));
	EXPECT_EQ(false, s2.pressed(2));
	EXPECT_EQ(true,  s2.pressed(3));
	EXPECT_EQ(false, s2.pressed(4));
	EXPECT_EQ(false, s2.pressed(5));
	EXPECT_EQ(2.0f, s2.analog_button(0));
	EXPECT_EQ(0.0f, s2.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 1, -1), s2.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 4,  5), s2.analog_stick(1));
}

GTEST_TEST(InputTest, GamePadState_AssignTest)
{
	bksge::GamePadState s;

	bksge::GamePadState s2;
	s2.pressed(6)		= true;
	s2.pressed(7)		= true;
	s2.pressed(8)		= true;
	s2.analog_button(0)	= 1.0f;
	s2.analog_stick(1)	= bksge::Vector2f(1, 2);

	EXPECT_EQ(false, s.pressed(9));
	EXPECT_EQ(false, s.pressed(6));
	EXPECT_EQ(false, s.pressed(10));
	EXPECT_EQ(false, s.pressed(7));
	EXPECT_EQ(false, s.pressed(11));
	EXPECT_EQ(false, s.pressed(8));
	EXPECT_EQ(0.0f, s.analog_button(0));
	EXPECT_EQ(0.0f, s.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s.analog_stick(1));

	s = s2;

	EXPECT_EQ(false, s.pressed(9));
	EXPECT_EQ(true,  s.pressed(6));
	EXPECT_EQ(false, s.pressed(10));
	EXPECT_EQ(true,  s.pressed(7));
	EXPECT_EQ(false, s.pressed(11));
	EXPECT_EQ(true,  s.pressed(8));
	EXPECT_EQ(1.0f, s.analog_button(0));
	EXPECT_EQ(0.0f, s.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 1,  2), s.analog_stick(1));

	// 自己代入
	s = s;
	EXPECT_EQ(false, s.pressed(9));
	EXPECT_EQ(true,  s.pressed(6));
	EXPECT_EQ(false, s.pressed(10));
	EXPECT_EQ(true,  s.pressed(7));
	EXPECT_EQ(false, s.pressed(11));
	EXPECT_EQ(true,  s.pressed(8));
	EXPECT_EQ(1.0f, s.analog_button(0));
	EXPECT_EQ(0.0f, s.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 1,  2), s.analog_stick(1));

	// 多重代入
	bksge::GamePadState s3;
	s3.pressed(9)		= true;
	s3.pressed(6)		= true;
	s3.pressed(10)		= true;
	s3.analog_button(0)	= 2.0f;
	s3.analog_stick(0)	= bksge::Vector2f(3, 4);

	s = s2 = s3;

	EXPECT_EQ(true,  s.pressed(9));
	EXPECT_EQ(true,  s.pressed(6));
	EXPECT_EQ(true,  s.pressed(10));
	EXPECT_EQ(false, s.pressed(7));
	EXPECT_EQ(false, s.pressed(11));
	EXPECT_EQ(false, s.pressed(8));
	EXPECT_EQ(2.0f, s.analog_button(0));
	EXPECT_EQ(0.0f, s.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 3,  4), s.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s.analog_stick(1));

	EXPECT_EQ(true,  s2.pressed(9));
	EXPECT_EQ(true,  s2.pressed(6));
	EXPECT_EQ(true,  s2.pressed(10));
	EXPECT_EQ(false, s2.pressed(7));
	EXPECT_EQ(false, s2.pressed(11));
	EXPECT_EQ(false, s2.pressed(8));
	EXPECT_EQ(2.0f, s2.analog_button(0));
	EXPECT_EQ(0.0f, s2.analog_button(1));
	EXPECT_EQ(bksge::Vector2f( 3,  4), s2.analog_stick(0));
	EXPECT_EQ(bksge::Vector2f( 0,  0), s2.analog_stick(1));
}

GTEST_TEST(InputTest, GamePadState_CompareTest)
{
	bksge::GamePadState s1;
	bksge::GamePadState s2;
	bksge::GamePadState s3;
	bksge::GamePadState s4;
	bksge::GamePadState s5;
	bksge::GamePadState s6;
	bksge::GamePadState s7;
	bksge::GamePadState s8;
	s3.pressed(0)		= true;
	s4.pressed(6)		= true;
	s5.pressed(10)		= true;
	s6.pressed(12)		= true;
	s7.analog_button(0)	= 1.0f;
	s8.analog_stick(0)	= bksge::Vector2f(0, 1);

	EXPECT_TRUE (s1 == s1);
	EXPECT_TRUE (s1 == s2);
	EXPECT_FALSE(s1 == s3);
	EXPECT_FALSE(s1 == s4);
	EXPECT_FALSE(s1 == s5);
	EXPECT_FALSE(s1 == s6);
	EXPECT_FALSE(s1 == s7);
	EXPECT_FALSE(s1 == s8);

	EXPECT_FALSE(s1 != s1);
	EXPECT_FALSE(s1 != s2);
	EXPECT_TRUE (s1 != s3);
	EXPECT_TRUE (s1 != s4);
	EXPECT_TRUE (s1 != s5);
	EXPECT_TRUE (s1 != s6);
	EXPECT_TRUE (s1 != s7);
	EXPECT_TRUE (s1 != s8);
}

// TODO
//GTEST_TEST(InputTest, GamePadState_OutputStreamTest)
//{
//}

// TODO
//GTEST_TEST(InputTest, GamePadState_SerializeTest)
//{
//}
