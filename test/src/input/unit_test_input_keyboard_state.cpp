/**
 *	@file	unit_test_input_keyboard_state.cpp
 *
 *	@brief	KeyboardStateのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/input/keyboard_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(InputTest, KeyboardState_ConstructTest)
{
	// デフォルトコンストラクタ
	bksge::KeyboardState s;

	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kLeft));

	s.pressed(bksge::KeyCode::k0)		= true;
	s.pressed(bksge::KeyCode::kA)		= true;

	// コピーコンストラクタ
	bksge::KeyboardState s2(s);
	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(true,  s2.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(true,  s2.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::kLeft));

	// KeyboardStateはディープコピーされるので、sを変更してもs2には影響がない
	s.pressed(bksge::KeyCode::k0)		= false;
	s.pressed(bksge::KeyCode::kLeft)	= true;

	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kLeft));

	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(true,  s2.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(true,  s2.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::kLeft));

	// 同様にs2を変更してもsには影響がない
	s2.pressed(bksge::KeyCode::kEscape)	= true;
	s2.pressed(bksge::KeyCode::kA)		= false;

	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kLeft));

	EXPECT_EQ(true,  s2.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(true,  s2.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::kLeft));
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

GTEST_TEST(InputTest, KeyboardState_AssignTest)
{
	bksge::KeyboardState s;

	bksge::KeyboardState s2;
	s2.pressed(bksge::KeyCode::k1)		= true;
	s2.pressed(bksge::KeyCode::kB)		= true;
	s2.pressed(bksge::KeyCode::kRight)	= true;

	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::k1));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kB));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kLeft));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kRight));

	s = s2;

	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::k1));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kB));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kLeft));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kRight));

	// 自己代入
	s = s;
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::k1));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kB));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kLeft));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kRight));

	// 多重代入
	bksge::KeyboardState s3;
	s3.pressed(bksge::KeyCode::kEscape)	= true;
	s3.pressed(bksge::KeyCode::k0)		= true;
	s3.pressed(bksge::KeyCode::kLeft)	= true;

	s = s2 = s3;

	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::k1));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kB));
	EXPECT_EQ(true,  s.pressed(bksge::KeyCode::kLeft));
	EXPECT_EQ(false, s.pressed(bksge::KeyCode::kRight));

	EXPECT_EQ(true,  s2.pressed(bksge::KeyCode::kEscape));
	EXPECT_EQ(true,  s2.pressed(bksge::KeyCode::k0));
	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::k1));
	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::kA));
	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::kB));
	EXPECT_EQ(true,  s2.pressed(bksge::KeyCode::kLeft));
	EXPECT_EQ(false, s2.pressed(bksge::KeyCode::kRight));
}

BKSGE_WARNING_POP()

GTEST_TEST(InputTest, KeyboardState_CompareTest)
{
	bksge::KeyboardState s1;
	bksge::KeyboardState s2;
	bksge::KeyboardState s3;
	bksge::KeyboardState s4;
	bksge::KeyboardState s5;
	bksge::KeyboardState s6;
	s3.pressed(bksge::KeyCode::kEscape)	= true;
	s4.pressed(bksge::KeyCode::kQ)		= true;
	s5.pressed(bksge::KeyCode::kF1)		= true;
	s6.pressed(bksge::KeyCode::kColon)	= true;

	EXPECT_TRUE (s1 == s1);
	EXPECT_TRUE (s1 == s2);
	EXPECT_FALSE(s1 == s3);
	EXPECT_FALSE(s1 == s4);
	EXPECT_FALSE(s1 == s5);
	EXPECT_FALSE(s1 == s6);

	EXPECT_FALSE(s1 != s1);
	EXPECT_FALSE(s1 != s2);
	EXPECT_TRUE (s1 != s3);
	EXPECT_TRUE (s1 != s4);
	EXPECT_TRUE (s1 != s5);
	EXPECT_TRUE (s1 != s6);
}

// TODO
//GTEST_TEST(InputTest, KeyboardState_OutputStreamTest)
//{
//}

// TODO
//GTEST_TEST(InputTest, KeyboardState_SerializeTest)
//{
//}
