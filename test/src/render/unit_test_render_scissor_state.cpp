/**
 *	@file	unit_test_render_scissor_state.cpp
 *
 *	@brief	ScissorState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/scissor_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_ScissorState, DefaultCtorTest)
{
	bksge::ScissorState const state;
	EXPECT_EQ(false,            state.enable());
	EXPECT_EQ(bksge::Rectf(),	state.rect());
}

GTEST_TEST(Render_ScissorState, SetEnableTest)
{
	bksge::ScissorState state;
	EXPECT_EQ(false, state.enable());

	state.SetEnable(true);
	EXPECT_EQ(true, state.enable());
}

GTEST_TEST(Render_ScissorState, SetRectTest)
{
	bksge::ScissorState state;
	EXPECT_EQ(bksge::Rectf(), state.rect());

	state.SetRect({bksge::Vector2f(2, 3), bksge::Size2f(20, 10)});
	EXPECT_EQ(bksge::Rectf(bksge::Vector2f(2, 3), bksge::Size2f(20, 10)), state.rect());
}
