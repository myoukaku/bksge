/**
 *	@file	unit_test_render_depth_state.cpp
 *
 *	@brief	DepthState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/depth_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_DepthState, DefaultCtorTest)
{
	bksge::DepthState const state;
	EXPECT_EQ(false,                            state.enable());
	EXPECT_EQ(false,                            state.write());
	EXPECT_EQ(bksge::ComparisonFunction::kLess, state.func());
}

GTEST_TEST(Render_DepthState, SetEnableTest)
{
	bksge::DepthState state;
	EXPECT_EQ(false, state.enable());

	state.SetEnable(true);
	EXPECT_EQ(true, state.enable());
}

GTEST_TEST(Render_DepthState, SetWriteTest)
{
	bksge::DepthState state;
	EXPECT_EQ(false, state.write());

	state.SetWrite(true);
	EXPECT_EQ(true, state.write());
}

GTEST_TEST(Render_DepthState, SetFuncTest)
{
	bksge::DepthState state;
	EXPECT_EQ(bksge::ComparisonFunction::kLess, state.func());

	state.SetFunc(
		bksge::ComparisonFunction::kGreater);
	EXPECT_EQ(bksge::ComparisonFunction::kGreater, state.func());
}
