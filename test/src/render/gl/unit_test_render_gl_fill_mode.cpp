/**
 *	@file	unit_test_render_gl_fill_mode.cpp
 *
 *	@brief	FillMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/detail/fill_mode.hpp>
#include <bksge/render/fill_mode.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlFillModeTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_FILL, bksge::render::gl::FillMode(bksge::FillMode::kSolid));
	EXPECT_EQ((GLenum)GL_LINE, bksge::render::gl::FillMode(bksge::FillMode::kWireframe));
#endif
}
