/**
 *	@file	unit_test_core_render_blend_state.cpp
 *
 *	@brief	BlendState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/blend_state.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <functional>
#include <vector>
#include <algorithm>
#include "serialize_test.hpp"

GTEST_TEST(Render_BlendState, DefaultCtorTest)
{
	bksge::BlendState const state;
	EXPECT_EQ(false,                       state.enable());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.dst_factor());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.alpha_operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.alpha_dst_factor());
}

GTEST_TEST(Render_BlendState, SetEnableTest)
{
	bksge::BlendState state;
	EXPECT_EQ(false, state.enable());

	state.SetEnable(true);
	EXPECT_EQ(true, state.enable());
}

GTEST_TEST(Render_BlendState, SetOperationTest)
{
	bksge::BlendState state;
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.operation());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.alpha_operation());

	state.SetOperation(bksge::BlendOperation::kSubtract);
	EXPECT_EQ(bksge::BlendOperation::kSubtract, state.operation());
	EXPECT_EQ(bksge::BlendOperation::kSubtract, state.alpha_operation());

	state.SetOperation(
		bksge::BlendOperation::kMin,
		bksge::BlendOperation::kMax);
	EXPECT_EQ(bksge::BlendOperation::kMin, state.operation());
	EXPECT_EQ(bksge::BlendOperation::kMax, state.alpha_operation());
}

GTEST_TEST(Render_BlendState, SetFactorTest)
{
	bksge::BlendState state;
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.alpha_dst_factor());

	state.SetFactor(
		bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,    state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,   state.dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,    state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,   state.alpha_dst_factor());

	state.SetFactor(
		bksge::BlendFactor::kInvSrcColor, bksge::BlendFactor::kInvDestColor,
		bksge::BlendFactor::kDestAlpha, bksge::BlendFactor::kSrcAlpha);
	EXPECT_EQ(bksge::BlendFactor::kInvSrcColor,  state.src_factor());
	EXPECT_EQ(bksge::BlendFactor::kInvDestColor, state.dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestAlpha,	 state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcAlpha,	 state.alpha_dst_factor());
}

GTEST_TEST(Render_BlendState, CompareTest)
{
	bksge::BlendState v1;
	bksge::BlendState v2;
	bksge::BlendState v3;
	bksge::BlendState v4;
	bksge::BlendState v5;

	v1.SetEnable(true);
	v1.SetOperation(bksge::BlendOperation::kSubtract);
	v1.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);

	v2.SetEnable(true);
	v2.SetOperation(bksge::BlendOperation::kSubtract);
	v2.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);

	v3.SetOperation(bksge::BlendOperation::kSubtract);
	v3.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);

	v4.SetEnable(true);
	v4.SetOperation(bksge::BlendOperation::kSubtract, bksge::BlendOperation::kMax);
	v4.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);

	v5.SetEnable(true);
	v5.SetOperation(bksge::BlendOperation::kSubtract);
	v5.SetFactor(
		bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor,
		bksge::BlendFactor::kDestAlpha, bksge::BlendFactor::kSrcAlpha);

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

GTEST_TEST(Render_BlendState, OutputStreamTest)
{
	{
		bksge::BlendState v;
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ false, BlendOperation::kAdd, BlendFactor::kOne, BlendFactor::kZero, BlendOperation::kAdd, BlendFactor::kOne, BlendFactor::kZero }", ss.str());
	}
	{
		bksge::BlendState v;
		v.SetEnable(true);
		v.SetOperation(
			bksge::BlendOperation::kReverseSubtract, bksge::BlendOperation::kAdd);
		v.SetFactor(
			bksge::BlendFactor::kBlendFactor, bksge::BlendFactor::kDestAlpha,
			bksge::BlendFactor::kInvBlendFactor, bksge::BlendFactor::kInvSrc1Alpha);
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ true, BlendOperation::kReverseSubtract, BlendFactor::kBlendFactor, BlendFactor::kDestAlpha, BlendOperation::kAdd, BlendFactor::kInvBlendFactor, BlendFactor::kInvSrc1Alpha }", ss.str());
	}
}

GTEST_TEST(Render_BlendState, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::BlendState v;
	v.SetEnable(true);
	v.SetOperation(bksge::BlendOperation::kMin, bksge::BlendOperation::kMax);
	v.SetFactor(
		bksge::BlendFactor::kInvSrcColor, bksge::BlendFactor::kInvDestColor,
		bksge::BlendFactor::kDestAlpha, bksge::BlendFactor::kSrcAlpha);

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_BlendState, HashTest)
{
	std::hash<bksge::BlendState> h;

	bksge::BlendState s1;
	bksge::BlendState s2;
	bksge::BlendState s3;
	bksge::BlendState s4;
	bksge::BlendState s5;
	bksge::BlendState s6;
	bksge::BlendState s7;
	bksge::BlendState s8;

	s2.SetEnable(true);
	s3.SetOperation(bksge::BlendOperation::kMax, bksge::BlendOperation::kAdd);
	s4.SetOperation(bksge::BlendOperation::kAdd, bksge::BlendOperation::kSubtract);
	s5.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kZero, bksge::BlendFactor::kOne, bksge::BlendFactor::kZero);
	s6.SetFactor(bksge::BlendFactor::kOne, bksge::BlendFactor::kOne, bksge::BlendFactor::kOne, bksge::BlendFactor::kZero);
	s7.SetFactor(bksge::BlendFactor::kOne, bksge::BlendFactor::kZero, bksge::BlendFactor::kDestAlpha, bksge::BlendFactor::kZero);
	s8.SetFactor(bksge::BlendFactor::kOne, bksge::BlendFactor::kZero, bksge::BlendFactor::kOne, bksge::BlendFactor::kInvDestAlpha);

	std::vector<std::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	v.push_back(h(s5));
	v.push_back(h(s6));
	v.push_back(h(s7));
	v.push_back(h(s8));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s2));
	std::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
