/**
 *	@file	sample_render_indexed_main.cpp
 *
 *	@brief	インデックスバッファーを使ってレンダリングするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>
#include <bksge/render.hpp>

#define SAMPLE_RENDERER_GL		0
#define SAMPLE_RENDERER_D3D11	1
#define SAMPLE_RENDERER_D3D12	2

#define	SAMPLE_RENDERER		SAMPLE_RENDERER_GL

int main()
{
	bksge::Window window({800, 600}, "sample_render_indexed");

#if SAMPLE_RENDERER == SAMPLE_RENDERER_GL
	bksge::GlRenderer renderer;
	#define USE_GLSL
#elif SAMPLE_RENDERER == SAMPLE_RENDERER_D3D11
	bksge::D3D11Renderer renderer;
#elif SAMPLE_RENDERER == SAMPLE_RENDERER_D3D12
	bksge::D3D12Renderer renderer;
#else
#endif
	renderer.SetRenderTarget(window);
	renderer.SetClearColor({0.5f, 0.0f, 0.5f, 1});

	const bksge::Vertex<bksge::VPosition, bksge::VColor> vertices[] =
	{
		{{{ -0.5f,  0.5f, 0.0f }}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
		{{{  0.5f,  0.5f, 0.0f }}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
		{{{ -0.5f, -0.5f, 0.0f }}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
		{{{  0.5f, -0.5f, 0.0f }}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},
	};

	const std::uint16_t indices[] =
	{
		0, 2, 1,
		1, 2, 3,
	};

	const bksge::Geometry geometry(bksge::Primitive::kTriangles, vertices, indices);

#if defined(USE_GLSL)
	// GLSL
	char const* vs_source =
		"attribute vec3 aPosition;					"
		"attribute vec4 aColor;						"
		"varying  vec4 vColor;						"
		"											"
		"void main()								"
		"{											"
		"	gl_Position = vec4(aPosition, 1.0);		"
		"	vColor = aColor;						"
		"}											"
	;

	char const* fs_source =
		"varying  vec4 vColor;						"
		"											"
		"void main()								"
		"{											"
		"	gl_FragColor = vColor;					"
		"}											"
	;
#else
	// HLSL
	char const* vs_source =
		"struct VS_INPUT							"
		"{											"
		"	float3 pos   : POSITION;				"
		"	float4 color : COLOR;					"
		"};											"
 		"											"
		"struct VS_OUTPUT							"
		"{											"
		"	float4 pos   : SV_POSITION;				"
		"	float4 color : COLOR;					"
		"};											"
		"											"
		"VS_OUTPUT main(VS_INPUT input)				"
		"{											"
		"	VS_OUTPUT output;						"
		"	output.pos = float4(input.pos, 1.0);	"
		"	output.color = input.color;				"
		"	return output;							"
		"}											"
	;

	char const* fs_source =
		"struct PS_INPUT							"
		"{											"
		"	float4 pos   : SV_POSITION;				"
		"	float4 color : COLOR;					"
		"};											"
		"											"
		"float4 main(PS_INPUT input) : SV_Target	"
		"{											"
		"	return input.color;						"
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
