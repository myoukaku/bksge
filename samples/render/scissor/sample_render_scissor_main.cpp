/**
 *	@file	sample_render_scissor_main.cpp
 *
 *	@brief	シザー領域の設定をするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/math.hpp>
#include <bksge/core/input.hpp>
#include <vector>
#include <memory>
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
	bksge::Size2f size{800, 600};

	std::vector<std::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<std::shared_ptr<bksge::Window>>		windows;

#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(size, "sample_render_scissor - D3D11"));
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
			new bksge::Window(size, "sample_render_scissor - D3D12"));
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
			new bksge::Window(size, "sample_render_scissor - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer(*window));
		renderers.push_back(renderer);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window({800, 600}, "sample_render_scissor - Vulkan"));
		windows.push_back(window);

		std::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);
		renderer->SetClearColor({0.5f, 0.0f, 0.5f, 1});
	}
#endif

	const bksge::Vertex<bksge::VPosition> vertices[] =
	{
		{{{ 0.0,  1.0, 0.0}}},
		{{{-1.0, -1.0, 0.0}}},
		{{{ 1.0, -1.0, 0.0}}},
	};

	const bksge::Geometry geometry(bksge::Primitive::kTriangles, vertices);

	std::vector<bksge::Shader const*> const shader_list
	{
		GetGLSLShader(),
		GetHLSLShader(),
	};

	bksge::ShaderParameterMap shader_parameter;

	bksge::RenderState render_state;
	render_state.scissor_state().SetEnable(true);
	render_state.scissor_state().SetRect({bksge::Vector2f{0, 0}, size});

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
			renderer->Begin();
			renderer->Render(
				geometry,
				shader_list,
				shader_parameter,
				render_state);
			renderer->End();
		}

		keyboard.Update();
		{
			auto& scissor_state = render_state.scissor_state();
			auto& scissor_rect = scissor_state.rect();
			bksge::Vector2f p1{scissor_rect.left(), scissor_rect.top()};
			bksge::Vector2f p2{scissor_rect.right(), scissor_rect.bottom()};
			const float v = 2.0f;

			auto const& state = keyboard.state(0);
			bksge::Vector2f* p =
				state.pressed(bksge::KeyCode::kLShift) ?
				&p1 : &p2;
			if (state.pressed(bksge::KeyCode::kLeft))
			{
				p->x() -= v;
			}
			if (state.pressed(bksge::KeyCode::kRight))
			{
				p->x() += v;
			}
			if (state.pressed(bksge::KeyCode::kUp))
			{
				p->y() -= v;
			}
			if (state.pressed(bksge::KeyCode::kDown))
			{
				p->y() += v;
			}

			if (state.pressed(bksge::KeyCode::kA))
			{
				scissor_state.SetEnable(false);
			}
			if (state.pressed(bksge::KeyCode::kS))
			{
				scissor_state.SetEnable(true);
			}
			scissor_state.SetRect({p1, p2});
		}
	}

	return 0;
}
