/**
 *	@file	sample_render_fill_mode_main.cpp
 *
 *	@brief	塗りつぶしモードの設定をするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/math.hpp>
#include <vector>
#include <bksge/fnd/memory.hpp>
#include <utility>

namespace
{

class Triangle
{
public:
	Triangle(float x, float y, bksge::FillMode fill_mode)
		: m_position(
			x,
			y,
			0.0f)
		, m_scale(
			0.5f,
			0.5f,
			0.0f)
		, m_color(
			1.0f,
			0.0f,
			0.0f)
	{
		m_render_state.rasterizer_state().SetFillMode(fill_mode);
	}

	void Update(void)
	{
	}

	void Draw(bksge::Renderer* renderer)
	{
		bksge::Matrix4x4f mat =
			bksge::Matrix4x4f::MakeScale(m_scale) *
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
			bksge::PrimitiveTopology::kTriangles, vertices);

		return geometry;
	}

	static bksge::Shader const* GetGLSLShader(void)
	{
		static char const* vs_source =
			"#version 420											\n"
			"#extension GL_ARB_separate_shader_objects : enable		\n"
			"														\n"
			"layout (location = 0) in vec3 aPosition;				\n"
			"														\n"
			"layout(set=0, binding=0) uniform UniformBuffer1 {		\n"
			"	mat4 uMatrix;										\n"
			"};														\n"
			"														\n"
			"void main()											\n"
			"{														\n"
			"	gl_Position = uMatrix * vec4(aPosition, 1.0);		\n"
			"}														\n"
		;

		static char const* fs_source =
			"#version 420											\n"
			"#extension GL_ARB_separate_shader_objects : enable		\n"
			"														\n"
			"layout (location = 0) out vec4 oColor;					\n"
			"														\n"
			"layout(set=0, binding=1) uniform UniformBuffer2 {		\n"
			"	vec3 uColor;										\n"
			"};														\n"
			"														\n"
			"void main()											\n"
			"{														\n"
			"	oColor = vec4(uColor, 1.0);							\n"
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
		static std::vector<bksge::Shader const*> const shader_list
		{
			GetGLSLShader(),
			GetHLSLShader(),
		};

		return shader_list;
	}

private:
	bksge::ShaderParameterMap	m_shader_parameter;
	bksge::RenderState			m_render_state;
	bksge::Vector3f				m_position;
	bksge::Scale3f				m_scale;
	bksge::Color3f				m_color;
};

}	// namespace

int main()
{
	bksge::Extent2f const extent{800, 600};
	std::vector<bksge::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<bksge::shared_ptr<bksge::Window>>		windows;

#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_fill_mode - D3D11"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::D3D11Renderer> renderer(new bksge::D3D11Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_fill_mode - D3D12"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::D3D12Renderer> renderer(new bksge::D3D12Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_fill_mode - GL"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::GlRenderer> renderer(new bksge::GlRenderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
	{
		bksge::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_fill_mode - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);
	}
#endif

	std::vector<bksge::shared_ptr<Triangle>>	triangles;

	triangles.push_back(bksge::make_shared<Triangle>(-0.5f,  0.0f, bksge::FillMode::kSolid));
	triangles.push_back(bksge::make_shared<Triangle>( 0.5f,  0.0f, bksge::FillMode::kWireframe));

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({bksge::Vector2f{0, 0}, extent});
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

		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass_info);
			for (auto&& triangle : triangles)
			{
				triangle->Draw(renderer.get());
			}
			renderer->EndRenderPass();
			renderer->End();
		}

		for (auto&& triangle : triangles)
		{
			triangle->Update();
		}
	}

	return 0;
}
