/**
 *	@file	hlsl_program_inl.hpp
 *
 *	@brief	HlslProgram クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_PROGRAM_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_PROGRAM_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/hlsl_program.hpp>
#include <bksge/core/render/d3d11/detail/hlsl_shader.hpp>
#include <bksge/core/render/d3d11/detail/device_context.hpp>
//#include <bksge/core/render/d3d11/d3d11_renderer.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/shader_stage.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <memory>
#include <string>
#include <utility>	// std::move

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
HlslProgram::HlslProgram(Device* device, bksge::Shader const& shader)
{
	for (auto&& it : shader)
	{
		bksge::ShaderStage const stage = it.first;
		std::string const& source = it.second;

		std::unique_ptr<HlslShaderBase> hlsl_shader;
		switch (stage)
		{
		case bksge::ShaderStage::kVertex:
			hlsl_shader = bksge::make_unique<HlslVertexShader>();
			break;
		case bksge::ShaderStage::kGeometry:
			break;
		case bksge::ShaderStage::kFragment:
			hlsl_shader = bksge::make_unique<HlslPixelShader>();
			break;
		case bksge::ShaderStage::kTessellationControl:
			break;
		case bksge::ShaderStage::kTessellationEvaluation:
			break;
		default:
			break;
		}

		if (!hlsl_shader)
		{
			continue;
		}

		auto const ret = hlsl_shader->Compile(device, source);
		if (!ret)
		{
			continue;
		}

		if (stage == bksge::ShaderStage::kVertex)
		{
			m_input_layout = hlsl_shader->CreateInputLayout(device);
		}

		m_shaders.push_back(std::move(hlsl_shader));
	}
}

BKSGE_INLINE
HlslProgram::~HlslProgram()
{
}

BKSGE_INLINE void
HlslProgram::Render(
	ResourceCache* resource_cache,
	DeviceContext* device_context,
	bksge::ShaderParameterMap const& shader_parameter_map)
{
	device_context->IASetInputLayout(m_input_layout.Get());

	for (auto& shader : m_shaders)
	{
		shader->SetEnable(device_context);
		shader->LoadParameters(
			resource_cache,
			device_context,
			shader_parameter_map);
	}
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_PROGRAM_INL_HPP
