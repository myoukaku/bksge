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
	bksge::DepthState const depth_state;
	EXPECT_EQ(false,                            depth_state.enable());
	EXPECT_EQ(false,                            depth_state.write());
	EXPECT_EQ(bksge::ComparisonFunction::kLess, depth_state.func());
}

GTEST_TEST(Render_DepthState, SetEnableTest)
{
	bksge::DepthState depth_state;
	EXPECT_EQ(false, depth_state.enable());

	depth_state.SetEnable(true);
	EXPECT_EQ(true, depth_state.enable());
}

GTEST_TEST(Render_DepthState, SetWriteTest)
{
	bksge::DepthState depth_state;
	EXPECT_EQ(false, depth_state.write());

	depth_state.SetWrite(true);
	EXPECT_EQ(true, depth_state.write());
}

GTEST_TEST(Render_DepthState, SetFuncTest)
{
	bksge::DepthState depth_state;
	EXPECT_EQ(bksge::ComparisonFunction::kLess, depth_state.func());

	depth_state.SetFunc(
		bksge::ComparisonFunction::kGreater);
	EXPECT_EQ(bksge::ComparisonFunction::kGreater, depth_state.func());
}
