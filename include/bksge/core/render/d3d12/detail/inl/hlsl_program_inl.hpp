/**
 *	@file	hlsl_program_inl.hpp
 *
 *	@brief	HlslProgram クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_HLSL_PROGRAM_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_HLSL_PROGRAM_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/hlsl_program.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_shader.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d12/detail/input_layout.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_constant_buffer.hpp>
#include <bksge/core/render/d3d12/detail/descriptor_heaps.hpp>
#include <bksge/core/render/d3d12/detail/command_list.hpp>
#include <bksge/core/render/d3d12/detail/root_signature.hpp>
#include <bksge/core/render/d3d12/detail/root_parameters.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_texture.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_sampler.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/shader_stage.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/utility/move.hpp>

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
		bksge::string const& source = it.second;

		bksge::unique_ptr<HlslShaderBase> hlsl_shader;
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

		hlsl_shader->CreateHlslConstantBuffers(/*device,*/ &m_hlsl_constant_buffers);
		hlsl_shader->CreateHlslTextures(&m_hlsl_textures);
		hlsl_shader->CreateHlslSamplers(&m_hlsl_samplers);

		m_shader_map[stage] = bksge::move(hlsl_shader);
	}

	m_root_parameters =
		bksge::make_unique<RootParameters>(m_shader_map);

	m_root_signature =
		bksge::make_unique<RootSignature>(device, *m_root_parameters);
}

BKSGE_INLINE
HlslProgram::~HlslProgram()
{
}

BKSGE_INLINE void
HlslProgram::SetDescriptorTables(
	CommandList* command_list,
	DescriptorHeaps* descriptor_heaps)
{
	descriptor_heaps->SetDescriptorTables(command_list, *m_root_parameters);
}

BKSGE_INLINE void
HlslProgram::UpdateParameters(
	Device* device,
	DescriptorHeaps* descriptor_heaps,
	ResourcePool* resource_pool,
	bksge::ShaderParameterMap const& shader_parameter_map)
{
	for (auto&& hlsl_constant_buffer : m_hlsl_constant_buffers)
	{
		hlsl_constant_buffer->UpdateParameters(
			device,
			descriptor_heaps,
			resource_pool,
			shader_parameter_map);
	}

	for (auto&& hlsl_texture : m_hlsl_textures)
	{
		hlsl_texture->UpdateParameters(
			device,
			descriptor_heaps,
			resource_pool,
			shader_parameter_map);
	}

	for (auto&& hlsl_sampler : m_hlsl_samplers)
	{
		hlsl_sampler->UpdateParameters(
			device,
			descriptor_heaps,
			resource_pool,
			shader_parameter_map);
	}
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

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_HLSL_PROGRAM_INL_HPP
