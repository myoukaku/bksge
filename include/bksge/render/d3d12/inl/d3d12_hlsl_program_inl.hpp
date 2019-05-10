/**
 *	@file	d3d12_hlsl_program_inl.hpp
 *
 *	@brief	D3D12HLSLProgram クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_HLSL_PROGRAM_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_HLSL_PROGRAM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_hlsl_program.hpp>
#include <bksge/render/d3d12/d3d12_hlsl_shader.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12_input_layout.hpp>
#include <bksge/render/d3d12/d3d12_constant_buffer.hpp>
#include <bksge/render/d3d12/d3d12_command_list.hpp>
#include <bksge/render/d3d12/d3d12_root_signature.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/shader_stage.hpp>
#include <bksge/memory/make_unique.hpp>
#include <string>
#include <memory>
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12HLSLProgram::D3D12HLSLProgram(D3D12Device* device, Shader const& shader)
{
	for (auto&& it : shader.program_map())
	{
		ShaderStage const stage = it.first;
		std::string const& source = it.second;

		std::unique_ptr<D3D12HLSLShaderBase> hlsl_shader;
		switch (stage)
		{
		case ShaderStage::kVertex:
			hlsl_shader = bksge::make_unique<D3D12HLSLVertexShader>();
			break;
		case ShaderStage::kGeometry:
			break;
		case ShaderStage::kFragment:
			hlsl_shader = bksge::make_unique<D3D12HLSLPixelShader>();
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
			m_input_layout = hlsl_shader->CreateInputLayout();
		}

		m_shader_map[stage] = std::move(hlsl_shader);
	}

	m_root_signature =
		bksge::make_unique<D3D12RootSignature>(device, m_shader_map);
}

BKSGE_INLINE auto
D3D12HLSLProgram::CreateConstantBuffers(D3D12Device* device)
-> D3D12ConstantBuffers
{
	D3D12ConstantBuffers result;

	for (auto&& it : m_shader_map)
	{
		auto cbs = it.second->CreateConstantBuffers(device);
		for (auto&& cb : cbs)
		{
			result.push_back(std::move(cb));
		}
	}
	return result;
}

BKSGE_INLINE
D3D12HLSLProgram::~D3D12HLSLProgram()
{
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
D3D12HLSLProgram::GetShaderBytecode(ShaderStage stage) const
{
	auto it = m_shader_map.find(stage);
	if (it != m_shader_map.end())
	{
		return it->second->GetBytecode();
	}
	else
	{
		return {};
	}
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
D3D12HLSLProgram::GetVertexShaderBytecode(void) const
{
	return GetShaderBytecode(ShaderStage::kVertex);
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
D3D12HLSLProgram::GetPixelShaderBytecode(void) const
{
	return GetShaderBytecode(ShaderStage::kFragment);
}

BKSGE_INLINE ::D3D12_INPUT_LAYOUT_DESC
D3D12HLSLProgram::GetInputLayout(void) const
{
	if (m_input_layout)
	{
		return *m_input_layout;
	}

	return {};
}

BKSGE_INLINE ::ID3D12RootSignature*
D3D12HLSLProgram::GetRootSignature(void) const
{
	if (m_root_signature)
	{
		return m_root_signature->Get();
	}

	return nullptr;
}

BKSGE_INLINE ::UINT
D3D12HLSLProgram::GetRootParameterCount(void) const
{
	if (m_root_signature)
	{
		return m_root_signature->GetRootParameterCount();
	}

	return 0u;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_HLSL_PROGRAM_INL_HPP
