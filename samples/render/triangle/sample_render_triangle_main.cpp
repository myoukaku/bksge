/**
 *	@file	sample_render_triangle_main.cpp
 *
 *	@brief	三角形をレンダリングするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>
#include <bksge/render.hpp>

int main()
{
	bksge::Window window({800, 600}, "sample_render_triangle");

#if 1
	bksge::GlRenderer renderer;
#else
	bksge::D3D11Renderer renderer;
#endif
	renderer.SetRenderTarget(window);
	renderer.SetClearColor({0.5f, 0.0f, 0.5f, 1});

	const bksge::Vertex<bksge::VPosition> vertices[] =
	{
		{{{-0.5,  0.5, 0.0}}},
		{{{-0.5, -0.5, 0.0}}},
		{{{ 0.5,  0.5, 0.0}}},
	};

	const std::uint16_t indices[] =
	{
		0, 1, 2,
	};

	const bksge::Geometry geometry(bksge::Primitive::kTriangles, vertices, indices);

#if 1
	// GLSL
	char const* vs_source =
		"attribute vec3 aPosition;					"
		"											"
		"void main()								"
		"{											"
		"	gl_Position = vec4(aPosition, 1.0);		"
		"}											"
	;

	char const* fs_source =
		"void main()								"
		"{											"
		"	gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);"
		"}											"
	;
#else
	// HLSL
	char const* vs_source =
		"float4 main(float3 aPosition : POSITION) : SV_POSITION	"
		"{												"
		"	return float4(aPosition, 1.0);				"
		"}												"
	;

	char const* fs_source =
		"float4 main() : SV_Target					"
		"{											"
		"	return float4(0.0, 0.0, 1.0, 1.0);		"
		"}											"
	;
#endif

	bksge::Shader shader;
	shader.SetProgram(bksge::ShaderStage::kVertex, vs_source);
	shader.SetProgram(bksge::ShaderStage::kFragment, fs_source);

	while (window.Update())
	{
		renderer.Begin();
		renderer.Clear();
		renderer.Render(geometry, shader);
		renderer.End();
	}

	return 0;
}
