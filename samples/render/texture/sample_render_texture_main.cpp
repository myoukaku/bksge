/**
 *	@file	sample_render_texture_main.cpp
 *
 *	@brief	テクスチャをレンダリングするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/math.hpp>
#include <vector>
#include <memory>
#include <utility>

namespace
{

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
		static std::uint16_t const indices[] =
		{
			0, 1, 2,
			2, 1, 3,
		};

		static bksge::Geometry const geometry(
			bksge::Primitive::kTriangles, vertices, indices);

		return geometry;
	}

	static bksge::Shader const* GetGLSLShader(void)
	{
		static char const* vs_source =
			"attribute vec3 aPosition;					"
			"attribute vec2 aTexCoord;					"
			"varying   vec2 vTexCoord;					"
			"											"
			"uniform mat4 uMatrix;						"
			"											"
			"void main()								"
			"{											"
			"	gl_Position = uMatrix * vec4(aPosition, 1.0);	"
			"	vTexCoord   = aTexCoord;				"
			"}											"
		;

		static char const* fs_source =
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
		static char const* vs_source =
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
			"cbuffer ConstantBuffer				"
			"{									"
			"	row_major float4x4 uMatrix;		"
			"};									"
			"									"
			"VS_OUTPUT main(VS_INPUT input)		"
			"{									"
			"	VS_OUTPUT output;						"
			"	output.pos = mul(float4(input.pos, 1.0), uMatrix);	"
			"	output.uv = input.uv;					"
			"	return output;					"
			"}									"
		;

		static char const* ps_source =
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

	static std::vector<bksge::Shader const*> const& GetShaderList(void)
	{
		static std::vector<bksge::Shader const*> const shader_list
		{
			GetGLSLShader(),
			GetHLSLShader(),
		};

		return shader_list;
	}

public:
	Sprite(bksge::Texture const& texture, float x, float y)
		: m_sampler(texture)
		, m_position(x, y, 0.0f)
		, m_scale(0.5f, 0.5f, 1.0f)
		, m_rotation(0)
	{
		m_sampler.SetMagFilter(bksge::FilterMode::kLinear);
		m_sampler.SetWrapS(bksge::WrapMode::kClamp);
		m_sampler.SetWrapT(bksge::WrapMode::kClamp);
	}

	void Update(void)
	{
		m_rotation += 0.01f;
	}

	void Draw(bksge::Renderer* renderer)
	{
		m_shader_parameter.SetParameter("uSampler", m_sampler);
		m_shader_parameter.SetParameter("uTexture", m_sampler.source());
		bksge::Matrix4x4f mat =
			bksge::Matrix4x4f::MakeScale(m_scale) *
			bksge::Matrix4x4f::MakeRotationZ(m_rotation) *
			bksge::Matrix4x4f::MakeTranslation(m_position);
		m_shader_parameter.SetParameter("uMatrix", mat);

		renderer->Render(
			GetGeometry(),
			GetShaderList(),
			m_shader_parameter,
			m_render_state);
	}

	bksge::Sampler& sampler(void) { return m_sampler; }

private:
	bksge::ShaderParameterMap	m_shader_parameter;
	bksge::RenderState			m_render_state;
	bksge::Sampler				m_sampler;
	bksge::Vector3f				m_position;
	bksge::Scale3f				m_scale;
	float						m_rotation;
};

}	// namespace

int main()
{
	std::vector<std::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<std::shared_ptr<bksge::Window>>		windows;

#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_texture - D3D11"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D11Renderer> renderer(
			new bksge::D3D11Renderer(*window));
		renderers.push_back(renderer);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_texture - D3D12"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D12Renderer> renderer(
			new bksge::D3D12Renderer(*window));
		renderers.push_back(renderer);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_texture - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer(*window));
		renderers.push_back(renderer);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif

	std::size_t const tex0_width  = 16;
	std::size_t const tex0_height = 16;

	std::uint8_t pixels0[tex0_width * tex0_height * 4];
	{
		auto* p = pixels0;
		for (std::size_t y = 0; y < tex0_height; ++y)
		{
			for (std::size_t x = 0; x < tex0_width; ++x)
			{
				*p++ = static_cast<std::uint8_t>(x * 16);
				*p++ = static_cast<std::uint8_t>(y * 16);
				*p++ = 0;
				*p++ = 255;
			}
		}
	}
	bksge::Texture const tex0(
		bksge::TextureFormat::kRGBA_U8, {tex0_width, tex0_height}, pixels0);

	std::size_t const tex1_width  = 8;
	std::size_t const tex1_height = 8;

	std::uint8_t pixels1[tex1_width * tex1_height * 4];
	{
		auto* p = pixels1;
		for (std::size_t y = 0; y < tex1_height; ++y)
		{
			for (std::size_t x = 0; x < tex1_width; ++x)
			{
				*p++ = static_cast<std::uint8_t>(x * 16);
				*p++ = static_cast<std::uint8_t>(x * 16);
				*p++ = static_cast<std::uint8_t>(x * 16);
				*p++ = 255;
			}
		}
	}
	bksge::Texture const tex1(
		bksge::TextureFormat::kRGBA_U8, {tex1_width, tex1_height}, pixels1);

	std::vector<std::shared_ptr<Sprite>>	sprites;

	{
		auto sprite = std::make_shared<Sprite>(tex0, -0.5f,  0.5f);
		sprites.push_back(sprite);
	}
	{
		auto sprite = std::make_shared<Sprite>(tex0,  0.5f,  0.5f);
		sprites.push_back(sprite);
	}
	{
		auto sprite = std::make_shared<Sprite>(tex0, -0.5f, -0.5f);
		sprite->sampler().SetMagFilter(bksge::FilterMode::kNearest);
		sprites.push_back(sprite);
	}
	{
		auto sprite = std::make_shared<Sprite>(tex0,  0.5f, -0.5f);
		sprite->sampler().SetMagFilter(bksge::FilterMode::kNearest);
		sprites.push_back(sprite);
	}

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

		if (((count / 60) % 2) == 0)
		{
			sprites[0]->sampler().SetSource(tex0);
			sprites[2]->sampler().SetSource(tex0);
		}
		else
		{
			sprites[0]->sampler().SetSource(tex1);
			sprites[2]->sampler().SetSource(tex1);
		}

		for (auto&& sprite : sprites)
		{
			sprite->Update();
		}

		for (auto& renderer : renderers)
		{
			renderer->Begin();

			for (auto&& sprite : sprites)
			{
				sprite->Draw(renderer.get());
			}

			renderer->End();
		}

		++count;
	}

	return 0;
}
