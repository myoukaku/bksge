/**
 *	@file	unit_test_core_render_sampler.cpp
 *
 *	@brief	Sampler のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/sampler.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <functional>
#include <vector>
#include <algorithm>
#include "serialize_test.hpp"

GTEST_TEST(Render_Sampler, DefaultConstructTest)
{
	using namespace bksge;

	Sampler sampler;

	EXPECT_EQ(FilterMode::kNearest, sampler.min_filter());
	EXPECT_EQ(FilterMode::kNearest, sampler.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler.border_color());
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
	EXPECT_EQ(FilterMode::kLinear,  sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest, sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat, sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,  sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat, sampler2.address_mode_w());

	// コピー元を変更してもコピー先は変わらない
	sampler1.SetMagFilter(FilterMode::kLinear);
	sampler1.SetAddressModeW(AddressMode::kClamp);
	EXPECT_EQ(FilterMode::kLinear,	sampler1.min_filter());
	EXPECT_EQ(FilterMode::kLinear,	sampler1.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_w());
	EXPECT_EQ(FilterMode::kLinear,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());

	// コピー先を変更してもコピー元は変わらない
	sampler2.SetMinFilter(FilterMode::kNearest);
	sampler2.SetAddressModeU(AddressMode::kClamp);
	EXPECT_EQ(FilterMode::kLinear,	sampler1.min_filter());
	EXPECT_EQ(FilterMode::kLinear,	sampler1.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_w());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());

	// コピー代入
	sampler1 = sampler2;
	EXPECT_EQ(FilterMode::kNearest,	sampler1.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler1.mag_filter());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_w());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());

	// 自己代入
	sampler2 = sampler2;
	EXPECT_EQ(FilterMode::kNearest,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kClamp,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());

	// 多重代入
	sampler1 = sampler2 = Sampler();
	EXPECT_EQ(FilterMode::kNearest,	sampler1.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler1.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler1.address_mode_w());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.min_filter());
	EXPECT_EQ(FilterMode::kNearest,	sampler2.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat,	sampler2.address_mode_w());
}

BKSGE_WARNING_POP()

GTEST_TEST(Render_Sampler, SetParameterTest)
{
	using namespace bksge;

	Sampler sampler;
	EXPECT_EQ(FilterMode::kNearest, sampler.min_filter());
	EXPECT_EQ(FilterMode::kNearest, sampler.mag_filter());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_u());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_v());
	EXPECT_EQ(AddressMode::kRepeat, sampler.address_mode_w());
	EXPECT_EQ(BorderColor::kOpaqueBlack, sampler.border_color());

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

	sampler.SetBorderColor(BorderColor::kOpaqueWhite);
	EXPECT_EQ(BorderColor::kOpaqueWhite, sampler.border_color());
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
	sampler8.SetBorderColor(BorderColor::kOpaqueBlack);

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
		EXPECT_EQ("{ FilterMode::kNearest, FilterMode::kNearest, AddressMode::kRepeat, AddressMode::kRepeat, AddressMode::kRepeat, BorderColor::kOpaqueBlack }", ss.str());
	}
	{
		Sampler sampler;
		sampler.SetMinFilter(FilterMode::kNearest);
		sampler.SetMagFilter(FilterMode::kLinear);
		sampler.SetAddressModeU(AddressMode::kClamp);
		sampler.SetAddressModeV(AddressMode::kRepeat);
		sampler.SetAddressModeW(AddressMode::kBorder);
		sampler.SetBorderColor(BorderColor::kTransparentBlack);

		std::wstringstream ss;
		ss << sampler;
		EXPECT_EQ(L"{ FilterMode::kNearest, FilterMode::kLinear, AddressMode::kClamp, AddressMode::kRepeat, AddressMode::kBorder, BorderColor::kTransparentBlack }", ss.str());
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
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(sampler);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(sampler);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(sampler);
#endif
}

GTEST_TEST(Render_Sampler, HashTest)
{
	std::hash<bksge::Sampler> h;

	bksge::Sampler s1;
	bksge::Sampler s2;
	bksge::Sampler s3;
	bksge::Sampler s4;
	bksge::Sampler s5;
	bksge::Sampler s6;
	bksge::Sampler s7;

	s2.SetMinFilter(bksge::FilterMode::kLinear);
	s3.SetMagFilter(bksge::FilterMode::kLinear);
	s4.SetAddressModeU(bksge::AddressMode::kClamp);
	s5.SetAddressModeV(bksge::AddressMode::kClamp);
	s6.SetAddressModeW(bksge::AddressMode::kBorder);
	s7.SetBorderColor(bksge::BorderColor::kTransparentBlack);

	std::vector<std::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	v.push_back(h(s5));
	v.push_back(h(s6));
	v.push_back(h(s7));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s1));
	std::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
