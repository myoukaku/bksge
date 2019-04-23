/**
 *	@file	unit_test_render_blend_state.cpp
 *
 *	@brief	BlendState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/blend_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_BlendState, DefaultCtorTest)
{
	bksge::BlendState const state;
	EXPECT_EQ(false,                       state.enable());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.dst_factor());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.alpha_operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.alpha_dst_factor());
}

GTEST_TEST(Render_BlendState, SetEnableTest)
{
	bksge::BlendState state;
	EXPECT_EQ(false, state.enable());

	state.SetEnable(true);
	EXPECT_EQ(true, state.enable());
}

GTEST_TEST(Render_BlendState, SetOperationTest)
{
	bksge::BlendState state;
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.operation());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.alpha_operation());

	state.SetOperation(bksge::BlendOperation::kSubtract);
	EXPECT_EQ(bksge::BlendOperation::kSubtract, state.operation());
	EXPECT_EQ(bksge::BlendOperation::kSubtract, state.alpha_operation());

	state.SetOperation(
		bksge::BlendOperation::kMin,
		bksge::BlendOperation::kMax);
	EXPECT_EQ(bksge::BlendOperation::kMin, state.operation());
	EXPECT_EQ(bksge::BlendOperation::kMax, state.alpha_operation());
}

GTEST_TEST(Render_BlendState, SetFactorTest)
{
	bksge::BlendState state;
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.alpha_dst_factor());

	state.SetFactor(
		bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,    state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,   state.dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,    state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,   state.alpha_dst_factor());

	state.SetFactor(
		bksge::BlendFactor::kInvSrcColor, bksge::BlendFactor::kInvDestColor,
		bksge::BlendFactor::kDestAlpha, bksge::BlendFactor::kSrcAlpha);
	EXPECT_EQ(bksge::BlendFactor::kInvSrcColor,  state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kInvDestColor, state.dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestAlpha,	 state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcAlpha,	 state.alpha_dst_factor());
}
