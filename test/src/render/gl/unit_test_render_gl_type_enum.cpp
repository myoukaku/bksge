/**
 *	@file	unit_test_render_gl_type_enum.cpp
 *
 *	@brief	TypeEnum のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/detail/type_enum.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlTypeEnumTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_BYTE,           bksge::render::gl::TypeEnum(bksge::TypeEnum::kSInt8));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  bksge::render::gl::TypeEnum(bksge::TypeEnum::kUInt8));
	EXPECT_EQ((GLenum)GL_SHORT,          bksge::render::gl::TypeEnum(bksge::TypeEnum::kSInt16));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, bksge::render::gl::TypeEnum(bksge::TypeEnum::kUInt16));
	EXPECT_EQ((GLenum)GL_INT,            bksge::render::gl::TypeEnum(bksge::TypeEnum::kSInt32));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   bksge::render::gl::TypeEnum(bksge::TypeEnum::kUInt32));
	EXPECT_EQ((GLenum)GL_FLOAT,          bksge::render::gl::TypeEnum(bksge::TypeEnum::kFloat));
#endif
}
