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
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace texture_format_test
{

static_assert(sizeof(bksge::TextureFormat) == 4, "");

GTEST_TEST(TextureFormatTest, GetSizeInBytesTest)
{
	using namespace bksge::render;

	EXPECT_EQ(   0u, GetSizeInBytes(TextureFormat::kUndefined, 4, 4));

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
}

GTEST_TEST(TextureFormatTest,GetStrideInBytesTest)
{
	using namespace bksge::render;

	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kUndefined, 0));
	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kUndefined, 1));
	EXPECT_EQ( 0u, GetStrideInBytes(TextureFormat::kUndefined, 4));

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

	EXPECT_EQ(0u, GetMipmappedSizeInBytes(TextureFormat::kUndefined, 4, 4, 2));
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
	OutputStreamTestSub(TextureFormat::kRGBA_U8,	"TextureFormat::kRGBA_U8");
	OutputStreamTestSub(TextureFormat::kRGBA_S8,	"TextureFormat::kRGBA_S8");
	OutputStreamTestSub(TextureFormat::kRGBA_U16,	"TextureFormat::kRGBA_U16");
	OutputStreamTestSub(TextureFormat::kRGBA_S16,	"TextureFormat::kRGBA_S16");
	OutputStreamTestSub(TextureFormat::kRGBA_U32,	"TextureFormat::kRGBA_U32");
	OutputStreamTestSub(TextureFormat::kRGBA_S32,	"TextureFormat::kRGBA_S32");
	OutputStreamTestSub(TextureFormat::kRGBA_F32,	"TextureFormat::kRGBA_F32");

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
	OutputStreamTestSub(TextureFormat::kRGBA_U8,	L"TextureFormat::kRGBA_U8");
	OutputStreamTestSub(TextureFormat::kRGBA_S8,	L"TextureFormat::kRGBA_S8");
	OutputStreamTestSub(TextureFormat::kRGBA_U16,	L"TextureFormat::kRGBA_U16");
	OutputStreamTestSub(TextureFormat::kRGBA_S16,	L"TextureFormat::kRGBA_S16");
	OutputStreamTestSub(TextureFormat::kRGBA_U32,	L"TextureFormat::kRGBA_U32");
	OutputStreamTestSub(TextureFormat::kRGBA_S32,	L"TextureFormat::kRGBA_S32");
	OutputStreamTestSub(TextureFormat::kRGBA_F32,	L"TextureFormat::kRGBA_F32");
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
	bksge::hash<bksge::TextureFormat> h;

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
	v.push_back(h(bksge::TextureFormat::kRGBA_U8));
	v.push_back(h(bksge::TextureFormat::kRGBA_S8));
	v.push_back(h(bksge::TextureFormat::kRGBA_U16));
	v.push_back(h(bksge::TextureFormat::kRGBA_S16));
	v.push_back(h(bksge::TextureFormat::kRGBA_U32));
	v.push_back(h(bksge::TextureFormat::kRGBA_S32));
	v.push_back(h(bksge::TextureFormat::kRGBA_F32));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::TextureFormat::kR_U8));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace texture_format_test

}	// namespace bksge_core_render_test
