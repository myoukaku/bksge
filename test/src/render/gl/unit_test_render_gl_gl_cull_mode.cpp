/**
 *	@file	unit_test_render_gl_gl_cull_mode.cpp
 *
 *	@brief	ToGlCullMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/gl_cull_mode.hpp>
#include <bksge/render/cull_mode.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, ToGlCullModeTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_BACK,  ToGlCullMode(bksge::CullMode::kBack));
	EXPECT_EQ((GLenum)GL_FRONT, ToGlCullMode(bksge::CullMode::kFront));
#endif
}
