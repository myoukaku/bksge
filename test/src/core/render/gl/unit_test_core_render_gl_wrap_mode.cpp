/**
 *	@file	unit_test_core_render_gl_wrap_mode.cpp
 *
 *	@brief	WrapMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/gl/detail/wrap_mode.hpp>
#include <bksge/core/render/wrap_mode.hpp>
#include <bksge/core/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlWrapModeTest)
{
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ(GL_REPEAT,          bksge::render::gl::WrapMode(bksge::WrapMode::kRepeat));
	EXPECT_EQ(GL_CLAMP_TO_EDGE,   bksge::render::gl::WrapMode(bksge::WrapMode::kClamp));
	EXPECT_EQ(GL_CLAMP_TO_BORDER, bksge::render::gl::WrapMode(bksge::WrapMode::kBorder));
#endif
}
