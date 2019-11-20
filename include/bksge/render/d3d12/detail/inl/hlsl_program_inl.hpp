/**
 *	@file	hlsl_program_inl.hpp
 *
 *	@brief	HlslProgram クラスの実装
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
#include <bksge/render/d3d12/detail/descriptor_heap.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d12/detail/root_signature.hpp>
#include <bksge/render/d3d12/detail/root_parameters.hpp>
#include <bksge/render/d3d12/detail/hlsl_texture.hpp>
#include <bksge/render/d3d12/detail/hlsl_sampler.hpp>
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
			m_input_layout = hlsl_shader->CreateInputLayout();
		}

		hlsl_shader->CreateConstantBuffers(device, &m_constant_buffers);
		hlsl_shader->CreateHlslTextures(device, &m_hlsl_textures);
		hlsl_shader->CreateHlslSamplers(device, &m_hlsl_samplers);

		m_shader_map[stage] = std::move(hlsl_shader);
	}

	m_root_parameters =
		bksge::make_unique<RootParameters>(m_shader_map);

	m_descriptor_heap =
		bksge::make_unique<DescriptorHeap>(
			device,
			*m_root_parameters,
			m_constant_buffers,
			m_hlsl_textures,
			m_hlsl_samplers);

	m_root_signature =
		bksge::make_unique<RootSignature>(device, *m_root_parameters);
}

BKSGE_INLINE
HlslProgram::~HlslProgram()
{
}

BKSGE_INLINE void
HlslProgram::UpdateParameters(ResourceCache* resource_cache, bksge::ShaderParameterMap const& shader_parameter_map)
{
	for (auto&& constant_buffer : m_constant_buffers)
	{
		constant_buffer->UpdateParameters(shader_parameter_map);
	}

	for (auto&& hlsl_texture : m_hlsl_textures)
	{
		hlsl_texture->UpdateParameters(resource_cache, shader_parameter_map);
	}

	for (auto&& hlsl_sampler : m_hlsl_samplers)
	{
		hlsl_sampler->UpdateParameters(resource_cache, shader_parameter_map);
	}
}

BKSGE_INLINE void
HlslProgram::SetEnable(CommandList* command_list)
{
	m_descriptor_heap->SetEnable(command_list);
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
HlslProgram::GetShaderBytecode(bksge::ShaderStage stage) const
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
HlslProgram::GetVertexShaderBytecode(void) const
{
	return GetShaderBytecode(bksge::ShaderStage::kVertex);
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
HlslProgram::GetPixelShaderBytecode(void) const
{
	return GetShaderBytecode(bksge::ShaderStage::kFragment);
}

BKSGE_INLINE ::D3D12_INPUT_LAYOUT_DESC
HlslProgram::GetInputLayout(void) const
{
	if (m_input_layout)
	{
		return *m_input_layout;
	}

	return {};
}

BKSGE_INLINE ::ID3D12RootSignature*
HlslProgram::GetRootSignature(void) const
{
	if (m_root_signature)
	{
		return m_root_signature->Get();
	}

	return nullptr;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_PROGRAM_INL_HPP
