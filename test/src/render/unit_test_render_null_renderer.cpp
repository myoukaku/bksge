/**
 *	@file	unit_test_render_null_renderer.cpp
 *
 *	@brief	NullRenderer のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/null_renderer.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/shader_map.hpp>
#include <bksge/render/shader_parameter_map.hpp>
#include <bksge/render/render_state.hpp>
#include <bksge/window/null/null_window.hpp>
#include <gtest/gtest.h>

namespace bksge_render_test
{

namespace null_renderer_test
{

GTEST_TEST(RenderTest, NullRendererTest)
{
#if BKSGE_RENDER_HAS_NULL_RENDERER
//	bksge::window::NullWindow window{{400, 300}, "test"};
	bksge::NullRenderer renderer;

//	renderer.SetRenderTarget(window);
	renderer.SetViewport({});
	renderer.SetScissor({});
	renderer.SetClearFlag(bksge::ClearFlag::kAll);
	renderer.SetClearColor({});
	renderer.Begin();
	renderer.Clear();
	bksge::Geometry geometry;
	bksge::ShaderMap shader_map({});
	bksge::ShaderParameterMap shader_parameter_map;
	bksge::RenderState render_state;
	renderer.Render(geometry, shader_map, shader_parameter_map, render_state);
	renderer.End();
#endif
}

}	// namespace null_renderer_test

}	// namespace bksge_render_test
