/**
 *	@file	unit_test_core_render_fill_mode.cpp
 *
 *	@brief	FillMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/fill_mode.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/sstream.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace fill_mode_test
{

static_assert(sizeof(bksge::FillMode) == 4, "");

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

GTEST_TEST(Render_FillMode, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::FillMode::kSolid;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_FillMode, HashTest)
{
	bksge::hash<bksge::FillMode> h;
	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::FillMode::kSolid));
	v.push_back(h(bksge::FillMode::kWireframe));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::FillMode::kSolid));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace fill_mode_test

}	// namespace bksge_core_render_test
