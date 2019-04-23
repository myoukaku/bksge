﻿/**
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
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <bksge/render/d3d_common/dxgi.hpp>
#include <utility>
#include <vector>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12Device::D3D12Device(std::vector<ComPtr<::IDXGIAdapter1>> const& adapters)
{
	::HRESULT hr = S_OK;

	for (auto& adapter : adapters)
	{
		::D3D_FEATURE_LEVEL const feature_level_tbl[] =
		{
			D3D_FEATURE_LEVEL_12_1,
			D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		bool scceeded = false;
		for (auto feature_level : feature_level_tbl)
		{
			hr = ::D3D12CreateDevice(
				adapter.Get(),
				feature_level,
				IID_PPV_ARGS(&m_device));

			if (SUCCEEDED(hr))
			{
				scceeded = true;
				m_feature_level = feature_level;
				break;
			}
		}

		if (scceeded)
		{
			break;
		}
	}

	ThrowIfFailed(hr);
}

BKSGE_INLINE
D3D12Device::~D3D12Device()
{
}

BKSGE_INLINE ComPtr<::ID3D12CommandQueue>
D3D12Device::CreateCommandQueue(
	::D3D12_COMMAND_QUEUE_DESC const& desc)
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
	::D3D12_COMMAND_LIST_TYPE type)
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
	::D3D12_COMMAND_LIST_TYPE type,
	::ID3D12CommandAllocator* command_allocator)
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
	::D3D12_DESCRIPTOR_HEAP_DESC const& desc)
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
	::D3D12_DESCRIPTOR_HEAP_TYPE descriptor_heap_type)
{
	return m_device->GetDescriptorHandleIncrementSize(descriptor_heap_type);
}

BKSGE_INLINE void
D3D12Device::CreateRenderTargetView(
	::ID3D12Resource*                      resource,
	::D3D12_RENDER_TARGET_VIEW_DESC const* desc,
	::D3D12_CPU_DESCRIPTOR_HANDLE          dest_descriptor)
{
	m_device->CreateRenderTargetView(
		resource,
		desc,
		dest_descriptor);
}

BKSGE_INLINE ComPtr<::ID3D12Fence>
D3D12Device::CreateFence(
	::UINT64            initial_value,
	::D3D12_FENCE_FLAGS flags)
{
	ComPtr<::ID3D12Fence> fence;
	ThrowIfFailed(
		m_device->CreateFence(
			initial_value,
			flags,
			IID_PPV_ARGS(&fence)));
	return std::move(fence);
}

BKSGE_INLINE ComPtr<::ID3D12RootSignature>
D3D12Device::CreateRootSignature(
	::UINT      node_mask,
	void const* blob_with_root_signature,
	::SIZE_T    blob_length_in_bytes)
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
	::D3D12_GRAPHICS_PIPELINE_STATE_DESC const& desc)
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
	::D3D12_HEAP_PROPERTIES const* heap_properties,
	::D3D12_HEAP_FLAGS             heap_flags,
	::D3D12_RESOURCE_DESC const*   desc,
	::D3D12_RESOURCE_STATES        initial_resource_state,
	::D3D12_CLEAR_VALUE const*     optimized_clearvalue)
{
	ComPtr<::ID3D12Resource> resource;
	ThrowIfFailed(
		m_device->CreateCommittedResource(
			heap_properties,
			heap_flags,
			desc,
			initial_resource_state,
			optimized_clearvalue,
			IID_PPV_ARGS(&resource)));
	return std::move(resource);
}

BKSGE_INLINE void
D3D12Device::CreateConstantBufferView(
	::D3D12_CONSTANT_BUFFER_VIEW_DESC const* desc,
	::D3D12_CPU_DESCRIPTOR_HANDLE            dest_descriptor)
{
	m_device->CreateConstantBufferView(desc, dest_descriptor);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_DEVICE_INL_HPP
