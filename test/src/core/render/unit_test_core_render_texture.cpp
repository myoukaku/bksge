/**
 *	@file	unit_test_core_render_texture.cpp
 *
 *	@brief	Texture のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/texture.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <gtest/gtest.h>
//#include "serialize_test.hpp"

GTEST_TEST(Render_Texture, BasicTest)
{
	using namespace bksge;

	Texture tex1;
	Texture tex2;
	Texture tex3(TextureFormat::kRGBA_U8, {16, 24});
	Texture tex4(TextureFormat::kRGBA_F32, {32, 64}, 2);

	EXPECT_TRUE(tex1.id() != tex2.id());
	EXPECT_TRUE(tex1.id() != tex3.id());
	EXPECT_TRUE(tex1.id() != tex4.id());
	EXPECT_TRUE(tex2.id() != tex3.id());
	EXPECT_TRUE(tex2.id() != tex4.id());
	EXPECT_TRUE(tex3.id() != tex4.id());

	EXPECT_EQ(TextureFormat::kUndefined, tex1.format());
	EXPECT_EQ(TextureFormat::kUndefined, tex2.format());
	EXPECT_EQ(TextureFormat::kRGBA_U8,   tex3.format());
	EXPECT_EQ(TextureFormat::kRGBA_F32,  tex4.format());

	EXPECT_EQ( 0u, tex1.width());
	EXPECT_EQ( 0u, tex2.width());
	EXPECT_EQ(16u, tex3.width());
	EXPECT_EQ(32u, tex4.width());

	EXPECT_EQ( 0u, tex1.height());
	EXPECT_EQ( 0u, tex2.height());
	EXPECT_EQ(24u, tex3.height());
	EXPECT_EQ(64u, tex4.height());

	EXPECT_EQ(0u, tex1.mipmap_count());
	EXPECT_EQ(0u, tex2.mipmap_count());
	EXPECT_EQ(1u, tex3.mipmap_count());
	EXPECT_EQ(2u, tex4.mipmap_count());

	EXPECT_EQ(  0u, tex1.stride());
	EXPECT_EQ(  0u, tex2.stride());
	EXPECT_EQ( 64u, tex3.stride());
	EXPECT_EQ(512u, tex4.stride());

	EXPECT_TRUE(tex1.data() == nullptr);
	EXPECT_TRUE(tex2.data() == nullptr);
	EXPECT_TRUE(tex3.data() != nullptr);
	EXPECT_TRUE(tex4.data() != nullptr);
}

GTEST_TEST(Render_Texture, CopyTest)
{
	using namespace bksge;

	Texture tex1(TextureFormat::kRGBA_U8, {64, 8});
	Texture tex2(tex1);

	EXPECT_EQ(TextureFormat::kRGBA_U8, tex2.format());
	EXPECT_EQ(64u, tex2.width());
	EXPECT_EQ( 8u, tex2.height());
	EXPECT_EQ( 1u, tex2.mipmap_count());
	EXPECT_TRUE(tex2.data() != nullptr);

	Texture tex3;
	tex3 = tex2;

	EXPECT_EQ(TextureFormat::kRGBA_U8, tex3.format());
	EXPECT_EQ(64u, tex3.width());
	EXPECT_EQ( 8u, tex3.height());
	EXPECT_EQ( 1u, tex3.mipmap_count());
	EXPECT_TRUE(tex3.data() != nullptr);
}

GTEST_TEST(Render_Texture, CompareTest)
{
	using namespace bksge;
	const bksge::uint8_t pixels1[] =
	{
		 0, 1, 2, 3,  4, 5, 6, 7,  8, 9,10,11, 12,13,14,15,
		16,17,18,19, 20,21,22,23, 24,25,26,27, 28,29,30,31,
		32,33,34,35, 36,37,38,39, 40,41,42,43, 44,45,46,47,
	};
	const bksge::uint8_t pixels2[] =
	{
		 0, 1, 2, 3,  4, 5, 6, 7,  8, 9,10,11, 12,13,14,15,
		16,17,18,19, 20,21,22,23, 24,25,26,27, 28,29,30,31,
		32,33,34,35, 36,37,38,39, 40,41,42,43, 44,45,46,47,
	};
	const bksge::uint8_t pixels3[] =
	{
		 0, 1, 2, 3,  4, 5, 6, 7,  8, 9,10,11, 12,13,14,15,
		16,17,18,19, 20,21,22,23, 24,25,26,27, 28,29,30,31,
		32,33,34,35, 36,37,38,39, 40,41,42,43, 44,45,46,99,
	};

	const Texture tex1(TextureFormat::kRGBA_U8, {4, 3}, pixels1);
	const Texture tex2(TextureFormat::kRGBA_U8, {4, 3}, pixels1);
	const Texture tex3(TextureFormat::kRGBA_U8, {4, 3}, pixels1);
	const Texture tex4(TextureFormat::kRGBA_U8, {3, 4}, pixels1);
	const Texture tex5(TextureFormat::kRGBA_U8, {4, 3}, pixels2);
	const Texture tex6(TextureFormat::kRGBA_U8, {4, 3}, pixels3);
	const Texture tex7(TextureFormat::kRGBA_S8, {4, 3}, pixels1);
	const Texture tex8;
	const Texture tex9;

	EXPECT_TRUE (tex1 == tex1);
	EXPECT_TRUE (tex1 == tex2);
	EXPECT_TRUE (tex1 == tex3);
	EXPECT_FALSE(tex1 == tex4);
	EXPECT_TRUE (tex1 == tex5);
	EXPECT_FALSE(tex1 == tex6);
	EXPECT_FALSE(tex1 == tex7);
	EXPECT_FALSE(tex1 == tex8);
	EXPECT_FALSE(tex1 == tex9);
	EXPECT_TRUE (tex2 == tex3);
	EXPECT_TRUE (tex8 == tex9);

	EXPECT_FALSE(tex1 != tex1);
	EXPECT_FALSE(tex1 != tex2);
	EXPECT_FALSE(tex1 != tex3);
	EXPECT_TRUE (tex1 != tex4);
	EXPECT_FALSE(tex1 != tex5);
	EXPECT_TRUE (tex1 != tex6);
	EXPECT_TRUE (tex1 != tex7);
	EXPECT_TRUE (tex1 != tex8);
	EXPECT_TRUE (tex1 != tex9);
	EXPECT_FALSE(tex2 != tex3);
	EXPECT_FALSE(tex8 != tex9);
}

#if 0
GTEST_TEST(Render_Texture, SerializeTest)
{
	using namespace bksge;
	using namespace bksge::archive;

	const bksge::uint8_t pixels[] =
	{
		0, 1, 2, 3,  4, 5, 6, 7,  8, 9,10,11, 12,13,14,15,
		16,17,18,19, 20,21,22,23, 24,25,26,27, 28,29,30,31,
		32,33,34,35, 36,37,38,39, 40,41,42,43, 44,45,46,47,
	};

	Texture tex(TextureFormat::kRGBA_U8, {4, 3}, pixels);

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream> (tex);
	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream> (tex);
	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream> (tex);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  bksge::wstringstream>(tex);
	SerializeTest<xml_woarchive,   xml_wiarchive,   bksge::wstringstream>(tex);
#endif
}
#endif
