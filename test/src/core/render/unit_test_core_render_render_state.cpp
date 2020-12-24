/**
 *	@file	unit_test_core_render_render_state.cpp
 *
 *	@brief	RenderState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/render_state.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/vector.hpp>
#include <functional>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

GTEST_TEST(Render_RenderState, DefaultCtorTest)
{
	bksge::RenderState const state;
	EXPECT_EQ(bksge::FillMode::kSolid,      state.rasterizer_state().fill_mode());
	EXPECT_EQ(bksge::CullMode::kNone,       state.rasterizer_state().cull_mode());
	EXPECT_EQ(bksge::FrontFace::kClockwise, state.rasterizer_state().front_face());

	EXPECT_EQ(false,                       state.blend_state().enable());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.blend_state().color_operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.blend_state().color_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.blend_state().color_dst_factor());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.blend_state().alpha_operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.blend_state().alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.blend_state().alpha_dst_factor());
	EXPECT_EQ(bksge::ColorWriteFlag::kAll, state.blend_state().color_write_mask());

	EXPECT_EQ(false,                            state.depth_state().enable());
	EXPECT_EQ(false,                            state.depth_state().write());
	EXPECT_EQ(bksge::ComparisonFunction::kLess, state.depth_state().func());

	EXPECT_EQ(false,                             state.stencil_state().enable());
	EXPECT_EQ(0u,                                state.stencil_state().read_mask());
	EXPECT_EQ(0u,                                state.stencil_state().write_mask());
	EXPECT_EQ(bksge::ComparisonFunction::kNever, state.stencil_state().func());
	EXPECT_EQ(bksge::StencilOperation::kKeep,    state.stencil_state().fail_operation());
	EXPECT_EQ(bksge::StencilOperation::kKeep,    state.stencil_state().depth_fail_operation());
	EXPECT_EQ(bksge::StencilOperation::kKeep,    state.stencil_state().pass_operation());
}

GTEST_TEST(Render_RenderState, SetValueTest)
{
	bksge::RenderState state;

	state.rasterizer_state().SetFillMode(bksge::FillMode::kWireframe);
	state.rasterizer_state().SetCullMode(bksge::CullMode::kBack);
	state.rasterizer_state().SetFrontFace(bksge::FrontFace::kCounterClockwise);

	state.blend_state().SetEnable(true);
	state.blend_state().SetColorOperation(bksge::BlendOperation::kMax);
	state.blend_state().SetAlphaOperation(bksge::BlendOperation::kMin);
	state.blend_state().SetColorSrcFactor(bksge::BlendFactor::kDestAlpha);
	state.blend_state().SetColorDstFactor(bksge::BlendFactor::kDestColor);
	state.blend_state().SetAlphaSrcFactor(bksge::BlendFactor::kSrcColor);
	state.blend_state().SetAlphaDstFactor(bksge::BlendFactor::kSrcAlpha);
	state.blend_state().SetColorWriteFlag(bksge::ColorWriteFlag::kNone);

	state.depth_state().SetEnable(true);
	state.depth_state().SetWrite(true);
	state.depth_state().SetFunc(bksge::ComparisonFunction::kGreater);

	state.stencil_state().SetEnable(true);
	state.stencil_state().SetReadMask(1);
	state.stencil_state().SetWriteMask(2);
	state.stencil_state().SetFunc(bksge::ComparisonFunction::kLess);
	state.stencil_state().SetFailOperation(bksge::StencilOperation::kIncr);
	state.stencil_state().SetDepthFailOperation(bksge::StencilOperation::kDecr);
	state.stencil_state().SetPassOperation(bksge::StencilOperation::kReplace);

	EXPECT_EQ(bksge::FillMode::kWireframe,         state.rasterizer_state().fill_mode());
	EXPECT_EQ(bksge::CullMode::kBack,              state.rasterizer_state().cull_mode());
	EXPECT_EQ(bksge::FrontFace::kCounterClockwise, state.rasterizer_state().front_face());

	EXPECT_EQ(true,                                state.blend_state().enable());
	EXPECT_EQ(bksge::BlendOperation::kMax,         state.blend_state().color_operation());
	EXPECT_EQ(bksge::BlendFactor::kDestAlpha,      state.blend_state().color_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,      state.blend_state().color_dst_factor());
	EXPECT_EQ(bksge::BlendOperation::kMin,         state.blend_state().alpha_operation());
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,       state.blend_state().alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcAlpha,       state.blend_state().alpha_dst_factor());
	EXPECT_EQ(bksge::ColorWriteFlag::kNone,        state.blend_state().color_write_mask());

	EXPECT_EQ(true,                                state.depth_state().enable());
	EXPECT_EQ(true,                                state.depth_state().write());
	EXPECT_EQ(bksge::ComparisonFunction::kGreater, state.depth_state().func());

	EXPECT_EQ(true,                                state.stencil_state().enable());
	EXPECT_EQ(1u,                                  state.stencil_state().read_mask());
	EXPECT_EQ(2u,                                  state.stencil_state().write_mask());
	EXPECT_EQ(bksge::ComparisonFunction::kLess,    state.stencil_state().func());
	EXPECT_EQ(bksge::StencilOperation::kIncr,      state.stencil_state().fail_operation());
	EXPECT_EQ(bksge::StencilOperation::kDecr,      state.stencil_state().depth_fail_operation());
	EXPECT_EQ(bksge::StencilOperation::kReplace,   state.stencil_state().pass_operation());
}

GTEST_TEST(Render_RenderState, CompareTest)
{
	bksge::RenderState v1;
	bksge::RenderState v2;
	bksge::RenderState v3;
	bksge::RenderState v4;
	bksge::RenderState v5;
	bksge::RenderState v6;

	v3.rasterizer_state().SetFillMode(bksge::FillMode::kWireframe);
	v4.blend_state().SetEnable(true);
	v5.depth_state().SetEnable(true);
	v6.stencil_state().SetEnable(true);

	EXPECT_TRUE (v1 == v1);
	EXPECT_TRUE (v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);
	EXPECT_FALSE(v1 == v5);
	EXPECT_FALSE(v1 == v6);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE (v1 != v3);
	EXPECT_TRUE (v1 != v4);
	EXPECT_TRUE (v1 != v5);
	EXPECT_TRUE (v1 != v6);
}

GTEST_TEST(Render_RenderState, OutputStreamTest)
{
	{
		bksge::RenderState v;
		bksge::stringstream ss;
		ss << v;
		EXPECT_EQ("{ { FillMode::kSolid, CullMode::kNone, FrontFace::kClockwise }, { false, BlendOperation::kAdd, BlendFactor::kOne, BlendFactor::kZero, BlendOperation::kAdd, BlendFactor::kOne, BlendFactor::kZero, ColorWriteFlag::kAll }, { false, false, ComparisonFunction::kLess }, { false, 0, 0, 0, ComparisonFunction::kNever, StencilOperation::kKeep, StencilOperation::kKeep, StencilOperation::kKeep } }", ss.str());
	}
	{
		bksge::RenderState v;
		v.rasterizer_state().SetFillMode(bksge::FillMode::kWireframe);
		v.rasterizer_state().SetCullMode(bksge::CullMode::kBack);
		v.rasterizer_state().SetFrontFace(bksge::FrontFace::kCounterClockwise);
		v.blend_state().SetEnable(true);
		v.blend_state().SetColorOperation(bksge::BlendOperation::kMax);
		v.blend_state().SetAlphaOperation(bksge::BlendOperation::kMin);
		v.blend_state().SetColorSrcFactor(bksge::BlendFactor::kDestAlpha);
		v.blend_state().SetColorDstFactor(bksge::BlendFactor::kDestColor);
		v.blend_state().SetAlphaSrcFactor(bksge::BlendFactor::kSrcColor);
		v.blend_state().SetAlphaDstFactor(bksge::BlendFactor::kSrcAlpha);
		v.blend_state().SetColorWriteFlag(bksge::ColorWriteFlag::kNone);
		v.depth_state().SetEnable(true);
		v.depth_state().SetWrite(true);
		v.depth_state().SetFunc(bksge::ComparisonFunction::kGreater);
		v.stencil_state().SetEnable(true);
		v.stencil_state().SetReadMask(1);
		v.stencil_state().SetWriteMask(2);
		v.stencil_state().SetReference(3);
		v.stencil_state().SetFunc(bksge::ComparisonFunction::kLess);
		v.stencil_state().SetFailOperation(bksge::StencilOperation::kIncr);
		v.stencil_state().SetDepthFailOperation(bksge::StencilOperation::kDecr);
		v.stencil_state().SetPassOperation(bksge::StencilOperation::kReplace);
		bksge::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ { FillMode::kWireframe, CullMode::kBack, FrontFace::kCounterClockwise }, { true, BlendOperation::kMax, BlendFactor::kDestAlpha, BlendFactor::kDestColor, BlendOperation::kMin, BlendFactor::kSrcColor, BlendFactor::kSrcAlpha, ColorWriteFlag::kNone }, { true, true, ComparisonFunction::kGreater }, { true, 1, 2, 3, ComparisonFunction::kLess, StencilOperation::kIncr, StencilOperation::kDecr, StencilOperation::kReplace } }", ss.str());
	}
}

GTEST_TEST(Render_RenderState, SerializeTest)
{
	using namespace bksge::serialization;

	bksge::RenderState v;
	v.rasterizer_state().SetFillMode(bksge::FillMode::kWireframe);
	v.blend_state().SetEnable(true);
	v.depth_state().SetEnable(true);
	v.stencil_state().SetEnable(true);

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_RenderState, HashTest)
{
	std::hash<bksge::RenderState> h;

	bksge::RenderState s1;
	bksge::RenderState s2;
	bksge::RenderState s3;
	bksge::RenderState s4;
	bksge::RenderState s5;
	bksge::RenderState s6;

	s2.rasterizer_state().SetFillMode(bksge::FillMode::kWireframe);
	s3.blend_state().SetEnable(true);
	s4.depth_state().SetEnable(true);
	s5.stencil_state().SetEnable(true);

	bksge::vector<bksge::size_t> v;
	v.push_back(h(s1));
	v.push_back(h(s2));
	v.push_back(h(s3));
	v.push_back(h(s4));
	v.push_back(h(s5));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(s6));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}
