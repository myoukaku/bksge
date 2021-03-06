﻿/**
 *	@file	unit_test_core_render_null_renderer.cpp
 *
 *	@brief	NullRenderer のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/null_renderer.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/core/render/render_pass_info.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_core_render_test
{

namespace null_renderer_test
{

GTEST_TEST(RenderTest, NullRendererTest)
{
#if BKSGE_CORE_RENDER_HAS_NULL_RENDERER
	bksge::NullRenderer renderer;

	renderer.Begin();

	bksge::RenderPassInfo render_pass_info;
	renderer.BeginRenderPass(render_pass_info);
	bksge::Geometry geometry;
	bksge::Shader shader{};
	bksge::ShaderParameterMap shader_parameter_map;
	bksge::RenderState render_state;
	renderer.Render(geometry, shader, shader_parameter_map, render_state);
	renderer.EndRenderPass();
	renderer.End();
#endif
}

}	// namespace null_renderer_test

}	// namespace bksge_core_render_test
