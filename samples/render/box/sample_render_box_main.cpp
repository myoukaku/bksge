/**
 *	@file	sample_render_box_main.cpp
 *
 *	@brief	立方体をレンダリングするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/math.hpp>
#include <bksge/fnd/cmath.hpp>
#include <bksge/fnd/memory.hpp>
#include <vector>
#include <utility>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	static char const* vs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec3 aPosition;				\n"
		"layout (location = 1) in vec4 aColor;					\n"
		"														\n"
		"layout (location = 0) out vec4 vColor;					\n"
		"														\n"
		"layout(set=0, binding=0) uniform SceneMatrices {		\n"
		"	mat4 uProjection;									\n"
		"	mat4 uView;											\n"
		"};														\n"
		"layout(set=0, binding=1) uniform ModelMatrices {		\n"
		"	mat4 uModel;										\n"
		"};														\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	vec4 pos = vec4(aPosition, 1.0);					\n"
		"	gl_Position = uProjection * uView * uModel * pos;	\n"
		"	vColor = aColor;									\n"
		"}														\n"
	;

	static char const* fs_source =
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
	static char const* vs_source =
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
		"cbuffer SceneMatrices							\n"
		"{												\n"
		"	row_major float4x4 uProjection;				\n"
		"	row_major float4x4 uView;					\n"
		"};												\n"
		"cbuffer ModelMatrices							\n"
		"{												\n"
		"	row_major float4x4 uModel;					\n"
		"};												\n"
		"												\n"
		"VS_OUTPUT main(VS_INPUT input)					\n"
		"{												\n"
		"	float4 pos = float4(input.pos, 1.0);		\n"
		"	pos = mul(pos, uModel);						\n"
		"	pos = mul(pos, uView);						\n"
		"	pos = mul(pos, uProjection);				\n"
		"												\n"
		"	VS_OUTPUT output;							\n"
		"	output.pos   = pos;							\n"
		"	output.color = input.color;					\n"
		"	return output;								\n"
		"}												\n"
	;

	static char const* ps_source =
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
	std::vector<std::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<std::shared_ptr<bksge::Window>>		windows;

#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_box - D3D11"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D11Renderer> renderer(
			new bksge::D3D11Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_box - D3D12"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D12Renderer> renderer(
			new bksge::D3D12Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_box - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_box - Vulkan"));
		windows.push_back(window);

		std::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);
	}
#endif

	const bksge::Vertex<bksge::VPosition, bksge::VColor> vertices[] =
	{
		{{{ 1.0f,  1.0f,  1.0f}}, {{ 1.0f, 0.0f, 1.0f, 1.0f }}},
		{{{ 1.0f,  1.0f, -1.0f}}, {{ 1.0f, 0.0f, 1.0f, 1.0f }}},
		{{{ 1.0f, -1.0f,  1.0f}}, {{ 1.0f, 0.0f, 1.0f, 1.0f }}},
		{{{ 1.0f, -1.0f, -1.0f}}, {{ 1.0f, 0.0f, 1.0f, 1.0f }}},

		{{{-1.0f,  1.0f,  1.0f}}, {{ 0.0f, 1.0f, 1.0f, 1.0f }}},
		{{{-1.0f, -1.0f,  1.0f}}, {{ 0.0f, 1.0f, 1.0f, 1.0f }}},
		{{{-1.0f,  1.0f, -1.0f}}, {{ 0.0f, 1.0f, 1.0f, 1.0f }}},
		{{{-1.0f, -1.0f, -1.0f}}, {{ 0.0f, 1.0f, 1.0f, 1.0f }}},

		{{{-1.0f,  1.0f,  1.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
		{{{ 1.0f,  1.0f,  1.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
		{{{-1.0f, -1.0f,  1.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
		{{{ 1.0f, -1.0f,  1.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},

		{{{-1.0f,  1.0f, -1.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
		{{{-1.0f, -1.0f, -1.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
		{{{ 1.0f,  1.0f, -1.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
		{{{ 1.0f, -1.0f, -1.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},

		{{{-1.0f,  1.0f, -1.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
		{{{ 1.0f,  1.0f, -1.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
		{{{-1.0f,  1.0f,  1.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
		{{{ 1.0f,  1.0f,  1.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},

		{{{-1.0f, -1.0f, -1.0f}}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},
		{{{-1.0f, -1.0f,  1.0f}}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},
		{{{ 1.0f, -1.0f, -1.0f}}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},
		{{{ 1.0f, -1.0f,  1.0f}}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},

	};

	const bksge::uint16_t indices[] =
	{
		0+0, 0+2, 0+1,
		0+1, 0+2, 0+3,

		4+0, 4+2, 4+1,
		4+1, 4+2, 4+3,

		8+0, 8+2, 8+1,
		8+1, 8+2, 8+3,

		12+0, 12+2, 12+1,
		12+1, 12+2, 12+3,

		16+0, 16+2, 16+1,
		16+1, 16+2, 16+3,

		20+0, 20+2, 20+1,
		20+1, 20+2, 20+3,
	};

	const bksge::Geometry geometry(bksge::PrimitiveTopology::kTriangles, vertices, indices);

	std::vector<bksge::Shader const*> const shader_list
	{
		GetGLSLShader(),
		GetHLSLShader(),
	};

	bksge::ShaderParameterMap shader_parameter;

	bksge::RenderState render_state;
	//render_state.rasterizer_state().SetCullMode(bksge::CullMode::kBack);
	render_state.depth_state().SetWrite(true);

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({bksge::Vector2f{0, 0}, extent});
	render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

	float	rotation_x = 0.0f;
	float	rotation_y = 0.0f;
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

		rotation_x += 0.01f;
		rotation_y += 0.02f;

		render_state.depth_state().SetEnable(((count / 120) % 2) == 0);
		count++;

		auto const projection =
			bksge::Matrix4x4f::MakePerspective(
				bksge::degrees_to_radians(45.0f),
				800.0f / 600.0f,
				0.1f,
				100.0f);

		auto const view =
			bksge::Matrix4x4f::MakeLookAt(
				bksge::Vector3f(0, 2, 5),
				bksge::Vector3f(0, 0, 0),
				bksge::Vector3f(0, 1, 0));

		auto const model =
			bksge::Matrix4x4f::MakeRotationX(rotation_x) *
			bksge::Matrix4x4f::MakeRotationY(rotation_y);

#if 0
		shader_parameter.SetParameter("uProjection", projection);
		shader_parameter.SetParameter("uView", view);
		shader_parameter.SetParameter("uModel", model);
#else
		struct SceneMatrices
		{
			bksge::Matrix4x4f	projection;
			bksge::Matrix4x4f	view;
		} scene_matrices;
		struct ModelMatrices
		{
			bksge::Matrix4x4f	model;
		} model_matrices;
		scene_matrices.projection = projection;
		scene_matrices.view = view;
		model_matrices.model = model;
		shader_parameter.SetParameter("SceneMatrices", scene_matrices);
		shader_parameter.SetParameter("ModelMatrices", model_matrices);
#endif

		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass_info);
			renderer->Render(
				geometry,
				shader_list,
				shader_parameter,
				render_state);
			renderer->EndRenderPass();
			renderer->End();
		}
	}

	return 0;
}
