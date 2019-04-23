/**
 *	@file	unit_test_render_comparison_function.cpp
 *
 *	@brief	ComparisonFunction のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/comparison_function.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_render_test
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

}	// namespace comparison_function_test

}	// namespace bksge_render_test
