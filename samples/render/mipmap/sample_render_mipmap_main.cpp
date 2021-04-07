/**
 *	@file	sample_render_mipmap_main.cpp
 *
 *	@brief	ミップマッピングのサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/render.hpp>
#include <bksge/core/math.hpp>
#include <bksge/fnd/cmath.hpp>
#include <bksge/fnd/iterator/size.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/memory.hpp>
#include <bksge/fnd/cstdint.hpp>
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
		"layout (location = 1) in vec2 aTexCoord;				\n"
		"														\n"
		"layout (location = 0) out vec2 vTexCoord;				\n"
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
		"	vTexCoord   = aTexCoord;							\n"
		"}														\n"
	;

	static char const* fs_source =
		"#version 420											\n"
		"#extension GL_ARB_separate_shader_objects : enable		\n"
		"														\n"
		"layout (location = 0) in vec2 vTexCoord;				\n"
		"														\n"
		"layout (location = 0) out vec4 oColor;					\n"
		"														\n"
		"layout (binding = 1) uniform sampler2D uSampler2D;		\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	oColor = texture(uSampler2D, vTexCoord);			\n"
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
		"    float3 pos : POSITION;						\n"
		"    float2 uv : TEXCOORD;						\n"
		"};												\n"
		"												\n"
		"struct VS_OUTPUT								\n"
		"{												\n"
		"    float4 pos : SV_POSITION;					\n"
		"    float2 uv : TEXCOORD;						\n"
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
		"	output.uv = input.uv;						\n"
		"	return output;								\n"
		"}												\n"
	;

	static char const* ps_source =
		"struct PS_INPUT								\n"
		"{												\n"
		"    float4 pos : SV_POSITION;					\n"
		"    float2 uv : TEXCOORD;						\n"
		"};												\n"
		"												\n"
		"Texture2D uTexture : register(t0);				\n"
		"SamplerState uSampler : register(s0);			\n"
		"												\n"
		"float4 main(PS_INPUT input) : SV_TARGET		\n"
		"{												\n"
		"	return uTexture.Sample(uSampler, input.uv);	\n"
		"}												\n"
	;

	static bksge::Shader const shader
	{
		{ bksge::ShaderStage::kVertex,   vs_source },
		{ bksge::ShaderStage::kFragment, ps_source },
	};

	return &shader;
}

class Plane
{
public:
	Plane()
	{
		m_model = bksge::Matrix4x4f::Identity();
	}

	void SetProjectionMatrix(bksge::Matrix4x4f const& mat)
	{
		m_projection = mat;
	}

	void SetViewMatrix(bksge::Matrix4x4f const& mat)
	{
		m_view = mat;
	}

	void SetTexture(bksge::Texture const& texture)
	{
		m_texture = texture;
	}

	void SetMipFilter(bksge::MipmapMode mip_filter)
	{
		m_sampler.SetMipFilter(mip_filter);
	}

	void Draw(bksge::Renderer* renderer, bksge::Shader const* shader)
	{
		m_shader_parameter.SetParameter("uProjection", m_projection);
		m_shader_parameter.SetParameter("uView", m_view);
		m_shader_parameter.SetParameter("uModel", m_model);

		m_shader_parameter.SetParameter("uSampler", m_sampler);
		m_shader_parameter.SetParameter("uTexture", m_texture);
		bksge::SampledTexture sampler2d(m_sampler, m_texture);
		m_shader_parameter.SetParameter("uSampler2D", sampler2d);

		renderer->Render(
			GetGeometry(),
			*shader,
			m_shader_parameter,
			m_render_state);
	}

private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition, bksge::VTexCoord> const vertices[] =
		{
			{{{-5.0,  5.0, 0.0}}, {{0, 0}}},
			{{{-5.0, -5.0, 0.0}}, {{0, 1}}},
			{{{ 5.0,  5.0, 0.0}}, {{1, 0}}},
			{{{ 5.0, -5.0, 0.0}}, {{1, 1}}},
		};
		static bksge::uint16_t const indices[] =
		{
			0, 1, 2,
			2, 1, 3,
		};

		static bksge::Geometry const geometry(
			bksge::PrimitiveTopology::kTriangles, vertices, indices);

		return geometry;
	}

private:
	bksge::ShaderParameterMap	m_shader_parameter;
	bksge::RenderState			m_render_state;
	bksge::Matrix4x4f			m_projection;
	bksge::Matrix4x4f			m_view;
	bksge::Matrix4x4f			m_model;
	bksge::Sampler				m_sampler;
	bksge::Texture				m_texture;
};

static bksge::Texture
MakeTexture(bksge::uint32_t width, bksge::uint32_t height, bksge::size_t mipmap_count)
{
	auto const bytes = bksge::render::GetMipmappedSizeInBytes(
		bksge::TextureFormat::kRGBA_U8,
		width, height,
		mipmap_count);
	bksge::vector<bksge::uint8_t> pixels(bytes);
	auto* p = pixels.data();

	bksge::uint32_t w = width;
	bksge::uint32_t h = height;
	for (bksge::size_t level = 0; level < mipmap_count; ++level)
	{
		for (bksge::uint32_t y = 0; y < h; ++y)
		{
			for (bksge::uint32_t x = 0; x < w; ++x)
			{
				bksge::uint8_t const c = ((y/1) % 2) == ((x/1) % 2) ? 255 : 128;
				auto index = level % 6 + 1;
				*p++ = (((index / 1) % 2) == 0) ? 0 : c;
				*p++ = (((index / 2) % 2) == 0) ? 0 : c;
				*p++ = (((index / 4) % 2) == 0) ? 0 : c;
				*p++ = 255;
			}
		}

		w = bksge::max(w / 2, 1u);
		h = bksge::max(h / 2, 1u);
	}

	return bksge::Texture(
		bksge::TextureFormat::kRGBA_U8,
		{ width, height },
		mipmap_count,
		pixels.data());
}

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
			new bksge::Window(extent, "sample_render_mipmap - D3D11"));
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
			new bksge::Window(extent, "sample_render_mipmap - D3D12"));
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
			new bksge::Window(extent, "sample_render_mipmap - GL"));
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
			new bksge::Window(extent, "sample_render_mipmap - Vulkan"));
		windows.push_back(window);

		bksge::shared_ptr<bksge::VulkanRenderer> renderer(
			new bksge::VulkanRenderer(*window));
		renderers.push_back(renderer);

		shaders.push_back(GetGLSLShader());
	}
#endif

	bksge::RenderPassInfo render_pass_info;
	render_pass_info.viewport().SetRect({bksge::Vector2f{0, 0}, extent});
	render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});

	auto const projection =
		bksge::Matrix4x4f::MakePerspective(
			bksge::degrees_to_radians(45.0f),
			800.0f / 600.0f,
			0.1f,
			100.0f);

	auto const view =
		bksge::Matrix4x4f::MakeLookAt(
			bksge::Vector3f(0.0f, -1.0f, -0.2f),
			bksge::Vector3f(0.0f,  0.0f,  0.0f),
			bksge::Vector3f(0.0f,  1.0f,  0.0f));

	Plane plane;
	plane.SetProjectionMatrix(projection);
	plane.SetViewMatrix(view);
	plane.SetTexture(MakeTexture(1024, 1024, 11));

	bksge::MipmapMode const mip_filter_tbl[] =
	{
		bksge::MipmapMode::kLinear,
		bksge::MipmapMode::kNearest,
		bksge::MipmapMode::kDisable,
	};

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

		plane.SetMipFilter(mip_filter_tbl[(count / 120) % bksge::size(mip_filter_tbl)]);

		int i = 0;
		for (auto& renderer : renderers)
		{
			renderer->Begin();
			renderer->BeginRenderPass(render_pass_info);

			plane.Draw(renderer.get(), shaders[i]);

			renderer->EndRenderPass();
			renderer->End();

			++i;
		}

		++count;
	}

	return 0;
}
