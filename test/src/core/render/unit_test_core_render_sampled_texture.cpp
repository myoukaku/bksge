/**
 *	@file	unit_test_core_render_sampled_texture.cpp
 *
 *	@brief	SampledTexture のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/sampled_texture.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <functional>
#include <vector>
#include <algorithm>
#include "serialize_test.hpp"

GTEST_TEST(Render_SampledTexture, DefaultConstructTest)
{
	bksge::SampledTexture st;

	EXPECT_EQ(bksge::FilterMode::kNearest,      st.sampler().min_filter());
	EXPECT_EQ(bksge::FilterMode::kNearest,      st.sampler().mag_filter());
	EXPECT_EQ(bksge::AddressMode::kRepeat,      st.sampler().address_mode_u());
	EXPECT_EQ(bksge::AddressMode::kRepeat,      st.sampler().address_mode_v());
	EXPECT_EQ(bksge::AddressMode::kRepeat,      st.sampler().address_mode_w());
	EXPECT_EQ(bksge::BorderColor::kOpaqueBlack, st.sampler().border_color());
	EXPECT_EQ(bksge::TextureFormat::kNone,      st.texture().format());
	EXPECT_EQ(0u,                               st.texture().width());
	EXPECT_EQ(0u,                               st.texture().height());
	EXPECT_EQ(0u,                               st.texture().mipmap_count());
	EXPECT_EQ(0u,                               st.texture().stride());
	EXPECT_EQ(nullptr,                          st.texture().data());
}

GTEST_TEST(Render_SampledTexture, SetParameterTest)
{
	bksge::SampledTexture st;

	st.sampler().SetMinFilter(bksge::FilterMode::kLinear);
	st.sampler().SetMagFilter(bksge::FilterMode::kLinear);
	st.sampler().SetAddressModeU(bksge::AddressMode::kBorder);
	st.sampler().SetAddressModeV(bksge::AddressMode::kClamp);
	st.sampler().SetAddressModeW(bksge::AddressMode::kBorder);
	st.sampler().SetBorderColor(bksge::BorderColor::kOpaqueWhite);
	st.texture() = bksge::Texture(bksge::TextureFormat::kRGBA_U8, {32, 24}, 3);

	EXPECT_EQ(bksge::FilterMode::kLinear,       st.sampler().min_filter());
	EXPECT_EQ(bksge::FilterMode::kLinear,       st.sampler().mag_filter());
	EXPECT_EQ(bksge::AddressMode::kBorder,      st.sampler().address_mode_u());
	EXPECT_EQ(bksge::AddressMode::kClamp,       st.sampler().address_mode_v());
	EXPECT_EQ(bksge::AddressMode::kBorder,      st.sampler().address_mode_w());
	EXPECT_EQ(bksge::BorderColor::kOpaqueWhite, st.sampler().border_color());
	EXPECT_EQ(bksge::TextureFormat::kRGBA_U8,   st.texture().format());
	EXPECT_EQ(32u,                              st.texture().width());
	EXPECT_EQ(24u,                              st.texture().height());
	EXPECT_EQ(3u,                               st.texture().mipmap_count());
	EXPECT_EQ(128u,                             st.texture().stride());
	EXPECT_NE(nullptr,                          st.texture().data());
}

GTEST_TEST(Render_SampledTexture, CompareTest)
{
	bksge::SampledTexture s1;
	bksge::SampledTexture s2;
	bksge::SampledTexture s3;
	bksge::SampledTexture s4;
	bksge::SampledTexture s5;
	bksge::SampledTexture s6;
	bksge::SampledTexture s7;
	bksge::SampledTexture s8;
	bksge::SampledTexture s9;

	s3.sampler().SetMinFilter(bksge::FilterMode::kLinear);
	s4.sampler().SetMagFilter(bksge::FilterMode::kLinear);
	s5.sampler().SetAddressModeU(bksge::AddressMode::kClamp);
	s6.sampler().SetAddressModeV(bksge::AddressMode::kClamp);
	s7.sampler().SetAddressModeW(bksge::AddressMode::kBorder);
	s8.sampler().SetBorderColor(bksge::BorderColor::kTransparentBlack);
	s9.texture() = bksge::Texture(bksge::TextureFormat::kRGBA_U8, {32, 24}, 3);

	EXPECT_TRUE (s1 == s1);
	EXPECT_TRUE (s1 == s2);
	EXPECT_FALSE(s1 == s3);
	EXPECT_FALSE(s1 == s4);
	EXPECT_FALSE(s1 == s5);
	EXPECT_FALSE(s1 == s6);
	EXPECT_FALSE(s1 == s7);
	EXPECT_FALSE(s1 == s8);
	EXPECT_FALSE(s1 == s9);

	EXPECT_FALSE(s1 != s1);
	EXPECT_FALSE(s1 != s2);
	EXPECT_TRUE (s1 != s3);
	EXPECT_TRUE (s1 != s4);
	EXPECT_TRUE (s1 != s5);
	EXPECT_TRUE (s1 != s6);
	EXPECT_TRUE (s1 != s7);
	EXPECT_TRUE (s1 != s8);
	EXPECT_TRUE (s1 != s9);
}

GTEST_TEST(Render_SampledTexture, OutputStreamTest)
{
	{
		bksge::SampledTexture st;

		std::stringstream ss;
		ss << st;
		EXPECT_EQ("{ { FilterMode::kNearest, FilterMode::kNearest, AddressMode::kRepeat, AddressMode::kRepeat, AddressMode::kRepeat, BorderColor::kOpaqueBlack }, { TextureFormat::kNone, { 0, 0 }, 0, {  } } }", ss.str());
	}
	{
		bksge::SampledTexture st;
		st.sampler().SetMinFilter(bksge::FilterMode::kNearest);
		st.sampler().SetMagFilter(bksge::FilterMode::kLinear);
		st.sampler().SetAddressModeU(bksge::AddressMode::kClamp);
		st.sampler().SetAddressModeV(bksge::AddressMode::kRepeat);
		st.sampler().SetAddressModeW(bksge::AddressMode::kBorder);
		st.sampler().SetBorderColor(bksge::BorderColor::kTransparentBlack);
		st.texture() = bksge::Texture(bksge::TextureFormat::kRGBA_U16, {1, 2}, 4);

		std::wstringstream ss;
		ss << st;
		EXPECT_EQ(L"{ { FilterMode::kNearest, FilterMode::kLinear, AddressMode::kClamp, AddressMode::kRepeat, AddressMode::kBorder, BorderColor::kTransparentBlack }, { TextureFormat::kRGBA_U16, { 1, 2 }, 4, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  } } }", ss.str());
	}
}

#if 0	// TODO
GTEST_TEST(Render_SampledTexture, SerializeTest)
{
}
#endif

GTEST_TEST(Render_SampledTexture, HashTest)
{
	std::hash<bksge::SampledTexture> h;

	bksge::SampledTexture s1;
	bksge::SampledTexture s2;
	bksge::SampledTexture s3;
	bksge::SampledTexture s4;
	bksge::SampledTexture s5;
	bksge::SampledTexture s6;
	bksge::SampledTexture s7;
	bksge::SampledTexture s8;

	s2.sampler().SetMinFilter(bksge::FilterMode::kLinear);
	s3.sampler().SetMagFilter(bksge::FilterMode::kLinear);
	s4.sampler().SetAddressModeU(bksge::AddressMode::kClamp);
	s5.sampler().SetAddressModeV(bksge::AddressMode::kClamp);
	s6.sampler().SetAddressModeW(bksge::AddressMode::kBorder);
	s7.sampler().SetBorderColor(bksge::BorderColor::kTransparentBlack);
	s8.texture() = bksge::Texture(bksge::TextureFormat::kRGBA_U8, {32, 24}, 3);

	std::vector<std::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	v.push_back(h(s5));
	v.push_back(h(s6));
	v.push_back(h(s7));
	v.push_back(h(s8));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s1));
	std::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
