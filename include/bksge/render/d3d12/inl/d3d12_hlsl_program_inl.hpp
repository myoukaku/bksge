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
	m_cbv_descriptor_handle_incrementsize =
		device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

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

		{
			auto cbs = hlsl_shader->CreateConstantBuffers(device);
			for (auto&& cb : cbs)
			{
				m_constant_buffers.push_back(std::move(cb));
			}
		}

		m_shader_map[stage] = std::move(hlsl_shader);
	}

	if (!m_constant_buffers.empty())
	{
		// Create descriptor heap.
		::D3D12_DESCRIPTOR_HEAP_DESC desc{};
		desc.NumDescriptors = static_cast<::UINT>(m_constant_buffers.size());
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

		m_descriptor_heap = device->CreateDescriptorHeap(desc);

		// Create ConstantBufferView.
		{
			::D3D12_CPU_DESCRIPTOR_HANDLE handle =
				m_descriptor_heap->GetCPUDescriptorHandleForHeapStart();
			for (auto&& constant_buffer : m_constant_buffers)
			{
				constant_buffer->CreateConstantBufferView(device, handle);
				handle.ptr += m_cbv_descriptor_handle_incrementsize;
			}
		}
	}

	m_root_signature =
		bksge::make_unique<D3D12RootSignature>(device, m_shader_map);
}

BKSGE_INLINE
D3D12HLSLProgram::~D3D12HLSLProgram()
{
}

BKSGE_INLINE void
D3D12HLSLProgram::UpdateParameters(
	ShaderParameterMap const& shader_parameter_map)
{
	for (auto&& constant_buffer : m_constant_buffers)
	{
		constant_buffer->UpdateParameters(shader_parameter_map);
	}
}

BKSGE_INLINE void
D3D12HLSLProgram::SetEnable(D3D12CommandList* command_list)
{
	if (m_descriptor_heap)
	{
		ID3D12DescriptorHeap* heaps[] = { m_descriptor_heap.Get() };
		command_list->SetDescriptorHeaps(_countof(heaps), heaps);

		auto handle = m_descriptor_heap->GetGPUDescriptorHandleForHeapStart();
		for (::UINT i = 0; i < m_root_signature->GetRootParameterCount(); ++i)
		{
			command_list->SetGraphicsRootDescriptorTable(
				i, handle);
			handle.ptr += m_cbv_descriptor_handle_incrementsize;
		}
	}
	//else
	//{
	//	ID3D12DescriptorHeap* heaps[] = { m_descriptor_heap.Get() };
	//	command_list->SetDescriptorHeaps(0, heaps);
	//}
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
D3D12HLSLProgram::GetShaderBytecode(ShaderStage stage) const
{
	auto const& shader = m_shader_map.at(stage);
	if (shader)
	{
		return shader->GetBytecode();
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

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_HLSL_PROGRAM_INL_HPP
