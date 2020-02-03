/**
 *	@file	unit_test_core_render_render_pass_info.cpp
 *
 *	@brief		RenderPassInfo のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/render_pass_info.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_RenderPassInfo, DefaultCtorTest)
{
	bksge::RenderPassInfo const state;

	EXPECT_EQ(bksge::ClearFlag::kAll,		state.clear_state().flag());
	EXPECT_EQ(bksge::Color4f(0, 0, 0, 0),	state.clear_state().color());
	EXPECT_EQ(1.0f,							state.clear_state().depth());
	EXPECT_EQ(0,							state.clear_state().stencil());

	EXPECT_EQ(false,			state.scissor_state().enable());
	EXPECT_EQ(bksge::Rectf(),	state.scissor_state().rect());

	EXPECT_EQ(bksge::Rectf(),	state.viewport().rect());
	EXPECT_EQ(0.0f,				state.viewport().min_depth());
	EXPECT_EQ(1.0f,				state.viewport().max_depth());
}

GTEST_TEST(Render_RenderPassInfo, SetValueTest)
{
	bksge::RenderPassInfo state;

	state.clear_state().SetFlag(bksge::ClearFlag::kDepth);
	state.clear_state().SetColor({1,2,3,4});
	state.clear_state().SetDepth(5.0f);
	state.clear_state().SetStencil(10);

	state.scissor_state().SetEnable(true);
	state.scissor_state().SetRect(
		bksge::Rectf(bksge::Vector2f{1, 2}, bksge::Extent2f{30, 20}));

	state.viewport().SetRect(
		bksge::Rectf(bksge::Vector2f{-10, 10}, bksge::Extent2f{5, 4}));
	state.viewport().SetMinDepth(10);
	state.viewport().SetMaxDepth(20);

	EXPECT_EQ(bksge::ClearFlag::kDepth,		state.clear_state().flag());
	EXPECT_EQ(bksge::Color4f(1, 2, 3, 4),	state.clear_state().color());
	EXPECT_EQ(5.0f,							state.clear_state().depth());
	EXPECT_EQ(10,							state.clear_state().stencil());

	EXPECT_EQ(true, state.scissor_state().enable());
	EXPECT_EQ(bksge::Rectf(bksge::Vector2f{1, 2}, bksge::Extent2f{30, 20}),
		state.scissor_state().rect());

	EXPECT_EQ(bksge::Rectf(bksge::Vector2f{-10, 10}, bksge::Extent2f{5, 4}),
		state.viewport().rect());
	EXPECT_EQ(10.0f, state.viewport().min_depth());
	EXPECT_EQ(20.0f, state.viewport().max_depth());
}
