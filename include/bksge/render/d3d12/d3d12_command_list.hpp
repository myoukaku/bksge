/**
 *	@file	d3d12_command_list.hpp
 *
 *	@brief	D3D12CommandList クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_COMMAND_LIST_HPP
#define BKSGE_RENDER_D3D12_D3D12_COMMAND_LIST_HPP

#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>

namespace bksge
{

namespace render
{

class D3D12CommandList
{
public:
	explicit D3D12CommandList(D3D12Device* device);

	~D3D12CommandList();

	void Reset(void);

	void Close(void);

	void RSSetViewports(
		::UINT                  num_viewports,
		::D3D12_VIEWPORT const* viewports);

	void RSSetScissorRects(
		::UINT              num_rects,
		::D3D12_RECT const* rects);

	void ResourceBarrier(
		::ID3D12Resource*       resource,
		::D3D12_RESOURCE_STATES state_before,
		::D3D12_RESOURCE_STATES state_after);

	void OMSetRenderTargets(
		::UINT                               num_render_target_descriptors,
		::D3D12_CPU_DESCRIPTOR_HANDLE const* render_target_descriptors);

	void ClearRenderTargetView(
		::D3D12_CPU_DESCRIPTOR_HANDLE const& render_target_view,
		::FLOAT const*                       color_rgba);

	void SetGraphicsRootSignature(
		::ID3D12RootSignature* root_signature);

	void SetPipelineState(
		::ID3D12PipelineState* pipeline_state);

	void IASetPrimitiveTopology(
		::D3D12_PRIMITIVE_TOPOLOGY primitive_topology);

	void IASetVertexBuffers(
		::UINT                            start_slot,
		::UINT                            num_views,
		::D3D12_VERTEX_BUFFER_VIEW const* views);

	void IASetIndexBuffer(
		::D3D12_INDEX_BUFFER_VIEW const* view);

	void DrawInstanced(
		::UINT vertex_count_per_instance,
		::UINT instance_count,
		::UINT start_vertex_location,
		::UINT start_instance_location);

	void DrawIndexedInstanced(
		::UINT index_count_per_instance,
		::UINT instance_count,
		::UINT start_index_location,
		::INT  base_vertex_location,
		::UINT start_instance_location);

	void Execute(::ID3D12CommandQueue* command_queue);

private:
	ComPtr<::ID3D12CommandAllocator>    m_command_allocator;
	ComPtr<::ID3D12GraphicsCommandList> m_command_list;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_command_list_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_COMMAND_LIST_HPP
