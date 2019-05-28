/**
 *	@file	unit_test_render_gl_gl_fill_mode.cpp
 *
 *	@brief	ToGlFillMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/gl_fill_mode.hpp>
#include <bksge/render/fill_mode.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, ToGlFillModeTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_FILL, ToGlFillMode(bksge::FillMode::kSolid));
	EXPECT_EQ((GLenum)GL_LINE, ToGlFillMode(bksge::FillMode::kWireframe));
#endif
}
