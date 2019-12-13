/**
 *	@file	unit_test_core_input_null_game_pad_manager.cpp
 *
 *	@brief	NullGamePadManagerのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/input/null/null_game_pad_manager.hpp>
#include <gtest/gtest.h>

GTEST_TEST(InputTest, NullGamePadManagerTest)
{
	bksge::input::NullGamePadManager man;

	man.Update();

	auto const state = man.state(0u);
	EXPECT_TRUE(state == bksge::GamePadState());
}
