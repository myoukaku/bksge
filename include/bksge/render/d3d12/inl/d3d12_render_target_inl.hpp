/**
 *	@file	d3d12_render_target_inl.hpp
 *
 *	@brief	D3D12RenderTarget クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_RENDER_TARGET_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_RENDER_TARGET_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_render_target.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12_swap_chain.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12RenderTarget::D3D12RenderTarget(
	D3D12Device* device,
	D3D12SwapChain* swap_chain)
{
	// Create descriptor heaps.
	{
		// Describe and create a render target view (RTV) descriptor heap.
		::D3D12_DESCRIPTOR_HEAP_DESC desc ={};
		desc.NumDescriptors = 2/*FrameCount*/;
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

		// Create a RTV for each frame.
		for (::UINT n = 0; n < 2/*FrameCount*/; n++)
		{
			swap_chain->GetBuffer(n, IID_PPV_ARGS(&m_resource[n]));
			device->CreateRenderTargetView(m_resource[n].Get(), nullptr, handle);
			handle.ptr += m_descriptor_size;
		}
	}
}

BKSGE_INLINE
D3D12RenderTarget::~D3D12RenderTarget()
{
}

BKSGE_INLINE ::ID3D12Resource*
D3D12RenderTarget::GetResource(::UINT index)
{
	return m_resource[index].Get();
}

BKSGE_INLINE ::D3D12_CPU_DESCRIPTOR_HANDLE
D3D12RenderTarget::GetHandle(::UINT index)
{
	::D3D12_CPU_DESCRIPTOR_HANDLE handle(
		m_descriptor_heap->GetCPUDescriptorHandleForHeapStart());
	handle.ptr += m_descriptor_size * index;
	return handle;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_RENDER_TARGET_INL_HPP
