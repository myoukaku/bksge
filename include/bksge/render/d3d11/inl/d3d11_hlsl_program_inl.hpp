/**
 *	@file	d3d11_hlsl_program_inl.hpp
 *
 *	@brief	D3D11HLSLProgram クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_HLSL_PROGRAM_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_HLSL_PROGRAM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_hlsl_program.hpp>
#include <bksge/render/d3d11/d3d11_hlsl_shader.hpp>
#include <bksge/render/d3d11/d3d11_geometry.hpp>
//#include <bksge/render/d3d11/d3d11_renderer.hpp>
#include <bksge/render/d3d11/d3d11_device_context.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/shader_stage.hpp>
#include <bksge/memory/make_unique.hpp>
#include <memory>
#include <string>
#include <utility>	// std::move

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11HLSLProgram::D3D11HLSLProgram(D3D11Device* device, Shader const& shader)
{
	for (auto&& it : shader)
	{
		ShaderStage const stage = it.first;
		std::string const& source = it.second;

		std::unique_ptr<D3D11HLSLShaderBase> hlsl_shader;
		switch (stage)
		{
		case ShaderStage::kVertex:
			hlsl_shader = bksge::make_unique<D3D11HLSLVertexShader>();
			break;
		case ShaderStage::kGeometry:
			break;
		case ShaderStage::kFragment:
			hlsl_shader = bksge::make_unique<D3D11HLSLPixelShader>();
			break;
		case ShaderStage::kTessellationControl:
			break;
		case ShaderStage::kTessellationEvaluation:
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

		if (stage == ShaderStage::kVertex)
		{
			m_input_layout = hlsl_shader->CreateInputLayout(device);
		}

		m_shaders.push_back(std::move(hlsl_shader));
	}
}

BKSGE_INLINE
D3D11HLSLProgram::~D3D11HLSLProgram()
{
}

BKSGE_INLINE void
D3D11HLSLProgram::Render(
	D3D11DeviceContext* device_context,
	D3D11Geometry const* geometry,
	ShaderParameterMap const& shader_parameter_map)
{
	device_context->IASetInputLayout(m_input_layout.Get());

	for (auto& shader : m_shaders)
	{
		shader->SetEnable(device_context);
		shader->LoadParameters(device_context, shader_parameter_map);
	}

	geometry->Draw(device_context);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_HLSL_PROGRAM_INL_HPP
