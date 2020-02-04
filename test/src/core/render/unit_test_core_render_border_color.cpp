/**
 *	@file	unit_test_core_render_border_color.cpp
 *
 *	@brief	BorderColor のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/border_color.hpp>
#include <gtest/gtest.h>
#include <sstream>
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

}	// namespace border_color_test

}	// namespace bksge_core_render_test
