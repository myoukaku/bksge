/**
 *	@file	d3d12_constant_buffer_descriptor_inl.hpp
 *
 *	@brief	D3D12BlendState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_CONSTANT_BUFFER_DESCRIPTOR_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_CONSTANT_BUFFER_DESCRIPTOR_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_constant_buffer_descriptor.hpp>
#include <bksge/render/d3d12/d3d12_constant_buffer.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12_command_list.hpp>
#include <bksge/render/d3d12/d3d12_hlsl_program.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12ConstantBufferDescriptor::D3D12ConstantBufferDescriptor(
	D3D12Device* device,
	D3D12HLSLProgram* hlsl_program)
{
	m_cbv_descriptor_handle_incrementsize =
		device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	m_constant_buffers = hlsl_program->CreateConstantBuffers(device);

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

	m_root_parameter_count = hlsl_program->GetRootParameterCount();
}

BKSGE_INLINE
D3D12ConstantBufferDescriptor::~D3D12ConstantBufferDescriptor()
{
}

BKSGE_INLINE void
D3D12ConstantBufferDescriptor::UpdateParameters(
	ShaderParameterMap const& shader_parameter_map)
{
	for (auto&& constant_buffer : m_constant_buffers)
	{
		constant_buffer->UpdateParameters(shader_parameter_map);
	}
}

BKSGE_INLINE void
D3D12ConstantBufferDescriptor::SetEnable(D3D12CommandList* command_list)
{
	if (m_descriptor_heap)
	{
		ID3D12DescriptorHeap* heaps[] = { m_descriptor_heap.Get() };
		command_list->SetDescriptorHeaps(_countof(heaps), heaps);

		auto handle = m_descriptor_heap->GetGPUDescriptorHandleForHeapStart();
		for (::UINT i = 0; i < m_root_parameter_count; ++i)
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

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_CONSTANT_BUFFER_DESCRIPTOR_INL_HPP
