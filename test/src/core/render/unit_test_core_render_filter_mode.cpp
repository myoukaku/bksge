/**
 *	@file	unit_test_core_render_filter_mode.cpp
 *
 *	@brief	FilterMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/filter_mode.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/sstream/basic_stringstream.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <functional>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace filter_mode_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::FilterMode filter_mode, const TChar* str)
{
	bksge::basic_stringstream<TChar> ss;
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

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_FilterMode, HashTest)
{
	std::hash<bksge::FilterMode> h;
	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::FilterMode::kNearest));
	v.push_back(h(bksge::FilterMode::kLinear));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::FilterMode::kNearest));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace filter_mode_test

}	// namespace bksge_core_render_test
