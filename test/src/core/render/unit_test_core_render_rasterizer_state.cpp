/**
 *	@file	unit_test_core_render_rasterizer_state.cpp
 *
 *	@brief	RasterizerState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/rasterizer_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_RasterizerState, DefaultCtorTest)
{
	bksge::RasterizerState const state;
	EXPECT_EQ(bksge::FillMode::kSolid, state.fill_mode());
	EXPECT_EQ(bksge::CullMode::kNone, state.cull_mode());
	EXPECT_EQ(bksge::FrontFace::kClockwise, state.front_face());
}

GTEST_TEST(Render_RasterizerState, SetFillModeTest)
{
	bksge::RasterizerState state;
	EXPECT_EQ(bksge::FillMode::kSolid, state.fill_mode());

	state.SetFillMode(bksge::FillMode::kWireframe);
	EXPECT_EQ(bksge::FillMode::kWireframe, state.fill_mode());
}

GTEST_TEST(Render_RasterizerState, SetCullModeTest)
{
	bksge::RasterizerState state;
	EXPECT_EQ(bksge::CullMode::kNone, state.cull_mode());

	state.SetCullMode(bksge::CullMode::kBack);
	EXPECT_EQ(bksge::CullMode::kBack, state.cull_mode());
}

GTEST_TEST(Render_RasterizerState, SetFrontFaceTest)
{
	bksge::RasterizerState state;
	EXPECT_EQ(bksge::FrontFace::kClockwise, state.front_face());

	state.SetFrontFace(bksge::FrontFace::kCounterClockwise);
	EXPECT_EQ(bksge::FrontFace::kCounterClockwise, state.front_face());
}
