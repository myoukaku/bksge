/**
 *	@file	unit_test_core_render_render_pass_info.cpp
 *
 *	@brief		RenderPassInfo のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/render_pass_info.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

GTEST_TEST(Render_RenderPassInfo, DefaultCtorTest)
{
	bksge::RenderPassInfo const state;

	EXPECT_EQ(bksge::ClearFlag::kAll,		state.clear_state().flag());
	EXPECT_EQ(bksge::Color4f(0, 0, 0, 0),	state.clear_state().color());
	EXPECT_EQ(1.0f,							state.clear_state().depth());
	EXPECT_EQ(0,							state.clear_state().stencil());

	EXPECT_EQ(false,			state.scissor_state().enable());
	EXPECT_EQ(bksge::Rectf(),	state.scissor_state().rect());

	EXPECT_EQ(bksge::Rectf(),	state.viewport().rect());
	EXPECT_EQ(0.0f,				state.viewport().min_depth());
	EXPECT_EQ(1.0f,				state.viewport().max_depth());
}

GTEST_TEST(Render_RenderPassInfo, SetValueTest)
{
	bksge::RenderPassInfo state;

	state.clear_state().SetFlag(bksge::ClearFlag::kDepth);
	state.clear_state().SetColor({1,2,3,4});
	state.clear_state().SetDepth(5.0f);
	state.clear_state().SetStencil(10);

	state.scissor_state().SetEnable(true);
	state.scissor_state().SetRect(
		bksge::Rectf(bksge::Vector2f{1, 2}, bksge::Extent2f{30, 20}));

	state.viewport().SetRect(
		bksge::Rectf(bksge::Vector2f{-10, 10}, bksge::Extent2f{5, 4}));
	state.viewport().SetMinDepth(10);
	state.viewport().SetMaxDepth(20);

	EXPECT_EQ(bksge::ClearFlag::kDepth,		state.clear_state().flag());
	EXPECT_EQ(bksge::Color4f(1, 2, 3, 4),	state.clear_state().color());
	EXPECT_EQ(5.0f,							state.clear_state().depth());
	EXPECT_EQ(10,							state.clear_state().stencil());

	EXPECT_EQ(true, state.scissor_state().enable());
	EXPECT_EQ(bksge::Rectf(bksge::Vector2f{1, 2}, bksge::Extent2f{30, 20}),
		state.scissor_state().rect());

	EXPECT_EQ(bksge::Rectf(bksge::Vector2f{-10, 10}, bksge::Extent2f{5, 4}),
		state.viewport().rect());
	EXPECT_EQ(10.0f, state.viewport().min_depth());
	EXPECT_EQ(20.0f, state.viewport().max_depth());
}

GTEST_TEST(Render_RenderPassInfo, CompareTest)
{
	bksge::RenderPassInfo v1;
	bksge::RenderPassInfo v2;
	bksge::RenderPassInfo v3;
	bksge::RenderPassInfo v4;
	bksge::RenderPassInfo v5;

	v3.clear_state().SetFlag(bksge::ClearFlag::kDepth);
	v4.scissor_state().SetEnable(true);
	v5.viewport().SetMinDepth(10);

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

GTEST_TEST(Render_RenderPassInfo, OutputStreamTest)
{
	{
		bksge::RenderPassInfo v;
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ { ClearFlag::kAll, { 0, 0, 0, 0 }, 1, 0 }, { false, { 0, 0, 0, 0 } }, { { 0, 0, 0, 0 }, 0, 1 } }", ss.str());
	}
	{
		bksge::RenderPassInfo v;
		v.clear_state().SetFlag(bksge::ClearFlag::kDepth);
		v.clear_state().SetColor({1,2,3,4});
		v.clear_state().SetDepth(5.0f);
		v.clear_state().SetStencil(10);
		v.scissor_state().SetEnable(true);
		v.scissor_state().SetRect(bksge::Rectf(bksge::Vector2f{1, 2}, bksge::Extent2f{30, 20}));
		v.viewport().SetRect(bksge::Rectf(bksge::Vector2f{-10, 10}, bksge::Extent2f{5, 4}));
		v.viewport().SetMinDepth(10);
		v.viewport().SetMaxDepth(20);
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ { ClearFlag::kDepth, { 1, 2, 3, 4 }, 5, 10 }, { true, { 1, 2, 31, 22 } }, { { -10, 10, -5, 14 }, 10, 20 } }", ss.str());
	}
}

GTEST_TEST(Render_RenderPassInfo, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::RenderPassInfo v;
	v.clear_state().SetFlag(bksge::ClearFlag::kColor);
	v.scissor_state().SetEnable(true);
	v.viewport().SetMaxDepth(10);

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_RenderPassInfo, HashTest)
{
	std::hash<bksge::RenderPassInfo> h;

	bksge::RenderPassInfo s1;
	bksge::RenderPassInfo s2;
	bksge::RenderPassInfo s3;
	bksge::RenderPassInfo s4;
	bksge::RenderPassInfo s5;

	s2.clear_state().SetFlag(bksge::ClearFlag::kColor);
	s3.scissor_state().SetEnable(true);
	s4.viewport().SetMaxDepth(10);

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
