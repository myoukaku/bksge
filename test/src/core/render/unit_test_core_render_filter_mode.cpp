/**
 *	@file	unit_test_core_render_filter_mode.cpp
 *
 *	@brief	FilterMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/filter_mode.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace filter_mode_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::FilterMode filter_mode, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << filter_mode;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_FilterMode, OutputStreamTest)
{
	using bksge::FilterMode;

	OutputStreamTestSub(FilterMode::kNearest,	"FilterMode::kNearest");
	OutputStreamTestSub(FilterMode::kLinear,	"FilterMode::kLinear");

	OutputStreamTestSub(FilterMode::kNearest,	L"FilterMode::kNearest");
	OutputStreamTestSub(FilterMode::kLinear,	L"FilterMode::kLinear");
}

GTEST_TEST(Render_FilterMode, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::FilterMode::kLinear;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace filter_mode_test

}	// namespace bksge_core_render_test
