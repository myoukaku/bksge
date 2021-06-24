/**
 *	@file	unit_test_core_render_gl_fill_mode.cpp
 *
 *	@brief	FillMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/gl/detail/fill_mode.hpp>
#include <bksge/core/render/fill_mode.hpp>
#include <bksge/core/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlFillModeTest)
{
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_FILL, bksge::render::gl::FillMode(bksge::FillMode::kSolid));
	EXPECT_EQ((GLenum)GL_LINE, bksge::render::gl::FillMode(bksge::FillMode::kWireframe));
#endif
}
