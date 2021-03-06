﻿/**
 *	@file	sample_render_constant_buffer_main.cpp
 *
 *	@brief	ConstantBufferに値を設定するサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/math.hpp>
#include <bksge/fnd/cmath.hpp>
#include <bksge/fnd/memory.hpp>
#include <bksge/fnd/vector.hpp>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	char const* vs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec3 aPosition;				\n"
		"														\n"
		"layout(set=0, binding=0) uniform UniformBuffer1 {		\n"
		"	vec3 uOffset;										\n"
		"};														\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position = vec4(aPosition + uOffset, 1.0);		\n"
		"}														\n"
	;

	char const* fs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) out vec4 oColor;					\n"
		"														\n"
		"layout(set=0, binding=1) uniform UniformBuffer2 {		\n"
		"	float uRed;											\n"
		"	float uGreen;										\n"
		"	float uBlue;										\n"
		"};														\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	oColor = vec4(uRed, uGreen, uBlue, 1.0);			\n"
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
		"cbuffer ConstantBuffer1								\n"
		"{														\n"
		"	float4 uDummyVariable;								\n"
		"	float3 uOffset;										\n"
		"};														\n"
		"														\n"
		"float4 main(float3 aPosition : POSITION) : SV_POSITION	\n"
		"{														\n"
		"	return float4(aPosition + uOffset, 1.0);			\n"
		"}														\n"
	;

	char const* ps_source =
		"cbuffer ConstantBuffer2								\n"
		"{														\n"
		"	float uRed;											\n"
		"	float uGreen;										\n"
		"};														\n"
		"cbuffer ConstantBuffer3								\n"
		"{														\n"
		"	float uBlue;										\n"
		"};														\n"
		"														\n"
		"float4 main() : SV_Target								\n"
		"{														\n"
		"	return float4(uRed, uGreen, uBlue, 1.0);			\n"
		"}														\n"
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
			new bksge::Window(extent, "sample_render_constant_buffer - D3D11"));
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
			new bksge::Window(extent, "sample_render_constant_buffer - D3D12"));
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
			new bksge::Window(extent, "sample_render_constant_buffer - GL"));
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
			new bksge::Window(extent, "sample_render_constant_buffer - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetGLSLShader());
	}
#endif

	const bksge::Vertex<bksge::VPosition> vertices[] =
	{
		{{{ 0.0,  0.5, 0.0}}},
		{{{-0.5, -0.5, 0.0}}},
		{{{ 0.5, -0.5, 0.0}}},
	};

	const bksge::Geometry geometry(
		bksge::PrimitiveTopology::kTriangles, vertices);

	bksge::ShaderParameterMap shader_parameter;
	shader_parameter.SetParameter("uGreen", 0.5f);

	bksge::RenderState render_state;

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({{0, 0}, extent});
	render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

	float r = 0.0f;
	float b = 0.0f;
	float t = 0.0f;
	bksge::Vector3f position_offset;

	for (;;)
	{
		for (auto& window : windows)
		{
			if (!window->Update())
			{
				return 0;
			}
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

		shader_parameter.SetParameter("uBlue", b);
		shader_parameter.SetParameter("uRed", r);
		shader_parameter.SetParameter("uOffset", position_offset);

		r += 0.01f;
		if (r > 1.0f)
		{
			r = 0.0f;
		}
		b += 0.005f;
		if (b > 1.0f)
		{
			b = 0.0f;
		}
		t += 0.01f;
		position_offset.x() = bksge::sin(t);
	}

	return 0;
}
