/**
 *	@file	unit_test_core_render_clear_state.cpp
 *
 *	@brief	ClearState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/clear_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_ClearState, DefaultCtorTest)
{
	bksge::ClearState const state;
	EXPECT_EQ(bksge::ClearFlag::kAll,  state.flag());
	EXPECT_EQ(bksge::Color4f(0,0,0,0), state.color());
	EXPECT_EQ(1.0f,                    state.depth());
	EXPECT_EQ(0u,                      state.stencil());
}

GTEST_TEST(Render_ClearState, SetFlagTest)
{
	bksge::ClearState state;
	EXPECT_EQ(bksge::ClearFlag::kAll, state.flag());

	state.SetFlag(bksge::ClearFlag::kColor);
	EXPECT_EQ(bksge::ClearFlag::kColor, state.flag());
}

GTEST_TEST(Render_ClearState, SetColorTest)
{
	bksge::ClearState state;
	EXPECT_EQ(bksge::Color4f(0,0,0,0), state.color());

	state.SetColor({1,2,3,4});
	EXPECT_EQ(bksge::Color4f(1,2,3,4), state.color());
}

GTEST_TEST(Render_ClearState, SetDepthTest)
{
	bksge::ClearState state;
	EXPECT_EQ(1.0f, state.depth());

	state.SetDepth(0.5f);
	EXPECT_EQ(0.5f, state.depth());
}

GTEST_TEST(Render_ClearState, SetStencilTest)
{
	bksge::ClearState state;
	EXPECT_EQ(0u, state.stencil());

	state.SetStencil(2);
	EXPECT_EQ(2u, state.stencil());
}
