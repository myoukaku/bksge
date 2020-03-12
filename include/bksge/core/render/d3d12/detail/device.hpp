/**
 *	@file	device.hpp
 *
 *	@brief	Device クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_DEVICE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_DEVICE_HPP

#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/d3d_common/dxgi.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

/**
 *	@brief	D3D12 デバイス
 */
class Device
{
public:
	explicit Device(std::vector<ComPtr<IDXGIAdapterN>> const& adapters);

	~Device();

	ComPtr<::ID3D12CommandQueue> CreateCommandQueue(
		::D3D12_COMMAND_QUEUE_DESC const& desc);

	ComPtr<::ID3D12CommandAllocator> CreateCommandAllocator(
		::D3D12_COMMAND_LIST_TYPE type);

	ComPtr<ID3D12GraphicsCommandListN> CreateGraphicsCommandList(
		::D3D12_COMMAND_LIST_TYPE type,
		::ID3D12CommandAllocator* command_allocator);

	ComPtr<::ID3D12DescriptorHeap> CreateDescriptorHeap(
		::D3D12_DESCRIPTOR_HEAP_DESC const& desc);

	::UINT GetDescriptorHandleIncrementSize(
		::D3D12_DESCRIPTOR_HEAP_TYPE descriptor_heap_type);

	void GetCopyableFootprints(
		::D3D12_RESOURCE_DESC const*			resource_desc,
		::UINT									first_subresource,
		::UINT									num_subresources,
		::UINT64								base_offset,
		::D3D12_PLACED_SUBRESOURCE_FOOTPRINT*	layouts,
		::UINT*									num_rows,
		::UINT64*								row_size_in_bytes,
		::UINT64*								total_bytes);

	void CreateRenderTargetView(
		ID3D12ResourceN*                       resource,
		::D3D12_RENDER_TARGET_VIEW_DESC const* desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE          dest_descriptor);

	void CreateDepthStencilView(
		ID3D12ResourceN*                       resource,
		::D3D12_DEPTH_STENCIL_VIEW_DESC const* desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE          dest_descriptor);

	void CreateConstantBufferView(
		::D3D12_CONSTANT_BUFFER_VIEW_DESC const* desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE            dest_descriptor);

	void CreateShaderResourceView(
		ID3D12ResourceN*                         resource,
		::D3D12_SHADER_RESOURCE_VIEW_DESC const* desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE            dest_descriptor);

	void CreateSampler(
		::D3D12_SAMPLER_DESC const*   desc,
		::D3D12_CPU_DESCRIPTOR_HANDLE dest_descriptor);

	ComPtr<ID3D12FenceN> CreateFence(
		::UINT64            initial_value,
		::D3D12_FENCE_FLAGS flags);

	ComPtr<::ID3D12RootSignature> CreateRootSignature(
		::UINT      node_mask,
		void const* blob_with_root_signature,
		::SIZE_T    blob_length_in_bytes);

	ComPtr<::ID3D12PipelineState> CreateGraphicsPipelineState(
		::D3D12_GRAPHICS_PIPELINE_STATE_DESC const& desc);

	ComPtr<ID3D12ResourceN> CreateCommittedResource(
		::D3D12_HEAP_PROPERTIES const* heap_properties,
		::D3D12_HEAP_FLAGS             heap_flags,
		::D3D12_RESOURCE_DESC const*   desc,
		::D3D12_RESOURCE_STATES        initial_resource_state,
		::D3D12_CLEAR_VALUE const*     optimized_clear_value);

private:
	// noncopyable
	Device(Device const&) = delete;
	Device& operator=(Device const&) = delete;

private:
	ComPtr<ID3D12DeviceN>	m_device;
	::D3D_FEATURE_LEVEL		m_feature_level;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/device_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_DEVICE_HPP
