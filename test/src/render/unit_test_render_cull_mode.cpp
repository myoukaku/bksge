/**
 *	@file	unit_test_render_cull_mode.cpp
 *
 *	@brief	CullMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/cull_mode.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_render_test
{

namespace cull_mode_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::CullMode cull_mode, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << cull_mode;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_CullMode, OutputStreamTest)
{
	using bksge::CullMode;

	OutputStreamTestSub(CullMode::kNone,  "CullMode::kNone");
	OutputStreamTestSub(CullMode::kFront, "CullMode::kFront");
	OutputStreamTestSub(CullMode::kBack,  "CullMode::kBack");

	OutputStreamTestSub(CullMode::kNone,  L"CullMode::kNone");
	OutputStreamTestSub(CullMode::kFront, L"CullMode::kFront");
	OutputStreamTestSub(CullMode::kBack,  L"CullMode::kBack");
}

}	// namespace cull_mode_test

}	// namespace bksge_render_test
