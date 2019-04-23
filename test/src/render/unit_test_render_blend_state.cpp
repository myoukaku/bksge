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
	bksge::BlendState const blend_state;
	EXPECT_EQ(false,                       blend_state.enable());
	EXPECT_EQ(bksge::BlendOperation::kAdd, blend_state.operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    blend_state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   blend_state.dst_factor());
	EXPECT_EQ(bksge::BlendOperation::kAdd, blend_state.alpha_operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    blend_state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   blend_state.alpha_dst_factor());
}

GTEST_TEST(Render_BlendState, SetEnableTest)
{
	bksge::BlendState blend_state;
	EXPECT_EQ(false, blend_state.enable());

	blend_state.SetEnable(true);
	EXPECT_EQ(true, blend_state.enable());
}

GTEST_TEST(Render_BlendState, SetOperationTest)
{
	bksge::BlendState blend_state;
	EXPECT_EQ(bksge::BlendOperation::kAdd, blend_state.operation());
	EXPECT_EQ(bksge::BlendOperation::kAdd, blend_state.alpha_operation());

	blend_state.SetOperation(bksge::BlendOperation::kSubtract);
	EXPECT_EQ(bksge::BlendOperation::kSubtract, blend_state.operation());
	EXPECT_EQ(bksge::BlendOperation::kSubtract, blend_state.alpha_operation());

	blend_state.SetOperation(
		bksge::BlendOperation::kMin,
		bksge::BlendOperation::kMax);
	EXPECT_EQ(bksge::BlendOperation::kMin, blend_state.operation());
	EXPECT_EQ(bksge::BlendOperation::kMax, blend_state.alpha_operation());
}

GTEST_TEST(Render_BlendState, SetFactorTest)
{
	bksge::BlendState blend_state;
	EXPECT_EQ(bksge::BlendFactor::kOne,    blend_state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   blend_state.dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kOne,    blend_state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   blend_state.alpha_dst_factor());

	blend_state.SetFactor(
		bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,    blend_state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,   blend_state.dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,    blend_state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,   blend_state.alpha_dst_factor());

	blend_state.SetFactor(
		bksge::BlendFactor::kInvSrcColor, bksge::BlendFactor::kInvDestColor,
		bksge::BlendFactor::kDestAlpha, bksge::BlendFactor::kSrcAlpha);
	EXPECT_EQ(bksge::BlendFactor::kInvSrcColor,  blend_state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kInvDestColor, blend_state.dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestAlpha,	 blend_state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcAlpha,	 blend_state.alpha_dst_factor());
}
