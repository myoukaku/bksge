﻿/**
 *	@file	hlsl_program_inl.hpp
 *
 *	@brief	HLSLProgram クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_PROGRAM_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_PROGRAM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/hlsl_program.hpp>
#include <bksge/render/d3d12/detail/hlsl_shader.hpp>
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d12/detail/input_layout.hpp>
#include <bksge/render/d3d12/detail/constant_buffer.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d12/detail/root_signature.hpp>
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

namespace d3d12
{

BKSGE_INLINE
HLSLProgram::HLSLProgram(Device* device, bksge::Shader const& shader)
{
	for (auto&& it : shader)
	{
		bksge::ShaderStage const stage = it.first;
		std::string const& source = it.second;

		std::unique_ptr<HLSLShaderBase> hlsl_shader;
		switch (stage)
		{
		case bksge::ShaderStage::kVertex:
			hlsl_shader = bksge::make_unique<HLSLVertexShader>();
			break;
		case bksge::ShaderStage::kGeometry:
			break;
		case bksge::ShaderStage::kFragment:
			hlsl_shader = bksge::make_unique<HLSLPixelShader>();
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
			m_input_layout = hlsl_shader->CreateInputLayout();
		}

		m_shader_map[stage] = std::move(hlsl_shader);
	}

	m_root_signature =
		bksge::make_unique<RootSignature>(device, m_shader_map);
}

BKSGE_INLINE auto
HLSLProgram::CreateConstantBuffers(Device* device)
-> ConstantBuffers
{
	ConstantBuffers result;

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
HLSLProgram::~HLSLProgram()
{
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
HLSLProgram::GetShaderBytecode(bksge::ShaderStage stage) const
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
HLSLProgram::GetVertexShaderBytecode(void) const
{
	return GetShaderBytecode(bksge::ShaderStage::kVertex);
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
HLSLProgram::GetPixelShaderBytecode(void) const
{
	return GetShaderBytecode(bksge::ShaderStage::kFragment);
}

BKSGE_INLINE ::D3D12_INPUT_LAYOUT_DESC
HLSLProgram::GetInputLayout(void) const
{
	if (m_input_layout)
	{
		return *m_input_layout;
	}

	return {};
}

BKSGE_INLINE ::ID3D12RootSignature*
HLSLProgram::GetRootSignature(void) const
{
	if (m_root_signature)
	{
		return m_root_signature->Get();
	}

	return nullptr;
}

BKSGE_INLINE ::UINT
HLSLProgram::GetRootParameterCount(void) const
{
	if (m_root_signature)
	{
		return m_root_signature->GetRootParameterCount();
	}

	return 0u;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_PROGRAM_INL_HPP