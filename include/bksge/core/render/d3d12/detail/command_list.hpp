/**
 *	@file	command_list.hpp
 *
 *	@brief	CommandList クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_COMMAND_LIST_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_COMMAND_LIST_HPP

#include <bksge/core/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

class CommandList
{
public:
	explicit CommandList(Device* device, ::UINT frame_buffer_count);

	~CommandList();

	void Reset(::UINT frame_index);

	void Close(void);

	void CopyBufferRegion(
		::ID3D12Resource*	dst_buffer,
		::UINT64			dst_offset,
		::ID3D12Resource*	src_buffer,
		::UINT64			src_offset,
		::UINT64			num_bytes);

	void CopyTextureRegion(
		::D3D12_TEXTURE_COPY_LOCATION const* dst,
		::UINT                               dst_x,
		::UINT                               dst_y,
		::UINT                               dst_z,
		::D3D12_TEXTURE_COPY_LOCATION const* src,
		::D3D12_BOX const*					 src_box);

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
		::D3D12_CPU_DESCRIPTOR_HANDLE const* render_target_descriptors,
		::BOOL                               rts_single_handle_to_descriptor_range,
		::D3D12_CPU_DESCRIPTOR_HANDLE const* depth_stencil_descriptor);

	void OMSetStencilRef(::UINT stencil_ref);

	void ClearRenderTargetView(
		::D3D12_CPU_DESCRIPTOR_HANDLE const& render_target_view,
		::FLOAT const*                       color_rgba,
		::UINT                               num_rects,
		::D3D12_RECT const*                  rects
	);

	void ClearDepthStencilView(
		::D3D12_CPU_DESCRIPTOR_HANDLE const& depth_stencil_view,
		::D3D12_CLEAR_FLAGS                  clear_flags,
		::FLOAT                              depth,
		::UINT8                              stencil,
		::UINT                               num_rects,
		::D3D12_RECT const *                 rects);

	void SetGraphicsRootSignature(
		::ID3D12RootSignature* root_signature);

	void SetPipelineState(
		::ID3D12PipelineState* pipeline_state);

	void SetDescriptorHeaps(
		::UINT                         num_descriptor_heaps,
		::ID3D12DescriptorHeap* const* descriptor_heaps);

	void SetGraphicsRootDescriptorTable(
		::UINT                        root_parameter_index,
		::D3D12_GPU_DESCRIPTOR_HANDLE base_descriptor);

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
	// noncopyable
	CommandList(CommandList const&) = delete;
	CommandList& operator=(CommandList const&) = delete;

private:
	std::vector<ComPtr<::ID3D12CommandAllocator>>	m_command_allocators;
	ComPtr<ID3D12GraphicsCommandListN>				m_command_list;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/command_list_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_COMMAND_LIST_HPP
