/**
 *	@file	sample_render_depth_test_main.cpp
 *
 *	@brief	デプステストのサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/input.hpp>
#include <bksge/core/math.hpp>
#include <bksge/fnd/cmath.hpp>
#include <bksge/fnd/memory.hpp>
#include <bksge/fnd/vector.hpp>

namespace
{

static bksge::Shader const* GetGLSLShader(void)
{
	static char const* vs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec3 aPosition;				\n"
		"layout (location = 1) in vec4 aColor;					\n"
		"														\n"
		"layout (location = 0) out vec4 vColor;					\n"
		"														\n"
		"layout(set=0, binding=0) uniform Matrices {			\n"
		"	mat4 uProjection;									\n"
		"	mat4 uView;											\n"
		"	mat4 uModel;										\n"
		"};														\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	vec4 pos = vec4(aPosition, 1.0);					\n"
		"	gl_Position = uProjection * uView * uModel * pos;	\n"
		"	vColor = aColor;									\n"
		"}														\n"
	;

	static char const* fs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec4 vColor;					\n"
		"														\n"
		"layout (location = 0) out vec4 oColor;					\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	oColor = vColor;									\n"
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
		"	float3 pos   : POSITION;					\n"
		"	float4 color : COLOR;						\n"
		"};												\n"
 		"												\n"
		"struct VS_OUTPUT								\n"
		"{												\n"
		"	float4 pos   : SV_POSITION;					\n"
		"	float4 color : COLOR;						\n"
		"};												\n"
		"												\n"
		"cbuffer Matrices								\n"
		"{												\n"
		"	row_major float4x4 uProjection;				\n"
		"	row_major float4x4 uView;					\n"
		"	row_major float4x4 uModel;					\n"
		"};												\n"
		"												\n"
		"VS_OUTPUT main(VS_INPUT input)					\n"
		"{												\n"
		"	float4 pos = float4(input.pos, 1.0);		\n"
		"	pos = mul(pos, uModel);						\n"
		"	pos = mul(pos, uView);						\n"
		"	pos = mul(pos, uProjection);				\n"
		"												\n"
		"	VS_OUTPUT output;							\n"
		"	output.pos   = pos;							\n"
		"	output.color = input.color;					\n"
		"	return output;								\n"
		"}												\n"
	;

	static char const* ps_source =
		"struct PS_INPUT								\n"
		"{												\n"
		"	float4 pos   : SV_POSITION;					\n"
		"	float4 color : COLOR;						\n"
		"};												\n"
		"												\n"
		"float4 main(PS_INPUT input) : SV_Target		\n"
		"{												\n"
		"	return input.color;							\n"
		"}												\n"
	;

	static bksge::Shader const shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, ps_source },
	};

	return &shader;
}

class DrawObject
{
public:
	void SetProjectionMatrix(bksge::Matrix4x4f const& mat)
	{
		m_projection = mat;
	}

	void SetViewMatrix(bksge::Matrix4x4f const& mat)
	{
		m_view = mat;
	}

protected:
	bksge::ShaderParameterMap	m_shader_parameter;
	bksge::RenderState			m_render_state;
	bksge::Matrix4x4f			m_projection;
	bksge::Matrix4x4f			m_view;
};

class Triangle : public DrawObject
{
public:
	Triangle()
	{
		SetDepthTestEnable(true);
	}

	void SetT(float t)
	{
		m_t = t;
	}

	void SetPositionX(float x)
	{
		m_x = x;
	}

	void SetDepthTestEnable(bool enable)
	{
		m_render_state.depth_state().SetEnable(enable);
		m_render_state.depth_state().SetWrite(enable);
	}

	void Update(void)
	{
		m_t += 0.02f;
	}

	void Draw(bksge::Renderer* renderer, bksge::Shader const* shader)
	{
		auto const model =
			bksge::Matrix4x4f::MakeTranslation(m_x, 0, 5.0f + bksge::sin(m_t) * 4.0f);

		m_shader_parameter.SetParameter("uProjection", m_projection);
		m_shader_parameter.SetParameter("uView", m_view);
		m_shader_parameter.SetParameter("uModel", model);

		renderer->Render(
			GetGeometry(),
			*shader,
			m_shader_parameter,
			m_render_state);
	}

private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition, bksge::VColor> const vertices[] =
		{
			{{{ 0.0f,  1.5f,  0.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
			{{{ 2.0f, -1.5f,  0.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
			{{{-2.0f, -1.5f,  0.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
		};

		static bksge::Geometry const geometry(
			bksge::PrimitiveTopology::kTriangles, vertices);

		return geometry;
	}

private:
	float		m_x = 0.0f;
	float		m_t = 0.0f;
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
			new bksge::Window(extent, "sample_render_depth_test - D3D11"));
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
			new bksge::Window(extent, "sample_render_depth_test - D3D12"));
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
			new bksge::Window(extent, "sample_render_depth_test - GL"));
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
			new bksge::Window(extent, "sample_render_depth_test - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetGLSLShader());
	}
#endif

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({{0, 0}, extent});
	render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

	auto const projection =
		bksge::Matrix4x4f::MakePerspective(
			bksge::degrees_to_radians(45.0f),
			extent.width() / extent.height(),
			0.1f,
			100.0f);

	auto const view =
		bksge::Matrix4x4f::MakeLookAt(
			{0, 0,-5},
			{0, 0, 0},
			{0, 1, 0});

	Triangle triangles[3];

	for (auto& triangle : triangles)
	{
		triangle.SetProjectionMatrix(projection);
		triangle.SetViewMatrix(view);
	}

	triangles[0].SetPositionX(-2);
	triangles[1].SetPositionX( 0);
	triangles[2].SetPositionX( 2);
	triangles[0].SetT(0.0f);
	triangles[1].SetT(0.5f);
	triangles[2].SetT(1.0f);

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

		for (auto& triangle : triangles)
		{
			triangle.Update();

			auto const& keyboard_state = keyboard.state(0);
			if (keyboard_state.pressed(bksge::KeyCode::kA))
			{
				triangle.SetDepthTestEnable(false);
			}
			if (keyboard_state.pressed(bksge::KeyCode::kS))
			{
				triangle.SetDepthTestEnable(true);
			}
		}

		int i = 0;
		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass_info);
			for (auto& triangle : triangles)
			{
				triangle.Draw(renderer.get(), shaders[i]);
			}
			renderer->EndRenderPass();
			renderer->End();

			++i;
		}
	}

	return 0;
}
