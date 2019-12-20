/**
 *	@file	unit_test_core_render_comparison_function.cpp
 *
 *	@brief	ComparisonFunction のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/comparison_function.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace comparison_function_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::ComparisonFunction comparison_function, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
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

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace comparison_function_test

}	// namespace bksge_core_render_test
