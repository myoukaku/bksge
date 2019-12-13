/**
 *	@file	unit_test_core_input_null_mouse_manager.cpp
 *
 *	@brief	NullMouseManagerのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/input/null/null_mouse_manager.hpp>
#include <gtest/gtest.h>

GTEST_TEST(InputTest, NullMouseManagerTest)
{
	bksge::input::NullMouseManager man;

	man.Update();

	auto const state = man.state(0u);
	EXPECT_TRUE(state == bksge::MouseState());
}
