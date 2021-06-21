/**
 *	@file	unit_test_core_render_sampler.cpp
 *
 *	@brief	Sampler のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/sampler.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

GTEST_TEST(Render_Sampler, DefaultConstructTest)
{
	using namespace bksge;

	Sampler sampler;

	EXPECT_EQ(FilterMode::kNearest,      sampler.min_filter());
	EXPECT_EQ(FilterMode::kNearest,      sampler.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,      sampler.mip_filter());
	EXPECT_EQ(AddressMode::kRepeat,      sampler.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat,      sampler.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,      sampler.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler.border_color());
	EXPECT_EQ(-FLT_MAX,                  sampler.min_lod());
	EXPECT_EQ( FLT_MAX,                  sampler.max_lod());
	EXPECT_FALSE(sampler.enable_mipmap());
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

GTEST_TEST(Render_Sampler, CopyTest)
{
	using namespace bksge;

	Sampler sampler1;
	sampler1.SetMinFilter(FilterMode::kLinear);
	sampler1.SetAddressModeV(AddressMode::kClamp);

	Sampler sampler2(sampler1);	// コピーコンストラクタ
	EXPECT_EQ(FilterMode::kLinear,       sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,      sampler2.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,      sampler2.mip_filter());
	EXPECT_EQ(AddressMode::kRepeat,      sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,       sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,      sampler2.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler2.border_color());
	EXPECT_EQ(-FLT_MAX,                  sampler2.min_lod());
	EXPECT_EQ( FLT_MAX,                  sampler2.max_lod());
	EXPECT_FALSE(sampler2.enable_mipmap());

	// コピー元を変更してもコピー先は変わらない
	sampler1.SetMagFilter(FilterMode::kLinear);
	sampler1.SetMipFilter(MipmapMode::kNearest);
	sampler1.SetAddressModeW(AddressMode::kClamp);
	EXPECT_EQ(FilterMode::kLinear,	     sampler1.min_filter());
	EXPECT_EQ(FilterMode::kLinear,	     sampler1.mag_filter());
	EXPECT_EQ(MipmapMode::kNearest,	     sampler1.mip_filter());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	     sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kClamp,	     sampler1.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler1.border_color());
	EXPECT_EQ(-FLT_MAX,                  sampler1.min_lod());
	EXPECT_EQ( FLT_MAX,                  sampler1.max_lod());
	EXPECT_TRUE(sampler1.enable_mipmap());
	EXPECT_EQ(FilterMode::kLinear,	     sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	     sampler2.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,	     sampler2.mip_filter());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	     sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler2.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler2.border_color());
	EXPECT_EQ(-FLT_MAX,                  sampler2.min_lod());
	EXPECT_EQ( FLT_MAX,                  sampler2.max_lod());
	EXPECT_FALSE(sampler2.enable_mipmap());

	// コピー先を変更してもコピー元は変わらない
	sampler2.SetMinFilter(FilterMode::kNearest);
	sampler2.SetAddressModeU(AddressMode::kClamp);
	sampler2.SetMinLod(0.0f);
	sampler2.SetMaxLod(1.0f);
	EXPECT_EQ(FilterMode::kLinear,	     sampler1.min_filter());
	EXPECT_EQ(FilterMode::kLinear,	     sampler1.mag_filter());
	EXPECT_EQ(MipmapMode::kNearest,	     sampler1.mip_filter());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	     sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kClamp,	     sampler1.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler1.border_color());
	EXPECT_EQ(-FLT_MAX,                  sampler1.min_lod());
	EXPECT_EQ( FLT_MAX,                  sampler1.max_lod());
	EXPECT_TRUE(sampler1.enable_mipmap());
	EXPECT_EQ(FilterMode::kNearest,	     sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	     sampler2.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,	     sampler2.mip_filter());
	EXPECT_EQ(AddressMode::kClamp,	     sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	     sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler2.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler2.border_color());
	EXPECT_EQ(0.0f,                      sampler2.min_lod());
	EXPECT_EQ(1.0f,                      sampler2.max_lod());
	EXPECT_FALSE(sampler2.enable_mipmap());

	// コピー代入
	sampler1 = sampler2;
	EXPECT_EQ(FilterMode::kNearest,	     sampler1.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	     sampler1.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,	     sampler1.mip_filter());
	EXPECT_EQ(AddressMode::kClamp,	     sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	     sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler1.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler1.border_color());
	EXPECT_EQ(0.0f,                      sampler1.min_lod());
	EXPECT_EQ(1.0f,                      sampler1.max_lod());
	EXPECT_FALSE(sampler1.enable_mipmap());
	EXPECT_EQ(FilterMode::kNearest,	     sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	     sampler2.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,	     sampler2.mip_filter());
	EXPECT_EQ(AddressMode::kClamp,	     sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	     sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler2.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler2.border_color());
	EXPECT_EQ(0.0f,                      sampler2.min_lod());
	EXPECT_EQ(1.0f,                      sampler2.max_lod());
	EXPECT_FALSE(sampler2.enable_mipmap());

	// 自己代入
	sampler2 = sampler2;
	EXPECT_EQ(FilterMode::kNearest,	     sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	     sampler2.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,	     sampler2.mip_filter());
	EXPECT_EQ(AddressMode::kClamp,	     sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	     sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler2.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler2.border_color());
	EXPECT_EQ(0.0f,                      sampler2.min_lod());
	EXPECT_EQ(1.0f,                      sampler2.max_lod());
	EXPECT_FALSE(sampler2.enable_mipmap());

	// 多重代入
	sampler1 = sampler2 = Sampler();
	EXPECT_EQ(FilterMode::kNearest,	     sampler1.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	     sampler1.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,	     sampler1.mip_filter());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler1.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler1.border_color());
	EXPECT_EQ(-FLT_MAX,                  sampler1.min_lod());
	EXPECT_EQ( FLT_MAX,                  sampler1.max_lod());
	EXPECT_FALSE(sampler1.enable_mipmap());
	EXPECT_EQ(FilterMode::kNearest,	     sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	     sampler2.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,	     sampler2.mip_filter());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	     sampler2.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler2.border_color());
	EXPECT_EQ(-FLT_MAX,                  sampler2.min_lod());
	EXPECT_EQ( FLT_MAX,                  sampler2.max_lod());
	EXPECT_FALSE(sampler2.enable_mipmap());
}

BKSGE_WARNING_POP()

GTEST_TEST(Render_Sampler, SetParameterTest)
{
	using namespace bksge;

	Sampler sampler;
	EXPECT_EQ(FilterMode::kNearest,      sampler.min_filter());
	EXPECT_EQ(FilterMode::kNearest,      sampler.mag_filter());
	EXPECT_EQ(MipmapMode::kDisable,      sampler.mip_filter());
	EXPECT_EQ(AddressMode::kRepeat,      sampler.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat,      sampler.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,      sampler.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler.border_color());
	EXPECT_EQ(-FLT_MAX,                  sampler.min_lod());
	EXPECT_EQ( FLT_MAX,                  sampler.max_lod());
	EXPECT_FALSE(sampler.enable_mipmap());

	sampler.SetMinFilter(FilterMode::kLinear);
	EXPECT_EQ(FilterMode::kLinear, sampler.min_filter());

	sampler.SetMagFilter(FilterMode::kLinear);
	EXPECT_EQ(FilterMode::kLinear, sampler.mag_filter());

	sampler.SetMipFilter(MipmapMode::kNearest);
	EXPECT_EQ(MipmapMode::kNearest, sampler.mip_filter());
	EXPECT_TRUE(sampler.enable_mipmap());

	sampler.SetAddressModeU(AddressMode::kBorder);
	EXPECT_EQ(AddressMode::kBorder, sampler.address_mode_u());

	sampler.SetAddressModeV(AddressMode::kClamp);
	EXPECT_EQ(AddressMode::kClamp, sampler.address_mode_v());

	sampler.SetAddressModeW(AddressMode::kBorder);
	EXPECT_EQ(AddressMode::kBorder, sampler.address_mode_w());

	sampler.SetBorderColor(BorderColor::kOpaqueWhite);
	EXPECT_EQ(BorderColor::kOpaqueWhite, sampler.border_color());

	sampler.SetMinLod(-1.0f);
	EXPECT_EQ(-1.0f, sampler.min_lod());

	sampler.SetMaxLod(42.0f);
	EXPECT_EQ(42.0f, sampler.max_lod());
}

GTEST_TEST(Render_Sampler, CompareTest)
{
	using namespace bksge;

	Sampler sampler1;
	sampler1.SetMinFilter(FilterMode::kLinear);
	sampler1.SetMagFilter(FilterMode::kNearest);
	sampler1.SetAddressModeU(AddressMode::kRepeat);
	sampler1.SetAddressModeV(AddressMode::kClamp);
	sampler1.SetAddressModeW(AddressMode::kBorder);
	sampler1.SetBorderColor(BorderColor::kOpaqueWhite);

	Sampler sampler2(sampler1);
	Sampler sampler3(sampler1);
	Sampler sampler4(sampler1);
	Sampler sampler5(sampler1);
	Sampler sampler6(sampler1);
	Sampler sampler7(sampler1);
	Sampler sampler8(sampler1);
	Sampler sampler9(sampler1);
	Sampler sampler10(sampler1);
	Sampler sampler11(sampler1);

	sampler3.SetMinFilter(FilterMode::kNearest);
	sampler4.SetMagFilter(FilterMode::kLinear);
	sampler5.SetMipFilter(MipmapMode::kLinear);
	sampler6.SetAddressModeU(AddressMode::kClamp);
	sampler7.SetAddressModeV(AddressMode::kBorder);
	sampler8.SetAddressModeW(AddressMode::kRepeat);
	sampler9.SetBorderColor(BorderColor::kOpaqueBlack);
	sampler10.SetMinLod(-0.5f);
	sampler11.SetMaxLod(0.5f);

	EXPECT_TRUE (sampler1 == sampler1);
	EXPECT_TRUE (sampler1 == sampler2);
	EXPECT_FALSE(sampler1 == sampler3);
	EXPECT_FALSE(sampler1 == sampler4);
	EXPECT_FALSE(sampler1 == sampler5);
	EXPECT_FALSE(sampler1 == sampler6);
	EXPECT_FALSE(sampler1 == sampler7);
	EXPECT_FALSE(sampler1 == sampler8);
	EXPECT_FALSE(sampler1 == sampler9);
	EXPECT_FALSE(sampler1 == sampler10);
	EXPECT_FALSE(sampler1 == sampler11);

	EXPECT_FALSE(sampler1 != sampler1);
	EXPECT_FALSE(sampler1 != sampler2);
	EXPECT_TRUE (sampler1 != sampler3);
	EXPECT_TRUE (sampler1 != sampler4);
	EXPECT_TRUE (sampler1 != sampler5);
	EXPECT_TRUE (sampler1 != sampler6);
	EXPECT_TRUE (sampler1 != sampler7);
	EXPECT_TRUE (sampler1 != sampler8);
	EXPECT_TRUE (sampler1 != sampler9);
	EXPECT_TRUE (sampler1 != sampler10);
	EXPECT_TRUE (sampler1 != sampler11);
}

GTEST_TEST(Render_Sampler, OutputStreamTest)
{
	using namespace bksge;

	{
		Sampler sampler;
		sampler.SetMinLod(0.0f);
		sampler.SetMaxLod(0.0f);

		std::stringstream ss;
		ss << sampler;
		EXPECT_EQ("{ FilterMode::kNearest, FilterMode::kNearest, MipmapMode::kDisable, AddressMode::kRepeat, AddressMode::kRepeat, AddressMode::kRepeat, BorderColor::kOpaqueBlack, 0, 0 }", ss.str());
	}
	{
		Sampler sampler;
		sampler.SetMinFilter(FilterMode::kNearest);
		sampler.SetMagFilter(FilterMode::kLinear);
		sampler.SetMipFilter(MipmapMode::kLinear);
		sampler.SetAddressModeU(AddressMode::kClamp);
		sampler.SetAddressModeV(AddressMode::kRepeat);
		sampler.SetAddressModeW(AddressMode::kBorder);
		sampler.SetBorderColor(BorderColor::kTransparentBlack);
		sampler.SetMinLod(1.0f);
		sampler.SetMaxLod(2.0f);

		std::wstringstream ss;
		ss << sampler;
		EXPECT_EQ(L"{ FilterMode::kNearest, FilterMode::kLinear, MipmapMode::kLinear, AddressMode::kClamp, AddressMode::kRepeat, AddressMode::kBorder, BorderColor::kTransparentBlack, 1, 2 }", ss.str());
	}
}

GTEST_TEST(Render_Sampler, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::Sampler sampler;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(sampler);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(sampler);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(sampler);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	sampler.SetMinFilter(bksge::FilterMode::kNearest);
	sampler.SetMagFilter(bksge::FilterMode::kLinear);
	sampler.SetMipFilter(bksge::MipmapMode::kNearest);
	sampler.SetAddressModeU(bksge::AddressMode::kClamp);
	sampler.SetAddressModeV(bksge::AddressMode::kRepeat);
	sampler.SetAddressModeW(bksge::AddressMode::kBorder);
	sampler.SetBorderColor(bksge::BorderColor::kTransparentBlack);
	sampler.SetMinLod(-2.5f);
	sampler.SetMaxLod( 2.5f);

	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(sampler);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(sampler);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(sampler);
#endif
}

GTEST_TEST(Render_Sampler, HashTest)
{
	bksge::hash<bksge::Sampler> h;

	bksge::Sampler s1;
	bksge::Sampler s2;
	bksge::Sampler s3;
	bksge::Sampler s4;
	bksge::Sampler s5;
	bksge::Sampler s6;
	bksge::Sampler s7;
	bksge::Sampler s8;
	bksge::Sampler s9;
	bksge::Sampler s10;

	s2.SetMinFilter(bksge::FilterMode::kLinear);
	s3.SetMagFilter(bksge::FilterMode::kLinear);
	s4.SetMipFilter(bksge::MipmapMode::kNearest);
	s5.SetAddressModeU(bksge::AddressMode::kClamp);
	s6.SetAddressModeV(bksge::AddressMode::kClamp);
	s7.SetAddressModeW(bksge::AddressMode::kBorder);
	s8.SetBorderColor(bksge::BorderColor::kTransparentBlack);
	s9.SetMinLod(-0.5f);
	s10.SetMaxLod(0.5f);

	bksge::vector<bksge::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	v.push_back(h(s5));
	v.push_back(h(s6));
	v.push_back(h(s7));
	v.push_back(h(s8));
	v.push_back(h(s9));
	v.push_back(h(s10));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s1));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
