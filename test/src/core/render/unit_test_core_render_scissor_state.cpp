/**
 *	@file	unit_test_core_render_scissor_state.cpp
 *
 *	@brief	ScissorState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/scissor_state.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

GTEST_TEST(Render_ScissorState, DefaultCtorTest)
{
	bksge::ScissorState const state;
	EXPECT_EQ(false,            state.enable());
	EXPECT_EQ(bksge::Rectf(),	state.rect());
}

GTEST_TEST(Render_ScissorState, SetEnableTest)
{
	bksge::ScissorState state;
	EXPECT_EQ(false, state.enable());

	state.SetEnable(true);
	EXPECT_EQ(true, state.enable());
}

GTEST_TEST(Render_ScissorState, SetRectTest)
{
	bksge::ScissorState state;
	EXPECT_EQ(bksge::Rectf(), state.rect());

	state.SetRect({bksge::Vector2f(2, 3), bksge::Extent2f(20, 10)});
	EXPECT_EQ(bksge::Rectf(bksge::Vector2f(2, 3), bksge::Extent2f(20, 10)), state.rect());
}

GTEST_TEST(Render_ScissorState, CompareTest)
{
	bksge::ScissorState v1;
	bksge::ScissorState v2;
	bksge::ScissorState v3;
	bksge::ScissorState v4;

	v3.SetEnable(true);
	v4.SetRect({bksge::Vector2f(2, 3), bksge::Extent2f(20, 10)});

	EXPECT_TRUE (v1 == v1);
	EXPECT_TRUE (v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE (v1 != v3);
	EXPECT_TRUE (v1 != v4);
}

GTEST_TEST(Render_ScissorState, OutputStreamTest)
{
	{
		bksge::ScissorState v;
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ false, { 0, 0, 0, 0 } }", ss.str());
	}
	{
		bksge::ScissorState v;
		v.SetEnable(true);
		v.SetRect({bksge::Vector2f(2, 3), bksge::Extent2f(20, 10)});
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ true, { 2, 3, 22, 13 } }", ss.str());
	}
}

GTEST_TEST(Render_ScissorState, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::ScissorState v;
	v.SetEnable(true);
	v.SetRect({bksge::Vector2f(-5, 4), bksge::Extent2f(20, 30)});

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_ScissorState, HashTest)
{
	std::hash<bksge::ScissorState> h;

	bksge::ScissorState s1;
	bksge::ScissorState s2;
	bksge::ScissorState s3;

	s2.SetEnable(true);
	s3.SetRect({bksge::Vector2f(-5, 4), bksge::Extent2f(20, 30)});

	std::vector<bksge::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s1));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
