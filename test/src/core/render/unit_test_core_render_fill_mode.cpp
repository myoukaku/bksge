/**
 *	@file	unit_test_core_render_fill_mode.cpp
 *
 *	@brief	FillMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/fill_mode.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_core_render_test
{

namespace fill_mode_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::FillMode fill_mode, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << fill_mode;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_FillMode, OutputStreamTest)
{
	using bksge::FillMode;

	OutputStreamTestSub(FillMode::kSolid,     "FillMode::kSolid");
	OutputStreamTestSub(FillMode::kWireframe, "FillMode::kWireframe");

	OutputStreamTestSub(FillMode::kSolid,     L"FillMode::kSolid");
	OutputStreamTestSub(FillMode::kWireframe, L"FillMode::kWireframe");
}

}	// namespace fill_mode_test

}	// namespace bksge_core_render_test
