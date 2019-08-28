/**
 *	@file	unit_test_render_gl_front_face.cpp
 *
 *	@brief	FrontFace のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/detail/front_face.hpp>
#include <bksge/render/front_face.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlFrontFaceTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_CW,  bksge::render::gl::FrontFace(bksge::FrontFace::kClockwise));
	EXPECT_EQ((GLenum)GL_CCW, bksge::render::gl::FrontFace(bksge::FrontFace::kCounterClockwise));
#endif
}
