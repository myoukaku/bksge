﻿/**
 *	@file	command_list_inl.hpp
 *
 *	@brief	CommandList クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_COMMAND_LIST_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_COMMAND_LIST_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/command_list.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d_common/throw_if_failed.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
CommandList::CommandList(Device* device, ::UINT frame_buffer_count)
{
	m_command_allocators.resize(frame_buffer_count);
	for (::UINT i = 0; i < frame_buffer_count; ++i)
	{
		m_command_allocators[i] = device->CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE_DIRECT);
	}

	m_command_list = device->CreateGraphicsCommandList(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		m_command_allocators[0].Get());
}

BKSGE_INLINE
CommandList::~CommandList()
{
}

BKSGE_INLINE void
CommandList::Reset(::UINT frame_index)
{
	ThrowIfFailed(m_command_allocators[frame_index]->Reset());

	ThrowIfFailed(m_command_list->Reset(m_command_allocators[frame_index].Get(), nullptr));
}

BKSGE_INLINE void
CommandList::Close(void)
{
	ThrowIfFailed(m_command_list->Close());
}

BKSGE_INLINE void
CommandList::CopyBufferRegion(
	::ID3D12Resource*	dst_buffer,
	::UINT64			dst_offset,
	::ID3D12Resource*	src_buffer,
	::UINT64			src_offset,
	::UINT64			num_bytes)
{
	m_command_list->CopyBufferRegion(
		dst_buffer,
		dst_offset,
		src_buffer,
		src_offset,
		num_bytes);
}

BKSGE_INLINE void
CommandList::CopyTextureRegion(
	::D3D12_TEXTURE_COPY_LOCATION const* dst,
	::UINT                               dst_x,
	::UINT                               dst_y,
	::UINT                               dst_z,
	::D3D12_TEXTURE_COPY_LOCATION const* src,
	::D3D12_BOX const*					 src_box)
{
	m_command_list->CopyTextureRegion(
		dst,
		dst_x,
		dst_y,
		dst_z,
		src,
		src_box);
}

BKSGE_INLINE void
CommandList::RSSetViewports(
	::UINT                  num_viewports,
	::D3D12_VIEWPORT const* viewports)
{
	m_command_list->RSSetViewports(num_viewports, viewports);
}

BKSGE_INLINE void
CommandList::RSSetScissorRects(
	::UINT              num_rects,
	::D3D12_RECT const* rects)
{
	m_command_list->RSSetScissorRects(num_rects, rects);
}

BKSGE_INLINE void
CommandList::ResourceBarrier(
	::ID3D12Resource*       resource,
	::D3D12_RESOURCE_STATES state_before,
	::D3D12_RESOURCE_STATES state_after)
{
	::D3D12_RESOURCE_BARRIER barrier;
	barrier.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource   = resource;
	barrier.Transition.StateBefore = state_before;
	barrier.Transition.StateAfter  = state_after;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	m_command_list->ResourceBarrier(1, &barrier);
}

BKSGE_INLINE void
CommandList::OMSetRenderTargets(
	::UINT                               num_render_target_descriptors,
	::D3D12_CPU_DESCRIPTOR_HANDLE const* render_target_descriptors,
	::BOOL                               rts_single_handle_to_descriptor_range,
	::D3D12_CPU_DESCRIPTOR_HANDLE const* depth_stencil_descriptor)
{
	m_command_list->OMSetRenderTargets(
		num_render_target_descriptors,
		render_target_descriptors,
		rts_single_handle_to_descriptor_range,
		depth_stencil_descriptor);
}

BKSGE_INLINE void
CommandList::OMSetStencilRef(::UINT stencil_ref)
{
	m_command_list->OMSetStencilRef(stencil_ref);
}

BKSGE_INLINE void
CommandList::ClearRenderTargetView(
	::D3D12_CPU_DESCRIPTOR_HANDLE const& render_target_view,
	::FLOAT const*                       color_rgba,
	::UINT                               num_rects,
	::D3D12_RECT const*                  rects)
{
	m_command_list->ClearRenderTargetView(
		render_target_view,
		color_rgba,
		num_rects,
		rects);
}

BKSGE_INLINE void
CommandList::ClearDepthStencilView(
	::D3D12_CPU_DESCRIPTOR_HANDLE const& depth_stencil_view,
	::D3D12_CLEAR_FLAGS                  clear_flags,
	::FLOAT                              depth,
	::UINT8                              stencil,
	::UINT                               num_rects,
	::D3D12_RECT const*                  rects)
{
	m_command_list->ClearDepthStencilView(
		depth_stencil_view,
		clear_flags,
		depth,
		stencil,
		num_rects,
		rects);
}

BKSGE_INLINE void
CommandList::SetGraphicsRootSignature(
	::ID3D12RootSignature* root_signature)
{
	m_command_list->SetGraphicsRootSignature(root_signature);
}

BKSGE_INLINE void
CommandList::SetPipelineState(
	::ID3D12PipelineState* pipeline_state)
{
	m_command_list->SetPipelineState(pipeline_state);
}

BKSGE_INLINE void
CommandList::SetDescriptorHeaps(
	::UINT                         num_descriptor_heaps,
	::ID3D12DescriptorHeap* const* descriptor_heaps)
{
	m_command_list->SetDescriptorHeaps(num_descriptor_heaps, descriptor_heaps);
}

BKSGE_INLINE void
CommandList::SetGraphicsRootDescriptorTable(
	::UINT                        root_parameter_index,
	::D3D12_GPU_DESCRIPTOR_HANDLE base_descriptor)
{
	m_command_list->SetGraphicsRootDescriptorTable(root_parameter_index, base_descriptor);
}

BKSGE_INLINE void
CommandList::IASetPrimitiveTopology(
	::D3D12_PRIMITIVE_TOPOLOGY primitive_topology)
{
	m_command_list->IASetPrimitiveTopology(primitive_topology);
}

BKSGE_INLINE void
CommandList::IASetVertexBuffers(
	::UINT                            start_slot,
	::UINT                            num_views,
	::D3D12_VERTEX_BUFFER_VIEW const* views)
{
	m_command_list->IASetVertexBuffers(start_slot, num_views, views);
}

BKSGE_INLINE void
CommandList::IASetIndexBuffer(
	::D3D12_INDEX_BUFFER_VIEW const* view)
{
	m_command_list->IASetIndexBuffer(view);
}

BKSGE_INLINE void
CommandList::DrawInstanced(
	::UINT vertex_count_per_instance,
	::UINT instance_count,
	::UINT start_vertex_location,
	::UINT start_instance_location)
{
	m_command_list->DrawInstanced(
		vertex_count_per_instance,
		instance_count,
		start_vertex_location,
		start_instance_location);
}

BKSGE_INLINE void
CommandList::DrawIndexedInstanced(
	::UINT index_count_per_instance,
	::UINT instance_count,
	::UINT start_index_location,
	::INT  base_vertex_location,
	::UINT start_instance_location)
{
	m_command_list->DrawIndexedInstanced(
		index_count_per_instance,
		instance_count,
		start_index_location,
		base_vertex_location,
		start_instance_location);
}

BKSGE_INLINE void
CommandList::Execute(::ID3D12CommandQueue* command_queue)
{
	::ID3D12CommandList* ppCommandLists[] ={m_command_list.Get()};
	command_queue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_COMMAND_LIST_INL_HPP
