/**
 *	@file	sample_render_clear_flag_main.cpp
 *
 *	@brief	ClearFlagを設定するサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/input.hpp>
#include <bksge/core/math.hpp>
#include <bksge/fnd/cmath.hpp>
#include <vector>
#include <bksge/fnd/memory.hpp>
#include <utility>

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
		bksge::ShaderType::kHLSL,
		{
			{ bksge::ShaderStage::kVertex,   vs_source },
			{ bksge::ShaderStage::kFragment, ps_source },
		}
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

	void SetColorWriteFlag(bksge::ColorWriteFlag flag)
	{
		m_render_state.blend_state().SetColorWriteFlag(flag);
	}

	bksge::StencilState& stencil_state(void)
	{
		return m_render_state.stencil_state();
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
		m_render_state.rasterizer_state().SetCullMode(bksge::CullMode::kBack);
	}

	void Update(void)
	{
		m_rotation_z += 0.01f;
	}

	void Draw(bksge::Renderer* renderer)
	{
		auto const model =
			bksge::Matrix4x4f::MakeScale(0.5f, 0.5f, 0.5f) *
			bksge::Matrix4x4f::MakeRotationZ(m_rotation_z);

		m_shader_parameter.SetParameter("uProjection", m_projection);
		m_shader_parameter.SetParameter("uView", m_view);
		m_shader_parameter.SetParameter("uModel", model);

		renderer->Render(
			GetGeometry(),
			GetShaderList(),
			m_shader_parameter,
			m_render_state);
	}

private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition, bksge::VColor> const vertices[] =
		{
			{{{ 0.0f,  1.5f,  0.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
			{{{-2.0f, -1.5f,  0.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
			{{{ 2.0f, -1.5f,  0.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
		};

		static bksge::uint16_t const indices[] =
		{
			0, 1, 2,
		};

		static bksge::Geometry const geometry(
			bksge::PrimitiveTopology::kTriangles, vertices, indices);

		return geometry;
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
	float						m_rotation_z = 0.0f;
};

class Box : public DrawObject
{
public:
	Box()
	{
		m_render_state.rasterizer_state().SetCullMode(bksge::CullMode::kBack);
		m_render_state.depth_state().SetEnable(true);
		m_render_state.depth_state().SetWrite(true);
	}

	void Update(void)
	{
		m_rotation_x += 0.01f;
		m_rotation_y += 0.02f;
	}

	void Draw(bksge::Renderer* renderer)
	{
		auto const model =
			bksge::Matrix4x4f::MakeRotationX(m_rotation_x) *
			bksge::Matrix4x4f::MakeRotationY(m_rotation_y);

		m_shader_parameter.SetParameter("uProjection", m_projection);
		m_shader_parameter.SetParameter("uView", m_view);
		m_shader_parameter.SetParameter("uModel", model);

		renderer->Render(
			GetGeometry(),
			GetShaderList(),
			m_shader_parameter,
			m_render_state);
	}

private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition, bksge::VColor> const vertices[] =
		{
			{{{ 1.0f,  1.0f,  1.0f}}, {{ 1.0f, 0.0f, 1.0f, 1.0f }}},
			{{{ 1.0f,  1.0f, -1.0f}}, {{ 1.0f, 0.0f, 1.0f, 1.0f }}},
			{{{ 1.0f, -1.0f,  1.0f}}, {{ 1.0f, 0.0f, 1.0f, 1.0f }}},
			{{{ 1.0f, -1.0f, -1.0f}}, {{ 1.0f, 0.0f, 1.0f, 1.0f }}},

			{{{-1.0f,  1.0f,  1.0f}}, {{ 0.0f, 1.0f, 1.0f, 1.0f }}},
			{{{-1.0f, -1.0f,  1.0f}}, {{ 0.0f, 1.0f, 1.0f, 1.0f }}},
			{{{-1.0f,  1.0f, -1.0f}}, {{ 0.0f, 1.0f, 1.0f, 1.0f }}},
			{{{-1.0f, -1.0f, -1.0f}}, {{ 0.0f, 1.0f, 1.0f, 1.0f }}},

			{{{-1.0f,  1.0f,  1.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
			{{{ 1.0f,  1.0f,  1.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
			{{{-1.0f, -1.0f,  1.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},
			{{{ 1.0f, -1.0f,  1.0f}}, {{ 1.0f, 0.0f, 0.0f, 1.0f }}},

			{{{-1.0f,  1.0f, -1.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
			{{{-1.0f, -1.0f, -1.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
			{{{ 1.0f,  1.0f, -1.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},
			{{{ 1.0f, -1.0f, -1.0f}}, {{ 0.0f, 1.0f, 0.0f, 1.0f }}},

			{{{-1.0f,  1.0f, -1.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
			{{{ 1.0f,  1.0f, -1.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
			{{{-1.0f,  1.0f,  1.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},
			{{{ 1.0f,  1.0f,  1.0f}}, {{ 0.0f, 0.0f, 1.0f, 1.0f }}},

			{{{-1.0f, -1.0f, -1.0f}}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},
			{{{-1.0f, -1.0f,  1.0f}}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},
			{{{ 1.0f, -1.0f, -1.0f}}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},
			{{{ 1.0f, -1.0f,  1.0f}}, {{ 1.0f, 1.0f, 0.0f, 1.0f }}},

		};

		static bksge::uint16_t const indices[] =
		{
			0+0, 0+2, 0+1,
			0+1, 0+2, 0+3,

			4+0, 4+2, 4+1,
			4+1, 4+2, 4+3,

			8+0, 8+2, 8+1,
			8+1, 8+2, 8+3,

			12+0, 12+2, 12+1,
			12+1, 12+2, 12+3,

			16+0, 16+2, 16+1,
			16+1, 16+2, 16+3,

			20+0, 20+2, 20+1,
			20+1, 20+2, 20+3,
		};

		static bksge::Geometry const geometry(
			bksge::PrimitiveTopology::kTriangles, vertices, indices);

		return geometry;
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
	float	m_rotation_x = 0.0f;
	float	m_rotation_y = 0.0f;
};

}	// namespace

int main()
{
	bksge::Extent2f const extent{800, 600};
	std::vector<std::shared_ptr<bksge::Renderer>>	renderers;
	std::vector<std::shared_ptr<bksge::Window>>		windows;

#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_clear_flag - D3D11"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D11Renderer> renderer(
			new bksge::D3D11Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_clear_flag - D3D12"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D12Renderer> renderer(
			new bksge::D3D12Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_clear_flag - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(
			new bksge::GlRenderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_clear_flag - Vulkan"));
		windows.push_back(window);

		std::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);
	}
#endif

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({bksge::Vector2f{0, 0}, extent});
	render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

	auto const projection =
		bksge::Matrix4x4f::MakePerspective(
			bksge::degrees_to_radians(45.0f),
			extent.width() / extent.height(),
			0.1f,
			100.0f);

	auto const view =
		bksge::Matrix4x4f::MakeLookAt(
			bksge::Vector3f(0, 0, 5),
			bksge::Vector3f(0, 0, 0),
			bksge::Vector3f(0, 1, 0));

	Triangle triangle;
	triangle.SetProjectionMatrix(projection);
	triangle.SetViewMatrix(view);
	triangle.SetColorWriteFlag(bksge::ColorWriteFlag::kNone);
	triangle.stencil_state().SetEnable(true);
	triangle.stencil_state().SetReadMask(0xFF);
	triangle.stencil_state().SetWriteMask(0xFF);
	triangle.stencil_state().SetReference(0x01);
	triangle.stencil_state().SetFunc(bksge::ComparisonFunction::kAlways);
	triangle.stencil_state().SetPassOperation(bksge::StencilOperation::kReplace);

	Box box;
	box.SetProjectionMatrix(projection);
	box.SetViewMatrix(view);
	box.stencil_state().SetEnable(true);
	box.stencil_state().SetReadMask(0xFF);
	box.stencil_state().SetWriteMask(0xFF);
	box.stencil_state().SetReference(0x01);
	box.stencil_state().SetFunc(bksge::ComparisonFunction::kNotEqual);
	box.stencil_state().SetPassOperation(bksge::StencilOperation::kKeep);

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
			bksge::ClearFlag clear_flag = bksge::ClearFlag::kNone;

			auto const& keyboard_state = keyboard.state(0);
			if (!keyboard_state.pressed(bksge::KeyCode::kC))
			{
				clear_flag |= bksge::ClearFlag::kColor;
			}
			if (!keyboard_state.pressed(bksge::KeyCode::kD))
			{
				clear_flag |= bksge::ClearFlag::kDepth;
			}
			if (!keyboard_state.pressed(bksge::KeyCode::kS))
			{
				clear_flag |= bksge::ClearFlag::kStencil;
			}

			render_pass_info.clear_state().SetFlag(clear_flag);
		}

		triangle.Update();
		box.Update();

		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass_info);
			{
				triangle.Draw(renderer.get());
				box.Draw(renderer.get());
			}
			renderer->EndRenderPass();
			renderer->End();
		}
	}

	return 0;
}
