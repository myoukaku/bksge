﻿/**
 *	@file	sample_render_logic_op_main.cpp
 *
 *	@brief	LogicOpのサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/bksge.hpp>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	char const* vs_source =
		"#version 400											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"#extension GL_ARB_shading_language_420pack : enable	\n"
		"														\n"
		"layout (location = 0) in vec3 aPosition;				\n"
		"														\n"
		"layout (binding = 0) uniform UniformBuffer1 {			\n"
		"	mat4 uMatrix;										\n"
		"};														\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position = uMatrix * vec4(aPosition, 1.0);		\n"
		"}														\n"
	;

	char const* fs_source =
		"#version 400											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"#extension GL_ARB_shading_language_420pack : enable	\n"
		"														\n"
		"layout (location = 0) out vec4 oColor;					\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	oColor = vec4(0.0, 0.0, 1.0, 1.0);					\n"
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
		"cbuffer ConstantBuffer									\n"
		"{														\n"
		"	row_major float4x4 uMatrix;							\n"
		"};														\n"
		"														\n"
		"float4 main(float3 aPosition : POSITION) : SV_POSITION	\n"
		"{														\n"
		"	return  mul(float4(aPosition, 1.0), uMatrix);		\n"
		"}														\n"
	;

	char const* ps_source =
		"float4 main() : SV_Target								\n"
		"{														\n"
		"	return float4(0.0, 0.0, 1.0, 1.0);					\n"
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
			new bksge::Window(extent, "sample_render_triangle - D3D11"));
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
			new bksge::Window(extent, "sample_render_triangle - D3D12"));
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
			new bksge::Window(extent, "sample_render_triangle - GL"));
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
			new bksge::Window(extent, "sample_render_triangle - Vulkan"));
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

	const bksge::Geometry geometry(bksge::PrimitiveTopology::kTriangles, vertices);

	bksge::ShaderParameterMap shader_parameter;

	bksge::RenderState render_state;

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({{0, 0}, extent});
	render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

	float	rotation = 0;

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

			{
				render_state.blend_state().SetLogicOpEnable(false);
				auto mat =
					bksge::Matrix4x4f::MakeRotationZ(-rotation) *
					bksge::Matrix4x4f::MakeTranslation({-0.2f,0.0f,0.0f});
				shader_parameter.SetParameter("uMatrix", mat);
				renderer->Render(
					geometry, *shaders[i], shader_parameter, render_state);
			}
			{
				render_state.blend_state().SetLogicOpEnable(true);
				render_state.blend_state().SetLogicOperation(bksge::LogicOperation::kInvert);
				auto mat =
					bksge::Matrix4x4f::MakeRotationZ(rotation) *
					bksge::Matrix4x4f::MakeTranslation({0.2f,0.0f,0.0f});
				shader_parameter.SetParameter("uMatrix", mat);
				renderer->Render(
					geometry, *shaders[i], shader_parameter, render_state);
			}

			renderer->EndRenderPass();
			renderer->End();

			++i;
		}

		rotation += 0.01f;
	}

	return 0;
}
