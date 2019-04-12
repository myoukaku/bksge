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
	UINT                 NumViewports,
	const D3D12_VIEWPORT *pViewports)
{
	m_command_list->RSSetViewports(NumViewports, pViewports);
}

BKSGE_INLINE void
D3D12CommandList::RSSetScissorRects(
	UINT             NumRects,
	const D3D12_RECT *pRects)
{
	m_command_list->RSSetScissorRects(NumRects, pRects);
}

BKSGE_INLINE void
D3D12CommandList::ResourceBarrier(
	ID3D12Resource* resource,
	D3D12_RESOURCE_STATES state_before,
	D3D12_RESOURCE_STATES state_after)
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
	UINT                              NumRenderTargetDescriptors,
	D3D12_CPU_DESCRIPTOR_HANDLE const& pRenderTargetDescriptors)
{
	m_command_list->OMSetRenderTargets(
		NumRenderTargetDescriptors,
		&pRenderTargetDescriptors,
		FALSE,
		nullptr);
}

BKSGE_INLINE void
D3D12CommandList::ClearRenderTargetView(
	D3D12_CPU_DESCRIPTOR_HANDLE const& RenderTargetView,
	const FLOAT* ColorRGBA)
{
	m_command_list->ClearRenderTargetView(
		RenderTargetView,
		ColorRGBA,
		0,
		nullptr);
}

BKSGE_INLINE void
D3D12CommandList::SetGraphicsRootSignature(
	ID3D12RootSignature *pRootSignature)
{
	m_command_list->SetGraphicsRootSignature(pRootSignature);
}

BKSGE_INLINE void
D3D12CommandList::SetPipelineState(
	ID3D12PipelineState *pPipelineState)
{
	m_command_list->SetPipelineState(pPipelineState);
}

BKSGE_INLINE void
D3D12CommandList::IASetPrimitiveTopology(
	D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology)
{
	m_command_list->IASetPrimitiveTopology(PrimitiveTopology);
}

BKSGE_INLINE void
D3D12CommandList::IASetVertexBuffers(
	UINT                           StartSlot,
	UINT                           NumViews,
	const D3D12_VERTEX_BUFFER_VIEW *pViews)
{
	m_command_list->IASetVertexBuffers(StartSlot, NumViews, pViews);
}

BKSGE_INLINE void
D3D12CommandList::IASetIndexBuffer(
	const D3D12_INDEX_BUFFER_VIEW *pView)
{
	m_command_list->IASetIndexBuffer(pView);
}

BKSGE_INLINE void
D3D12CommandList::DrawInstanced(
	UINT VertexCountPerInstance,
	UINT InstanceCount,
	UINT StartVertexLocation,
	UINT StartInstanceLocation)
{
	m_command_list->DrawInstanced(
		VertexCountPerInstance,
		InstanceCount,
		StartVertexLocation,
		StartInstanceLocation);
}

BKSGE_INLINE void
D3D12CommandList::DrawIndexedInstanced(
	UINT IndexCountPerInstance,
	UINT InstanceCount,
	UINT StartIndexLocation,
	INT  BaseVertexLocation,
	UINT StartInstanceLocation)
{
	m_command_list->DrawIndexedInstanced(
		IndexCountPerInstance,
		InstanceCount,
		StartIndexLocation,
		BaseVertexLocation,
		StartInstanceLocation);
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
