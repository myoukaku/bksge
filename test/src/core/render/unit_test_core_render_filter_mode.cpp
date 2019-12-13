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

}	// namespace filter_mode_test

}	// namespace bksge_core_render_test
