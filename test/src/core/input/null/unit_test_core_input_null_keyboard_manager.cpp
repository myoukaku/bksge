/**
 *	@file	unit_test_core_input_null_keyboard_manager.cpp
 *
 *	@brief	NullKeyboardManagerのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/input/null/null_keyboard_manager.hpp>
#include <gtest/gtest.h>

GTEST_TEST(InputTest, NullKeyboardManagerTest)
{
	bksge::input::NullKeyboardManager man;

	man.Update();

	auto const state = man.state(0u);
	EXPECT_TRUE(state == bksge::KeyboardState());
}
