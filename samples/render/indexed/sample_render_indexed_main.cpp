/**
 *	@file	sample_render_indexed_main.cpp
 *
 *	@brief	インデックスバッファーを使ってレンダリングするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <vector>
#include <bksge/fnd/memory.hpp>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	char const* vs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec3 aPosition;				\n"
		"layout (location = 1) in vec4 aColor;					\n"
		"														\n"
		"layout (location = 0) out vec4 vColor;					\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position = vec4(aPosition, 1.0);					\n"
		"	vColor = aColor;									\n"
		"}														\n"
	;

	char const* fs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec4 vColor;					\n"
		"														\n"
		"layout (location = 0) out vec4 oColor;					\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	oColor = vColor;									\n"
		"}														\n"
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
	bksge::Extent2f const extent{800, 600};
	std::vector<bksge::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<bksge::shared_ptr<bksge::Window>>		windows;

#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_indexed - D3D11"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::D3D11Renderer> renderer(
			new bksge::D3D11Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_indexed - D3D12"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::D3D12Renderer> renderer(
			new bksge::D3D12Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_indexed - GL"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_indexed - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);
	}
#endif

	const bksge::Vertex<bksge::VPosition, bksge::VColor> vertices[] =
	{
		{{{ -0.5f,  0.5f, 0.0f }}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
		{{{  0.5f,  0.5f, 0.0f }}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
		{{{ -0.5f, -0.5f, 0.0f }}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
		{{{  0.5f, -0.5f, 0.0f }}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},
	};

	const bksge::uint16_t indices[] =
	{
		0, 2, 1,
		1, 2, 3,
	};

	const bksge::Geometry geometry(
		bksge::PrimitiveTopology::kTriangles, vertices, indices);

	std::vector<bksge::Shader const*> const shader_list
	{
		GetGLSLShader(),
		GetHLSLShader(),
	};

	bksge::ShaderParameterMap shader_parameter;

	bksge::RenderState render_state;

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({bksge::Vector2f{0, 0}, extent});
	render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

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
			renderer->BeginRenderPass(render_pass_info);
			renderer->Render(
				geometry, shader_list, shader_parameter, render_state);
			renderer->EndRenderPass();
			renderer->End();
		}
	}

	return 0;
}
