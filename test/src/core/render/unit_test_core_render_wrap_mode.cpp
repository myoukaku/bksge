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
#include "serialize_test.hpp"

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

GTEST_TEST(Render_WrapMode, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::WrapMode::kBorder;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace wrap_mode_test

}	// namespace bksge_core_render_test
