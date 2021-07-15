/**
 *	@file	unit_test_core_render_address_mode.cpp
 *
 *	@brief	AddressMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/address_mode.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <sstream>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace address_mode_test
{

static_assert(sizeof(bksge::AddressMode) == 4, "");

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
	OutputStreamTestSub(AddressMode::kMirror, "AddressMode::kMirror");
	OutputStreamTestSub(AddressMode::kClamp,  "AddressMode::kClamp");
	OutputStreamTestSub(AddressMode::kBorder, "AddressMode::kBorder");

	OutputStreamTestSub(AddressMode::kRepeat, L"AddressMode::kRepeat");
	OutputStreamTestSub(AddressMode::kMirror, L"AddressMode::kMirror");
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

GTEST_TEST(Render_AddressMode, HashTest)
{
	bksge::hash<bksge::AddressMode> h;
	bksge::vector<std::size_t> v;
	v.push_back(h(bksge::AddressMode::kRepeat));
	v.push_back(h(bksge::AddressMode::kMirror));
	v.push_back(h(bksge::AddressMode::kClamp));
	v.push_back(h(bksge::AddressMode::kBorder));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::AddressMode::kRepeat));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace address_mode_test

}	// namespace bksge_core_render_test
