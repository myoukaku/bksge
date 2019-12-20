﻿/**
 *	@file	unit_test_core_render_cull_mode.cpp
 *
 *	@brief	CullMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/cull_mode.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

namespace bksge_core_render_test
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

GTEST_TEST(Render_CullMode, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::CullMode::kBack;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace cull_mode_test

}	// namespace bksge_core_render_test
