/**
 *	@file	unit_test_core_render_gl_primitive.cpp
 *
 *	@brief	Primitive のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/gl/detail/primitive.hpp>
#include <bksge/core/render/primitive.hpp>
#include <bksge/core/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlPrimitiveTest)
{
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_POINTS,    bksge::render::gl::Primitive(bksge::Primitive::kPoints));
	EXPECT_EQ((GLenum)GL_LINES,     bksge::render::gl::Primitive(bksge::Primitive::kLines));
	EXPECT_EQ((GLenum)GL_TRIANGLES, bksge::render::gl::Primitive(bksge::Primitive::kTriangles));
#endif
}
