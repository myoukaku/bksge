/**
 *	@file	sample_render_viewport_main.cpp
 *
 *	@brief	ビューポートの設定をするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/math.hpp>
#include <bksge/core/input.hpp>
#include <vector>
#include <bksge/fnd/memory.hpp>
#include <utility>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	char const* vs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec3 aPosition;				\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position = vec4(aPosition, 1.0);					\n"
		"}														\n"
	;

	char const* fs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
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
	bksge::Rectf viewport({bksge::Vector2f{0, 0}, extent});

	std::vector<bksge::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<bksge::shared_ptr<bksge::Window>>		windows;

#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_viewport - D3D11"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::D3D11Renderer> renderer(
			new bksge::D3D11Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_viewport - D3D12"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::D3D12Renderer> renderer(
			new bksge::D3D12Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_viewport - GL"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_viewport - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);
	}
#endif

	const bksge::Vertex<bksge::VPosition> vertices[] =
	{
		{{{ 0.0,  1.0, 0.0}}},
		{{{-1.0, -1.0, 0.0}}},
		{{{ 1.0, -1.0, 0.0}}},
	};

	const bksge::Geometry geometry(bksge::PrimitiveTopology::kTriangles, vertices);

	std::vector<bksge::Shader const*> const shader_list
	{
		GetGLSLShader(),
		GetHLSLShader(),
	};

	bksge::ShaderParameterMap shader_parameter;

	bksge::RenderState render_state;

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

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
			render_pass_info.viewport().SetRect(viewport);
		}

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
