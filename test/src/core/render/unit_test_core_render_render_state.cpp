/**
 *	@file	unit_test_core_render_render_state.cpp
 *
 *	@brief	RenderState のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/render_state.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_RenderState, DefaultCtorTest)
{
	bksge::RenderState const state;
	EXPECT_EQ(bksge::FillMode::kSolid,      state.rasterizer_state().fill_mode());
	EXPECT_EQ(bksge::CullMode::kNone,       state.rasterizer_state().cull_mode());
	EXPECT_EQ(bksge::FrontFace::kClockwise, state.rasterizer_state().front_face());

	EXPECT_EQ(false,                       state.blend_state().enable());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.blend_state().operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.blend_state().src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.blend_state().dst_factor());
	EXPECT_EQ(bksge::BlendOperation::kAdd, state.blend_state().alpha_operation());
	EXPECT_EQ(bksge::BlendFactor::kOne,    state.blend_state().alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kZero,   state.blend_state().alpha_dst_factor());

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
	state.blend_state().SetOperation(
		bksge::BlendOperation::kMax,
		bksge::BlendOperation::kMin);
	state.blend_state().SetFactor(
		bksge::BlendFactor::kDestAlpha, bksge::BlendFactor::kDestColor,
		bksge::BlendFactor::kSrcColor,  bksge::BlendFactor::kSrcAlpha);

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
	EXPECT_EQ(bksge::BlendOperation::kMax,         state.blend_state().operation());
	EXPECT_EQ(bksge::BlendFactor::kDestAlpha,      state.blend_state().src_factor());
	EXPECT_EQ(bksge::BlendFactor::kDestColor,      state.blend_state().dst_factor());
	EXPECT_EQ(bksge::BlendOperation::kMin,         state.blend_state().alpha_operation());
	EXPECT_EQ(bksge::BlendFactor::kSrcColor,       state.blend_state().alpha_src_factor());
	EXPECT_EQ(bksge::BlendFactor::kSrcAlpha,       state.blend_state().alpha_dst_factor());

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
