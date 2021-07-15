/**
 *	@file	sample_render_render_to_texture_main.cpp
 *
 *	@brief	テクスチャにレンダリングするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/render.hpp>
#include <bksge/core/window.hpp>
#include <bksge/core/math.hpp>
#include <bksge/fnd/cmath.hpp>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	static char const* vs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec3 aPosition;				\n"
		"layout (location = 1) in vec2 aTexCoord;				\n"
		"														\n"
		"layout (location = 0) out vec2 vTexCoord;				\n"
		"														\n"
		"layout(set=0, binding=0) uniform SceneMatrices {		\n"
		"	mat4 uProjection;									\n"
		"	mat4 uView;											\n"
		"	mat4 uModel;										\n"
		"};														\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	vec4 pos = vec4(aPosition, 1.0);					\n"
		"	gl_Position = uProjection * uView * uModel * pos;	\n"
		"	vTexCoord   = aTexCoord;							\n"
		"}														\n"
	;

	static char const* fs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec2 vTexCoord;				\n"
		"														\n"
		"layout (location = 0) out vec4 oColor;					\n"
		"														\n"
		"layout (binding = 1) uniform sampler2D uSampler2D;		\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	oColor = texture(uSampler2D, vTexCoord);			\n"
		"}														\n"
	;

	static bksge::Shader const shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, fs_source },
	};

	return &shader;
}

#if 0
static bksge::Shader const* GetHLSLShader(void)
{
	static char const* vs_source =
		"struct VS_INPUT								\n"
		"{												\n"
		"	float3 pos : POSITION;						\n"
		"	float2 uv : TEXCOORD;						\n"
		"};												\n"
 		"												\n"
		"struct VS_OUTPUT								\n"
		"{												\n"
		"	float4 pos : SV_POSITION;					\n"
		"	float2 uv : TEXCOORD;						\n"
		"};												\n"
		"												\n"
		"cbuffer SceneMatrices							\n"
		"{												\n"
		"	row_major float4x4 uProjection;				\n"
		"	row_major float4x4 uView;					\n"
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
		"	output.pos = pos;							\n"
		"	output.uv = input.uv;						\n"
		"	return output;								\n"
		"}												\n"
	;

	static char const* ps_source =
		"struct PS_INPUT								\n"
		"{												\n"
		"	float4 pos : SV_POSITION;					\n"
		"	float2 uv : TEXCOORD;						\n"
		"};												\n"
		"												\n"
		"Texture2D uTexture : register(t0);				\n"
		"SamplerState uSampler : register(s0);			\n"
		"												\n"
		"float4 main(PS_INPUT input) : SV_Target		\n"
		"{												\n"
		"	return uTexture.Sample(uSampler, input.uv);	\n"
		"}												\n"
	;

	static bksge::Shader const shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, ps_source },
	};

	return &shader;
}
#endif

}	// namespace

int main()
{
	bksge::Extent2f const extent{800, 600};
	bksge::vector<bksge::shared_ptr<bksge::Renderer>>	renderers;
	bksge::vector<bksge::shared_ptr<bksge::Window>>		windows;
	bksge::vector<bksge::Shader const*>					shaders;

#if 0//BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_to_texture - D3D11"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::D3D11Renderer> renderer(
			new bksge::D3D11Renderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetHLSLShader());
	}
#endif
#if 0//BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_to_texture - D3D12"));
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
			new bksge::Window(extent, "sample_render_to_texture - GL"));
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
			new bksge::Window(extent, "sample_render_to_texture - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetGLSLShader());
	}
#endif

	const bksge::Vertex<bksge::VPosition, bksge::VTexCoord> vertices[] =
	{
		{{{ 1.0f,  1.0f,  1.0f}}, {{ 0, 0 }}},
		{{{ 1.0f,  1.0f, -1.0f}}, {{ 0, 1 }}},
		{{{ 1.0f, -1.0f,  1.0f}}, {{ 1, 0 }}},
		{{{ 1.0f, -1.0f, -1.0f}}, {{ 1, 1 }}},

		{{{-1.0f,  1.0f,  1.0f}}, {{ 0, 0 }}},
		{{{-1.0f, -1.0f,  1.0f}}, {{ 0, 1 }}},
		{{{-1.0f,  1.0f, -1.0f}}, {{ 1, 0 }}},
		{{{-1.0f, -1.0f, -1.0f}}, {{ 1, 1 }}},

		{{{-1.0f,  1.0f,  1.0f}}, {{ 0, 0 }}},
		{{{ 1.0f,  1.0f,  1.0f}}, {{ 0, 1 }}},
		{{{-1.0f, -1.0f,  1.0f}}, {{ 1, 0 }}},
		{{{ 1.0f, -1.0f,  1.0f}}, {{ 1, 1 }}},

		{{{-1.0f,  1.0f, -1.0f}}, {{ 0, 0 }}},
		{{{-1.0f, -1.0f, -1.0f}}, {{ 0, 1 }}},
		{{{ 1.0f,  1.0f, -1.0f}}, {{ 1, 0 }}},
		{{{ 1.0f, -1.0f, -1.0f}}, {{ 1, 1 }}},

		{{{-1.0f,  1.0f, -1.0f}}, {{ 0, 0 }}},
		{{{ 1.0f,  1.0f, -1.0f}}, {{ 0, 1 }}},
		{{{-1.0f,  1.0f,  1.0f}}, {{ 1, 0 }}},
		{{{ 1.0f,  1.0f,  1.0f}}, {{ 1, 1 }}},

		{{{-1.0f, -1.0f, -1.0f}}, {{ 0, 0 }}},
		{{{-1.0f, -1.0f,  1.0f}}, {{ 0, 1 }}},
		{{{ 1.0f, -1.0f, -1.0f}}, {{ 1, 0 }}},
		{{{ 1.0f, -1.0f,  1.0f}}, {{ 1, 1 }}},

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

	std::size_t const tex_width  = 16;
	std::size_t const tex_height = 16;

	bksge::vector<bksge::uint8_t> pixels(tex_width * tex_height * 4);
	{
		auto* p = pixels.data();
		for (std::size_t y = 0; y < tex_height; ++y)
		{
			for (std::size_t x = 0; x < tex_width; ++x)
			{
				*p++ = static_cast<bksge::uint8_t>(x * 16);
				*p++ = static_cast<bksge::uint8_t>(y * 16);
				*p++ = 0;
				*p++ = 255;
			}
		}
	}
	bksge::Texture texture(
		bksge::TextureFormat::kRGBA_U8_NORM,
		{tex_width, tex_height},
		pixels.data());

	bksge::Sampler sampler;
	sampler.SetMagFilter(bksge::FilterMode::kLinear);
	sampler.SetAddressModeU(bksge::AddressMode::kClamp);
	sampler.SetAddressModeV(bksge::AddressMode::kClamp);

	bksge::Extent2f const offscreen_extent{256, 256};

	bksge::RenderTexture render_texture(
		bksge::TextureFormat::kRGBA_U8_NORM,
		offscreen_extent);

	bksge::RenderTexture depth_stencil_buffer(
		bksge::TextureFormat::kDepth24_Stencil8,
		offscreen_extent);

	bksge::FrameBuffer frame_buffer(render_texture, depth_stencil_buffer);

	bksge::RenderState render_state;
	render_state.depth_state().SetEnable(true);
	render_state.depth_state().SetWrite(true);

	bksge::RenderPassInfo offscreen_render_pass_info;
	offscreen_render_pass_info.SetFrameBuffer(&frame_buffer);
	offscreen_render_pass_info.viewport().SetRect({{0, 0}, offscreen_extent});
	offscreen_render_pass_info.clear_state().SetColor({0.0f, 0.0f, 0.5f, 1.0f});

	bksge::RenderPassInfo main_render_pass_info;
	main_render_pass_info.viewport().SetRect({{0, 0}, extent});
	main_render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

	bksge::ShaderParameterMap offscreen_shader_parameter;
	offscreen_shader_parameter.SetParameter("uSampler", sampler);
	offscreen_shader_parameter.SetParameter("uTexture", texture);
	offscreen_shader_parameter.SetParameter("uSampler2D", bksge::make_pair(sampler, texture));

	bksge::ShaderParameterMap main_shader_parameter;
	main_shader_parameter.SetParameter("uSampler", sampler);
	main_shader_parameter.SetParameter("uTexture", render_texture);
	main_shader_parameter.SetParameter("uSampler2D", bksge::make_pair(sampler, render_texture));

	float	rotation_x = 0.0f;
	float	rotation_y = 0.0f;

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

		auto const projection =
			bksge::Matrix4x4f::MakePerspective(
				bksge::degrees_to_radians(45.0f),
				extent.width() / extent.height(),
				0.1f,
				100.0f);

		auto const view =
			bksge::Matrix4x4f::MakeLookAt(
				{0, 2, 5},
				{0, 0, 0},
				{0, 1, 0});

		auto const model =
			bksge::Matrix4x4f::MakeRotationX(rotation_x) *
			bksge::Matrix4x4f::MakeRotationY(rotation_y);

		offscreen_shader_parameter.SetParameter("uProjection", projection);
		offscreen_shader_parameter.SetParameter("uView", view);
		offscreen_shader_parameter.SetParameter("uModel", model);
		main_shader_parameter.SetParameter("uProjection", projection);
		main_shader_parameter.SetParameter("uView", view);
		main_shader_parameter.SetParameter("uModel", model);

		int i = 0;
		for (auto& renderer : renderers)
		{
			renderer->Begin();
			{
				renderer->BeginRenderPass(offscreen_render_pass_info);
				renderer->Render(
					geometry, *shaders[i], offscreen_shader_parameter, render_state);
				renderer->EndRenderPass();
			}
			{
				renderer->BeginRenderPass(main_render_pass_info);
				renderer->Render(
					geometry, *shaders[i], main_shader_parameter, render_state);
				renderer->EndRenderPass();
			}
			renderer->End();

			++i;
		}
	}

	return 0;
}
