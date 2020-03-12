/**
 *	@file	unit_test_core_render_depth_state.cpp
 *
 *	@brief	DepthState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/depth_state.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <functional>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

GTEST_TEST(Render_DepthState, DefaultCtorTest)
{
	bksge::DepthState const state;
	EXPECT_EQ(false,                            state.enable());
	EXPECT_EQ(false,                            state.write());
	EXPECT_EQ(bksge::ComparisonFunction::kLess, state.func());
}

GTEST_TEST(Render_DepthState, SetEnableTest)
{
	bksge::DepthState state;
	EXPECT_EQ(false, state.enable());

	state.SetEnable(true);
	EXPECT_EQ(true, state.enable());
}

GTEST_TEST(Render_DepthState, SetWriteTest)
{
	bksge::DepthState state;
	EXPECT_EQ(false, state.write());

	state.SetWrite(true);
	EXPECT_EQ(true, state.write());
}

GTEST_TEST(Render_DepthState, SetFuncTest)
{
	bksge::DepthState state;
	EXPECT_EQ(bksge::ComparisonFunction::kLess, state.func());

	state.SetFunc(
		bksge::ComparisonFunction::kGreater);
	EXPECT_EQ(bksge::ComparisonFunction::kGreater, state.func());
}

GTEST_TEST(Render_DepthState, CompareTest)
{
	bksge::DepthState v1;
	bksge::DepthState v2;
	bksge::DepthState v3;
	bksge::DepthState v4;
	bksge::DepthState v5;

	v1.SetEnable(true);
	v1.SetWrite(true);
	v1.SetFunc(bksge::ComparisonFunction::kEqual);

	v2.SetEnable(true);
	v2.SetWrite(true);
	v2.SetFunc(bksge::ComparisonFunction::kEqual);

	v3.SetEnable(false);
	v3.SetWrite(true);
	v3.SetFunc(bksge::ComparisonFunction::kEqual);

	v4.SetEnable(true);
	v4.SetWrite(false);
	v4.SetFunc(bksge::ComparisonFunction::kEqual);

	v5.SetEnable(true);
	v5.SetWrite(true);
	v5.SetFunc(bksge::ComparisonFunction::kGreaterEqual);

	EXPECT_TRUE (v1 == v1);
	EXPECT_TRUE (v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);
	EXPECT_FALSE(v1 == v5);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE (v1 != v3);
	EXPECT_TRUE (v1 != v4);
	EXPECT_TRUE (v1 != v5);
}

GTEST_TEST(Render_DepthState, OutputStreamTest)
{
	{
		bksge::DepthState v;
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ false, false, ComparisonFunction::kLess }", ss.str());
	}
	{
		bksge::DepthState v;
		v.SetEnable(true);
		v.SetWrite(true);
		v.SetFunc(bksge::ComparisonFunction::kNotEqual);
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ true, true, ComparisonFunction::kNotEqual }", ss.str());
	}
}

GTEST_TEST(Render_DepthState, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::DepthState v;
	v.SetEnable(true);
	v.SetWrite(true);
	v.SetFunc(bksge::ComparisonFunction::kGreater);

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_DepthState, HashTest)
{
	std::hash<bksge::DepthState> h;

	bksge::DepthState s1;
	bksge::DepthState s2;
	bksge::DepthState s3;
	bksge::DepthState s4;
	bksge::DepthState s5;

	s2.SetEnable(true);
	s3.SetWrite(true);
	s4.SetFunc(bksge::ComparisonFunction::kGreater);

	std::vector<bksge::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s5));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
