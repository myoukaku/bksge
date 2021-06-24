/**
 *	@file	unit_test_core_render_blend_state.cpp
 *
 *	@brief	BlendState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/blend_state.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

GTEST_TEST(Render_BlendState, DefaultCtorTest)
{
	bksge::BlendState const state;
	EXPECT_EQ(false,                        state.enable());
	EXPECT_EQ(bksge::BlendOperation::kAdd,  state.color_operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,     state.color_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,    state.color_dst_factor());
	EXPECT_EQ(bksge::BlendOperation::kAdd,  state.alpha_operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,     state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,    state.alpha_dst_factor());
	EXPECT_EQ(bksge::ColorWriteFlag::kAll,  state.color_write_mask());
	EXPECT_EQ(false,                        state.logic_op_enable());
	EXPECT_EQ(bksge::LogicOperation::kCopy, state.logic_operation());
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
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.color_operation());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.alpha_operation());

	state.SetOperation(bksge::BlendOperation::kSubtract);
	EXPECT_EQ(bksge::BlendOperation::kSubtract, state.color_operation());
	EXPECT_EQ(bksge::BlendOperation::kSubtract, state.alpha_operation());

	state.SetColorOperation(bksge::BlendOperation::kMin);
	state.SetAlphaOperation(bksge::BlendOperation::kMax);
	EXPECT_EQ(bksge::BlendOperation::kMin, state.color_operation());
	EXPECT_EQ(bksge::BlendOperation::kMax, state.alpha_operation());
}

GTEST_TEST(Render_BlendState, SetFactorTest)
{
	bksge::BlendState state;
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.color_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.color_dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.alpha_dst_factor());

	state.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,    state.color_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,   state.color_dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,    state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,   state.alpha_dst_factor());

	state.SetColorSrcFactor(bksge::BlendFactor::kInvSrcColor);
	state.SetColorDstFactor(bksge::BlendFactor::kInvDestColor);
	state.SetAlphaSrcFactor(bksge::BlendFactor::kDestAlpha);
	state.SetAlphaDstFactor(bksge::BlendFactor::kSrcAlpha);
	EXPECT_EQ(bksge::BlendFactor::kInvSrcColor,  state.color_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kInvDestColor, state.color_dst_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestAlpha,	 state.alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcAlpha,	 state.alpha_dst_factor());
}

GTEST_TEST(Render_BlendState, SetColorWriteFlagTest)
{
	bksge::BlendState state;
	EXPECT_EQ(bksge::ColorWriteFlag::kAll, state.color_write_mask());

	state.SetColorWriteFlag(bksge::ColorWriteFlag::kRed);
	EXPECT_EQ(bksge::ColorWriteFlag::kRed, state.color_write_mask());
}

GTEST_TEST(Render_BlendState, SetLogicOperationTest)
{
	bksge::BlendState state;
	EXPECT_EQ(false, state.logic_op_enable());
	EXPECT_EQ(bksge::LogicOperation::kCopy, state.logic_operation());

	state.SetLogicOpEnable(true);
	EXPECT_EQ(true, state.logic_op_enable());
	EXPECT_EQ(bksge::LogicOperation::kCopy, state.logic_operation());

	state.SetLogicOperation(bksge::LogicOperation::kAnd);
	EXPECT_EQ(true, state.logic_op_enable());
	EXPECT_EQ(bksge::LogicOperation::kAnd, state.logic_operation());
}

GTEST_TEST(Render_BlendState, CompareTest)
{
	bksge::BlendState v1;
	bksge::BlendState v2;
	bksge::BlendState v3;
	bksge::BlendState v4;
	bksge::BlendState v5;
	bksge::BlendState v6;
	bksge::BlendState v7;
	bksge::BlendState v8;

	v1.SetEnable(true);
	v1.SetOperation(bksge::BlendOperation::kSubtract);
	v1.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);

	v2.SetEnable(true);
	v2.SetOperation(bksge::BlendOperation::kSubtract);
	v2.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);

	v3.SetOperation(bksge::BlendOperation::kSubtract);
	v3.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);

	v4.SetEnable(true);
	v4.SetColorOperation(bksge::BlendOperation::kSubtract);
	v4.SetAlphaOperation(bksge::BlendOperation::kMax);
	v4.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);

	v5.SetEnable(true);
	v5.SetOperation(bksge::BlendOperation::kSubtract);
	v5.SetColorSrcFactor(bksge::BlendFactor::kSrcColor);
	v5.SetColorDstFactor(bksge::BlendFactor::kDestColor);
	v5.SetAlphaSrcFactor(bksge::BlendFactor::kDestAlpha);
	v5.SetAlphaDstFactor(bksge::BlendFactor::kSrcAlpha);

	v6.SetEnable(true);
	v6.SetOperation(bksge::BlendOperation::kSubtract);
	v6.SetFactor(bksge::BlendFactor::kSrcColor, bksge::BlendFactor::kDestColor);
	v6.SetColorWriteFlag(bksge::ColorWriteFlag::kRed);

	v7.SetLogicOpEnable(true);
	v8.SetLogicOperation(bksge::LogicOperation::kInvert);

	EXPECT_TRUE (v1 == v1);
	EXPECT_TRUE (v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);
	EXPECT_FALSE(v1 == v5);
	EXPECT_FALSE(v1 == v6);
	EXPECT_FALSE(v1 == v7);
	EXPECT_FALSE(v1 == v8);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE (v1 != v3);
	EXPECT_TRUE (v1 != v4);
	EXPECT_TRUE (v1 != v5);
	EXPECT_TRUE (v1 != v6);
	EXPECT_TRUE (v1 != v7);
	EXPECT_TRUE (v1 != v8);
}

GTEST_TEST(Render_BlendState, OutputStreamTest)
{
	{
		bksge::BlendState v;
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ false, BlendOperation::kAdd, BlendFactor::kOne, BlendFactor::kZero, BlendOperation::kAdd, BlendFactor::kOne, BlendFactor::kZero, ColorWriteFlag::kAll, false, LogicOperation::kCopy }", ss.str());
	}
	{
		bksge::BlendState v;
		v.SetEnable(true);
		v.SetColorOperation(bksge::BlendOperation::kReverseSubtract);
		v.SetAlphaOperation(bksge::BlendOperation::kAdd);
		v.SetColorSrcFactor(bksge::BlendFactor::kBlendFactor);
		v.SetColorDstFactor(bksge::BlendFactor::kDestAlpha);
		v.SetAlphaSrcFactor(bksge::BlendFactor::kInvBlendFactor);
		v.SetAlphaDstFactor(bksge::BlendFactor::kInvSrc1Alpha);
		v.SetColorWriteFlag(bksge::ColorWriteFlag::kGreen);
		v.SetLogicOpEnable(true);
		v.SetLogicOperation(bksge::LogicOperation::kInvert);
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ true, BlendOperation::kReverseSubtract, BlendFactor::kBlendFactor, BlendFactor::kDestAlpha, BlendOperation::kAdd, BlendFactor::kInvBlendFactor, BlendFactor::kInvSrc1Alpha, ColorWriteFlag::kGreen, true, LogicOperation::kInvert }", ss.str());
	}
}

GTEST_TEST(Render_BlendState, SerializeTest)
{
	using namespace bksge::serialization;

	{
		bksge::BlendState v;
		v.SetEnable(true);
		v.SetColorOperation(bksge::BlendOperation::kMin);
		v.SetAlphaOperation(bksge::BlendOperation::kMax);
		v.SetColorSrcFactor(bksge::BlendFactor::kInvSrcColor);
		v.SetColorDstFactor(bksge::BlendFactor::kInvDestColor);
		v.SetAlphaSrcFactor(bksge::BlendFactor::kDestAlpha);
		v.SetAlphaDstFactor(bksge::BlendFactor::kSrcAlpha);
		v.SetColorWriteFlag(bksge::ColorWriteFlag::kBlue);
		v.SetLogicOpEnable(true);
		v.SetLogicOperation(bksge::LogicOperation::kXor);

		SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//		SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//		SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);
	}

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	{
		bksge::BlendState v;
		v.SetEnable(false);
		v.SetColorOperation(bksge::BlendOperation::kAdd);
		v.SetAlphaOperation(bksge::BlendOperation::kReverseSubtract);
		v.SetColorSrcFactor(bksge::BlendFactor::kBlendFactor);
		v.SetColorDstFactor(bksge::BlendFactor::kDestAlpha);
		v.SetAlphaSrcFactor(bksge::BlendFactor::kDestColor);
		v.SetAlphaDstFactor(bksge::BlendFactor::kInvBlendFactor);
		v.SetColorWriteFlag(bksge::ColorWriteFlag::kBlue);
		v.SetLogicOpEnable(true);
		v.SetLogicOperation(bksge::LogicOperation::kClear);
		SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//		SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//		SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
	}
#endif
}

GTEST_TEST(Render_BlendState, HashTest)
{
	bksge::hash<bksge::BlendState> h;

	bksge::BlendState s1;
	bksge::BlendState s2;
	bksge::BlendState s3;
	bksge::BlendState s4;
	bksge::BlendState s5;
	bksge::BlendState s6;
	bksge::BlendState s7;
	bksge::BlendState s8;
	bksge::BlendState s9;
	bksge::BlendState s10;
	bksge::BlendState s11;
	bksge::BlendState s12;

	s2.SetEnable(true);
	s3.SetColorOperation(bksge::BlendOperation::kMax);
	s4.SetAlphaOperation(bksge::BlendOperation::kSubtract);
	s5.SetColorSrcFactor(bksge::BlendFactor::kSrcColor);
	s6.SetColorDstFactor(bksge::BlendFactor::kOne);
	s7.SetAlphaSrcFactor(bksge::BlendFactor::kDestAlpha);
	s8.SetAlphaDstFactor(bksge::BlendFactor::kInvDestAlpha);
	s9.SetColorWriteFlag(bksge::ColorWriteFlag::kAlpha);
	s10.SetLogicOpEnable(true);
	s11.SetLogicOperation(bksge::LogicOperation::kSet);

	bksge::vector<bksge::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	v.push_back(h(s5));
	v.push_back(h(s6));
	v.push_back(h(s7));
	v.push_back(h(s8));
	v.push_back(h(s9));
	v.push_back(h(s10));
	v.push_back(h(s11));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s9));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));

	EXPECT_EQ(h(s1), h(s12));
}
