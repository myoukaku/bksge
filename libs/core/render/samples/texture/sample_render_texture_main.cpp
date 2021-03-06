﻿/**
 *	@file	sample_render_texture_main.cpp
 *
 *	@brief	テクスチャをレンダリングするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/render.hpp>
#include <bksge/core/window.hpp>
#include <bksge/core/math.hpp>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	static char const* vs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"#extension GL_KHR_vulkan_glsl : enable					\n"
		"														\n"
		"layout (location = 0) in vec3 aPosition;				\n"
		"layout (location = 1) in vec2 aTexCoord;				\n"
		"														\n"
		"layout (location = 0) out vec2 vTexCoord;				\n"
		"														\n"
		"layout (binding = 0) uniform UniformBuffer1 {			\n"
		"	mat4 uMatrix;										\n"
		"};														\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position = uMatrix * vec4(aPosition, 1.0);		\n"
		"	vTexCoord   = aTexCoord;							\n"
		"}														\n"
	;

	static char const* fs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"#extension GL_KHR_vulkan_glsl : enable					\n"
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
		"struct VS_INPUT										\n"
		"{														\n"
		"    float3 pos : POSITION;								\n"
		"    float2 uv : TEXCOORD;								\n"
		"};														\n"
		"														\n"
		"struct VS_OUTPUT										\n"
		"{														\n"
		"    float4 pos : SV_POSITION;							\n"
		"    float2 uv : TEXCOORD;								\n"
		"};														\n"
		"														\n"
		"cbuffer ConstantBuffer									\n"
		"{														\n"
		"	row_major float4x4 uMatrix;							\n"
		"};														\n"
		"														\n"
		"VS_OUTPUT main(VS_INPUT input)							\n"
		"{														\n"
		"	VS_OUTPUT output;									\n"
		"	output.pos = mul(float4(input.pos, 1.0), uMatrix);	\n"
		"	output.uv = input.uv;								\n"
		"	return output;										\n"
		"}														\n"
	;

	static char const* ps_source =
		"struct PS_INPUT										\n"
		"{														\n"
		"    float4 pos : SV_POSITION;							\n"
		"    float2 uv : TEXCOORD;								\n"
		"};														\n"
		"														\n"
		"Texture2D uTexture : register(t0);						\n"
		"SamplerState uSampler : register(s0);					\n"
		"														\n"
		"float4 main(PS_INPUT input) : SV_TARGET				\n"
		"{														\n"
		"	return uTexture.Sample(uSampler, input.uv);			\n"
		"}														\n"
	;

	static bksge::Shader const shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, ps_source },
	};

	return &shader;
}

class Sprite
{
private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition, bksge::VTexCoord> const vertices[] =
		{
			{{{-0.5,  0.5, 0.0}}, {{0, 0}}},
			{{{-0.5, -0.5, 0.0}}, {{0, 1}}},
			{{{ 0.5,  0.5, 0.0}}, {{1, 0}}},
			{{{ 0.5, -0.5, 0.0}}, {{1, 1}}},
		};
		static bksge::uint16_t const indices[] =
		{
			0, 1, 2,
			2, 1, 3,
		};

		static bksge::Geometry const geometry(
			bksge::PrimitiveTopology::kTriangles, vertices, indices);

		return geometry;
	}

public:
	Sprite(bksge::Texture const& texture, float x, float y)
		: m_texture(texture)
		, m_position(x, y, 0.0f)
		, m_scale(0.5f, 0.5f, 1.0f)
		, m_rotation(0)
	{
		m_sampler.SetMagFilter(bksge::FilterMode::kLinear);
		m_sampler.SetAddressModeU(bksge::AddressMode::kClamp);
		m_sampler.SetAddressModeV(bksge::AddressMode::kClamp);
	}

	void Update(void)
	{
		m_rotation += 0.01f;
	}

	void Draw(bksge::Renderer* renderer, bksge::Shader const* shader)
	{
		m_shader_parameter.SetParameter("uSampler", m_sampler);
		m_shader_parameter.SetParameter("uTexture", m_texture);
		m_shader_parameter.SetParameter("uSampler2D", bksge::make_pair(m_sampler, m_texture));
		bksge::Matrix4x4f mat =
			bksge::Matrix4x4f::MakeScale(m_scale) *
			bksge::Matrix4x4f::MakeRotationZ(m_rotation) *
			bksge::Matrix4x4f::MakeTranslation(m_position);
		m_shader_parameter.SetParameter("uMatrix", mat);

		renderer->Render(
			GetGeometry(),
			*shader,
			m_shader_parameter,
			m_render_state);
	}

	bksge::Sampler& sampler(void) { return m_sampler; }

	void SetTexture(bksge::Texture const& texture)
	{
		m_texture = texture;
	}

private:
	bksge::ShaderParameterMap	m_shader_parameter;
	bksge::RenderState			m_render_state;
	bksge::Sampler				m_sampler;
	bksge::Texture				m_texture;
	bksge::Vector3f				m_position;
	bksge::Scale3f				m_scale;
	float						m_rotation;
};

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
			new bksge::Window(extent, "sample_render_texture - D3D11"));
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
			new bksge::Window(extent, "sample_render_texture - D3D12"));
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
			new bksge::Window(extent, "sample_render_texture - GL"));
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
			new bksge::Window(extent, "sample_render_texture - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetGLSLShader());
	}
#endif

	bksge::size_t const tex0_width  = 16;
	bksge::size_t const tex0_height = 16;

	bksge::vector<bksge::uint8_t> pixels0(tex0_width * tex0_height * 4);
	{
		auto* p = pixels0.data();
		for (bksge::size_t y = 0; y < tex0_height; ++y)
		{
			for (bksge::size_t x = 0; x < tex0_width; ++x)
			{
				*p++ = static_cast<bksge::uint8_t>(x * 16);
				*p++ = static_cast<bksge::uint8_t>(y * 16);
				*p++ = 0;
				*p++ = 255;
			}
		}
	}
	bksge::Texture const tex0(
		bksge::TextureFormat::kRGBA_U8_NORM, {tex0_width, tex0_height}, pixels0.data());

	bksge::size_t const tex1_width  = 8;
	bksge::size_t const tex1_height = 8;

	bksge::vector<bksge::uint8_t> pixels1(tex1_width * tex1_height * 4);
	{
		auto* p = pixels1.data();
		for (bksge::size_t y = 0; y < tex1_height; ++y)
		{
			for (bksge::size_t x = 0; x < tex1_width; ++x)
			{
				*p++ = static_cast<bksge::uint8_t>(x * 16);
				*p++ = static_cast<bksge::uint8_t>(x * 16);
				*p++ = static_cast<bksge::uint8_t>(x * 16);
				*p++ = 255;
			}
		}
	}
	bksge::Texture const tex1(
		bksge::TextureFormat::kRGBA_U8_NORM, {tex1_width, tex1_height}, pixels1.data());

	bksge::vector<bksge::shared_ptr<Sprite>>	sprites;

	{
		auto sprite = bksge::make_shared<Sprite>(tex0, -0.5f,  0.5f);
		sprites.push_back(sprite);
	}
	{
		auto sprite = bksge::make_shared<Sprite>(tex0,  0.5f,  0.5f);
		sprites.push_back(sprite);
	}
	{
		auto sprite = bksge::make_shared<Sprite>(tex0, -0.5f, -0.5f);
		sprite->sampler().SetMagFilter(bksge::FilterMode::kNearest);
		sprites.push_back(sprite);
	}
	{
		auto sprite = bksge::make_shared<Sprite>(tex0,  0.5f, -0.5f);
		sprite->sampler().SetMagFilter(bksge::FilterMode::kNearest);
		sprites.push_back(sprite);
	}

	int count = 0;

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({{0, 0}, extent});
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

		if (((count / 60) % 2) == 0)
		{
			sprites[0]->SetTexture(tex0);
			sprites[2]->SetTexture(tex0);
		}
		else
		{
			sprites[0]->SetTexture(tex1);
			sprites[2]->SetTexture(tex1);
		}

		for (auto&& sprite : sprites)
		{
			sprite->Update();
		}

		int i = 0;
		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass_info);

			for (auto&& sprite : sprites)
			{
				sprite->Draw(renderer.get(), shaders[i]);
			}

			renderer->EndRenderPass();
			renderer->End();

			++i;
		}

		++count;
	}

	return 0;
}
