/**
 *	@file	unit_test_core_render_stencil_state.cpp
 *
 *	@brief	StencilState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/stencil_state.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

GTEST_TEST(Render_StencilState, DefaultCtorTest)
{
	bksge::StencilState const state;
	EXPECT_EQ(false,                             state.enable());
	EXPECT_EQ(0u,                                state.read_mask());
	EXPECT_EQ(0u,                                state.write_mask());
	EXPECT_EQ(bksge::ComparisonFunction::kNever, state.func());
	EXPECT_EQ(bksge::StencilOperation::kKeep,    state.fail_operation());
	EXPECT_EQ(bksge::StencilOperation::kKeep,    state.depth_fail_operation());
	EXPECT_EQ(bksge::StencilOperation::kKeep,    state.pass_operation());
}

GTEST_TEST(Render_StencilState, SetEnableTest)
{
	bksge::StencilState state;
	EXPECT_EQ(false, state.enable());

	state.SetEnable(true);
	EXPECT_EQ(true, state.enable());
}

GTEST_TEST(Render_StencilState, SetReadMaskTest)
{
	bksge::StencilState state;
	EXPECT_EQ(0u, state.read_mask());

	state.SetReadMask(1u);
	EXPECT_EQ(1u, state.read_mask());
}

GTEST_TEST(Render_StencilState, SetWriteMaskTest)
{
	bksge::StencilState state;
	EXPECT_EQ(0u, state.write_mask());

	state.SetWriteMask(2u);
	EXPECT_EQ(2u, state.write_mask());
}

GTEST_TEST(Render_StencilState, SetFuncTest)
{
	bksge::StencilState state;
	EXPECT_EQ(bksge::ComparisonFunction::kNever, state.func());

	state.SetFunc(bksge::ComparisonFunction::kLessEqual);
	EXPECT_EQ(bksge::ComparisonFunction::kLessEqual, state.func());
}

GTEST_TEST(Render_StencilState, SetFailOperationTest)
{
	bksge::StencilState state;
	EXPECT_EQ(bksge::StencilOperation::kKeep, state.fail_operation());

	state.SetFailOperation(bksge::StencilOperation::kIncr);
	EXPECT_EQ(bksge::StencilOperation::kIncr, state.fail_operation());
}

GTEST_TEST(Render_StencilState, SetDepthFailOperationTest)
{
	bksge::StencilState state;
	EXPECT_EQ(bksge::StencilOperation::kKeep, state.depth_fail_operation());

	state.SetDepthFailOperation(bksge::StencilOperation::kDecr);
	EXPECT_EQ(bksge::StencilOperation::kDecr, state.depth_fail_operation());
}

GTEST_TEST(Render_StencilState, SetPassOperationTest)
{
	bksge::StencilState state;
	EXPECT_EQ(bksge::StencilOperation::kKeep, state.pass_operation());

	state.SetPassOperation(bksge::StencilOperation::kReplace);
	EXPECT_EQ(bksge::StencilOperation::kReplace, state.pass_operation());
}

GTEST_TEST(Render_StencilState, CompareTest)
{
	bksge::StencilState v1;
	bksge::StencilState v2;
	bksge::StencilState v3;
	bksge::StencilState v4;
	bksge::StencilState v5;
	bksge::StencilState v6;
	bksge::StencilState v7;
	bksge::StencilState v8;
	bksge::StencilState v9;

	v3.SetEnable(true);
	v4.SetReadMask(1u);
	v5.SetWriteMask(2u);
	v6.SetFunc(bksge::ComparisonFunction::kLessEqual);
	v7.SetFailOperation(bksge::StencilOperation::kIncr);
	v8.SetDepthFailOperation(bksge::StencilOperation::kDecr);
	v9.SetPassOperation(bksge::StencilOperation::kReplace);

	EXPECT_TRUE (v1 == v1);
	EXPECT_TRUE (v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);
	EXPECT_FALSE(v1 == v5);
	EXPECT_FALSE(v1 == v6);
	EXPECT_FALSE(v1 == v7);
	EXPECT_FALSE(v1 == v8);
	EXPECT_FALSE(v1 == v9);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE (v1 != v3);
	EXPECT_TRUE (v1 != v4);
	EXPECT_TRUE (v1 != v5);
	EXPECT_TRUE (v1 != v6);
	EXPECT_TRUE (v1 != v7);
	EXPECT_TRUE (v1 != v8);
	EXPECT_TRUE (v1 != v9);
}

GTEST_TEST(Render_StencilState, OutputStreamTest)
{
	{
		bksge::StencilState v;
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ false, 0, 0, ComparisonFunction::kNever, StencilOperation::kKeep, StencilOperation::kKeep, StencilOperation::kKeep }", ss.str());
	}
	{
		bksge::StencilState v;
		v.SetEnable(true);
		v.SetReadMask(1u);
		v.SetWriteMask(2u);
		v.SetFunc(bksge::ComparisonFunction::kLessEqual);
		v.SetFailOperation(bksge::StencilOperation::kIncr);
		v.SetDepthFailOperation(bksge::StencilOperation::kDecr);
		v.SetPassOperation(bksge::StencilOperation::kReplace);
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ true, 1, 2, ComparisonFunction::kLessEqual, StencilOperation::kIncr, StencilOperation::kDecr, StencilOperation::kReplace }", ss.str());
	}
}

GTEST_TEST(Render_StencilState, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::StencilState v;
	v.SetEnable(true);
	v.SetReadMask(1u);
	v.SetWriteMask(2u);
	v.SetFunc(bksge::ComparisonFunction::kGreater);
	v.SetFailOperation(bksge::StencilOperation::kIncrSaturate);
	v.SetDepthFailOperation(bksge::StencilOperation::kInvert);
	v.SetPassOperation(bksge::StencilOperation::kIncr);

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}
