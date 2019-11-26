﻿/**
 *	@file	sample_render_cull_face_main.cpp
 *
 *	@brief	フェースカリングの設定をするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>
#include <bksge/render.hpp>
#include <bksge/math.hpp>
#include <vector>
#include <memory>
#include <utility>

namespace
{

class Triangle
{
public:
	Triangle(float x, float y, bksge::FrontFace front_face, bksge::CullMode cull_mode)
		: m_position(
			x,
			y,
			0.0f)
		, m_scale(
			0.25f,
			0.25f,
			0.0f)
		, m_rotation(0)
		, m_color(
			1.0f,
			0.0f,
			0.0f)
	{
		m_render_state.rasterizer_state().SetFrontFace(front_face);
		m_render_state.rasterizer_state().SetCullMode(cull_mode);
	}

	void Update(void)
	{
		m_rotation += 0.01f;
	}

	void Draw(bksge::Renderer* renderer)
	{
		bksge::Matrix4x4f mat =
			bksge::Matrix4x4f::MakeScale(m_scale) *
			bksge::Matrix4x4f::MakeRotationY(m_rotation) *
			bksge::Matrix4x4f::MakeTranslation(m_position) *
			bksge::Matrix4x4f::MakeOrthographic(-1, 1, -1, 1, -100.0f, 100.0f);
		m_shader_parameter.SetParameter("uMatrix", mat);

		m_shader_parameter.SetParameter("uColor", m_color);
		renderer->Render(
			GetGeometry(),
			GetShaderList(),
			m_shader_parameter,
			m_render_state);
	}

private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition> const vertices[] =
		{
			{{{ 0.0,  1.0, 0.0}}},
			{{{ 1.0, -1.0, 0.0}}},
			{{{-1.0, -1.0, 0.0}}},
		};

		static bksge::Geometry const geometry(
			bksge::Primitive::kTriangles, vertices);

		return geometry;
	}

	static bksge::Shader const* GetGLSLShader(void)
	{
		static char const* vs_source =
			"attribute vec3 aPosition;					"
			"uniform mat4 uMatrix;						"
			"											"
			"void main()								"
			"{											"
			"	gl_Position = uMatrix * vec4(aPosition, 1.0);		"
			"}											"
		;

		static char const* fs_source =
			"uniform vec3 uColor;						"
			"											"
			"void main()								"
			"{											"
			"	gl_FragColor = vec4(uColor, 1.0);		"
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
			"cbuffer ConstantBuffer1						"
			"{												"
			"	row_major float4x4 uMatrix;					"
			"};												"
			"												"
			"float4 main(float3 aPosition : POSITION) : SV_POSITION	"
			"{												"
			"	return mul(float4(aPosition, 1.0), uMatrix);	"
			"}												"
		;

		static char const* ps_source =
			"cbuffer ConstantBuffer2						"
			"{												"
			"	float3 uColor;								"
			"};												"
			"												"
			"float4 main() : SV_Target						"
			"{												"
			"	return float4(uColor, 1.0);	"
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
		static std::vector<bksge::Shader const*> const shader_map
		{
			GetGLSLShader(),
			GetHLSLShader(),
		};

		return shader_map;
	}

private:
	bksge::ShaderParameterMap	m_shader_parameter;
	bksge::RenderState			m_render_state;
	bksge::Vector3f				m_position;
	bksge::Scale3f				m_scale;
	float						m_rotation;
	bksge::Color3f				m_color;
};

}	// namespace

int main()
{
	std::vector<std::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<std::shared_ptr<bksge::Window>>		windows;

#if BKSGE_RENDER_HAS_D3D11_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_cull_face - D3D11"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D11Renderer> renderer(new bksge::D3D11Renderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif
#if BKSGE_RENDER_HAS_D3D12_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_cull_face - D3D12"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D12Renderer> renderer(new bksge::D3D12Renderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif
#if BKSGE_RENDER_HAS_GL_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_cull_face - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(new bksge::GlRenderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif

	std::vector<std::shared_ptr<Triangle>>	triangles;

	triangles.push_back(std::make_shared<Triangle>(-0.5f,  0.5f, bksge::FrontFace::kClockwise, bksge::CullMode::kNone));
	triangles.push_back(std::make_shared<Triangle>( 0.0f,  0.5f, bksge::FrontFace::kClockwise, bksge::CullMode::kBack));
	triangles.push_back(std::make_shared<Triangle>( 0.5f,  0.5f, bksge::FrontFace::kClockwise, bksge::CullMode::kFront));
	triangles.push_back(std::make_shared<Triangle>(-0.5f, -0.5f, bksge::FrontFace::kCounterClockwise, bksge::CullMode::kNone));
	triangles.push_back(std::make_shared<Triangle>( 0.0f, -0.5f, bksge::FrontFace::kCounterClockwise, bksge::CullMode::kBack));
	triangles.push_back(std::make_shared<Triangle>( 0.5f, -0.5f, bksge::FrontFace::kCounterClockwise, bksge::CullMode::kFront));

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
			for (auto&& triangle : triangles)
			{
				triangle->Draw(renderer.get());
			}
			renderer->End();
		}

		for (auto&& triangle : triangles)
		{
			triangle->Update();
		}
	}

	return 0;
}
