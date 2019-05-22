/**
 *	@file	unit_test_render_gl_gl_type_enum.cpp
 *
 *	@brief	ToGlTypeEnum のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/gl_type_enum.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, ToGlTypeEnumTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_BYTE,           ToGlTypeEnum(bksge::TypeEnum::kByte));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlTypeEnum(bksge::TypeEnum::kUnsignedByte));
	EXPECT_EQ((GLenum)GL_SHORT,          ToGlTypeEnum(bksge::TypeEnum::kShort));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, ToGlTypeEnum(bksge::TypeEnum::kUnsignedShort));
	EXPECT_EQ((GLenum)GL_INT,            ToGlTypeEnum(bksge::TypeEnum::kInt));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   ToGlTypeEnum(bksge::TypeEnum::kUnsignedInt));
	EXPECT_EQ((GLenum)GL_FLOAT,          ToGlTypeEnum(bksge::TypeEnum::kFloat));
#endif
}
