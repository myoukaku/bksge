/**
 *	@file	unit_test_render_gl_gl_wrap_mode.cpp
 *
 *	@brief	ToGlWrapMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/gl_wrap_mode.hpp>
#include <bksge/render/wrap_mode.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, ToGlWrapModeTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ(GL_REPEAT,          ToGlWrapMode(bksge::WrapMode::kRepeat));
	EXPECT_EQ(GL_CLAMP_TO_EDGE,   ToGlWrapMode(bksge::WrapMode::kClamp));
	EXPECT_EQ(GL_CLAMP_TO_BORDER, ToGlWrapMode(bksge::WrapMode::kBorder));
#endif
}
