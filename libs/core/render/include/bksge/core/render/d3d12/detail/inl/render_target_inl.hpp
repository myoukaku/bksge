/**
 *	@file	render_target_inl.hpp
 *
 *	@brief	RenderTarget クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_RENDER_TARGET_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_RENDER_TARGET_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/render_target.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/dxgi/dxgi_swap_chain.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
RenderTarget::RenderTarget(
	Device* device,
	DXGISwapChain* swap_chain)
{
	auto const frame_buffer_count = swap_chain->GetBufferCount();

	// Create descriptor heaps.
	{
		// Describe and create a render target view (RTV) descriptor heap.
		::D3D12_DESCRIPTOR_HEAP_DESC desc ={};
		desc.NumDescriptors = frame_buffer_count;
		desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		m_descriptor_heap = device->CreateDescriptorHeap(desc);

		m_descriptor_size =
			device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	// Create frame resources.
	{
		::D3D12_CPU_DESCRIPTOR_HANDLE handle(
			m_descriptor_heap->GetCPUDescriptorHandleForHeapStart());

		m_resource.resize(frame_buffer_count);
		// Create a RTV for each frame.
		for (::UINT i = 0; i < frame_buffer_count; i++)
		{
			swap_chain->GetBuffer(i, IID_PPV_ARGS(&m_resource[i]));
			device->CreateRenderTargetView(m_resource[i].Get(), nullptr, handle);
			handle.ptr += m_descriptor_size;
		}
	}
}

BKSGE_INLINE
RenderTarget::~RenderTarget()
{
}

BKSGE_INLINE ID3D12ResourceN*
RenderTarget::GetResource(::UINT index)
{
	return m_resource[index].Get();
}

BKSGE_INLINE ::D3D12_CPU_DESCRIPTOR_HANDLE
RenderTarget::GetHandle(::UINT index) const
{
	::D3D12_CPU_DESCRIPTOR_HANDLE handle(
		m_descriptor_heap->GetCPUDescriptorHandleForHeapStart());
	handle.ptr += m_descriptor_size * index;
	return handle;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_RENDER_TARGET_INL_HPP
