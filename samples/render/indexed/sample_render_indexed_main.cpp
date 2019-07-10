/**
 *	@file	sample_render_indexed_main.cpp
 *
 *	@brief	インデックスバッファーを使ってレンダリングするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>
#include <bksge/render.hpp>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
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

	static bksge::Shader const shader
	{
		bksge::ShaderType::kGLSL,
		{
			{ bksge::ShaderStage::kVertex,   vs_source },
			{ bksge::ShaderStage::kFragment, fs_source },
		}
	};

	return &shader;
}

static bksge::Shader const* GetHLSLShader(void)
{
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

	char const* ps_source =
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

	static bksge::Shader const shader
	{
		bksge::ShaderType::kHLSL,
		{
			{ bksge::ShaderStage::kVertex,   vs_source },
			{ bksge::ShaderStage::kFragment, ps_source },
		}
	};

	return &shader;
}

}	// namespace

int main()
{
	std::vector<std::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<std::shared_ptr<bksge::Window>>		windows;

#if BKSGE_RENDER_HAS_D3D11_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_indexed - D3D11"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D11Renderer> renderer(
			new bksge::D3D11Renderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif
#if BKSGE_RENDER_HAS_D3D12_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_indexed - D3D12"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D12Renderer> renderer(
			new bksge::D3D12Renderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif
#if BKSGE_RENDER_HAS_GL_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_indexed - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif

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

	const bksge::Geometry geometry(
		bksge::Primitive::kTriangles, vertices, indices);

	std::vector<bksge::Shader const*> const shader_list
	{
		GetGLSLShader(),
		GetHLSLShader(),
	};

	bksge::ShaderParameterMap shader_parameter;

	bksge::RenderState render_state;

	for (;;)
	{
		for (auto& window : windows)
		{
			if (!window->Update())
			{
				return 0;
			}
		}

		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->Render(
				geometry, shader_list, shader_parameter, render_state);
			renderer->End();
		}
	}

	return 0;
}
