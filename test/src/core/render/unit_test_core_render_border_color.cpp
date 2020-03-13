/**
 *	@file	unit_test_core_render_border_color.cpp
 *
 *	@brief	BorderColor のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/border_color.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <functional>
#include <vector>
#include <sstream>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace border_color_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::BorderColor border_color, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << border_color;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_BorderColor, OutputStreamTest)
{
	using bksge::BorderColor;

	OutputStreamTestSub(BorderColor::kTransparentBlack, "BorderColor::kTransparentBlack");
	OutputStreamTestSub(BorderColor::kOpaqueBlack,      "BorderColor::kOpaqueBlack");
	OutputStreamTestSub(BorderColor::kOpaqueWhite,      "BorderColor::kOpaqueWhite");

	OutputStreamTestSub(BorderColor::kTransparentBlack, L"BorderColor::kTransparentBlack");
	OutputStreamTestSub(BorderColor::kOpaqueBlack,      L"BorderColor::kOpaqueBlack");
	OutputStreamTestSub(BorderColor::kOpaqueWhite,      L"BorderColor::kOpaqueWhite");
}

GTEST_TEST(Render_BorderColor, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::BorderColor::kOpaqueWhite;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_BorderColor, HashTest)
{
	std::hash<bksge::BorderColor> h;
	std::vector<std::size_t> v;
	v.push_back(h(bksge::BorderColor::kTransparentBlack));
	v.push_back(h(bksge::BorderColor::kOpaqueBlack));
	v.push_back(h(bksge::BorderColor::kOpaqueWhite));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::BorderColor::kOpaqueWhite));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace border_color_test

}	// namespace bksge_core_render_test
