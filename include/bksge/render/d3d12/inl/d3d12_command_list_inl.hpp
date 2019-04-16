/**
 *	@file	d3d12_command_list_inl.hpp
 *
 *	@brief	D3D12CommandList クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_COMMAND_LIST_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_COMMAND_LIST_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_command_list.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12CommandList::D3D12CommandList(D3D12Device* device)
{
	m_command_allocator = device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT);

	m_command_list = device->CreateGraphicsCommandList(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		m_command_allocator.Get());
}

BKSGE_INLINE
D3D12CommandList::~D3D12CommandList()
{
}

BKSGE_INLINE void
D3D12CommandList::Reset(void)
{
	ThrowIfFailed(m_command_allocator->Reset());

	ThrowIfFailed(m_command_list->Reset(m_command_allocator.Get(), nullptr));
}

BKSGE_INLINE void
D3D12CommandList::Close(void)
{
	ThrowIfFailed(m_command_list->Close());
}

BKSGE_INLINE void
D3D12CommandList::RSSetViewports(
	::UINT                  num_viewports,
	::D3D12_VIEWPORT const* viewports)
{
	m_command_list->RSSetViewports(num_viewports, viewports);
}

BKSGE_INLINE void
D3D12CommandList::RSSetScissorRects(
	::UINT              num_rects,
	::D3D12_RECT const* rects)
{
	m_command_list->RSSetScissorRects(num_rects, rects);
}

BKSGE_INLINE void
D3D12CommandList::ResourceBarrier(
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
D3D12CommandList::OMSetRenderTargets(
	::UINT                               num_render_target_descriptors,
	::D3D12_CPU_DESCRIPTOR_HANDLE const* render_target_descriptors)
{
	m_command_list->OMSetRenderTargets(
		num_render_target_descriptors,
		render_target_descriptors,
		FALSE,
		nullptr);
}

BKSGE_INLINE void
D3D12CommandList::ClearRenderTargetView(
	::D3D12_CPU_DESCRIPTOR_HANDLE const& render_target_view,
	::FLOAT const*                       color_rgba)
{
	m_command_list->ClearRenderTargetView(
		render_target_view,
		color_rgba,
		0,
		nullptr);
}

BKSGE_INLINE void
D3D12CommandList::SetGraphicsRootSignature(
	::ID3D12RootSignature* root_signature)
{
	m_command_list->SetGraphicsRootSignature(root_signature);
}

BKSGE_INLINE void
D3D12CommandList::SetPipelineState(
	::ID3D12PipelineState* pipeline_state)
{
	m_command_list->SetPipelineState(pipeline_state);
}

BKSGE_INLINE void
D3D12CommandList::IASetPrimitiveTopology(
	::D3D12_PRIMITIVE_TOPOLOGY primitive_topology)
{
	m_command_list->IASetPrimitiveTopology(primitive_topology);
}

BKSGE_INLINE void
D3D12CommandList::IASetVertexBuffers(
	::UINT                            start_slot,
	::UINT                            num_views,
	::D3D12_VERTEX_BUFFER_VIEW const* views)
{
	m_command_list->IASetVertexBuffers(start_slot, num_views, views);
}

BKSGE_INLINE void
D3D12CommandList::IASetIndexBuffer(
	::D3D12_INDEX_BUFFER_VIEW const* view)
{
	m_command_list->IASetIndexBuffer(view);
}

BKSGE_INLINE void
D3D12CommandList::DrawInstanced(
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
D3D12CommandList::DrawIndexedInstanced(
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
D3D12CommandList::Execute(::ID3D12CommandQueue* command_queue)
{
	::ID3D12CommandList* ppCommandLists[] ={m_command_list.Get()};
	command_queue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_COMMAND_LIST_INL_HPP
