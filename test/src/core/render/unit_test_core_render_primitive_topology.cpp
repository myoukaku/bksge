/**
 *	@file	unit_test_core_render_primitive_topology.cpp
 *
 *	@brief	PrimitiveTopology のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/primitive_topology.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <functional>
#include <vector>
#include <algorithm>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace primitive_topology_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::PrimitiveTopology p, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << p;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_PrimitiveTopology, OutputStreamTest)
{
	using bksge::PrimitiveTopology;

	OutputStreamTestSub(PrimitiveTopology::kPoints,		"PrimitiveTopology::kPoints");
	OutputStreamTestSub(PrimitiveTopology::kLines,		"PrimitiveTopology::kLines");
	OutputStreamTestSub(PrimitiveTopology::kTriangles,	"PrimitiveTopology::kTriangles");

	OutputStreamTestSub(PrimitiveTopology::kPoints,		L"PrimitiveTopology::kPoints");
	OutputStreamTestSub(PrimitiveTopology::kLines,		L"PrimitiveTopology::kLines");
	OutputStreamTestSub(PrimitiveTopology::kTriangles,	L"PrimitiveTopology::kTriangles");
}

GTEST_TEST(Render_PrimitiveTopology, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::PrimitiveTopology::kTriangles;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_PrimitiveTopology, HashTest)
{
	std::hash<bksge::PrimitiveTopology> h;
	std::vector<std::size_t> v;
	v.push_back(h(bksge::PrimitiveTopology::kPoints));
	v.push_back(h(bksge::PrimitiveTopology::kLines));
	v.push_back(h(bksge::PrimitiveTopology::kTriangles));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::PrimitiveTopology::kTriangles));
	std::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace primitive_topology_test

}	// namespace bksge_core_render_test
