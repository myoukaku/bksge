/**
 *	@file	unit_test_core_render_wrap_mode.cpp
 *
 *	@brief	WrapMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/wrap_mode.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_core_render_test
{

namespace wrap_mode_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::WrapMode wrap, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << wrap;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_WrapMode, OutputStreamTest)
{
	using bksge::WrapMode;

	OutputStreamTestSub(WrapMode::kRepeat, "WrapMode::kRepeat");
	OutputStreamTestSub(WrapMode::kClamp,  "WrapMode::kClamp");
	OutputStreamTestSub(WrapMode::kBorder, "WrapMode::kBorder");

	OutputStreamTestSub(WrapMode::kRepeat, L"WrapMode::kRepeat");
	OutputStreamTestSub(WrapMode::kClamp,  L"WrapMode::kClamp");
	OutputStreamTestSub(WrapMode::kBorder, L"WrapMode::kBorder");
}

}	// namespace wrap_mode_test

}	// namespace bksge_core_render_test
