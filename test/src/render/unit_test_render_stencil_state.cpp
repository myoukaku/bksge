/**
 *	@file	unit_test_render_stencil_state.cpp
 *
 *	@brief	StencilState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/stencil_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_StencilState, DefaultCtorTest)
{
	bksge::StencilState const state;
	EXPECT_EQ(false,                             state.enable());
	EXPECT_EQ(0u,                                state.read_mask());
	EXPECT_EQ(0u,                                state.write_mask());
	EXPECT_EQ(bksge::ComparisonFunction::kNever, state.func());
	EXPECT_EQ(bksge::StencilOperation::kKeep,    state.fail_operation());
	EXPECT_EQ(bksge::StencilOperation::kKeep,    state.depth_fail_operation());
	EXPECT_EQ(bksge::StencilOperation::kKeep,    state.pass_operation());
}

GTEST_TEST(Render_StencilState, SetEnableTest)
{
	bksge::StencilState state;
	EXPECT_EQ(false, state.enable());

	state.SetEnable(true);
	EXPECT_EQ(true, state.enable());
}

GTEST_TEST(Render_StencilState, SetReadMaskTest)
{
	bksge::StencilState state;
	EXPECT_EQ(0u, state.read_mask());

	state.SetReadMask(1u);
	EXPECT_EQ(1u, state.read_mask());
}

GTEST_TEST(Render_StencilState, SetWriteMaskTest)
{
	bksge::StencilState state;
	EXPECT_EQ(0u, state.write_mask());

	state.SetWriteMask(2u);
	EXPECT_EQ(2u, state.write_mask());
}

GTEST_TEST(Render_StencilState, SetFuncTest)
{
	bksge::StencilState state;
	EXPECT_EQ(bksge::ComparisonFunction::kNever, state.func());

	state.SetFunc(bksge::ComparisonFunction::kLessEqual);
	EXPECT_EQ(bksge::ComparisonFunction::kLessEqual, state.func());
}

GTEST_TEST(Render_StencilState, SetFailOperationTest)
{
	bksge::StencilState state;
	EXPECT_EQ(bksge::StencilOperation::kKeep, state.fail_operation());

	state.SetFailOperation(bksge::StencilOperation::kIncr);
	EXPECT_EQ(bksge::StencilOperation::kIncr, state.fail_operation());
}

GTEST_TEST(Render_StencilState, SetDepthFailOperationTest)
{
	bksge::StencilState state;
	EXPECT_EQ(bksge::StencilOperation::kKeep, state.depth_fail_operation());

	state.SetDepthFailOperation(bksge::StencilOperation::kDecr);
	EXPECT_EQ(bksge::StencilOperation::kDecr, state.depth_fail_operation());
}

GTEST_TEST(Render_StencilState, SetPassOperationTest)
{
	bksge::StencilState state;
	EXPECT_EQ(bksge::StencilOperation::kKeep, state.pass_operation());

	state.SetPassOperation(bksge::StencilOperation::kReplace);
	EXPECT_EQ(bksge::StencilOperation::kReplace, state.pass_operation());
}
