﻿/**
 *	@file	unit_test_core_render_address_mode.cpp
 *
 *	@brief	AddressMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/address_mode.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace address_mode_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::AddressMode address_mode, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << address_mode;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_AddressMode, OutputStreamTest)
{
	using bksge::AddressMode;

	OutputStreamTestSub(AddressMode::kRepeat, "AddressMode::kRepeat");
	OutputStreamTestSub(AddressMode::kClamp,  "AddressMode::kClamp");
	OutputStreamTestSub(AddressMode::kBorder, "AddressMode::kBorder");

	OutputStreamTestSub(AddressMode::kRepeat, L"AddressMode::kRepeat");
	OutputStreamTestSub(AddressMode::kClamp,  L"AddressMode::kClamp");
	OutputStreamTestSub(AddressMode::kBorder, L"AddressMode::kBorder");
}

GTEST_TEST(Render_AddressMode, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::AddressMode::kBorder;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace address_mode_test

}	// namespace bksge_core_render_test
