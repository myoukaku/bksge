/**
 *	@file	constant_buffer_descriptor_inl.hpp
 *
 *	@brief	ConstantBufferDescriptor クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_CONSTANT_BUFFER_DESCRIPTOR_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_CONSTANT_BUFFER_DESCRIPTOR_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/constant_buffer_descriptor.hpp>
#include <bksge/render/d3d12/detail/constant_buffer.hpp>
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d12/detail/hlsl_program.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
ConstantBufferDescriptor::ConstantBufferDescriptor(
	Device* device,
	ConstantBuffers const& constant_buffers,
	::UINT root_parameter_count)
{
	m_cbv_descriptor_handle_incrementsize =
		device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	if (!constant_buffers.empty())
	{
		// Create descriptor heap.
		::D3D12_DESCRIPTOR_HEAP_DESC desc{};
		desc.NumDescriptors = static_cast<::UINT>(constant_buffers.size());
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

		m_descriptor_heap = device->CreateDescriptorHeap(desc);

		// Create ConstantBufferView.
		{
			::D3D12_CPU_DESCRIPTOR_HANDLE handle =
				m_descriptor_heap->GetCPUDescriptorHandleForHeapStart();
			for (auto&& constant_buffer : constant_buffers)
			{
				constant_buffer->CreateConstantBufferView(device, handle);
				handle.ptr += m_cbv_descriptor_handle_incrementsize;
			}
		}
	}

	m_root_parameter_count = root_parameter_count;
}

BKSGE_INLINE
ConstantBufferDescriptor::~ConstantBufferDescriptor()
{
}

BKSGE_INLINE void
ConstantBufferDescriptor::SetEnable(CommandList* command_list)
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

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_CONSTANT_BUFFER_DESCRIPTOR_INL_HPP
