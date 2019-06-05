﻿/**
 *	@file	sample_render_viewport_main.cpp
 *
 *	@brief	ビューポートの設定をするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>
#include <bksge/render.hpp>
#include <bksge/math.hpp>
#include <bksge/input.hpp>
#include <vector>
#include <memory>
#include <utility>

namespace
{

static bksge::Shader GetGLSLShader(void)
{
	char const* vs_source =
		"attribute vec3 aPosition;					"
		"											"
		"void main()								"
		"{											"
		"	gl_Position = vec4(aPosition, 1.0);		"
		"}											"
	;

	char const* fs_source =
		"void main()								"
		"{											"
		"	gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);"
		"}											"
	;

	return bksge::Shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, fs_source },
	};
}

static bksge::Shader GetHLSLShader(void)
{
	char const* vs_source =
		"float4 main(float3 aPosition : POSITION) : SV_POSITION	"
		"{												"
		"	return float4(aPosition, 1.0);				"
		"}												"
	;

	char const* ps_source =
		"float4 main() : SV_Target					"
		"{											"
		"	return float4(0.0, 0.0, 1.0, 1.0);		"
		"}											"
	;

	return bksge::Shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, ps_source },
	};
}

}	// namespace

int main()
{
	bksge::Size2f size{800, 600};
	bksge::Rectf viewport({bksge::Vector2f{0, 0}, size});

	std::vector<std::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<std::shared_ptr<bksge::Window>>		windows;

#if BKSGE_RENDER_HAS_D3D11_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(size, "sample_render_viewport - D3D11"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D11Renderer> renderer(
			new bksge::D3D11Renderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
	}
#endif
#if BKSGE_RENDER_HAS_D3D12_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(size, "sample_render_viewport - D3D12"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D12Renderer> renderer(
			new bksge::D3D12Renderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
	}
#endif
#if BKSGE_RENDER_HAS_GL_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(size, "sample_render_viewport - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer());
		renderers.push_back(renderer);
		renderer->SetRenderTarget(*window);
	}
#endif

	for (auto& renderer : renderers)
	{
		renderer->SetViewport(viewport);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}

	const bksge::Vertex<bksge::VPosition> vertices[] =
	{
		{{{ 0.0,  1.0, 0.0}}},
		{{{-1.0, -1.0, 0.0}}},
		{{{ 1.0, -1.0, 0.0}}},
	};

	const bksge::Geometry geometry(bksge::Primitive::kTriangles, vertices);

	bksge::ShaderMap const shader_map
	{
		{ bksge::ShaderType::kGLSL, GetGLSLShader() },
		{ bksge::ShaderType::kHLSL, GetHLSLShader() },
	};

	bksge::ShaderParameterMap shader_parameter;

	bksge::RenderState render_state;

	bksge::KeyboardManager keyboard;

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
			renderer->SetViewport(viewport);
			renderer->Begin();
			renderer->Clear();
			renderer->Render(
				geometry,
				shader_map,
				shader_parameter,
				render_state);
			renderer->End();
		}

		keyboard.Update();
		{
			bksge::Vector2f p1{viewport.left(), viewport.top()};
			bksge::Vector2f p2{viewport.right(), viewport.bottom()};
			const float v = 2.0f;

			auto const& state = keyboard.state(0);
			bksge::Vector2f* p =
				state.pressed(bksge::KeyCode::kLShift) ?
				&p1 : &p2;
			if (state.pressed(bksge::KeyCode::kLeft))
			{
				p->x() += v;
			}
			if (state.pressed(bksge::KeyCode::kRight))
			{
				p->x() -= v;
			}
			if (state.pressed(bksge::KeyCode::kUp))
			{
				p->y() += v;
			}
			if (state.pressed(bksge::KeyCode::kDown))
			{
				p->y() -= v;
			}

			viewport = bksge::Rectf(p1, p2);
		}
	}

	return 0;
}