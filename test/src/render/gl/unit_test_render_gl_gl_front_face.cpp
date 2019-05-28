/**
 *	@file	unit_test_render_gl_gl_front_face.cpp
 *
 *	@brief	ToGlFrontFace のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/gl_front_face.hpp>
#include <bksge/render/front_face.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, ToGlFrontFaceTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_CW,  ToGlFrontFace(bksge::FrontFace::kClockwise));
	EXPECT_EQ((GLenum)GL_CCW, ToGlFrontFace(bksge::FrontFace::kCounterClockwise));
#endif
}
