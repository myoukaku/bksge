/**
 *	@file	unit_test_core_render_viewport.cpp
 *
 *	@brief	Viewport のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/viewport.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

GTEST_TEST(Render_Viewport, DefaultCtorTest)
{
	bksge::Viewport const state;
	EXPECT_EQ(bksge::Rectf(), state.rect());
	EXPECT_EQ(0.0f,	          state.min_depth());
	EXPECT_EQ(1.0f,	          state.max_depth());
}

GTEST_TEST(Render_Viewport, SetRectTest)
{
	bksge::Viewport state;
	EXPECT_EQ(bksge::Rectf(), state.rect());

	state.SetRect({bksge::Vector2f(2, 3), bksge::Extent2f(20, 10)});
	EXPECT_EQ(bksge::Rectf(bksge::Vector2f(2, 3), bksge::Extent2f(20, 10)), state.rect());
}

GTEST_TEST(Render_Viewport, SetMinDepthTest)
{
	bksge::Viewport state;
	EXPECT_EQ(0.0f, state.min_depth());

	state.SetMinDepth(0.5f);
	EXPECT_EQ(0.5f, state.min_depth());
}

GTEST_TEST(Render_Viewport, SetMaxDepthTest)
{
	bksge::Viewport state;
	EXPECT_EQ(1.0f, state.max_depth());

	state.SetMaxDepth(2.0f);
	EXPECT_EQ(2.0f, state.max_depth());
}

GTEST_TEST(Render_Viewport, CompareTest)
{
	bksge::Viewport v1;
	bksge::Viewport v2;
	bksge::Viewport v3;
	bksge::Viewport v4;
	bksge::Viewport v5;

	v3.SetRect({bksge::Vector2f(2, 3), bksge::Extent2f(20, 10)});
	v4.SetMinDepth(0.5f);
	v5.SetMaxDepth(2.0f);

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

GTEST_TEST(Render_Viewport, OutputStreamTest)
{
	{
		bksge::Viewport v;
		bksge::stringstream ss;
		ss << v;
		EXPECT_EQ("{ { 0, 0, 0, 0 }, 0, 1 }", ss.str());
	}
	{
		bksge::Viewport v;
		v.SetRect({bksge::Vector2f(2, 3), bksge::Extent2f(20, 10)});
		v.SetMinDepth(0.0f);
		v.SetMaxDepth(2.0f);
		bksge::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ { 2, 3, 22, 13 }, 0, 2 }", ss.str());
	}
}

GTEST_TEST(Render_Viewport, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::Viewport v;
	v.SetRect({bksge::Vector2f(-5, 4), bksge::Extent2f(20, 30)});
	v.SetMinDepth(1.0f);
	v.SetMaxDepth(3.0f);

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_Viewport, HashTest)
{
	bksge::hash<bksge::Viewport> h;

	bksge::Viewport s1;
	bksge::Viewport s2;
	bksge::Viewport s3;
	bksge::Viewport s4;

	s2.SetRect({bksge::Vector2f(-5, 4), bksge::Extent2f(20, 30)});
	s3.SetMinDepth(1.0f);
	s4.SetMaxDepth(3.0f);

	bksge::vector<bksge::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s1));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
