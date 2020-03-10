/**
 *	@file	unit_test_core_render_comparison_function.cpp
 *
 *	@brief	ComparisonFunction のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/comparison_function.hpp>
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

namespace comparison_function_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::ComparisonFunction comparison_function, const TChar* str)
{
	bksge::basic_stringstream<TChar> ss;
	ss << comparison_function;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_ComparisonFunction, OutputStreamTest)
{
	using bksge::ComparisonFunction;

	OutputStreamTestSub(ComparisonFunction::kNever,			"ComparisonFunction::kNever");
	OutputStreamTestSub(ComparisonFunction::kLess,			"ComparisonFunction::kLess");
	OutputStreamTestSub(ComparisonFunction::kEqual,			"ComparisonFunction::kEqual");
	OutputStreamTestSub(ComparisonFunction::kLessEqual,		"ComparisonFunction::kLessEqual");
	OutputStreamTestSub(ComparisonFunction::kGreater,		"ComparisonFunction::kGreater");
	OutputStreamTestSub(ComparisonFunction::kNotEqual,		"ComparisonFunction::kNotEqual");
	OutputStreamTestSub(ComparisonFunction::kGreaterEqual,	"ComparisonFunction::kGreaterEqual");
	OutputStreamTestSub(ComparisonFunction::kAlways,		"ComparisonFunction::kAlways");

	OutputStreamTestSub(ComparisonFunction::kNever,			L"ComparisonFunction::kNever");
	OutputStreamTestSub(ComparisonFunction::kLess,			L"ComparisonFunction::kLess");
	OutputStreamTestSub(ComparisonFunction::kEqual,			L"ComparisonFunction::kEqual");
	OutputStreamTestSub(ComparisonFunction::kLessEqual,		L"ComparisonFunction::kLessEqual");
	OutputStreamTestSub(ComparisonFunction::kGreater,		L"ComparisonFunction::kGreater");
	OutputStreamTestSub(ComparisonFunction::kNotEqual,		L"ComparisonFunction::kNotEqual");
	OutputStreamTestSub(ComparisonFunction::kGreaterEqual,	L"ComparisonFunction::kGreaterEqual");
	OutputStreamTestSub(ComparisonFunction::kAlways,		L"ComparisonFunction::kAlways");
}

GTEST_TEST(Render_ComparisonFunction, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::ComparisonFunction::kGreater;

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_ComparisonFunction, HashTest)
{
	std::hash<bksge::ComparisonFunction> h;
	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::ComparisonFunction::kNever));
	v.push_back(h(bksge::ComparisonFunction::kLess));
	v.push_back(h(bksge::ComparisonFunction::kEqual));
	v.push_back(h(bksge::ComparisonFunction::kLessEqual));
	v.push_back(h(bksge::ComparisonFunction::kGreater));
	v.push_back(h(bksge::ComparisonFunction::kNotEqual));
	v.push_back(h(bksge::ComparisonFunction::kGreaterEqual));
	v.push_back(h(bksge::ComparisonFunction::kAlways));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::ComparisonFunction::kAlways));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace comparison_function_test

}	// namespace bksge_core_render_test
