/**
 *	@file	sample_render_constant_buffer_main.cpp
 *
 *	@brief	ConstantBufferに値を設定するサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>
#include <bksge/render.hpp>
#include <bksge/math.hpp>
#include <vector>
#include <memory>
#include <utility>
#include <cmath>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	char const* vs_source =
		"attribute vec3 aPosition;					"
		"uniform vec3 uOffset;						"
		"											"
		"void main()								"
		"{											"
		"	gl_Position = vec4(aPosition + uOffset, 1.0);		"
		"}											"
	;

	char const* fs_source =
		"uniform float uRed;						"
		"uniform float uGreen;						"
		"uniform float uBlue;						"
		"											"
		"void main()								"
		"{											"
		"	gl_FragColor = vec4(uRed, uGreen, uBlue, 1.0);"
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
		"cbuffer ConstantBuffer1						"
		"{												"
		"	float4 uDummyVariable;						"
		"	float3 uOffset;								"
		"};												"
		"												"
		"float4 main(float3 aPosition : POSITION) : SV_POSITION	"
		"{												"
		"	return float4(aPosition + uOffset, 1.0);	"
		"}												"
	;

	char const* ps_source =
		"cbuffer ConstantBuffer2						"
		"{												"
		"	float uRed;									"
		"	float uGreen;								"
		"};												"
		"cbuffer ConstantBuffer3						"
		"{												"
		"	float uBlue;								"
		"};												"
		"												"
		"float4 main() : SV_Target						"
		"{												"
		"	return float4(uRed, uGreen, uBlue, 1.0);	"
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
			new bksge::Window({800, 600}, "sample_render_constant_buffer - D3D11"));
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
			new bksge::Window({800, 600}, "sample_render_constant_buffer - D3D12"));
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
			new bksge::Window({800, 600}, "sample_render_constant_buffer - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif

	const bksge::Vertex<bksge::VPosition> vertices[] =
	{
		{{{ 0.0,  0.5, 0.0}}},
		{{{-0.5, -0.5, 0.0}}},
		{{{ 0.5, -0.5, 0.0}}},
	};

	const bksge::Geometry geometry(
		bksge::Primitive::kTriangles, vertices);

	std::vector<bksge::Shader const*> const shader_list
	{
		GetGLSLShader(),
		GetHLSLShader(),
	};

	bksge::ShaderParameterMap shader_parameter;
	shader_parameter.SetParameter("uGreen", 0.5f);

	bksge::RenderState render_state;

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

		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->Render(
				geometry, shader_list, shader_parameter, render_state);
			renderer->End();
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
		position_offset.x() = std::sin(t);
	}

	return 0;
}
