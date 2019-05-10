/**
 *	@file	sample_render_triangle_main.cpp
 *
 *	@brief	三角形をレンダリングするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>
#include <bksge/render.hpp>
#include <vector>
#include <memory>
#include <utility>

namespace
{

static bksge::Shader GetGLSLShader(void)
{
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

	return bksge::Shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, fs_source },
	};
}

static bksge::Shader GetHLSLShader(void)
{
	char const* vs_source =
		"float4 main(float3 aPosition : POSITION) : SV_POSITION	"
		"{												"
		"	return float4(aPosition, 1.0);				"
		"}												"
	;

	char const* ps_source =
		"float4 main() : SV_Target					"
		"{											"
		"	return float4(0.0, 0.0, 1.0, 1.0);		"
		"}											"
	;

	return bksge::Shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, ps_source },
	};
}

}	// namespace

int main()
{
	std::vector<std::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<std::shared_ptr<bksge::Window>>		windows;

#if BKSGE_RENDER_HAS_D3D11_RENDERER
	{
		std::shared_ptr<bksge::D3D11Renderer> renderer(new bksge::D3D11Renderer());
		std::shared_ptr<bksge::Window> window(new bksge::Window({800, 600}, "sample_render_triangle - D3D11"));
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
		renderers.push_back(renderer);
		windows.push_back(window);
	}
#endif
#if BKSGE_RENDER_HAS_D3D12_RENDERER
	{
		std::shared_ptr<bksge::D3D12Renderer> renderer(new bksge::D3D12Renderer());
		std::shared_ptr<bksge::Window> window(new bksge::Window({800, 600}, "sample_render_triangle - D3D12"));
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
		renderers.push_back(renderer);
		windows.push_back(window);
	}
#endif
#if BKSGE_RENDER_HAS_GL_RENDERER
	{
		std::shared_ptr<bksge::GlRenderer> renderer(new bksge::GlRenderer());
		std::shared_ptr<bksge::Window> window(new bksge::Window({800, 600}, "sample_render_triangle - GL"));
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
		renderers.push_back(renderer);
		windows.push_back(window);
	}
#endif

	const bksge::Vertex<bksge::VPosition> vertices[] =
	{
		{{{ 0.0,  0.5, 0.0}}},
		{{{-0.5, -0.5, 0.0}}},
		{{{ 0.5, -0.5, 0.0}}},
	};

	const bksge::Geometry geometry(bksge::Primitive::kTriangles, vertices);

	bksge::ShaderMap const shader_map
	{
		{ bksge::ShaderType::kGLSL, GetGLSLShader() },
		{ bksge::ShaderType::kHLSL, GetHLSLShader() },
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
			renderer->Clear();
			renderer->Render(geometry, shader_map, shader_parameter, render_state);
			renderer->End();
		}
	}

	return 0;
}
