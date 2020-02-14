/**
 *	@file	unit_test_core_render_color_write_flag.cpp
 *
 *	@brief	ColorWriteFlag のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/color_write_flag.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <functional>
#include <vector>
#include <algorithm>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace color_write_flag_test
{

GTEST_TEST(Render_ColorWriteFlag, BasicTest)
{
	using bksge::ColorWriteFlag;

	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kNone;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kAlpha);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kRed;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kRed,   f & ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kAlpha);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kGreen;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kGreen, f & ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kAlpha);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kBlue;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kBlue,  f & ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kAlpha);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kAlpha;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kAlpha, f & ColorWriteFlag::kAlpha);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kRed | ColorWriteFlag::kBlue;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kRed,   f & ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kBlue,  f & ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kAlpha);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kGreen | ColorWriteFlag::kAlpha;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kGreen, f & ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kAlpha, f & ColorWriteFlag::kAlpha);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kAll;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kRed,   f & ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kGreen, f & ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kBlue,  f & ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kAlpha, f & ColorWriteFlag::kAlpha);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kNone;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kRed,   f ^ ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kGreen, f ^ ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kBlue,  f ^ ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kAlpha, f ^ ColorWriteFlag::kAlpha);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kRed | ColorWriteFlag::kGreen | ColorWriteFlag::kBlue;
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kGreen | ColorWriteFlag::kBlue,  f ^ ColorWriteFlag::kRed);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kRed   | ColorWriteFlag::kBlue,  f ^ ColorWriteFlag::kGreen);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kRed   | ColorWriteFlag::kGreen, f ^ ColorWriteFlag::kBlue);
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorWriteFlag::kAll,                            f ^ ColorWriteFlag::kAlpha);
	}
	{
		auto f = ColorWriteFlag::kNone;
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kRed);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kGreen);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kBlue);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kAlpha);

		f |= ColorWriteFlag::kRed;
		EXPECT_EQ(ColorWriteFlag::kRed,   f & ColorWriteFlag::kRed);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kGreen);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kBlue);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kAlpha);

		f |= ColorWriteFlag::kBlue;
		EXPECT_EQ(ColorWriteFlag::kRed,   f & ColorWriteFlag::kRed);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kGreen);
		EXPECT_EQ(ColorWriteFlag::kBlue,  f & ColorWriteFlag::kBlue);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kAlpha);

		f ^= ColorWriteFlag::kAll;
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kRed);
		EXPECT_EQ(ColorWriteFlag::kGreen, f & ColorWriteFlag::kGreen);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kBlue);
		EXPECT_EQ(ColorWriteFlag::kAlpha, f & ColorWriteFlag::kAlpha);

		f ^= ColorWriteFlag::kBlue;
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kRed);
		EXPECT_EQ(ColorWriteFlag::kGreen, f & ColorWriteFlag::kGreen);
		EXPECT_EQ(ColorWriteFlag::kBlue,  f & ColorWriteFlag::kBlue);
		EXPECT_EQ(ColorWriteFlag::kAlpha, f & ColorWriteFlag::kAlpha);

		f &= ColorWriteFlag::kRed | ColorWriteFlag::kGreen | ColorWriteFlag::kBlue;
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kRed);
		EXPECT_EQ(ColorWriteFlag::kGreen, f & ColorWriteFlag::kGreen);
		EXPECT_EQ(ColorWriteFlag::kBlue,  f & ColorWriteFlag::kBlue);
		EXPECT_EQ(ColorWriteFlag::kNone,  f & ColorWriteFlag::kAlpha);
	}
}

GTEST_TEST(Render_ColorWriteFlag, TestTest)
{
	using bksge::ColorWriteFlag;

	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kNone;
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kRed));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kGreen));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kBlue));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kAlpha));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kRed;
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ColorWriteFlag::kRed));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kGreen));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kBlue));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kAlpha));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kGreen;
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kRed));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ColorWriteFlag::kGreen));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kBlue));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kAlpha));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kBlue;
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kRed));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kGreen));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ColorWriteFlag::kBlue));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kAlpha));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kAlpha;
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kRed));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kGreen));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ColorWriteFlag::kBlue));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ColorWriteFlag::kAlpha));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto f = ColorWriteFlag::kAll;
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ColorWriteFlag::kRed));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ColorWriteFlag::kGreen));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ColorWriteFlag::kBlue));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ColorWriteFlag::kAlpha));
	}
}

template <typename TChar>
static void OutputStreamTestSub(bksge::ColorWriteFlag color_write_flag, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << color_write_flag;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_ColorWriteFlag, OutputStreamTest)
{
	using bksge::ColorWriteFlag;

	OutputStreamTestSub(ColorWriteFlag::kNone,  "ColorWriteFlag::kNone");
	OutputStreamTestSub(ColorWriteFlag::kRed,   "ColorWriteFlag::kRed");
	OutputStreamTestSub(ColorWriteFlag::kGreen, "ColorWriteFlag::kGreen");
	OutputStreamTestSub(ColorWriteFlag::kBlue,  "ColorWriteFlag::kBlue");
	OutputStreamTestSub(ColorWriteFlag::kAlpha, "ColorWriteFlag::kAlpha");
	OutputStreamTestSub(ColorWriteFlag::kAll,   "ColorWriteFlag::kAll");
	OutputStreamTestSub(
		 ColorWriteFlag::kRed | ColorWriteFlag::kGreen,
		"ColorWriteFlag::kRed | ColorWriteFlag::kGreen");
	OutputStreamTestSub(
		 ColorWriteFlag::kGreen | ColorWriteFlag::kBlue,
		"ColorWriteFlag::kGreen | ColorWriteFlag::kBlue");
	OutputStreamTestSub(
		 ColorWriteFlag::kRed | ColorWriteFlag::kGreen | ColorWriteFlag::kBlue,
		"ColorWriteFlag::kRed | ColorWriteFlag::kGreen | ColorWriteFlag::kBlue");

	OutputStreamTestSub(ColorWriteFlag::kNone,  L"ColorWriteFlag::kNone");
	OutputStreamTestSub(ColorWriteFlag::kRed,   L"ColorWriteFlag::kRed");
	OutputStreamTestSub(ColorWriteFlag::kGreen, L"ColorWriteFlag::kGreen");
	OutputStreamTestSub(ColorWriteFlag::kBlue,  L"ColorWriteFlag::kBlue");
	OutputStreamTestSub(ColorWriteFlag::kAlpha, L"ColorWriteFlag::kAlpha");
	OutputStreamTestSub(ColorWriteFlag::kAll,   L"ColorWriteFlag::kAll");
	OutputStreamTestSub(
		  ColorWriteFlag::kRed | ColorWriteFlag::kGreen,
		L"ColorWriteFlag::kRed | ColorWriteFlag::kGreen");
	OutputStreamTestSub(
		  ColorWriteFlag::kGreen | ColorWriteFlag::kBlue,
		L"ColorWriteFlag::kGreen | ColorWriteFlag::kBlue");
	OutputStreamTestSub(
		  ColorWriteFlag::kRed | ColorWriteFlag::kGreen | ColorWriteFlag::kBlue,
		L"ColorWriteFlag::kRed | ColorWriteFlag::kGreen | ColorWriteFlag::kBlue");
}

GTEST_TEST(Render_ColorWriteFlag, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::ColorWriteFlag::kRed | bksge::ColorWriteFlag::kGreen;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_ColorWriteFlag, HashTest)
{
	std::hash<bksge::ColorWriteFlag> h;
	std::vector<std::size_t> v;
	v.push_back(h(bksge::ColorWriteFlag::kNone));
	v.push_back(h(bksge::ColorWriteFlag::kRed));
	v.push_back(h(bksge::ColorWriteFlag::kGreen));
	v.push_back(h(bksge::ColorWriteFlag::kBlue));
	v.push_back(h(bksge::ColorWriteFlag::kAlpha));
	v.push_back(h(bksge::ColorWriteFlag::kAll));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::ColorWriteFlag::kRed   | bksge::ColorWriteFlag::kGreen));
	v.push_back(h(bksge::ColorWriteFlag::kGreen | bksge::ColorWriteFlag::kBlue));
	v.push_back(h(bksge::ColorWriteFlag::kBlue  | bksge::ColorWriteFlag::kAlpha));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::ColorWriteFlag::kNone));
	std::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace color_write_flag_test

}	// namespace bksge_core_render_test
