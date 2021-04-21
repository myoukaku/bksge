/**
 *	@file	sample_render_sampler_main.cpp
 *
 *	@brief	テクスチャのサンプラーを設定するサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/fnd/iterator/size.hpp>
#include <bksge/fnd/memory.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/vector.hpp>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	static char const* vs_source =
		"#version 400											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"#extension GL_ARB_shading_language_420pack : enable	\n"
		"														\n"
		"layout (location = 0) in vec3 aPosition;				\n"
		"layout (location = 1) in vec2 aTexCoord;				\n"
		"														\n"
		"layout (location = 0) out vec2 vTexCoord;				\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position = vec4(aPosition, 1.0);					\n"
		"	vTexCoord   = aTexCoord;							\n"
		"}														\n"
	;

	static char const* fs_source =
		"#version 400											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"#extension GL_ARB_shading_language_420pack : enable	\n"
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

static bksge::Shader const* GetHLSLShader(void)
{
	static char const* vs_source =
		"struct VS_INPUT								\n"
		"{												\n"
		"    float3 pos : POSITION;						\n"
		"    float2 uv : TEXCOORD;						\n"
		"};												\n"
		"												\n"
		"struct VS_OUTPUT								\n"
		"{												\n"
		"    float4 pos : SV_POSITION;					\n"
		"    float2 uv : TEXCOORD;						\n"
		"};												\n"
		"												\n"
		"VS_OUTPUT main(VS_INPUT input)					\n"
		"{												\n"
		"	VS_OUTPUT output;							\n"
		"	output.pos = float4(input.pos, 1.0);		\n"
		"	output.uv = input.uv;						\n"
		"	return output;								\n"
		"}												\n"
	;

	static char const* ps_source =
		"struct PS_INPUT								\n"
		"{												\n"
		"    float4 pos : SV_POSITION;					\n"
		"    float2 uv : TEXCOORD;						\n"
		"};												\n"
		"												\n"
		"Texture2D uTexture : register(t0);				\n"
		"SamplerState uSampler : register(s0);			\n"
		"												\n"
		"float4 main(PS_INPUT input) : SV_TARGET		\n"
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
			new bksge::Window(extent, "sample_render_sampler - D3D11"));
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
			new bksge::Window(extent, "sample_render_sampler - D3D12"));
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
			new bksge::Window(extent, "sample_render_sampler - GL"));
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
			new bksge::Window(extent, "sample_render_sampler - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetGLSLShader());
	}
#endif

	static bksge::Vertex<bksge::VPosition, bksge::VTexCoord> const vertices[] =
	{
		{{{-0.75f,  0.75f, 0.0f}}, {{0.0f - 0.2f, 0.0f - 0.2f}}},
		{{{-0.75f, -0.75f, 0.0f}}, {{0.0f - 0.2f, 1.0f + 0.2f}}},
		{{{ 0.75f,  0.75f, 0.0f}}, {{1.0f + 0.2f, 0.0f - 0.2f}}},
		{{{ 0.75f, -0.75f, 0.0f}}, {{1.0f + 0.2f, 1.0f + 0.2f}}},
	};
	static bksge::uint16_t const indices[] =
	{
		0, 1, 2,
		2, 1, 3,
	};

	bksge::Geometry const geometry(bksge::PrimitiveTopology::kTriangles, vertices, indices);

	bksge::size_t const tex_width  = 16;
	bksge::size_t const tex_height = 16;

	bksge::vector<bksge::uint8_t> pixels(tex_width * tex_height * 4);
	{
		auto* p = pixels.data();
		for (bksge::size_t y = 0; y < tex_height; ++y)
		{
			for (bksge::size_t x = 0; x < tex_width; ++x)
			{
				*p++ = static_cast<bksge::uint8_t>(x * 16);
				*p++ = static_cast<bksge::uint8_t>(y * 16);
				*p++ = 0;
				*p++ = 255;
			}
		}
	}
	bksge::Texture const tex(
		bksge::TextureFormat::kRGBA_U8, {tex_width, tex_height}, pixels.data());

	bksge::Sampler	sampler;
	sampler.SetAddressModeU(bksge::AddressMode::kBorder);

	bksge::ShaderParameterMap shader_parameter;

	bksge::RenderState render_state;

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({{0, 0}, extent});
	render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

	bksge::FilterMode const filter_mode_tbl[] =
	{
		bksge::FilterMode::kLinear,
		bksge::FilterMode::kNearest,
	};
	bksge::AddressMode const address_mode_tbl[] =
	{
		bksge::AddressMode::kRepeat,
		bksge::AddressMode::kMirror,
		bksge::AddressMode::kClamp,
		bksge::AddressMode::kBorder,
	};
	bksge::BorderColor const border_color_tbl[] =
	{
		bksge::BorderColor::kTransparentBlack,
		bksge::BorderColor::kOpaqueBlack,
		bksge::BorderColor::kOpaqueWhite,
	};

	int frame_count = 0;
	bksge::size_t filter_mode_index = 0;
	bksge::size_t address_mode_index = 0;
	bksge::size_t border_color_index = 0;

	for (;;)
	{
		for (auto& window : windows)
		{
			if (!window->Update())
			{
				return 0;
			}
		}

		frame_count++;
		if (frame_count > 60)
		{
			frame_count = 0;

			filter_mode_index++;
			if (filter_mode_index >= bksge::size(filter_mode_tbl))
			{
				filter_mode_index = 0;

				address_mode_index++;
				if (address_mode_index >= bksge::size(address_mode_tbl))
				{
					address_mode_index = 0;

					border_color_index++;
					if (border_color_index >= bksge::size(border_color_tbl))
					{
						border_color_index = 0;
					}
				}
			}
		}

		sampler.SetMagFilter(filter_mode_tbl[filter_mode_index]);
		sampler.SetMinFilter(filter_mode_tbl[filter_mode_index]);
		sampler.SetAddressModeU(address_mode_tbl[address_mode_index]);
		sampler.SetAddressModeV(address_mode_tbl[address_mode_index]);
		sampler.SetAddressModeW(address_mode_tbl[address_mode_index]);
		sampler.SetBorderColor(border_color_tbl[border_color_index]);

		shader_parameter.SetParameter("uSampler", sampler);
		shader_parameter.SetParameter("uTexture", tex);
		bksge::SampledTexture sampler2d(sampler, tex);
		shader_parameter.SetParameter("uSampler2D", sampler2d);

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
