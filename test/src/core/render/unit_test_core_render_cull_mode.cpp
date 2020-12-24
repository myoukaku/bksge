/**
 *	@file	unit_test_core_render_cull_mode.cpp
 *
 *	@brief	CullMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/cull_mode.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/vector.hpp>
#include <functional>
#include <sstream>
#include <gtest/gtest.h>
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

GTEST_TEST(Render_CullMode, HashTest)
{
	std::hash<bksge::CullMode> h;
	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::CullMode::kNone));
	v.push_back(h(bksge::CullMode::kFront));
	v.push_back(h(bksge::CullMode::kBack));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::CullMode::kNone));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace cull_mode_test

}	// namespace bksge_core_render_test
