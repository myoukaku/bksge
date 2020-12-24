/**
 *	@file	unit_test_core_render_texture_format.cpp
 *
 *	@brief	TextureFormat のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/texture_format.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/vector.hpp>
#include <functional>
#include <sstream>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace texture_format_test
{

GTEST_TEST(TextureFormatTest, GetPixelSwizzleTest)
{
	using namespace bksge::render;

	EXPECT_EQ(PixelSwizzle::kNone, GetPixelSwizzle(TextureFormat::kNone));
	EXPECT_EQ(PixelSwizzle::kR,    GetPixelSwizzle(TextureFormat::kR_U8));
	EXPECT_EQ(PixelSwizzle::kR,    GetPixelSwizzle(TextureFormat::kR_S8));
	EXPECT_EQ(PixelSwizzle::kR,    GetPixelSwizzle(TextureFormat::kR_U16));
	EXPECT_EQ(PixelSwizzle::kR,    GetPixelSwizzle(TextureFormat::kR_S16));
	EXPECT_EQ(PixelSwizzle::kR,    GetPixelSwizzle(TextureFormat::kR_U32));
	EXPECT_EQ(PixelSwizzle::kR,    GetPixelSwizzle(TextureFormat::kR_S32));
	EXPECT_EQ(PixelSwizzle::kR,    GetPixelSwizzle(TextureFormat::kR_F32));
	EXPECT_EQ(PixelSwizzle::kRG,   GetPixelSwizzle(TextureFormat::kRG_U8));
	EXPECT_EQ(PixelSwizzle::kRG,   GetPixelSwizzle(TextureFormat::kRG_S8));
	EXPECT_EQ(PixelSwizzle::kRG,   GetPixelSwizzle(TextureFormat::kRG_U16));
	EXPECT_EQ(PixelSwizzle::kRG,   GetPixelSwizzle(TextureFormat::kRG_S16));
	EXPECT_EQ(PixelSwizzle::kRG,   GetPixelSwizzle(TextureFormat::kRG_U32));
	EXPECT_EQ(PixelSwizzle::kRG,   GetPixelSwizzle(TextureFormat::kRG_S32));
	EXPECT_EQ(PixelSwizzle::kRG,   GetPixelSwizzle(TextureFormat::kRG_F32));
	EXPECT_EQ(PixelSwizzle::kRGB,  GetPixelSwizzle(TextureFormat::kRGB_U8));
	EXPECT_EQ(PixelSwizzle::kRGB,  GetPixelSwizzle(TextureFormat::kRGB_S8));
	EXPECT_EQ(PixelSwizzle::kRGB,  GetPixelSwizzle(TextureFormat::kRGB_U16));
	EXPECT_EQ(PixelSwizzle::kRGB,  GetPixelSwizzle(TextureFormat::kRGB_S16));
	EXPECT_EQ(PixelSwizzle::kRGB,  GetPixelSwizzle(TextureFormat::kRGB_U32));
	EXPECT_EQ(PixelSwizzle::kRGB,  GetPixelSwizzle(TextureFormat::kRGB_S32));
	EXPECT_EQ(PixelSwizzle::kRGB,  GetPixelSwizzle(TextureFormat::kRGB_F32));
	EXPECT_EQ(PixelSwizzle::kBGR,  GetPixelSwizzle(TextureFormat::kBGR_U8));
	EXPECT_EQ(PixelSwizzle::kBGR,  GetPixelSwizzle(TextureFormat::kBGR_S8));
	EXPECT_EQ(PixelSwizzle::kBGR,  GetPixelSwizzle(TextureFormat::kBGR_U16));
	EXPECT_EQ(PixelSwizzle::kBGR,  GetPixelSwizzle(TextureFormat::kBGR_S16));
	EXPECT_EQ(PixelSwizzle::kBGR,  GetPixelSwizzle(TextureFormat::kBGR_U32));
	EXPECT_EQ(PixelSwizzle::kBGR,  GetPixelSwizzle(TextureFormat::kBGR_S32));
	EXPECT_EQ(PixelSwizzle::kBGR,  GetPixelSwizzle(TextureFormat::kBGR_F32));
	EXPECT_EQ(PixelSwizzle::kRGBA, GetPixelSwizzle(TextureFormat::kRGBA_U8));
	EXPECT_EQ(PixelSwizzle::kRGBA, GetPixelSwizzle(TextureFormat::kRGBA_S8));
	EXPECT_EQ(PixelSwizzle::kRGBA, GetPixelSwizzle(TextureFormat::kRGBA_U16));
	EXPECT_EQ(PixelSwizzle::kRGBA, GetPixelSwizzle(TextureFormat::kRGBA_S16));
	EXPECT_EQ(PixelSwizzle::kRGBA, GetPixelSwizzle(TextureFormat::kRGBA_U32));
	EXPECT_EQ(PixelSwizzle::kRGBA, GetPixelSwizzle(TextureFormat::kRGBA_S32));
	EXPECT_EQ(PixelSwizzle::kRGBA, GetPixelSwizzle(TextureFormat::kRGBA_F32));
	EXPECT_EQ(PixelSwizzle::kBGRA, GetPixelSwizzle(TextureFormat::kBGRA_U8));
	EXPECT_EQ(PixelSwizzle::kBGRA, GetPixelSwizzle(TextureFormat::kBGRA_S8));
	EXPECT_EQ(PixelSwizzle::kBGRA, GetPixelSwizzle(TextureFormat::kBGRA_U16));
	EXPECT_EQ(PixelSwizzle::kBGRA, GetPixelSwizzle(TextureFormat::kBGRA_S16));
	EXPECT_EQ(PixelSwizzle::kBGRA, GetPixelSwizzle(TextureFormat::kBGRA_U32));
	EXPECT_EQ(PixelSwizzle::kBGRA, GetPixelSwizzle(TextureFormat::kBGRA_S32));
	EXPECT_EQ(PixelSwizzle::kBGRA, GetPixelSwizzle(TextureFormat::kBGRA_F32));
	EXPECT_EQ(PixelSwizzle::kARGB, GetPixelSwizzle(TextureFormat::kARGB_U8));
	EXPECT_EQ(PixelSwizzle::kARGB, GetPixelSwizzle(TextureFormat::kARGB_S8));
	EXPECT_EQ(PixelSwizzle::kARGB, GetPixelSwizzle(TextureFormat::kARGB_U16));
	EXPECT_EQ(PixelSwizzle::kARGB, GetPixelSwizzle(TextureFormat::kARGB_S16));
	EXPECT_EQ(PixelSwizzle::kARGB, GetPixelSwizzle(TextureFormat::kARGB_U32));
	EXPECT_EQ(PixelSwizzle::kARGB, GetPixelSwizzle(TextureFormat::kARGB_S32));
	EXPECT_EQ(PixelSwizzle::kARGB, GetPixelSwizzle(TextureFormat::kARGB_F32));
	EXPECT_EQ(PixelSwizzle::kABGR, GetPixelSwizzle(TextureFormat::kABGR_U8));
	EXPECT_EQ(PixelSwizzle::kABGR, GetPixelSwizzle(TextureFormat::kABGR_S8));
	EXPECT_EQ(PixelSwizzle::kABGR, GetPixelSwizzle(TextureFormat::kABGR_U16));
	EXPECT_EQ(PixelSwizzle::kABGR, GetPixelSwizzle(TextureFormat::kABGR_S16));
	EXPECT_EQ(PixelSwizzle::kABGR, GetPixelSwizzle(TextureFormat::kABGR_U32));
	EXPECT_EQ(PixelSwizzle::kABGR, GetPixelSwizzle(TextureFormat::kABGR_S32));
	EXPECT_EQ(PixelSwizzle::kABGR, GetPixelSwizzle(TextureFormat::kABGR_F32));
	EXPECT_EQ(PixelSwizzle::kDxt1, GetPixelSwizzle(TextureFormat::kDxt1));
	EXPECT_EQ(PixelSwizzle::kDxt3, GetPixelSwizzle(TextureFormat::kDxt3));
	EXPECT_EQ(PixelSwizzle::kDxt5, GetPixelSwizzle(TextureFormat::kDxt5));
}

GTEST_TEST(TextureFormatTest, GetPixelBaseFormatTest)
{
	using namespace bksge::render;

	EXPECT_EQ(PixelBaseFormat::kNone, GetPixelBaseFormat(TextureFormat::kNone));
	EXPECT_EQ(PixelBaseFormat::kU8,   GetPixelBaseFormat(TextureFormat::kR_U8));
	EXPECT_EQ(PixelBaseFormat::kS8,   GetPixelBaseFormat(TextureFormat::kR_S8));
	EXPECT_EQ(PixelBaseFormat::kU16,  GetPixelBaseFormat(TextureFormat::kR_U16));
	EXPECT_EQ(PixelBaseFormat::kS16,  GetPixelBaseFormat(TextureFormat::kR_S16));
	EXPECT_EQ(PixelBaseFormat::kU32,  GetPixelBaseFormat(TextureFormat::kR_U32));
	EXPECT_EQ(PixelBaseFormat::kS32,  GetPixelBaseFormat(TextureFormat::kR_S32));
	EXPECT_EQ(PixelBaseFormat::kF32,  GetPixelBaseFormat(TextureFormat::kR_F32));
	EXPECT_EQ(PixelBaseFormat::kU8,   GetPixelBaseFormat(TextureFormat::kRG_U8));
	EXPECT_EQ(PixelBaseFormat::kS8,   GetPixelBaseFormat(TextureFormat::kRG_S8));
	EXPECT_EQ(PixelBaseFormat::kU16,  GetPixelBaseFormat(TextureFormat::kRG_U16));
	EXPECT_EQ(PixelBaseFormat::kS16,  GetPixelBaseFormat(TextureFormat::kRG_S16));
	EXPECT_EQ(PixelBaseFormat::kU32,  GetPixelBaseFormat(TextureFormat::kRG_U32));
	EXPECT_EQ(PixelBaseFormat::kS32,  GetPixelBaseFormat(TextureFormat::kRG_S32));
	EXPECT_EQ(PixelBaseFormat::kF32,  GetPixelBaseFormat(TextureFormat::kRG_F32));
	EXPECT_EQ(PixelBaseFormat::kU8,   GetPixelBaseFormat(TextureFormat::kRGB_U8));
	EXPECT_EQ(PixelBaseFormat::kS8,   GetPixelBaseFormat(TextureFormat::kRGB_S8));
	EXPECT_EQ(PixelBaseFormat::kU16,  GetPixelBaseFormat(TextureFormat::kRGB_U16));
	EXPECT_EQ(PixelBaseFormat::kS16,  GetPixelBaseFormat(TextureFormat::kRGB_S16));
	EXPECT_EQ(PixelBaseFormat::kU32,  GetPixelBaseFormat(TextureFormat::kRGB_U32));
	EXPECT_EQ(PixelBaseFormat::kS32,  GetPixelBaseFormat(TextureFormat::kRGB_S32));
	EXPECT_EQ(PixelBaseFormat::kF32,  GetPixelBaseFormat(TextureFormat::kRGB_F32));
	EXPECT_EQ(PixelBaseFormat::kU8,   GetPixelBaseFormat(TextureFormat::kBGR_U8));
	EXPECT_EQ(PixelBaseFormat::kS8,   GetPixelBaseFormat(TextureFormat::kBGR_S8));
	EXPECT_EQ(PixelBaseFormat::kU16,  GetPixelBaseFormat(TextureFormat::kBGR_U16));
	EXPECT_EQ(PixelBaseFormat::kS16,  GetPixelBaseFormat(TextureFormat::kBGR_S16));
	EXPECT_EQ(PixelBaseFormat::kU32,  GetPixelBaseFormat(TextureFormat::kBGR_U32));
	EXPECT_EQ(PixelBaseFormat::kS32,  GetPixelBaseFormat(TextureFormat::kBGR_S32));
	EXPECT_EQ(PixelBaseFormat::kF32,  GetPixelBaseFormat(TextureFormat::kBGR_F32));
	EXPECT_EQ(PixelBaseFormat::kU8,   GetPixelBaseFormat(TextureFormat::kRGBA_U8));
	EXPECT_EQ(PixelBaseFormat::kS8,   GetPixelBaseFormat(TextureFormat::kRGBA_S8));
	EXPECT_EQ(PixelBaseFormat::kU16,  GetPixelBaseFormat(TextureFormat::kRGBA_U16));
	EXPECT_EQ(PixelBaseFormat::kS16,  GetPixelBaseFormat(TextureFormat::kRGBA_S16));
	EXPECT_EQ(PixelBaseFormat::kU32,  GetPixelBaseFormat(TextureFormat::kRGBA_U32));
	EXPECT_EQ(PixelBaseFormat::kS32,  GetPixelBaseFormat(TextureFormat::kRGBA_S32));
	EXPECT_EQ(PixelBaseFormat::kF32,  GetPixelBaseFormat(TextureFormat::kRGBA_F32));
	EXPECT_EQ(PixelBaseFormat::kU8,   GetPixelBaseFormat(TextureFormat::kBGRA_U8));
	EXPECT_EQ(PixelBaseFormat::kS8,   GetPixelBaseFormat(TextureFormat::kBGRA_S8));
	EXPECT_EQ(PixelBaseFormat::kU16,  GetPixelBaseFormat(TextureFormat::kBGRA_U16));
	EXPECT_EQ(PixelBaseFormat::kS16,  GetPixelBaseFormat(TextureFormat::kBGRA_S16));
	EXPECT_EQ(PixelBaseFormat::kU32,  GetPixelBaseFormat(TextureFormat::kBGRA_U32));
	EXPECT_EQ(PixelBaseFormat::kS32,  GetPixelBaseFormat(TextureFormat::kBGRA_S32));
	EXPECT_EQ(PixelBaseFormat::kF32,  GetPixelBaseFormat(TextureFormat::kBGRA_F32));
	EXPECT_EQ(PixelBaseFormat::kU8,   GetPixelBaseFormat(TextureFormat::kARGB_U8));
	EXPECT_EQ(PixelBaseFormat::kS8,   GetPixelBaseFormat(TextureFormat::kARGB_S8));
	EXPECT_EQ(PixelBaseFormat::kU16,  GetPixelBaseFormat(TextureFormat::kARGB_U16));
	EXPECT_EQ(PixelBaseFormat::kS16,  GetPixelBaseFormat(TextureFormat::kARGB_S16));
	EXPECT_EQ(PixelBaseFormat::kU32,  GetPixelBaseFormat(TextureFormat::kARGB_U32));
	EXPECT_EQ(PixelBaseFormat::kS32,  GetPixelBaseFormat(TextureFormat::kARGB_S32));
	EXPECT_EQ(PixelBaseFormat::kF32,  GetPixelBaseFormat(TextureFormat::kARGB_F32));
	EXPECT_EQ(PixelBaseFormat::kU8,   GetPixelBaseFormat(TextureFormat::kABGR_U8));
	EXPECT_EQ(PixelBaseFormat::kS8,   GetPixelBaseFormat(TextureFormat::kABGR_S8));
	EXPECT_EQ(PixelBaseFormat::kU16,  GetPixelBaseFormat(TextureFormat::kABGR_U16));
	EXPECT_EQ(PixelBaseFormat::kS16,  GetPixelBaseFormat(TextureFormat::kABGR_S16));
	EXPECT_EQ(PixelBaseFormat::kU32,  GetPixelBaseFormat(TextureFormat::kABGR_U32));
	EXPECT_EQ(PixelBaseFormat::kS32,  GetPixelBaseFormat(TextureFormat::kABGR_S32));
	EXPECT_EQ(PixelBaseFormat::kF32,  GetPixelBaseFormat(TextureFormat::kABGR_F32));
	EXPECT_EQ(PixelBaseFormat::kDxt1,  GetPixelBaseFormat(TextureFormat::kDxt1));
	EXPECT_EQ(PixelBaseFormat::kDxt35, GetPixelBaseFormat(TextureFormat::kDxt3));
	EXPECT_EQ(PixelBaseFormat::kDxt35, GetPixelBaseFormat(TextureFormat::kDxt5));
}

GTEST_TEST(TextureFormatTest, GetChannelCountTest)
{
	using namespace bksge::render;

	EXPECT_EQ(0u, GetChannelCount(TextureFormat::kNone));
	EXPECT_EQ(1u, GetChannelCount(TextureFormat::kR_U8));
	EXPECT_EQ(1u, GetChannelCount(TextureFormat::kR_S8));
	EXPECT_EQ(1u, GetChannelCount(TextureFormat::kR_U16));
	EXPECT_EQ(1u, GetChannelCount(TextureFormat::kR_S16));
	EXPECT_EQ(1u, GetChannelCount(TextureFormat::kR_U32));
	EXPECT_EQ(1u, GetChannelCount(TextureFormat::kR_S32));
	EXPECT_EQ(1u, GetChannelCount(TextureFormat::kR_F32));
	EXPECT_EQ(2u, GetChannelCount(TextureFormat::kRG_U8));
	EXPECT_EQ(2u, GetChannelCount(TextureFormat::kRG_S8));
	EXPECT_EQ(2u, GetChannelCount(TextureFormat::kRG_U16));
	EXPECT_EQ(2u, GetChannelCount(TextureFormat::kRG_S16));
	EXPECT_EQ(2u, GetChannelCount(TextureFormat::kRG_U32));
	EXPECT_EQ(2u, GetChannelCount(TextureFormat::kRG_S32));
	EXPECT_EQ(2u, GetChannelCount(TextureFormat::kRG_F32));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kRGB_U8));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kRGB_S8));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kRGB_U16));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kRGB_S16));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kRGB_U32));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kRGB_S32));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kRGB_F32));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kBGR_U8));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kBGR_S8));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kBGR_U16));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kBGR_S16));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kBGR_U32));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kBGR_S32));
	EXPECT_EQ(3u, GetChannelCount(TextureFormat::kBGR_F32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kRGBA_U8));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kRGBA_S8));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kRGBA_U16));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kRGBA_S16));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kRGBA_U32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kRGBA_S32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kRGBA_F32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kBGRA_U8));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kBGRA_S8));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kBGRA_U16));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kBGRA_S16));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kBGRA_U32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kBGRA_S32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kBGRA_F32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kARGB_U8));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kARGB_S8));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kARGB_U16));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kARGB_S16));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kARGB_U32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kARGB_S32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kARGB_F32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kABGR_U8));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kABGR_S8));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kABGR_U16));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kABGR_S16));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kABGR_U32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kABGR_S32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kABGR_F32));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kDxt1));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kDxt3));
	EXPECT_EQ(4u, GetChannelCount(TextureFormat::kDxt5));
}

GTEST_TEST(TextureFormatTest, GetBitsPerChannelTest)
{
	using namespace bksge::render;

	EXPECT_EQ( 0u, GetBitsPerChannel(TextureFormat::kNone));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kR_U8));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kR_S8));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kR_U16));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kR_S16));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kR_U32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kR_S32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kR_F32));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kRG_U8));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kRG_S8));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kRG_U16));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kRG_S16));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kRG_U32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kRG_S32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kRG_F32));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kRGB_U8));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kRGB_S8));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kRGB_U16));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kRGB_S16));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kRGB_U32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kRGB_S32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kRGB_F32));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kBGR_U8));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kBGR_S8));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kBGR_U16));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kBGR_S16));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kBGR_U32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kBGR_S32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kBGR_F32));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kRGBA_U8));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kRGBA_S8));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kRGBA_U16));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kRGBA_S16));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kRGBA_U32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kRGBA_S32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kRGBA_F32));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kBGRA_U8));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kBGRA_S8));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kBGRA_U16));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kBGRA_S16));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kBGRA_U32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kBGRA_S32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kBGRA_F32));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kARGB_U8));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kARGB_S8));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kARGB_U16));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kARGB_S16));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kARGB_U32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kARGB_S32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kARGB_F32));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kABGR_U8));
	EXPECT_EQ( 8u, GetBitsPerChannel(TextureFormat::kABGR_S8));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kABGR_U16));
	EXPECT_EQ(16u, GetBitsPerChannel(TextureFormat::kABGR_S16));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kABGR_U32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kABGR_S32));
	EXPECT_EQ(32u, GetBitsPerChannel(TextureFormat::kABGR_F32));
	EXPECT_EQ( 1u, GetBitsPerChannel(TextureFormat::kDxt1));
	EXPECT_EQ( 2u, GetBitsPerChannel(TextureFormat::kDxt3));
	EXPECT_EQ( 2u, GetBitsPerChannel(TextureFormat::kDxt5));
}

GTEST_TEST(TextureFormatTest, IsDxtCompressedTest)
{
	using namespace bksge::render;

	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kNone));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kR_U8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kR_S8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kR_U16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kR_S16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kR_U32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kR_S32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kR_F32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRG_U8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRG_S8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRG_U16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRG_S16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRG_U32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRG_S32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRG_F32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGB_U8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGB_S8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGB_U16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGB_S16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGB_U32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGB_S32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGB_F32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGR_U8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGR_S8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGR_U16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGR_S16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGR_U32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGR_S32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGR_F32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGBA_U8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGBA_S8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGBA_U16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGBA_S16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGBA_U32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGBA_S32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kRGBA_F32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGRA_U8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGRA_S8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGRA_U16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGRA_S16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGRA_U32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGRA_S32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kBGRA_F32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kARGB_U8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kARGB_S8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kARGB_U16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kARGB_S16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kARGB_U32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kARGB_S32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kARGB_F32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kABGR_U8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kABGR_S8));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kABGR_U16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kABGR_S16));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kABGR_U32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kABGR_S32));
	EXPECT_EQ(false, IsDxtCompressed(TextureFormat::kABGR_F32));
	EXPECT_EQ(true,  IsDxtCompressed(TextureFormat::kDxt1));
	EXPECT_EQ(true,  IsDxtCompressed(TextureFormat::kDxt3));
	EXPECT_EQ(true,  IsDxtCompressed(TextureFormat::kDxt5));
}

GTEST_TEST(TextureFormatTest, GetBitsPerPixelTest)
{
	using namespace bksge::render;

	EXPECT_EQ(  0u, GetBitsPerPixel(TextureFormat::kNone));
	EXPECT_EQ(  8u, GetBitsPerPixel(TextureFormat::kR_U8));
	EXPECT_EQ(  8u, GetBitsPerPixel(TextureFormat::kR_S8));
	EXPECT_EQ( 16u, GetBitsPerPixel(TextureFormat::kR_U16));
	EXPECT_EQ( 16u, GetBitsPerPixel(TextureFormat::kR_S16));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kR_U32));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kR_S32));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kR_F32));
	EXPECT_EQ( 16u, GetBitsPerPixel(TextureFormat::kRG_U8));
	EXPECT_EQ( 16u, GetBitsPerPixel(TextureFormat::kRG_S8));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kRG_U16));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kRG_S16));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kRG_U32));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kRG_S32));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kRG_F32));
	EXPECT_EQ( 24u, GetBitsPerPixel(TextureFormat::kRGB_U8));
	EXPECT_EQ( 24u, GetBitsPerPixel(TextureFormat::kRGB_S8));
	EXPECT_EQ( 48u, GetBitsPerPixel(TextureFormat::kRGB_U16));
	EXPECT_EQ( 48u, GetBitsPerPixel(TextureFormat::kRGB_S16));
	EXPECT_EQ( 96u, GetBitsPerPixel(TextureFormat::kRGB_U32));
	EXPECT_EQ( 96u, GetBitsPerPixel(TextureFormat::kRGB_S32));
	EXPECT_EQ( 96u, GetBitsPerPixel(TextureFormat::kRGB_F32));
	EXPECT_EQ( 24u, GetBitsPerPixel(TextureFormat::kBGR_U8));
	EXPECT_EQ( 24u, GetBitsPerPixel(TextureFormat::kBGR_S8));
	EXPECT_EQ( 48u, GetBitsPerPixel(TextureFormat::kBGR_U16));
	EXPECT_EQ( 48u, GetBitsPerPixel(TextureFormat::kBGR_S16));
	EXPECT_EQ( 96u, GetBitsPerPixel(TextureFormat::kBGR_U32));
	EXPECT_EQ( 96u, GetBitsPerPixel(TextureFormat::kBGR_S32));
	EXPECT_EQ( 96u, GetBitsPerPixel(TextureFormat::kBGR_F32));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kRGBA_U8));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kRGBA_S8));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kRGBA_U16));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kRGBA_S16));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kRGBA_U32));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kRGBA_S32));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kRGBA_F32));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kBGRA_U8));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kBGRA_S8));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kBGRA_U16));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kBGRA_S16));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kBGRA_U32));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kBGRA_S32));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kBGRA_F32));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kARGB_U8));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kARGB_S8));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kARGB_U16));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kARGB_S16));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kARGB_U32));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kARGB_S32));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kARGB_F32));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kABGR_U8));
	EXPECT_EQ( 32u, GetBitsPerPixel(TextureFormat::kABGR_S8));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kABGR_U16));
	EXPECT_EQ( 64u, GetBitsPerPixel(TextureFormat::kABGR_S16));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kABGR_U32));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kABGR_S32));
	EXPECT_EQ(128u, GetBitsPerPixel(TextureFormat::kABGR_F32));
	EXPECT_EQ(  4u, GetBitsPerPixel(TextureFormat::kDxt1));
	EXPECT_EQ(  8u, GetBitsPerPixel(TextureFormat::kDxt3));
	EXPECT_EQ(  8u, GetBitsPerPixel(TextureFormat::kDxt5));
}

GTEST_TEST(TextureFormatTest, GetSizeInBytesTest)
{
	using namespace bksge::render;

	EXPECT_EQ(   0u, GetSizeInBytes(TextureFormat::kNone, 4, 4));

	EXPECT_EQ(   0u, GetSizeInBytes(TextureFormat::kRGBA_U8, 0, 0));
	EXPECT_EQ(   0u, GetSizeInBytes(TextureFormat::kRGBA_U8, 4, 0));
	EXPECT_EQ(   0u, GetSizeInBytes(TextureFormat::kRGBA_U8, 0, 8));
	EXPECT_EQ( 128u, GetSizeInBytes(TextureFormat::kRGBA_U8, 4, 8));
	EXPECT_EQ( 160u, GetSizeInBytes(TextureFormat::kRGBA_U8, 5, 8));
	EXPECT_EQ( 192u, GetSizeInBytes(TextureFormat::kRGBA_U8, 6, 8));
	EXPECT_EQ( 224u, GetSizeInBytes(TextureFormat::kRGBA_U8, 7, 8));
	EXPECT_EQ( 252u, GetSizeInBytes(TextureFormat::kRGBA_U8, 7, 9));
	EXPECT_EQ( 280u, GetSizeInBytes(TextureFormat::kRGBA_U8, 7, 10));

	EXPECT_EQ( 256u, GetSizeInBytes(TextureFormat::kRGBA_U16, 4, 8));
	EXPECT_EQ( 320u, GetSizeInBytes(TextureFormat::kRGBA_U16, 5, 8));
	EXPECT_EQ( 384u, GetSizeInBytes(TextureFormat::kRGBA_U16, 6, 8));
	EXPECT_EQ( 448u, GetSizeInBytes(TextureFormat::kRGBA_U16, 7, 8));
	EXPECT_EQ( 504u, GetSizeInBytes(TextureFormat::kRGBA_U16, 7, 9));
	EXPECT_EQ( 560u, GetSizeInBytes(TextureFormat::kRGBA_U16, 7, 10));

	EXPECT_EQ( 512u, GetSizeInBytes(TextureFormat::kRGBA_F32, 4, 8));
	EXPECT_EQ( 640u, GetSizeInBytes(TextureFormat::kRGBA_F32, 5, 8));
	EXPECT_EQ( 768u, GetSizeInBytes(TextureFormat::kRGBA_F32, 6, 8));
	EXPECT_EQ( 896u, GetSizeInBytes(TextureFormat::kRGBA_F32, 7, 8));
	EXPECT_EQ(1008u, GetSizeInBytes(TextureFormat::kRGBA_F32, 7, 9));
	EXPECT_EQ(1120u, GetSizeInBytes(TextureFormat::kRGBA_F32, 7, 10));

	EXPECT_EQ(  96u, GetSizeInBytes(TextureFormat::kRGB_U8, 4, 8));
	EXPECT_EQ( 108u, GetSizeInBytes(TextureFormat::kRGB_U8, 4, 9));
	EXPECT_EQ( 135u, GetSizeInBytes(TextureFormat::kRGB_U8, 5, 9));

	EXPECT_EQ(   8u, GetSizeInBytes(TextureFormat::kDxt1, 4, 4));
	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt1, 5, 4));
	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt1, 6, 4));
	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt1, 7, 4));
	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt1, 8, 4));
	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt1, 4, 5));
	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt1, 4, 6));
	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt1, 4, 7));
	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt1, 4, 8));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt1, 8, 8));

	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt3, 4, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt3, 5, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt3, 6, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt3, 7, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt3, 8, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt3, 4, 5));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt3, 4, 6));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt3, 4, 7));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt3, 4, 8));
	EXPECT_EQ(  64u, GetSizeInBytes(TextureFormat::kDxt3, 8, 8));

	EXPECT_EQ(  16u, GetSizeInBytes(TextureFormat::kDxt5, 4, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt5, 5, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt5, 6, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt5, 7, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt5, 8, 4));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt5, 4, 5));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt5, 4, 6));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt5, 4, 7));
	EXPECT_EQ(  32u, GetSizeInBytes(TextureFormat::kDxt5, 4, 8));
	EXPECT_EQ(  64u, GetSizeInBytes(TextureFormat::kDxt5, 8, 8));
}

GTEST_TEST(TextureFormatTest,GetStrideInBytesTest)
{
	using namespace bksge::render;

	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kNone, 0));
	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kNone, 1));
	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kNone, 4));

	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kRGB_U8, 0));
	EXPECT_EQ( 3u, GetStrideInBytes(TextureFormat::kRGB_U8, 1));
	EXPECT_EQ(12u, GetStrideInBytes(TextureFormat::kRGB_U8, 4));

	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kRGB_U16, 0));
	EXPECT_EQ( 6u, GetStrideInBytes(TextureFormat::kRGB_U16, 1));
	EXPECT_EQ(24u, GetStrideInBytes(TextureFormat::kRGB_U16, 4));

	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kRGB_F32, 0));
	EXPECT_EQ(12u, GetStrideInBytes(TextureFormat::kRGB_F32, 1));
	EXPECT_EQ(48u, GetStrideInBytes(TextureFormat::kRGB_F32, 4));

	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kRGBA_U8, 0));
	EXPECT_EQ( 4u, GetStrideInBytes(TextureFormat::kRGBA_U8, 1));
	EXPECT_EQ(16u, GetStrideInBytes(TextureFormat::kRGBA_U8, 4));

	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kRGBA_U16, 0));
	EXPECT_EQ( 8u, GetStrideInBytes(TextureFormat::kRGBA_U16, 1));
	EXPECT_EQ(32u, GetStrideInBytes(TextureFormat::kRGBA_U16, 4));

	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kRGBA_F32, 0));
	EXPECT_EQ(16u, GetStrideInBytes(TextureFormat::kRGBA_F32, 1));
	EXPECT_EQ(64u, GetStrideInBytes(TextureFormat::kRGBA_F32, 4));
}

GTEST_TEST(TextureFormatTest, GetMipmappedSizeInBytesTest)
{
	using namespace bksge::render;

	EXPECT_EQ(64u, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 4, 4, 1));
	EXPECT_EQ(64u + 16, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 4, 4, 2));
	EXPECT_EQ(64u + 16 + 4, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 4, 4, 3));
	EXPECT_EQ(64u + 16 + 4, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 4, 4, 4));

	EXPECT_EQ(240u + 56 + 12, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 15, 4, 3));
	EXPECT_EQ(240u + 56 + 12 + 4, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 15, 4, 4));
	EXPECT_EQ(240u + 56 + 12 + 4, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 15, 4, 5));

	EXPECT_EQ(320u + 64 + 16, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 16, 5, 3));
	EXPECT_EQ(320u + 64 + 16 + 8, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 16, 5, 4));
	EXPECT_EQ(320u + 64 + 16 + 8 + 4, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 16, 5, 5));
	EXPECT_EQ(320u + 64 + 16 + 8 + 4, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 16, 5, 6));

	EXPECT_EQ(0u, GetMipmappedSizeInBytes(TextureFormat::kNone, 4, 4, 2));
	EXPECT_EQ(0u, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 0, 4, 2));
	EXPECT_EQ(0u, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 4, 0, 2));
	EXPECT_EQ(0u, GetMipmappedSizeInBytes(TextureFormat::kRGBA_U8, 4, 4, 0));
}

template <typename TChar>
static void OutputStreamTestSub(bksge::TextureFormat texture_format, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << texture_format;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_TextureFormat, OutputStreamTest)
{
	using bksge::TextureFormat;

	OutputStreamTestSub(TextureFormat::kR_U8,		"TextureFormat::kR_U8");
	OutputStreamTestSub(TextureFormat::kR_S8,		"TextureFormat::kR_S8");
	OutputStreamTestSub(TextureFormat::kR_U16,		"TextureFormat::kR_U16");
	OutputStreamTestSub(TextureFormat::kR_S16,		"TextureFormat::kR_S16");
	OutputStreamTestSub(TextureFormat::kR_U32,		"TextureFormat::kR_U32");
	OutputStreamTestSub(TextureFormat::kR_S32,		"TextureFormat::kR_S32");
	OutputStreamTestSub(TextureFormat::kR_F32,		"TextureFormat::kR_F32");
	OutputStreamTestSub(TextureFormat::kRG_U8,		"TextureFormat::kRG_U8");
	OutputStreamTestSub(TextureFormat::kRG_S8,		"TextureFormat::kRG_S8");
	OutputStreamTestSub(TextureFormat::kRG_U16,		"TextureFormat::kRG_U16");
	OutputStreamTestSub(TextureFormat::kRG_S16,		"TextureFormat::kRG_S16");
	OutputStreamTestSub(TextureFormat::kRG_U32,		"TextureFormat::kRG_U32");
	OutputStreamTestSub(TextureFormat::kRG_S32,		"TextureFormat::kRG_S32");
	OutputStreamTestSub(TextureFormat::kRG_F32,		"TextureFormat::kRG_F32");
	OutputStreamTestSub(TextureFormat::kRGB_U8,		"TextureFormat::kRGB_U8");
	OutputStreamTestSub(TextureFormat::kRGB_S8,		"TextureFormat::kRGB_S8");
	OutputStreamTestSub(TextureFormat::kRGB_U16,	"TextureFormat::kRGB_U16");
	OutputStreamTestSub(TextureFormat::kRGB_S16,	"TextureFormat::kRGB_S16");
	OutputStreamTestSub(TextureFormat::kRGB_U32,	"TextureFormat::kRGB_U32");
	OutputStreamTestSub(TextureFormat::kRGB_S32,	"TextureFormat::kRGB_S32");
	OutputStreamTestSub(TextureFormat::kRGB_F32,	"TextureFormat::kRGB_F32");
	OutputStreamTestSub(TextureFormat::kBGR_U8,		"TextureFormat::kBGR_U8");
	OutputStreamTestSub(TextureFormat::kBGR_S8,		"TextureFormat::kBGR_S8");
	OutputStreamTestSub(TextureFormat::kBGR_U16,	"TextureFormat::kBGR_U16");
	OutputStreamTestSub(TextureFormat::kBGR_S16,	"TextureFormat::kBGR_S16");
	OutputStreamTestSub(TextureFormat::kBGR_U32,	"TextureFormat::kBGR_U32");
	OutputStreamTestSub(TextureFormat::kBGR_S32,	"TextureFormat::kBGR_S32");
	OutputStreamTestSub(TextureFormat::kBGR_F32,	"TextureFormat::kBGR_F32");
	OutputStreamTestSub(TextureFormat::kRGBA_U8,	"TextureFormat::kRGBA_U8");
	OutputStreamTestSub(TextureFormat::kRGBA_S8,	"TextureFormat::kRGBA_S8");
	OutputStreamTestSub(TextureFormat::kRGBA_U16,	"TextureFormat::kRGBA_U16");
	OutputStreamTestSub(TextureFormat::kRGBA_S16,	"TextureFormat::kRGBA_S16");
	OutputStreamTestSub(TextureFormat::kRGBA_U32,	"TextureFormat::kRGBA_U32");
	OutputStreamTestSub(TextureFormat::kRGBA_S32,	"TextureFormat::kRGBA_S32");
	OutputStreamTestSub(TextureFormat::kRGBA_F32,	"TextureFormat::kRGBA_F32");
	OutputStreamTestSub(TextureFormat::kBGRA_U8,	"TextureFormat::kBGRA_U8");
	OutputStreamTestSub(TextureFormat::kBGRA_S8,	"TextureFormat::kBGRA_S8");
	OutputStreamTestSub(TextureFormat::kBGRA_U16,	"TextureFormat::kBGRA_U16");
	OutputStreamTestSub(TextureFormat::kBGRA_S16,	"TextureFormat::kBGRA_S16");
	OutputStreamTestSub(TextureFormat::kBGRA_U32,	"TextureFormat::kBGRA_U32");
	OutputStreamTestSub(TextureFormat::kBGRA_S32,	"TextureFormat::kBGRA_S32");
	OutputStreamTestSub(TextureFormat::kBGRA_F32,	"TextureFormat::kBGRA_F32");
	OutputStreamTestSub(TextureFormat::kARGB_U8,	"TextureFormat::kARGB_U8");
	OutputStreamTestSub(TextureFormat::kARGB_S8,	"TextureFormat::kARGB_S8");
	OutputStreamTestSub(TextureFormat::kARGB_U16,	"TextureFormat::kARGB_U16");
	OutputStreamTestSub(TextureFormat::kARGB_S16,	"TextureFormat::kARGB_S16");
	OutputStreamTestSub(TextureFormat::kARGB_U32,	"TextureFormat::kARGB_U32");
	OutputStreamTestSub(TextureFormat::kARGB_S32,	"TextureFormat::kARGB_S32");
	OutputStreamTestSub(TextureFormat::kARGB_F32,	"TextureFormat::kARGB_F32");
	OutputStreamTestSub(TextureFormat::kABGR_U8,	"TextureFormat::kABGR_U8");
	OutputStreamTestSub(TextureFormat::kABGR_S8,	"TextureFormat::kABGR_S8");
	OutputStreamTestSub(TextureFormat::kABGR_U16,	"TextureFormat::kABGR_U16");
	OutputStreamTestSub(TextureFormat::kABGR_S16,	"TextureFormat::kABGR_S16");
	OutputStreamTestSub(TextureFormat::kABGR_U32,	"TextureFormat::kABGR_U32");
	OutputStreamTestSub(TextureFormat::kABGR_S32,	"TextureFormat::kABGR_S32");
	OutputStreamTestSub(TextureFormat::kABGR_F32,	"TextureFormat::kABGR_F32");
	OutputStreamTestSub(TextureFormat::kDxt1,		"TextureFormat::kDxt1");
	OutputStreamTestSub(TextureFormat::kDxt3,		"TextureFormat::kDxt3");
	OutputStreamTestSub(TextureFormat::kDxt5,		"TextureFormat::kDxt5");

	OutputStreamTestSub(TextureFormat::kR_U8,		L"TextureFormat::kR_U8");
	OutputStreamTestSub(TextureFormat::kR_S8,		L"TextureFormat::kR_S8");
	OutputStreamTestSub(TextureFormat::kR_U16,		L"TextureFormat::kR_U16");
	OutputStreamTestSub(TextureFormat::kR_S16,		L"TextureFormat::kR_S16");
	OutputStreamTestSub(TextureFormat::kR_U32,		L"TextureFormat::kR_U32");
	OutputStreamTestSub(TextureFormat::kR_S32,		L"TextureFormat::kR_S32");
	OutputStreamTestSub(TextureFormat::kR_F32,		L"TextureFormat::kR_F32");
	OutputStreamTestSub(TextureFormat::kRG_U8,		L"TextureFormat::kRG_U8");
	OutputStreamTestSub(TextureFormat::kRG_S8,		L"TextureFormat::kRG_S8");
	OutputStreamTestSub(TextureFormat::kRG_U16,		L"TextureFormat::kRG_U16");
	OutputStreamTestSub(TextureFormat::kRG_S16,		L"TextureFormat::kRG_S16");
	OutputStreamTestSub(TextureFormat::kRG_U32,		L"TextureFormat::kRG_U32");
	OutputStreamTestSub(TextureFormat::kRG_S32,		L"TextureFormat::kRG_S32");
	OutputStreamTestSub(TextureFormat::kRG_F32,		L"TextureFormat::kRG_F32");
	OutputStreamTestSub(TextureFormat::kRGB_U8,		L"TextureFormat::kRGB_U8");
	OutputStreamTestSub(TextureFormat::kRGB_S8,		L"TextureFormat::kRGB_S8");
	OutputStreamTestSub(TextureFormat::kRGB_U16,	L"TextureFormat::kRGB_U16");
	OutputStreamTestSub(TextureFormat::kRGB_S16,	L"TextureFormat::kRGB_S16");
	OutputStreamTestSub(TextureFormat::kRGB_U32,	L"TextureFormat::kRGB_U32");
	OutputStreamTestSub(TextureFormat::kRGB_S32,	L"TextureFormat::kRGB_S32");
	OutputStreamTestSub(TextureFormat::kRGB_F32,	L"TextureFormat::kRGB_F32");
	OutputStreamTestSub(TextureFormat::kBGR_U8,		L"TextureFormat::kBGR_U8");
	OutputStreamTestSub(TextureFormat::kBGR_S8,		L"TextureFormat::kBGR_S8");
	OutputStreamTestSub(TextureFormat::kBGR_U16,	L"TextureFormat::kBGR_U16");
	OutputStreamTestSub(TextureFormat::kBGR_S16,	L"TextureFormat::kBGR_S16");
	OutputStreamTestSub(TextureFormat::kBGR_U32,	L"TextureFormat::kBGR_U32");
	OutputStreamTestSub(TextureFormat::kBGR_S32,	L"TextureFormat::kBGR_S32");
	OutputStreamTestSub(TextureFormat::kBGR_F32,	L"TextureFormat::kBGR_F32");
	OutputStreamTestSub(TextureFormat::kRGBA_U8,	L"TextureFormat::kRGBA_U8");
	OutputStreamTestSub(TextureFormat::kRGBA_S8,	L"TextureFormat::kRGBA_S8");
	OutputStreamTestSub(TextureFormat::kRGBA_U16,	L"TextureFormat::kRGBA_U16");
	OutputStreamTestSub(TextureFormat::kRGBA_S16,	L"TextureFormat::kRGBA_S16");
	OutputStreamTestSub(TextureFormat::kRGBA_U32,	L"TextureFormat::kRGBA_U32");
	OutputStreamTestSub(TextureFormat::kRGBA_S32,	L"TextureFormat::kRGBA_S32");
	OutputStreamTestSub(TextureFormat::kRGBA_F32,	L"TextureFormat::kRGBA_F32");
	OutputStreamTestSub(TextureFormat::kBGRA_U8,	L"TextureFormat::kBGRA_U8");
	OutputStreamTestSub(TextureFormat::kBGRA_S8,	L"TextureFormat::kBGRA_S8");
	OutputStreamTestSub(TextureFormat::kBGRA_U16,	L"TextureFormat::kBGRA_U16");
	OutputStreamTestSub(TextureFormat::kBGRA_S16,	L"TextureFormat::kBGRA_S16");
	OutputStreamTestSub(TextureFormat::kBGRA_U32,	L"TextureFormat::kBGRA_U32");
	OutputStreamTestSub(TextureFormat::kBGRA_S32,	L"TextureFormat::kBGRA_S32");
	OutputStreamTestSub(TextureFormat::kBGRA_F32,	L"TextureFormat::kBGRA_F32");
	OutputStreamTestSub(TextureFormat::kARGB_U8,	L"TextureFormat::kARGB_U8");
	OutputStreamTestSub(TextureFormat::kARGB_S8,	L"TextureFormat::kARGB_S8");
	OutputStreamTestSub(TextureFormat::kARGB_U16,	L"TextureFormat::kARGB_U16");
	OutputStreamTestSub(TextureFormat::kARGB_S16,	L"TextureFormat::kARGB_S16");
	OutputStreamTestSub(TextureFormat::kARGB_U32,	L"TextureFormat::kARGB_U32");
	OutputStreamTestSub(TextureFormat::kARGB_S32,	L"TextureFormat::kARGB_S32");
	OutputStreamTestSub(TextureFormat::kARGB_F32,	L"TextureFormat::kARGB_F32");
	OutputStreamTestSub(TextureFormat::kABGR_U8,	L"TextureFormat::kABGR_U8");
	OutputStreamTestSub(TextureFormat::kABGR_S8,	L"TextureFormat::kABGR_S8");
	OutputStreamTestSub(TextureFormat::kABGR_U16,	L"TextureFormat::kABGR_U16");
	OutputStreamTestSub(TextureFormat::kABGR_S16,	L"TextureFormat::kABGR_S16");
	OutputStreamTestSub(TextureFormat::kABGR_U32,	L"TextureFormat::kABGR_U32");
	OutputStreamTestSub(TextureFormat::kABGR_S32,	L"TextureFormat::kABGR_S32");
	OutputStreamTestSub(TextureFormat::kABGR_F32,	L"TextureFormat::kABGR_F32");
	OutputStreamTestSub(TextureFormat::kDxt1,		L"TextureFormat::kDxt1");
	OutputStreamTestSub(TextureFormat::kDxt3,		L"TextureFormat::kDxt3");
	OutputStreamTestSub(TextureFormat::kDxt5,		L"TextureFormat::kDxt5");
}

GTEST_TEST(TextureFormatTest, SerializeTest)
{
	using namespace bksge::serialization;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(bksge::TextureFormat::kRGBA_U8);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(bksge::TextureFormat::kR_F32);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(bksge::TextureFormat::kRG_S32);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(bksge::TextureFormat::kRGBA_U16);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(bksge::TextureFormat::kBGR_U32);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(bksge::TextureFormat::kDxt1);
#endif
}

GTEST_TEST(Render_TextureFormat, HashTest)
{
	std::hash<bksge::TextureFormat> h;

	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::TextureFormat::kR_U8));
	v.push_back(h(bksge::TextureFormat::kR_S8));
	v.push_back(h(bksge::TextureFormat::kR_U16));
	v.push_back(h(bksge::TextureFormat::kR_S16));
	v.push_back(h(bksge::TextureFormat::kR_U32));
	v.push_back(h(bksge::TextureFormat::kR_S32));
	v.push_back(h(bksge::TextureFormat::kR_F32));
	v.push_back(h(bksge::TextureFormat::kRG_U8));
	v.push_back(h(bksge::TextureFormat::kRG_S8));
	v.push_back(h(bksge::TextureFormat::kRG_U16));
	v.push_back(h(bksge::TextureFormat::kRG_S16));
	v.push_back(h(bksge::TextureFormat::kRG_U32));
	v.push_back(h(bksge::TextureFormat::kRG_S32));
	v.push_back(h(bksge::TextureFormat::kRG_F32));
	v.push_back(h(bksge::TextureFormat::kRGB_U8));
	v.push_back(h(bksge::TextureFormat::kRGB_S8));
	v.push_back(h(bksge::TextureFormat::kRGB_U16));
	v.push_back(h(bksge::TextureFormat::kRGB_S16));
	v.push_back(h(bksge::TextureFormat::kRGB_U32));
	v.push_back(h(bksge::TextureFormat::kRGB_S32));
	v.push_back(h(bksge::TextureFormat::kRGB_F32));
	v.push_back(h(bksge::TextureFormat::kBGR_U8));
	v.push_back(h(bksge::TextureFormat::kBGR_S8));
	v.push_back(h(bksge::TextureFormat::kBGR_U16));
	v.push_back(h(bksge::TextureFormat::kBGR_S16));
	v.push_back(h(bksge::TextureFormat::kBGR_U32));
	v.push_back(h(bksge::TextureFormat::kBGR_S32));
	v.push_back(h(bksge::TextureFormat::kBGR_F32));
	v.push_back(h(bksge::TextureFormat::kRGBA_U8));
	v.push_back(h(bksge::TextureFormat::kRGBA_S8));
	v.push_back(h(bksge::TextureFormat::kRGBA_U16));
	v.push_back(h(bksge::TextureFormat::kRGBA_S16));
	v.push_back(h(bksge::TextureFormat::kRGBA_U32));
	v.push_back(h(bksge::TextureFormat::kRGBA_S32));
	v.push_back(h(bksge::TextureFormat::kRGBA_F32));
	v.push_back(h(bksge::TextureFormat::kBGRA_U8));
	v.push_back(h(bksge::TextureFormat::kBGRA_S8));
	v.push_back(h(bksge::TextureFormat::kBGRA_U16));
	v.push_back(h(bksge::TextureFormat::kBGRA_S16));
	v.push_back(h(bksge::TextureFormat::kBGRA_U32));
	v.push_back(h(bksge::TextureFormat::kBGRA_S32));
	v.push_back(h(bksge::TextureFormat::kBGRA_F32));
	v.push_back(h(bksge::TextureFormat::kARGB_U8));
	v.push_back(h(bksge::TextureFormat::kARGB_S8));
	v.push_back(h(bksge::TextureFormat::kARGB_U16));
	v.push_back(h(bksge::TextureFormat::kARGB_S16));
	v.push_back(h(bksge::TextureFormat::kARGB_U32));
	v.push_back(h(bksge::TextureFormat::kARGB_S32));
	v.push_back(h(bksge::TextureFormat::kARGB_F32));
	v.push_back(h(bksge::TextureFormat::kABGR_U8));
	v.push_back(h(bksge::TextureFormat::kABGR_S8));
	v.push_back(h(bksge::TextureFormat::kABGR_U16));
	v.push_back(h(bksge::TextureFormat::kABGR_S16));
	v.push_back(h(bksge::TextureFormat::kABGR_U32));
	v.push_back(h(bksge::TextureFormat::kABGR_S32));
	v.push_back(h(bksge::TextureFormat::kABGR_F32));
	v.push_back(h(bksge::TextureFormat::kDxt1));
	v.push_back(h(bksge::TextureFormat::kDxt3));
	v.push_back(h(bksge::TextureFormat::kDxt5));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::TextureFormat::kR_U8));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace texture_format_test

}	// namespace bksge_core_render_test
