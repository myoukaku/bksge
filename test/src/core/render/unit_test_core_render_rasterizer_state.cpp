/**
 *	@file	unit_test_core_render_rasterizer_state.cpp
 *
 *	@brief	RasterizerState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/rasterizer_state.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <functional>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

GTEST_TEST(Render_RasterizerState, DefaultCtorTest)
{
	bksge::RasterizerState const state;
	EXPECT_EQ(bksge::FillMode::kSolid, state.fill_mode());
	EXPECT_EQ(bksge::CullMode::kNone, state.cull_mode());
	EXPECT_EQ(bksge::FrontFace::kClockwise, state.front_face());
}

GTEST_TEST(Render_RasterizerState, SetFillModeTest)
{
	bksge::RasterizerState state;
	EXPECT_EQ(bksge::FillMode::kSolid, state.fill_mode());

	state.SetFillMode(bksge::FillMode::kWireframe);
	EXPECT_EQ(bksge::FillMode::kWireframe, state.fill_mode());
}

GTEST_TEST(Render_RasterizerState, SetCullModeTest)
{
	bksge::RasterizerState state;
	EXPECT_EQ(bksge::CullMode::kNone, state.cull_mode());

	state.SetCullMode(bksge::CullMode::kBack);
	EXPECT_EQ(bksge::CullMode::kBack, state.cull_mode());
}

GTEST_TEST(Render_RasterizerState, SetFrontFaceTest)
{
	bksge::RasterizerState state;
	EXPECT_EQ(bksge::FrontFace::kClockwise, state.front_face());

	state.SetFrontFace(bksge::FrontFace::kCounterClockwise);
	EXPECT_EQ(bksge::FrontFace::kCounterClockwise, state.front_face());
}

GTEST_TEST(Render_RasterizerState, CompareTest)
{
	bksge::RasterizerState v1;
	bksge::RasterizerState v2;
	bksge::RasterizerState v3;
	bksge::RasterizerState v4;
	bksge::RasterizerState v5;

	v3.SetFillMode(bksge::FillMode::kWireframe);
	v4.SetCullMode(bksge::CullMode::kFront);
	v5.SetFrontFace(bksge::FrontFace::kCounterClockwise);

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

GTEST_TEST(Render_RasterizerState, OutputStreamTest)
{
	{
		bksge::RasterizerState v;
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ FillMode::kSolid, CullMode::kNone, FrontFace::kClockwise }", ss.str());
	}
	{
		bksge::RasterizerState v;
		v.SetFillMode(bksge::FillMode::kWireframe);
		v.SetCullMode(bksge::CullMode::kFront);
		v.SetFrontFace(bksge::FrontFace::kCounterClockwise);
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ FillMode::kWireframe, CullMode::kFront, FrontFace::kCounterClockwise }", ss.str());
	}
}

GTEST_TEST(Render_RasterizerState, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::RasterizerState v;
	v.SetFillMode(bksge::FillMode::kWireframe);
	v.SetCullMode(bksge::CullMode::kFront);
	v.SetFrontFace(bksge::FrontFace::kCounterClockwise);

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_RasterizerState, HashTest)
{
	std::hash<bksge::RasterizerState> h;

	bksge::RasterizerState s1;
	bksge::RasterizerState s2;
	bksge::RasterizerState s3;
	bksge::RasterizerState s4;
	bksge::RasterizerState s5;

	s2.SetFillMode(bksge::FillMode::kWireframe);
	s3.SetCullMode(bksge::CullMode::kFront);
	s4.SetFrontFace(bksge::FrontFace::kCounterClockwise);
	s5.SetFillMode(bksge::FillMode::kWireframe);
	s5.SetCullMode(bksge::CullMode::kFront);
	s5.SetFrontFace(bksge::FrontFace::kCounterClockwise);

	std::vector<bksge::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	v.push_back(h(s5));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s5));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
