/**
 *	@file	unit_test_core_render_sampler.cpp
 *
 *	@brief	Sampler のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/sampler.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
//#include "serialize_test.hpp"

GTEST_TEST(Render_Sampler, DefaultConstructTest)
{
	using namespace bksge;

	Sampler sampler;

	EXPECT_EQ(nullptr, sampler.source().data());
	EXPECT_EQ(FilterMode::kNearest, sampler.min_filter());
	EXPECT_EQ(FilterMode::kNearest, sampler.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_w());
	EXPECT_EQ(Color4f(0,0,0,0), sampler.border_color());
	EXPECT_EQ(0u, sampler.source().width());
	EXPECT_EQ(0u, sampler.source().height());
	EXPECT_EQ(TextureFormat::kNone, sampler.source().format());
}

GTEST_TEST(Render_Sampler, Arg1ConstructTest)
{
	using namespace bksge;

	const Texture texture(TextureFormat::kRGBA_U8, {16, 8});
	const Sampler sampler(texture);

	EXPECT_EQ(FilterMode::kNearest, sampler.min_filter());
	EXPECT_EQ(FilterMode::kNearest, sampler.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_w());
	EXPECT_EQ(Color4f(0,0,0,0), sampler.border_color());
	EXPECT_NE(nullptr, sampler.source().data());
	EXPECT_EQ(texture.data(), sampler.source().data());
	EXPECT_EQ(16u, sampler.source().width());
	EXPECT_EQ( 8u, sampler.source().height());
	EXPECT_EQ(TextureFormat::kRGBA_U8, sampler.source().format());
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

GTEST_TEST(Render_Sampler, CopyTest)
{
	using namespace bksge;

	const Texture texture1(TextureFormat::kRGBA_U8, {16, 8});
	const Texture texture2(TextureFormat::kRGB_F32, {32, 24});
	Sampler sampler1(texture1);
	sampler1.SetMinFilter(FilterMode::kLinear);
	sampler1.SetAddressModeV(AddressMode::kClamp);

	Sampler sampler2(sampler1);	// コピーコンストラクタ
	EXPECT_EQ(FilterMode::kLinear,  sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest, sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat, sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,  sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat, sampler2.address_mode_w());
	EXPECT_EQ(texture1, sampler2.source());

	// コピー元を変更してもコピー先は変わらない
	sampler1.SetMagFilter(FilterMode::kLinear);
	sampler1.SetAddressModeW(AddressMode::kClamp);
	sampler1.SetSource(texture2);
	EXPECT_EQ(FilterMode::kLinear,	sampler1.min_filter());
	EXPECT_EQ(FilterMode::kLinear,	sampler1.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_w());
	EXPECT_EQ(texture2,				sampler1.source());
	EXPECT_EQ(FilterMode::kLinear,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());
	EXPECT_EQ(texture1,				sampler2.source());

	// コピー先を変更してもコピー元は変わらない
	sampler2.SetMinFilter(FilterMode::kNearest);
	sampler2.SetAddressModeU(AddressMode::kClamp);
	EXPECT_EQ(FilterMode::kLinear,	sampler1.min_filter());
	EXPECT_EQ(FilterMode::kLinear,	sampler1.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_w());
	EXPECT_EQ(texture2,				sampler1.source());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());
	EXPECT_EQ(texture1,				sampler2.source());

	// コピー代入
	sampler1 = sampler2;
	EXPECT_EQ(FilterMode::kNearest,	sampler1.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler1.mag_filter());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_w());
	EXPECT_EQ(texture1,				sampler1.source());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());
	EXPECT_EQ(texture1,				sampler2.source());

	// 自己代入
	sampler2 = sampler2;
	EXPECT_EQ(FilterMode::kNearest,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());
	EXPECT_EQ(texture1,				sampler2.source());

	// 多重代入
	sampler1 = sampler2 = Sampler();
	EXPECT_EQ(FilterMode::kNearest,	sampler1.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler1.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_w());
	EXPECT_EQ(nullptr,				sampler1.source().data());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());
	EXPECT_EQ(nullptr,				sampler2.source().data());
}

BKSGE_WARNING_POP()

GTEST_TEST(Render_Sampler, IdTest)
{
	using namespace bksge;

	const Texture tex1(TextureFormat::kRGBA_U8, {8, 8});
	const Texture tex2(TextureFormat::kRGBA_U8, {8, 8});
	const Texture tex3(TextureFormat::kRGB_F32, {32, 64});

	const Sampler sampler1;
	const Sampler sampler2;
	const Sampler sampler3(tex1);
	const Sampler sampler4(tex1);
	const Sampler sampler5(tex2);
	const Sampler sampler6(tex3);
	const Sampler sampler7(sampler1);
	const Sampler sampler8(sampler3);
	Sampler sampler9;
	sampler9 = sampler1;

	EXPECT_TRUE (sampler1 == sampler1);
	EXPECT_TRUE (sampler1 == sampler2);
	EXPECT_FALSE(sampler1 == sampler3);
	EXPECT_FALSE(sampler1 == sampler4);
	EXPECT_FALSE(sampler1 == sampler5);
	EXPECT_FALSE(sampler1 == sampler6);
	EXPECT_TRUE (sampler1 == sampler7);
	EXPECT_FALSE(sampler1 == sampler8);
	EXPECT_TRUE (sampler1 == sampler9);
}

GTEST_TEST(Render_Sampler, SetParameterTest)
{
	using namespace bksge;

	const Texture texture(TextureFormat::kRGBA_U8, {16, 8});

	Sampler sampler;
	EXPECT_EQ(nullptr, sampler.source().data());
	EXPECT_EQ(FilterMode::kNearest, sampler.min_filter());
	EXPECT_EQ(FilterMode::kNearest, sampler.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_w());
	EXPECT_EQ(Color4f(0,0,0,0), sampler.border_color());

	sampler.SetSource(texture);
	EXPECT_NE(nullptr, sampler.source().data());
	EXPECT_EQ(texture.data(), sampler.source().data());

	sampler.SetMinFilter(FilterMode::kLinear);
	EXPECT_EQ(FilterMode::kLinear, sampler.min_filter());

	sampler.SetMagFilter(FilterMode::kLinear);
	EXPECT_EQ(FilterMode::kLinear, sampler.mag_filter());

	sampler.SetAddressModeU(AddressMode::kBorder);
	EXPECT_EQ(AddressMode::kBorder, sampler.address_mode_u());

	sampler.SetAddressModeV(AddressMode::kClamp);
	EXPECT_EQ(AddressMode::kClamp, sampler.address_mode_v());

	sampler.SetAddressModeW(AddressMode::kBorder);
	EXPECT_EQ(AddressMode::kBorder, sampler.address_mode_w());

	sampler.SetBorderColor(Color4f{0, 1, 0, 0});
	EXPECT_EQ(Color4f(0,1,0,0), sampler.border_color());
}

GTEST_TEST(Render_Sampler, CompareTest)
{
	using namespace bksge;

	const Texture texture(TextureFormat::kRGBA_U8, {16, 8});

	Sampler sampler1;
	sampler1.SetSource(texture);
	sampler1.SetMinFilter(FilterMode::kLinear);
	sampler1.SetMagFilter(FilterMode::kNearest);
	sampler1.SetAddressModeU(AddressMode::kRepeat);
	sampler1.SetAddressModeV(AddressMode::kClamp);
	sampler1.SetAddressModeW(AddressMode::kBorder);
	sampler1.SetBorderColor(Color4f{0, 1, 0, 0});

	const Sampler sampler2(sampler1);
	Sampler sampler3(sampler1);
	sampler3.SetMinFilter(FilterMode::kNearest);
	Sampler sampler4(sampler1);
	sampler4.SetMagFilter(FilterMode::kLinear);
	Sampler sampler5(sampler1);
	sampler5.SetAddressModeU(AddressMode::kClamp);
	Sampler sampler6(sampler1);
	sampler6.SetAddressModeV(AddressMode::kBorder);
	Sampler sampler7(sampler1);
	sampler7.SetAddressModeW(AddressMode::kRepeat);
	Sampler sampler8(sampler1);
	sampler8.SetBorderColor(Color4f{1, 1, 0, 0});

	EXPECT_TRUE (sampler1 == sampler1);
	EXPECT_TRUE (sampler1 == sampler2);
	EXPECT_FALSE(sampler1 == sampler3);
	EXPECT_FALSE(sampler1 == sampler4);
	EXPECT_FALSE(sampler1 == sampler5);
	EXPECT_FALSE(sampler1 == sampler6);
	EXPECT_FALSE(sampler1 == sampler7);
	EXPECT_FALSE(sampler1 == sampler8);

	EXPECT_FALSE(sampler1 != sampler1);
	EXPECT_FALSE(sampler1 != sampler2);
	EXPECT_TRUE (sampler1 != sampler3);
	EXPECT_TRUE (sampler1 != sampler4);
	EXPECT_TRUE (sampler1 != sampler5);
	EXPECT_TRUE (sampler1 != sampler6);
	EXPECT_TRUE (sampler1 != sampler7);
	EXPECT_TRUE (sampler1 != sampler8);
}

GTEST_TEST(Render_Sampler, OutputStreamTest)
{
	using namespace bksge;

	{
		Sampler sampler;

		std::stringstream ss;
		ss << sampler;
		EXPECT_EQ("{ { TextureFormat::kNone, { 0, 0 }, 0, {  } }, FilterMode::kNearest, FilterMode::kNearest, AddressMode::kRepeat, AddressMode::kRepeat, AddressMode::kRepeat, { 0, 0, 0, 0 } }", ss.str());
	}
	{
		const std::uint8_t pixels[] =
		{
			 1, 2, 3, 4,  5, 6, 7, 8,
			 9,10,11,12, 13,14,15,16,
			17,18,19,20, 21,22,23,24,
		};
		const Texture texture(TextureFormat::kRGBA_U8, {2, 3}, pixels);

		Sampler sampler;
		sampler.SetSource(texture);
		sampler.SetMinFilter(FilterMode::kNearest);
		sampler.SetMagFilter(FilterMode::kLinear);
		sampler.SetAddressModeU(AddressMode::kClamp);
		sampler.SetAddressModeV(AddressMode::kRepeat);
		sampler.SetAddressModeW(AddressMode::kBorder);
		sampler.SetBorderColor(Color4f{ 1, 0, 0, 1 });

		std::wstringstream ss;
		ss << sampler;
		EXPECT_EQ(L"{ { TextureFormat::kRGBA_U8, { 2, 3 }, 1, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,  } }, FilterMode::kNearest, FilterMode::kLinear, AddressMode::kClamp, AddressMode::kRepeat, AddressMode::kBorder, { 1, 0, 0, 1 } }", ss.str());
	}
}

#if 0
GTEST_TEST(Render_Sampler, SerializeTest)
{
	using namespace bksge;
	using namespace bksge::archive;

	const Texture texture(TextureFormat::kRGBA_U8, {16, 8});

	Sampler sampler;
	sampler.SetSource(texture);
	sampler.SetMinFilter(FilterMode::kNearest);
	sampler.SetMagFilter(FilterMode::kLinear);
	sampler.SetAddressModeU(AddressMode::kClamp);
	sampler.SetAddressModeV(AddressMode::kRepeat);
	sampler.SetAddressModeW(AddressMode::kBorder);

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (sampler);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (sampler);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (sampler);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(sampler);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(sampler);
#endif
}
#endif
