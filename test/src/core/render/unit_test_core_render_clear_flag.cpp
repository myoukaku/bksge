/**
 *	@file	unit_test_core_render_clear_flag.cpp
 *
 *	@brief	ClearFlag のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/clear_flag.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <functional>
#include <vector>
#include <algorithm>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace clear_flag_test
{

GTEST_TEST(Render_ClearFlag, BasicTest)
{
	using bksge::ClearFlag;

	ClearFlag f0 = ClearFlag::kNone;
	EXPECT_FALSE(bool(f0 & ClearFlag::kColor));
	EXPECT_FALSE(bool(f0 & ClearFlag::kDepth));
	EXPECT_FALSE(bool(f0 & ClearFlag::kStencil));

	ClearFlag f1 = ClearFlag::kColor;
	EXPECT_TRUE (bool(f1 & ClearFlag::kColor));
	EXPECT_FALSE(bool(f1 & ClearFlag::kDepth));
	EXPECT_FALSE(bool(f1 & ClearFlag::kStencil));

	ClearFlag f2 = ClearFlag::kColor | ClearFlag::kStencil;
	EXPECT_TRUE (bool(f2 & ClearFlag::kColor));
	EXPECT_FALSE(bool(f2 & ClearFlag::kDepth));
	EXPECT_TRUE (bool(f2 & ClearFlag::kStencil));
}

template <typename TChar>
static void OutputStreamTestSub(bksge::ClearFlag clear_flag, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << clear_flag;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_ClearFlag, OutputStreamTest)
{
	using bksge::ClearFlag;

	OutputStreamTestSub(ClearFlag::kNone,                        "ClearFlag::kNone");
	OutputStreamTestSub(ClearFlag::kColor,                       "ClearFlag::kColor");
	OutputStreamTestSub(ClearFlag::kDepth,                       "ClearFlag::kDepth");
	OutputStreamTestSub(ClearFlag::kStencil,                     "ClearFlag::kStencil");
	OutputStreamTestSub(ClearFlag::kAll,                         "ClearFlag::kAll");
	OutputStreamTestSub(ClearFlag::kColor | ClearFlag::kDepth,   "ClearFlag::kColor | ClearFlag::kDepth");
	OutputStreamTestSub(ClearFlag::kDepth | ClearFlag::kStencil, "ClearFlag::kDepth | ClearFlag::kStencil");
	OutputStreamTestSub(ClearFlag::kColor | ClearFlag::kStencil, "ClearFlag::kColor | ClearFlag::kStencil");

	OutputStreamTestSub(ClearFlag::kNone,                        L"ClearFlag::kNone");
	OutputStreamTestSub(ClearFlag::kColor,                       L"ClearFlag::kColor");
	OutputStreamTestSub(ClearFlag::kDepth,                       L"ClearFlag::kDepth");
	OutputStreamTestSub(ClearFlag::kStencil,                     L"ClearFlag::kStencil");
	OutputStreamTestSub(ClearFlag::kAll,                         L"ClearFlag::kAll");
	OutputStreamTestSub(ClearFlag::kColor | ClearFlag::kDepth,   L"ClearFlag::kColor | ClearFlag::kDepth");
	OutputStreamTestSub(ClearFlag::kDepth | ClearFlag::kStencil, L"ClearFlag::kDepth | ClearFlag::kStencil");
	OutputStreamTestSub(ClearFlag::kColor | ClearFlag::kStencil, L"ClearFlag::kColor | ClearFlag::kStencil");
}

GTEST_TEST(Render_ClearFlag, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::ClearFlag::kColor | bksge::ClearFlag::kStencil;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_ClearFlag, HashTest)
{
	std::hash<bksge::ClearFlag> h;
	std::vector<std::size_t> v;
	v.push_back(h(bksge::ClearFlag::kNone));
	v.push_back(h(bksge::ClearFlag::kColor));
	v.push_back(h(bksge::ClearFlag::kDepth));
	v.push_back(h(bksge::ClearFlag::kStencil));
	v.push_back(h(bksge::ClearFlag::kAll));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::ClearFlag::kColor | bksge::ClearFlag::kDepth));
	v.push_back(h(bksge::ClearFlag::kDepth | bksge::ClearFlag::kStencil));
	v.push_back(h(bksge::ClearFlag::kColor | bksge::ClearFlag::kStencil));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::ClearFlag::kNone));
	std::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace clear_flag_test

}	// namespace bksge_core_render_test
