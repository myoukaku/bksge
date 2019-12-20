/**
 *	@file	unit_test_core_render_rasterizer_state.cpp
 *
 *	@brief	RasterizerState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/rasterizer_state.hpp>
#include <gtest/gtest.h>
#include <sstream>
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
