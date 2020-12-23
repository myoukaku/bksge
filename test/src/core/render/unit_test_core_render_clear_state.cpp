/**
 *	@file	unit_test_core_render_clear_state.cpp
 *
 *	@brief	ClearState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/clear_state.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

GTEST_TEST(Render_ClearState, DefaultCtorTest)
{
	bksge::ClearState const state;
	EXPECT_EQ(bksge::ClearFlag::kAll,  state.flag());
	EXPECT_EQ(bksge::Color4f(0,0,0,0), state.color());
	EXPECT_EQ(1.0f,                    state.depth());
	EXPECT_EQ(0u,                      state.stencil());
}

GTEST_TEST(Render_ClearState, SetFlagTest)
{
	bksge::ClearState state;
	EXPECT_EQ(bksge::ClearFlag::kAll, state.flag());

	state.SetFlag(bksge::ClearFlag::kColor);
	EXPECT_EQ(bksge::ClearFlag::kColor, state.flag());
}

GTEST_TEST(Render_ClearState, SetColorTest)
{
	bksge::ClearState state;
	EXPECT_EQ(bksge::Color4f(0,0,0,0), state.color());

	state.SetColor({1,2,3,4});
	EXPECT_EQ(bksge::Color4f(1,2,3,4), state.color());
}

GTEST_TEST(Render_ClearState, SetDepthTest)
{
	bksge::ClearState state;
	EXPECT_EQ(1.0f, state.depth());

	state.SetDepth(0.5f);
	EXPECT_EQ(0.5f, state.depth());
}

GTEST_TEST(Render_ClearState, SetStencilTest)
{
	bksge::ClearState state;
	EXPECT_EQ(0u, state.stencil());

	state.SetStencil(2);
	EXPECT_EQ(2u, state.stencil());
}

GTEST_TEST(Render_ClearState, CompareTest)
{
	bksge::ClearState s1;
	bksge::ClearState s2;
	bksge::ClearState s3;
	bksge::ClearState s4;
	bksge::ClearState s5;
	bksge::ClearState s6;

	s3.SetFlag(bksge::ClearFlag::kColor);
	s4.SetColor({1,2,3,4});
	s5.SetDepth(0.5f);
	s6.SetStencil(2);

	EXPECT_TRUE (s1 == s1);
	EXPECT_TRUE (s1 == s2);
	EXPECT_FALSE(s1 == s3);
	EXPECT_FALSE(s1 == s4);
	EXPECT_FALSE(s1 == s5);
	EXPECT_FALSE(s1 == s6);

	EXPECT_FALSE(s1 != s1);
	EXPECT_FALSE(s1 != s2);
	EXPECT_TRUE (s1 != s3);
	EXPECT_TRUE (s1 != s4);
	EXPECT_TRUE (s1 != s5);
	EXPECT_TRUE (s1 != s6);
}

GTEST_TEST(Render_ClearState, OutputStreamTest)
{
	{
		bksge::ClearState s;
		std::stringstream ss;
		ss << s;
		EXPECT_EQ("{ ClearFlag::kAll, { 0, 0, 0, 0 }, 1, 0 }", ss.str());
	}
	{
		bksge::ClearState s;
		s.SetFlag(bksge::ClearFlag::kColor);
		s.SetColor({1,2,3,4});
		s.SetDepth(0.5f);
		s.SetStencil(2);
		std::wstringstream ss;
		ss << s;
		EXPECT_EQ(L"{ ClearFlag::kColor, { 1, 2, 3, 4 }, 0.5, 2 }", ss.str());
	}
}

GTEST_TEST(Render_ClearState, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::ClearState s;
	s.SetFlag(bksge::ClearFlag::kDepth);
	s.SetColor({3, 2, 1, 0});
	s.SetDepth(1.5f);
	s.SetStencil(10);

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(s);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(s);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(s);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(s);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(s);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(s);
#endif
}

GTEST_TEST(Render_ClearState, HashTest)
{
	std::hash<bksge::ClearState> h;

	bksge::ClearState s1;
	bksge::ClearState s2;
	bksge::ClearState s3;
	bksge::ClearState s4;
	bksge::ClearState s5;

	s2.SetFlag(bksge::ClearFlag::kColor);
	s3.SetColor({1,2,3,4});
	s4.SetDepth(0.5f);
	s5.SetStencil(2);

	std::vector<bksge::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	v.push_back(h(s5));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s4));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
