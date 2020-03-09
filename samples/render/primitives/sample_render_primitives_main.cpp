/**
 *	@file	sample_render_primitives_main.cpp
 *
 *	@brief	各種プリミティブを同時に描画するサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/math.hpp>
#include <bksge/fnd/vector.hpp>
#include <memory>
#include <utility>
#include <random>

namespace
{

inline std::mt19937& get_random_engine()
{
	static std::mt19937 mt;
	return mt;
}

template <typename T>
inline T get_random_float(T min, T max)
{
	std::uniform_real_distribution<T> dist(min, max);
	return dist(get_random_engine());
}

class Primitive
{
public:
	virtual ~Primitive() {}

	void Update(void)
	{
		VUpdate();
	}

	void Draw(bksge::Renderer* renderer)
	{
		VDraw(renderer);
	}

private:
	virtual void VUpdate(void) = 0;
	virtual void VDraw(bksge::Renderer* renderer) = 0;
};

class Triangle : public Primitive
{
public:
	Triangle()
		: m_position(
			get_random_float(-1.0f, 1.0f),
			get_random_float(-1.0f, 1.0f),
			0.0f)
		, m_velocity(
			get_random_float(-0.01f, 0.01f),
			get_random_float(-0.01f, 0.01f),
			0.0f)
		, m_scale(
			get_random_float(0.1f, 1.0f),
			get_random_float(0.1f, 1.0f),
			0.0f)
		, m_rotation(0)
		, m_color(
			get_random_float(0.0f, 1.0f),
			get_random_float(0.0f, 1.0f),
			get_random_float(0.0f, 1.0f))
	{}

private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition> const vertices[] =
		{
			{{{ 0.0,  0.5, 0.0}}},
			{{{-0.5, -0.5, 0.0}}},
			{{{ 0.5, -0.5, 0.0}}},
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

	static bksge::vector<bksge::Shader const*> const& GetShaderList(void)
	{
		static bksge::vector<bksge::Shader const*> const shader_list
		{
			GetGLSLShader(),
			GetHLSLShader(),
		};

		return shader_list;
	}

	void VUpdate(void)
	{
		m_position += m_velocity;

		if (m_position.x() > 1.0f)
		{
			m_position.x() = 1.0f;
			m_velocity.x() *= -1;
		}
		if (m_position.x() < -1.0f)
		{
			m_position.x() = -1.0f;
			m_velocity.x() *= -1;
		}
		if (m_position.y() > 1.0f)
		{
			m_position.y() = 1.0f;
			m_velocity.y() *= -1;
		}
		if (m_position.y() < -1.0f)
		{
			m_position.y() = -1.0f;
			m_velocity.y() *= -1;
		}

		m_rotation += 0.01f;
	}

	void VDraw(bksge::Renderer* renderer)
	{
		bksge::Matrix4x4f mat =
			bksge::Matrix4x4f::MakeScale(m_scale) *
			bksge::Matrix4x4f::MakeRotationZ(m_rotation) *
			bksge::Matrix4x4f::MakeTranslation(m_position);
		m_shader_parameter.SetParameter("uMatrix", mat);

		m_shader_parameter.SetParameter("uColor", m_color);
		renderer->Render(
			GetGeometry(),
			GetShaderList(),
			m_shader_parameter,
			m_render_state);
	}

private:
	bksge::ShaderParameterMap	m_shader_parameter;
	bksge::RenderState			m_render_state;
	bksge::Vector3f				m_position;
	bksge::Vector3f				m_velocity;
	bksge::Scale3f				m_scale;
	float						m_rotation;
	bksge::Color3f				m_color;
};

class Line : public Primitive
{
public:
	Line()
		: m_position_offset(
			get_random_float(-1.0f, 1.0f),
			get_random_float(-1.0f, 1.0f),
			0.0f)
		, m_velocity(
			get_random_float(-0.01f, 0.01f),
			get_random_float(-0.01f, 0.01f),
			0.0f)
		, m_color(
			get_random_float(0.0f, 1.0f),
			get_random_float(0.0f, 1.0f),
			get_random_float(0.0f, 1.0f))
	{}

private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition> const vertices[] =
		{
			{{{ 0.0f, 0.0f, 0.0f}}},
			{{{ 0.0f, 0.1f, 0.0f}}},
		};

		static bksge::Geometry const geometry(
			bksge::PrimitiveTopology::kLines, vertices);

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
			"	vec3 uOffset;										\n"
			"};														\n"
			"														\n"
			"void main()											\n"
			"{														\n"
			"	gl_Position = vec4(aPosition + uOffset, 1.0);		\n"
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
			"	float3 uOffset;								"
			"};												"
			"												"
			"float4 main(float3 aPosition : POSITION) : SV_POSITION	"
			"{												"
			"	return float4(aPosition + uOffset, 1.0);	"
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

	static bksge::vector<bksge::Shader const*> const& GetShaderList(void)
	{
		static bksge::vector<bksge::Shader const*> const shader_map
		{
			GetGLSLShader(),
			GetHLSLShader(),
		};

		return shader_map;
	}

	void VUpdate(void)
	{
		m_position_offset += m_velocity;

		if (m_position_offset.x() > 1.0f)
		{
			m_position_offset.x() = 1.0f;
			m_velocity.x() *= -1;
		}
		if (m_position_offset.x() < -1.0f)
		{
			m_position_offset.x() = -1.0f;
			m_velocity.x() *= -1;
		}
		if (m_position_offset.y() > 1.0f)
		{
			m_position_offset.y() = 1.0f;
			m_velocity.y() *= -1;
		}
		if (m_position_offset.y() < -1.0f)
		{
			m_position_offset.y() = -1.0f;
			m_velocity.y() *= -1;
		}
	}

	void VDraw(bksge::Renderer* renderer)
	{
		m_shader_parameter.SetParameter("uOffset", m_position_offset);
		m_shader_parameter.SetParameter("uColor", m_color);
		renderer->Render(
			GetGeometry(),
			GetShaderList(),
			m_shader_parameter,
			m_render_state);
	}

private:
	bksge::ShaderParameterMap	m_shader_parameter;
	bksge::RenderState			m_render_state;
	bksge::Vector3f				m_position_offset;
	bksge::Vector3f				m_velocity;
	bksge::Color3f				m_color;
};

class Point : public Primitive
{
public:
	Point()
		: m_position_offset(
			get_random_float(-1.0f, 1.0f),
			get_random_float(-1.0f, 1.0f),
			0.0f)
		, m_velocity(
			get_random_float(-0.01f, 0.01f),
			get_random_float(-0.01f, 0.01f),
			0.0f)
	{}

private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition> const vertices[] =
		{
			{{{ 0.0, 0.0, 0.0}}},
		};

		static bksge::Geometry const geometry(
			bksge::PrimitiveTopology::kPoints, vertices);

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
			"	vec3 uOffset;										\n"
			"};														\n"
			"														\n"
			"void main()											\n"
			"{														\n"
			"	gl_PointSize = 1.0;									\n"
			"	gl_Position = vec4(aPosition + uOffset, 1.0);		\n"
			"}														\n"
		;

		static char const* fs_source =
			"#version 420											\n"
			"#extension GL_ARB_separate_shader_objects : enable		\n"
			"														\n"
			"layout (location = 0) out vec4 oColor;					\n"
			"														\n"
			"void main()											\n"
			"{														\n"
			"	oColor = vec4(1.0, 1.0, 1.0, 1.0);					\n"
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
			"	float3 uOffset;								"
			"};												"
			"												"
			"float4 main(float3 aPosition : POSITION) : SV_POSITION	"
			"{												"
			"	return float4(aPosition + uOffset, 1.0);	"
			"}												"
		;

		static char const* ps_source =
			"float4 main() : SV_Target						"
			"{												"
			"	return float4(1.0, 1.0, 1.0, 1.0);			"
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

	static bksge::vector<bksge::Shader const*> const& GetShaderList(void)
	{
		static bksge::vector<bksge::Shader const*> const shader_map
		{
			GetGLSLShader(),
			GetHLSLShader(),
		};

		return shader_map;
	}

	void VUpdate(void)
	{
		m_position_offset += m_velocity;

		if (m_position_offset.x() > 1.0f)
		{
			m_position_offset.x() = 1.0f;
			m_velocity.x() *= -1;
		}
		if (m_position_offset.x() < -1.0f)
		{
			m_position_offset.x() = -1.0f;
			m_velocity.x() *= -1;
		}
		if (m_position_offset.y() > 1.0f)
		{
			m_position_offset.y() = 1.0f;
			m_velocity.y() *= -1;
		}
		if (m_position_offset.y() < -1.0f)
		{
			m_position_offset.y() = -1.0f;
			m_velocity.y() *= -1;
		}
	}

	void VDraw(bksge::Renderer* renderer)
	{
		m_shader_parameter.SetParameter("uOffset", m_position_offset);
		renderer->Render(
			GetGeometry(),
			GetShaderList(),
			m_shader_parameter,
			m_render_state);
	}

private:
	bksge::ShaderParameterMap	m_shader_parameter;
	bksge::RenderState			m_render_state;
	bksge::Vector3f				m_position_offset;
	bksge::Vector3f				m_velocity;
};

}	// namespace

int main()
{
	bksge::Extent2f const extent{800, 600};

	bksge::vector<std::shared_ptr<bksge::Renderer>>	renderers;
	bksge::vector<std::shared_ptr<bksge::Window>>		windows;

#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_primitives - D3D11"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D11Renderer> renderer(new bksge::D3D11Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_primitives - D3D12"));
		windows.push_back(window);

		std::shared_ptr<bksge::D3D12Renderer> renderer(new bksge::D3D12Renderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_primitives - GL"));
		windows.push_back(window);

		std::shared_ptr<bksge::GlRenderer> renderer(new bksge::GlRenderer(*window));
		renderers.push_back(renderer);
	}
#endif
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
	{
		std::shared_ptr<bksge::Window> window(
			new bksge::Window(extent, "sample_render_primitives - Vulkan"));
		windows.push_back(window);

		std::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);
	}
#endif

	bksge::vector<std::shared_ptr<Primitive>>	primitives;

	static const int kTriangleNum = 5;
	static const int kLineNum = 100;
	static const int kPointNum = 100;

	for (int i = 0; i < kTriangleNum; ++i)
	{
		primitives.push_back(std::make_shared<Triangle>());
	}
	for (int i = 0; i < kLineNum; ++i)
	{
		primitives.push_back(std::make_shared<Line>());
	}
	for (int i = 0; i < kPointNum; ++i)
	{
		primitives.push_back(std::make_shared<Point>());
	}

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
			for (auto&& primitive : primitives)
			{
				primitive->Draw(renderer.get());
			}
			renderer->EndRenderPass();
			renderer->End();
		}

		for (auto&& primitive : primitives)
		{
			primitive->Update();
		}
	}

	return 0;
}
