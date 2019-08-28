/**
 *	@file	unit_test_render_gl_cull_mode.cpp
 *
 *	@brief	CullMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/detail/cull_mode.hpp>
#include <bksge/render/cull_mode.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlCullModeTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_BACK,  bksge::render::gl::CullMode(bksge::CullMode::kBack));
	EXPECT_EQ((GLenum)GL_FRONT, bksge::render::gl::CullMode(bksge::CullMode::kFront));
#endif
}
