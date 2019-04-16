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
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/dxgi/dxgi.hpp>
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
	explicit D3D12Device(std::vector<ComPtr<::IDXGIAdapter1>> const& adapters);

	~D3D12Device();

	ComPtr<::ID3D12CommandQueue> CreateCommandQueue(
		::D3D12_COMMAND_QUEUE_DESC const& desc);

	ComPtr<::ID3D12CommandAllocator> CreateCommandAllocator(
		::D3D12_COMMAND_LIST_TYPE type);

	ComPtr<::ID3D12GraphicsCommandList> CreateGraphicsCommandList(
		::D3D12_COMMAND_LIST_TYPE type,
		::ID3D12CommandAllocator* command_allocator);

	ComPtr<::ID3D12DescriptorHeap> CreateDescriptorHeap(
		::D3D12_DESCRIPTOR_HEAP_DESC const& desc);

	UINT GetDescriptorHandleIncrementSize(
		::D3D12_DESCRIPTOR_HEAP_TYPE descriptor_heap_type);

	void CreateRenderTargetView(
		::ID3D12Resource*                      resource,
		::D3D12_RENDER_TARGET_VIEW_DESC const* desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE          dest_descriptor
	);

	ComPtr<::ID3D12Fence> CreateFence(
		::UINT64            initial_value,
		::D3D12_FENCE_FLAGS flags);

	ComPtr<::ID3D12RootSignature> CreateRootSignature(
		::UINT      node_mask,
		void const* blob_with_root_signature,
		::SIZE_T    blob_length_in_bytes);

	ComPtr<::ID3D12PipelineState> CreateGraphicsPipelineState(
		::D3D12_GRAPHICS_PIPELINE_STATE_DESC const& desc);

	ComPtr<::ID3D12Resource> CreateCommittedResource(
		::D3D12_HEAP_PROPERTIES const* heap_properties,
		::D3D12_HEAP_FLAGS             heap_flags,
		::D3D12_RESOURCE_DESC const*   desc,
		::D3D12_RESOURCE_STATES        initial_resource_state,
		::D3D12_CLEAR_VALUE const*     optimized_clear_value);

private:
	ComPtr<::ID3D12Device>	m_device;
	::D3D_FEATURE_LEVEL		m_feature_level;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_device_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_DEVICE_HPP
