/**
 *	@file	sample_render_texture_main.cpp
 *
 *	@brief	テクスチャをレンダリングするサンプル
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

static bksge::Shader const* GetGLSLShader(void)
{
	char const* vs_source =
		"attribute vec3 aPosition;					"
		"attribute vec2 aTexCoord;					"
		"varying   vec2 vTexCoord;					"
		"											"
		"void main()								"
		"{											"
		"	gl_Position = vec4(aPosition, 1.0);		"
		"	vTexCoord   = aTexCoord;				"
		"}											"
	;

	char const* fs_source =
		"varying vec2 vTexCoord;					"
		"uniform sampler2D uSampler;				"
		"											"
		"void main()								"
		"{											"
		"	gl_FragColor = texture2D(uSampler, vTexCoord);	"
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
		"struct VS_INPUT					"
		"{									"
		"    float3 pos : POSITION;			"
		"    float2 uv : TEXCOORD;			"
		"};									"
		"									"
		"struct VS_OUTPUT					"
		"{									"
		"    float4 pos : SV_POSITION;		"
		"    float2 uv : TEXCOORD;			"
		"};									"
		"									"
		"VS_OUTPUT main(VS_INPUT input)		"
		"{									"
		"	VS_OUTPUT output;						"
		"	output.pos = float4(input.pos, 1.0);	"
		"	output.uv = input.uv;					"
		"	return output;					"
		"}									"
	;

	char const* ps_source =
		"struct PS_INPUT								"
		"{												"
		"    float4 pos : SV_POSITION;					"
		"    float2 uv : TEXCOORD;						"
		"};												"
		"												"
		"Texture2D uTexture : register(t0);				"
		"SamplerState uSampler : register(s0);			"
		"												"
		"float4 main(PS_INPUT input) : SV_TARGET		"
		"{												"
		"	return uTexture.Sample(uSampler, input.uv);	"
		"}												"
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
			new bksge::Window({800, 600}, "sample_render_texture - D3D11"));
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
			new bksge::Window({800, 600}, "sample_render_texture - D3D12"));
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
			new bksge::Window({800, 600}, "sample_render_texture - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif

	bksge::Vertex<bksge::VPosition, bksge::VTexCoord> const vertices[] =
	{
		{{{-0.5,  0.5, 0.0}}, {{0, 0}}},
		{{{-0.5, -0.5, 0.0}}, {{0, 1}}},
		{{{ 0.5,  0.5, 0.0}}, {{1, 0}}},
		{{{ 0.5, -0.5, 0.0}}, {{1, 1}}},
	};
	std::uint16_t const indices[] =
	{
		0, 1, 2,
		2, 1, 3,
	};

	bksge::Geometry const geometry(
		bksge::Primitive::kTriangles, vertices, indices);

	std::size_t const tex_width  = 16;
	std::size_t const tex_height = 16;

	std::uint8_t pixels[tex_width * tex_height * 4];
	auto* p = pixels;
	for (std::size_t y = 0; y < tex_height; ++y)
	{
		for (std::size_t x = 0; x < tex_width; ++x)
		{
			*p++ = static_cast<std::uint8_t>(x * 16);
			*p++ = static_cast<std::uint8_t>(y * 16);
			*p++ = 0;
			*p++ = 255;
		}
	}
	bksge::Texture const texture(
		bksge::TextureFormat::kRGBA_U8, {tex_width, tex_height}, pixels);
	bksge::Sampler sampler(texture);
	sampler.SetMagFilter(bksge::FilterMode::kLinear);
	sampler.SetWrapS(bksge::WrapMode::kClamp);
	sampler.SetWrapT(bksge::WrapMode::kClamp);

	std::vector<bksge::Shader const*> const shader_list
	{
		GetGLSLShader(),
		GetHLSLShader(),
	};

	bksge::ShaderParameterMap shader_parameter;
	shader_parameter.SetParameter("uSampler", sampler);
	shader_parameter.SetParameter("uTexture", texture);

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
				geometry,
				shader_list,
				shader_parameter,
				render_state);
			renderer->End();
		}
	}

	return 0;
}
