/**
 *	@file	unit_test_render_gl_gl_primitive.cpp
 *
 *	@brief	ToGlPrimitive のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/gl_primitive.hpp>
#include <bksge/render/primitive.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, ToGlPrimitiveTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_POINTS,    ToGlPrimitive(bksge::Primitive::kPoints));
	EXPECT_EQ((GLenum)GL_LINES,     ToGlPrimitive(bksge::Primitive::kLines));
	EXPECT_EQ((GLenum)GL_TRIANGLES, ToGlPrimitive(bksge::Primitive::kTriangles));
#endif
}
