﻿/**
 *	@file	sample_render_color_write_mask_main.cpp
 *
 *	@brief	ColorWriteMask を設定するサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/fnd/iterator/size.hpp>
#include <bksge/fnd/memory.hpp>
#include <bksge/fnd/vector.hpp>
#include <utility>

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
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, fs_source },
	};

	return &shader;
}

static bksge::Shader const* GetHLSLShader(void)
{
	char const* vs_source =
		"struct VS_INPUT								\n"
		"{												\n"
		"	float3 pos   : POSITION;					\n"
		"	float4 color : COLOR;						\n"
		"};												\n"
 		"												\n"
		"struct VS_OUTPUT								\n"
		"{												\n"
		"	float4 pos   : SV_POSITION;					\n"
		"	float4 color : COLOR;						\n"
		"};												\n"
		"												\n"
		"VS_OUTPUT main(VS_INPUT input)					\n"
		"{												\n"
		"	VS_OUTPUT output;							\n"
		"	output.pos   = float4(input.pos, 1.0);		\n"
		"	output.color = input.color;					\n"
		"	return output;								\n"
		"}												\n"
	;

	char const* ps_source =
		"struct PS_INPUT								\n"
		"{												\n"
		"	float4 pos   : SV_POSITION;					\n"
		"	float4 color : COLOR;						\n"
		"};												\n"
		"												\n"
		"float4 main(PS_INPUT input) : SV_Target		\n"
		"{												\n"
		"	return input.color;							\n"
		"}												\n"
	;

	static bksge::Shader const shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, ps_source },
	};

	return &shader;
}

}	// namespace

int main()
{
	bksge::Extent2f const extent{800, 600};
	bksge::vector<bksge::shared_ptr<bksge::Renderer>>	renderers;
	bksge::vector<bksge::shared_ptr<bksge::Window>>		windows;
	bksge::vector<bksge::Shader const*>					shaders;

#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_color_write_mask - D3D11"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::D3D11Renderer> renderer(
			new bksge::D3D11Renderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetHLSLShader());
	}
#endif
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_color_write_mask - D3D12"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::D3D12Renderer> renderer(
			new bksge::D3D12Renderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetHLSLShader());
	}
#endif
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_color_write_mask - GL"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetGLSLShader());
	}
#endif
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_color_write_mask - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetGLSLShader());
	}
#endif

	const bksge::Vertex<bksge::VPosition, bksge::VColor> vertices[] =
	{
		{{{ 0.0,  0.5, 0.0}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
		{{{-0.5, -0.5, 0.0}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
		{{{ 0.5, -0.5, 0.0}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
	};

	const bksge::Geometry geometry(bksge::PrimitiveTopology::kTriangles, vertices);

	bksge::ShaderParameterMap shader_parameter;

	bksge::RenderState render_state;

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({{0, 0}, extent});
	render_pass_info.clear_state().SetColor({0.0f, 0.0f, 0.0f, 0.0f});

	int count = 0;

	for (;;)
	{
		for (auto& window : windows)
		{
			if (!window->Update())
			{
				return 0;
			}
		}

		{
			static bksge::ColorWriteFlag const tbl[] =
			{
				bksge::ColorWriteFlag::kNone,
				bksge::ColorWriteFlag::kRed,
				bksge::ColorWriteFlag::kGreen,
				bksge::ColorWriteFlag::kBlue,
				bksge::ColorWriteFlag::kRed   | bksge::ColorWriteFlag::kGreen,
				bksge::ColorWriteFlag::kGreen | bksge::ColorWriteFlag::kBlue,
				bksge::ColorWriteFlag::kRed   | bksge::ColorWriteFlag::kBlue,
				bksge::ColorWriteFlag::kAll,
			};

			auto& blend_state = render_state.blend_state();
			blend_state.SetColorWriteFlag(
				tbl[(count / 60) % bksge::size(tbl)]);

			count++;
		}

		int i = 0;
		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass_info);
			renderer->Render(
				geometry, *shaders[i], shader_parameter, render_state);
			renderer->EndRenderPass();
			renderer->End();

			++i;
		}
	}

	return 0;
}
