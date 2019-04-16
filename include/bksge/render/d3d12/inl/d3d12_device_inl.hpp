/**
 *	@file	d3d12_device_inl.hpp
 *
 *	@brief	D3D12Device クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_DEVICE_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_DEVICE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12_adapter.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>
#include <utility>
#include <vector>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12Device::D3D12Device(std::vector<D3D12Adapter> const& adapters)
{
	m_device = adapters[0].CreateDevice();
}

BKSGE_INLINE
D3D12Device::~D3D12Device()
{
}

BKSGE_INLINE ComPtr<::ID3D12CommandQueue>
D3D12Device::CreateCommandQueue(
	D3D12_COMMAND_QUEUE_DESC const& desc)
{
	ComPtr<::ID3D12CommandQueue> command_queue;
	ThrowIfFailed(
		m_device->CreateCommandQueue(
			&desc,
			IID_PPV_ARGS(&command_queue)));
	return std::move(command_queue);
}

BKSGE_INLINE ComPtr<::ID3D12CommandAllocator>
D3D12Device::CreateCommandAllocator(
	D3D12_COMMAND_LIST_TYPE type)
{
	ComPtr<::ID3D12CommandAllocator> command_allocator;
	ThrowIfFailed(
		m_device->CreateCommandAllocator(
			type,
			IID_PPV_ARGS(&command_allocator)));
	return std::move(command_allocator);
}

BKSGE_INLINE ComPtr<::ID3D12GraphicsCommandList>
D3D12Device::CreateGraphicsCommandList(
	D3D12_COMMAND_LIST_TYPE type,
	ID3D12CommandAllocator* command_allocator)
{
	ComPtr<::ID3D12GraphicsCommandList> command_list;
	ThrowIfFailed(
		m_device->CreateCommandList(
			0,
			type,
			command_allocator,
			nullptr,
			IID_PPV_ARGS(&command_list)));
	return std::move(command_list);
}

BKSGE_INLINE ComPtr<::ID3D12DescriptorHeap>
D3D12Device::CreateDescriptorHeap(
	D3D12_DESCRIPTOR_HEAP_DESC const& desc)
{
	ComPtr<::ID3D12DescriptorHeap> descriptor_heap;
	ThrowIfFailed(
		m_device->CreateDescriptorHeap(
			&desc,
			IID_PPV_ARGS(&descriptor_heap)));
	return std::move(descriptor_heap);
}

BKSGE_INLINE UINT
D3D12Device::GetDescriptorHandleIncrementSize(
	D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType)
{
	return m_device->GetDescriptorHandleIncrementSize(DescriptorHeapType);
}

BKSGE_INLINE void
D3D12Device::CreateRenderTargetView(
	ID3D12Resource                      *pResource,
	const D3D12_RENDER_TARGET_VIEW_DESC *pDesc,
	D3D12_CPU_DESCRIPTOR_HANDLE         DestDescriptor)
{
	m_device->CreateRenderTargetView(
		pResource,
		pDesc,
		DestDescriptor);
}

BKSGE_INLINE ComPtr<::ID3D12Fence>
D3D12Device::CreateFence(
	UINT64            InitialValue,
	D3D12_FENCE_FLAGS Flags)
{
	ComPtr<::ID3D12Fence> fence;
	ThrowIfFailed(
		m_device->CreateFence(
			InitialValue,
			Flags,
			IID_PPV_ARGS(&fence)));
	return std::move(fence);
}

BKSGE_INLINE ComPtr<::ID3D12RootSignature>
D3D12Device::CreateRootSignature(
	UINT        node_mask,
	void const* blob_with_root_signature,
	SIZE_T      blob_length_in_bytes)
{
	ComPtr<::ID3D12RootSignature> root_signature;
	ThrowIfFailed(
		m_device->CreateRootSignature(
			node_mask,
			blob_with_root_signature,
			blob_length_in_bytes,
			IID_PPV_ARGS(&root_signature)));
	return std::move(root_signature);
}

BKSGE_INLINE ComPtr<::ID3D12PipelineState>
D3D12Device::CreateGraphicsPipelineState(
	D3D12_GRAPHICS_PIPELINE_STATE_DESC const& desc)
{
	ComPtr<::ID3D12PipelineState> pipeline_state;
	ThrowIfFailed(
		m_device->CreateGraphicsPipelineState(
			&desc,
			IID_PPV_ARGS(&pipeline_state)));
	return std::move(pipeline_state);
}

BKSGE_INLINE ComPtr<::ID3D12Resource>
D3D12Device::CreateCommittedResource(
	const D3D12_HEAP_PROPERTIES *pHeapProperties,
	D3D12_HEAP_FLAGS            HeapFlags,
	const D3D12_RESOURCE_DESC   *pDesc,
	D3D12_RESOURCE_STATES       InitialResourceState,
	const D3D12_CLEAR_VALUE     *pOptimizedClearValue)
{
	ComPtr<::ID3D12Resource>	resource;
	ThrowIfFailed(
		m_device->CreateCommittedResource(
			pHeapProperties,
			HeapFlags,
			pDesc,
			InitialResourceState,
			pOptimizedClearValue,
			IID_PPV_ARGS(&resource)));
	return std::move(resource);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_DEVICE_INL_HPP
