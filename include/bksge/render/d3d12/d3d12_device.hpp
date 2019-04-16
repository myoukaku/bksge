/**
 *	@file	d3d12_device.hpp
 *
 *	@brief	D3D12Device クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_DEVICE_HPP
#define BKSGE_RENDER_D3D12_D3D12_DEVICE_HPP

#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d12/d3d12_adapter.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief	D3D12 デバイス
 */
class D3D12Device
{
public:
	explicit D3D12Device(std::vector<D3D12Adapter> const& adapters);

	~D3D12Device();

	ComPtr<::ID3D12CommandQueue> CreateCommandQueue(
		D3D12_COMMAND_QUEUE_DESC const& desc);

	ComPtr<::ID3D12CommandAllocator> CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE type);

	ComPtr<::ID3D12GraphicsCommandList> CreateGraphicsCommandList(
		D3D12_COMMAND_LIST_TYPE type,
		ID3D12CommandAllocator* command_allocator);

	ComPtr<::ID3D12DescriptorHeap> CreateDescriptorHeap(
		D3D12_DESCRIPTOR_HEAP_DESC const& desc);

	UINT GetDescriptorHandleIncrementSize(
		D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType);

	void CreateRenderTargetView(
		ID3D12Resource*                      pResource,
		const D3D12_RENDER_TARGET_VIEW_DESC* pDesc,
		D3D12_CPU_DESCRIPTOR_HANDLE          DestDescriptor
	);

	ComPtr<::ID3D12Fence> CreateFence(
		UINT64            InitialValue,
		D3D12_FENCE_FLAGS Flags);

	ComPtr<::ID3D12RootSignature> CreateRootSignature(
		UINT        node_mask,
		void const* blob_with_root_signature,
		SIZE_T      blob_length_in_bytes);

	ComPtr<::ID3D12PipelineState> CreateGraphicsPipelineState(
		D3D12_GRAPHICS_PIPELINE_STATE_DESC const& desc);

	ComPtr<::ID3D12Resource> CreateCommittedResource(
		const D3D12_HEAP_PROPERTIES *pHeapProperties,
		D3D12_HEAP_FLAGS            HeapFlags,
		const D3D12_RESOURCE_DESC   *pDesc,
		D3D12_RESOURCE_STATES       InitialResourceState,
		const D3D12_CLEAR_VALUE     *pOptimizedClearValue);

private:
	ComPtr<::ID3D12Device> m_device;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_device_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_DEVICE_HPP
