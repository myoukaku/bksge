/**
 *	@file	unit_test_render_gl_gl_pixel_format.cpp
 *
 *	@brief	ToGlPixelFormat のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/gl_pixel_format.hpp>
#include <bksge/render/texture_format.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, ToGlPixelFormatTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_RED,  ToGlPixelFormat(bksge::TextureFormat::kR_U8));
	EXPECT_EQ((GLenum)GL_RED,  ToGlPixelFormat(bksge::TextureFormat::kR_S8));
	EXPECT_EQ((GLenum)GL_RED,  ToGlPixelFormat(bksge::TextureFormat::kR_U16));
	EXPECT_EQ((GLenum)GL_RED,  ToGlPixelFormat(bksge::TextureFormat::kR_S16));
	EXPECT_EQ((GLenum)GL_RED,  ToGlPixelFormat(bksge::TextureFormat::kR_U32));
	EXPECT_EQ((GLenum)GL_RED,  ToGlPixelFormat(bksge::TextureFormat::kR_S32));
	EXPECT_EQ((GLenum)GL_RED,  ToGlPixelFormat(bksge::TextureFormat::kR_F32));
	EXPECT_EQ((GLenum)GL_RG,   ToGlPixelFormat(bksge::TextureFormat::kRG_U8));
	EXPECT_EQ((GLenum)GL_RG,   ToGlPixelFormat(bksge::TextureFormat::kRG_S8));
	EXPECT_EQ((GLenum)GL_RG,   ToGlPixelFormat(bksge::TextureFormat::kRG_U16));
	EXPECT_EQ((GLenum)GL_RG,   ToGlPixelFormat(bksge::TextureFormat::kRG_S16));
	EXPECT_EQ((GLenum)GL_RG,   ToGlPixelFormat(bksge::TextureFormat::kRG_U32));
	EXPECT_EQ((GLenum)GL_RG,   ToGlPixelFormat(bksge::TextureFormat::kRG_S32));
	EXPECT_EQ((GLenum)GL_RG,   ToGlPixelFormat(bksge::TextureFormat::kRG_F32));
	EXPECT_EQ((GLenum)GL_RGB,  ToGlPixelFormat(bksge::TextureFormat::kRGB_U8));
	EXPECT_EQ((GLenum)GL_RGB,  ToGlPixelFormat(bksge::TextureFormat::kRGB_S8));
	EXPECT_EQ((GLenum)GL_RGB,  ToGlPixelFormat(bksge::TextureFormat::kRGB_U16));
	EXPECT_EQ((GLenum)GL_RGB,  ToGlPixelFormat(bksge::TextureFormat::kRGB_S16));
	EXPECT_EQ((GLenum)GL_RGB,  ToGlPixelFormat(bksge::TextureFormat::kRGB_U32));
	EXPECT_EQ((GLenum)GL_RGB,  ToGlPixelFormat(bksge::TextureFormat::kRGB_S32));
	EXPECT_EQ((GLenum)GL_RGB,  ToGlPixelFormat(bksge::TextureFormat::kRGB_F32));
	EXPECT_EQ((GLenum)GL_BGR,  ToGlPixelFormat(bksge::TextureFormat::kBGR_U8));
	EXPECT_EQ((GLenum)GL_BGR,  ToGlPixelFormat(bksge::TextureFormat::kBGR_S8));
	EXPECT_EQ((GLenum)GL_BGR,  ToGlPixelFormat(bksge::TextureFormat::kBGR_U16));
	EXPECT_EQ((GLenum)GL_BGR,  ToGlPixelFormat(bksge::TextureFormat::kBGR_S16));
	EXPECT_EQ((GLenum)GL_BGR,  ToGlPixelFormat(bksge::TextureFormat::kBGR_U32));
	EXPECT_EQ((GLenum)GL_BGR,  ToGlPixelFormat(bksge::TextureFormat::kBGR_S32));
	EXPECT_EQ((GLenum)GL_BGR,  ToGlPixelFormat(bksge::TextureFormat::kBGR_F32));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kRGBA_U8));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kRGBA_S8));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kRGBA_U16));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kRGBA_S16));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kRGBA_U32));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kRGBA_S32));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kRGBA_F32));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kBGRA_U8));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kBGRA_S8));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kBGRA_U16));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kBGRA_S16));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kBGRA_U32));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kBGRA_S32));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kBGRA_F32));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kARGB_U8));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kARGB_S8));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kARGB_U16));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kARGB_S16));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kARGB_U32));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kARGB_S32));
	EXPECT_EQ((GLenum)GL_BGRA, ToGlPixelFormat(bksge::TextureFormat::kARGB_F32));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kABGR_U8));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kABGR_S8));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kABGR_U16));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kABGR_S16));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kABGR_U32));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kABGR_S32));
	EXPECT_EQ((GLenum)GL_RGBA, ToGlPixelFormat(bksge::TextureFormat::kABGR_F32));
	EXPECT_EQ((GLenum)GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, ToGlPixelFormat(bksge::TextureFormat::kDxt1));
	EXPECT_EQ((GLenum)GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, ToGlPixelFormat(bksge::TextureFormat::kDxt3));
	EXPECT_EQ((GLenum)GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, ToGlPixelFormat(bksge::TextureFormat::kDxt5));
#endif
}

GTEST_TEST(Render_GlTest, ToGlInternalPixelFormatTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ(GL_RED,  ToGlInternalPixelFormat(bksge::TextureFormat::kR_U8));
	EXPECT_EQ(GL_RED,  ToGlInternalPixelFormat(bksge::TextureFormat::kR_S8));
	EXPECT_EQ(GL_RED,  ToGlInternalPixelFormat(bksge::TextureFormat::kR_U16));
	EXPECT_EQ(GL_RED,  ToGlInternalPixelFormat(bksge::TextureFormat::kR_S16));
	EXPECT_EQ(GL_RED,  ToGlInternalPixelFormat(bksge::TextureFormat::kR_U32));
	EXPECT_EQ(GL_RED,  ToGlInternalPixelFormat(bksge::TextureFormat::kR_S32));
	EXPECT_EQ(GL_RED,  ToGlInternalPixelFormat(bksge::TextureFormat::kR_F32));
	EXPECT_EQ(GL_RG,   ToGlInternalPixelFormat(bksge::TextureFormat::kRG_U8));
	EXPECT_EQ(GL_RG,   ToGlInternalPixelFormat(bksge::TextureFormat::kRG_S8));
	EXPECT_EQ(GL_RG,   ToGlInternalPixelFormat(bksge::TextureFormat::kRG_U16));
	EXPECT_EQ(GL_RG,   ToGlInternalPixelFormat(bksge::TextureFormat::kRG_S16));
	EXPECT_EQ(GL_RG,   ToGlInternalPixelFormat(bksge::TextureFormat::kRG_U32));
	EXPECT_EQ(GL_RG,   ToGlInternalPixelFormat(bksge::TextureFormat::kRG_S32));
	EXPECT_EQ(GL_RG,   ToGlInternalPixelFormat(bksge::TextureFormat::kRG_F32));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kRGB_U8));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kRGB_S8));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kRGB_U16));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kRGB_S16));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kRGB_U32));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kRGB_S32));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kRGB_F32));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kBGR_U8));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kBGR_S8));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kBGR_U16));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kBGR_S16));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kBGR_U32));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kBGR_S32));
	EXPECT_EQ(GL_RGB,  ToGlInternalPixelFormat(bksge::TextureFormat::kBGR_F32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kRGBA_U8));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kRGBA_S8));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kRGBA_U16));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kRGBA_S16));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kRGBA_U32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kRGBA_S32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kRGBA_F32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kBGRA_U8));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kBGRA_S8));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kBGRA_U16));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kBGRA_S16));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kBGRA_U32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kBGRA_S32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kBGRA_F32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kARGB_U8));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kARGB_S8));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kARGB_U16));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kARGB_S16));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kARGB_U32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kARGB_S32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kARGB_F32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kABGR_U8));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kABGR_S8));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kABGR_U16));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kABGR_S16));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kABGR_U32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kABGR_S32));
	EXPECT_EQ(GL_RGBA, ToGlInternalPixelFormat(bksge::TextureFormat::kABGR_F32));
	EXPECT_EQ(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, ToGlInternalPixelFormat(bksge::TextureFormat::kDxt1));
	EXPECT_EQ(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, ToGlInternalPixelFormat(bksge::TextureFormat::kDxt3));
	EXPECT_EQ(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, ToGlInternalPixelFormat(bksge::TextureFormat::kDxt5));
#endif
}

GTEST_TEST(Render_GlTest, ToGlPixelTypeTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kR_U8));
	EXPECT_EQ((GLenum)GL_BYTE,           ToGlPixelType(bksge::TextureFormat::kR_S8));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, ToGlPixelType(bksge::TextureFormat::kR_U16));
	EXPECT_EQ((GLenum)GL_SHORT,          ToGlPixelType(bksge::TextureFormat::kR_S16));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   ToGlPixelType(bksge::TextureFormat::kR_U32));
	EXPECT_EQ((GLenum)GL_INT,            ToGlPixelType(bksge::TextureFormat::kR_S32));
	EXPECT_EQ((GLenum)GL_FLOAT,          ToGlPixelType(bksge::TextureFormat::kR_F32));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kRG_U8));
	EXPECT_EQ((GLenum)GL_BYTE,           ToGlPixelType(bksge::TextureFormat::kRG_S8));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, ToGlPixelType(bksge::TextureFormat::kRG_U16));
	EXPECT_EQ((GLenum)GL_SHORT,          ToGlPixelType(bksge::TextureFormat::kRG_S16));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   ToGlPixelType(bksge::TextureFormat::kRG_U32));
	EXPECT_EQ((GLenum)GL_INT,            ToGlPixelType(bksge::TextureFormat::kRG_S32));
	EXPECT_EQ((GLenum)GL_FLOAT,          ToGlPixelType(bksge::TextureFormat::kRG_F32));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kRGB_U8));
	EXPECT_EQ((GLenum)GL_BYTE,           ToGlPixelType(bksge::TextureFormat::kRGB_S8));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, ToGlPixelType(bksge::TextureFormat::kRGB_U16));
	EXPECT_EQ((GLenum)GL_SHORT,          ToGlPixelType(bksge::TextureFormat::kRGB_S16));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   ToGlPixelType(bksge::TextureFormat::kRGB_U32));
	EXPECT_EQ((GLenum)GL_INT,            ToGlPixelType(bksge::TextureFormat::kRGB_S32));
	EXPECT_EQ((GLenum)GL_FLOAT,          ToGlPixelType(bksge::TextureFormat::kRGB_F32));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kBGR_U8));
	EXPECT_EQ((GLenum)GL_BYTE,           ToGlPixelType(bksge::TextureFormat::kBGR_S8));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, ToGlPixelType(bksge::TextureFormat::kBGR_U16));
	EXPECT_EQ((GLenum)GL_SHORT,          ToGlPixelType(bksge::TextureFormat::kBGR_S16));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   ToGlPixelType(bksge::TextureFormat::kBGR_U32));
	EXPECT_EQ((GLenum)GL_INT,            ToGlPixelType(bksge::TextureFormat::kBGR_S32));
	EXPECT_EQ((GLenum)GL_FLOAT,          ToGlPixelType(bksge::TextureFormat::kBGR_F32));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kRGBA_U8));
	EXPECT_EQ((GLenum)GL_BYTE,           ToGlPixelType(bksge::TextureFormat::kRGBA_S8));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, ToGlPixelType(bksge::TextureFormat::kRGBA_U16));
	EXPECT_EQ((GLenum)GL_SHORT,          ToGlPixelType(bksge::TextureFormat::kRGBA_S16));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   ToGlPixelType(bksge::TextureFormat::kRGBA_U32));
	EXPECT_EQ((GLenum)GL_INT,            ToGlPixelType(bksge::TextureFormat::kRGBA_S32));
	EXPECT_EQ((GLenum)GL_FLOAT,          ToGlPixelType(bksge::TextureFormat::kRGBA_F32));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kBGRA_U8));
	EXPECT_EQ((GLenum)GL_BYTE,           ToGlPixelType(bksge::TextureFormat::kBGRA_S8));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, ToGlPixelType(bksge::TextureFormat::kBGRA_U16));
	EXPECT_EQ((GLenum)GL_SHORT,          ToGlPixelType(bksge::TextureFormat::kBGRA_S16));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   ToGlPixelType(bksge::TextureFormat::kBGRA_U32));
	EXPECT_EQ((GLenum)GL_INT,            ToGlPixelType(bksge::TextureFormat::kBGRA_S32));
	EXPECT_EQ((GLenum)GL_FLOAT,          ToGlPixelType(bksge::TextureFormat::kBGRA_F32));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kARGB_U8));
	EXPECT_EQ((GLenum)GL_BYTE,           ToGlPixelType(bksge::TextureFormat::kARGB_S8));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, ToGlPixelType(bksge::TextureFormat::kARGB_U16));
	EXPECT_EQ((GLenum)GL_SHORT,          ToGlPixelType(bksge::TextureFormat::kARGB_S16));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   ToGlPixelType(bksge::TextureFormat::kARGB_U32));
	EXPECT_EQ((GLenum)GL_INT,            ToGlPixelType(bksge::TextureFormat::kARGB_S32));
	EXPECT_EQ((GLenum)GL_FLOAT,          ToGlPixelType(bksge::TextureFormat::kARGB_F32));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kABGR_U8));
	EXPECT_EQ((GLenum)GL_BYTE,           ToGlPixelType(bksge::TextureFormat::kABGR_S8));
	EXPECT_EQ((GLenum)GL_UNSIGNED_SHORT, ToGlPixelType(bksge::TextureFormat::kABGR_U16));
	EXPECT_EQ((GLenum)GL_SHORT,          ToGlPixelType(bksge::TextureFormat::kABGR_S16));
	EXPECT_EQ((GLenum)GL_UNSIGNED_INT,   ToGlPixelType(bksge::TextureFormat::kABGR_U32));
	EXPECT_EQ((GLenum)GL_INT,            ToGlPixelType(bksge::TextureFormat::kABGR_S32));
	EXPECT_EQ((GLenum)GL_FLOAT,          ToGlPixelType(bksge::TextureFormat::kABGR_F32));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kDxt1));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kDxt3));
	EXPECT_EQ((GLenum)GL_UNSIGNED_BYTE,  ToGlPixelType(bksge::TextureFormat::kDxt5));
#endif
}
