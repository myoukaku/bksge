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
	D3D12CommandList(D3D12Device* device);

	~D3D12CommandList();

	void Reset(void);

	void Close(void);

	void RSSetViewports(
		UINT                 NumViewports,
		const D3D12_VIEWPORT *pViewports);

	void RSSetScissorRects(
		UINT             NumRects,
		const D3D12_RECT *pRects);

	void ResourceBarrier(
		ID3D12Resource* resource,
		D3D12_RESOURCE_STATES state_before,
		D3D12_RESOURCE_STATES state_after);

	void OMSetRenderTargets(
		UINT                              NumRenderTargetDescriptors,
		D3D12_CPU_DESCRIPTOR_HANDLE const& pRenderTargetDescriptors);

	void ClearRenderTargetView(
		D3D12_CPU_DESCRIPTOR_HANDLE const& RenderTargetView,
		const FLOAT* ColorRGBA);

	void SetGraphicsRootSignature(
		ID3D12RootSignature *pRootSignature);

	void SetPipelineState(
		ID3D12PipelineState *pPipelineState);

	void IASetPrimitiveTopology(
		D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology);

	void IASetVertexBuffers(
		UINT                           StartSlot,
		UINT                           NumViews,
		const D3D12_VERTEX_BUFFER_VIEW *pViews);

	void IASetIndexBuffer(
		const D3D12_INDEX_BUFFER_VIEW *pView);

	void DrawInstanced(
		UINT VertexCountPerInstance,
		UINT InstanceCount,
		UINT StartVertexLocation,
		UINT StartInstanceLocation);

	void DrawIndexedInstanced(
		UINT IndexCountPerInstance,
		UINT InstanceCount,
		UINT StartIndexLocation,
		INT  BaseVertexLocation,
		UINT StartInstanceLocation);

	void Execute(::ID3D12CommandQueue* command_queue);

private:
	ComPtr<::ID3D12CommandAllocator> m_command_allocator;
	ComPtr<::ID3D12GraphicsCommandList> m_command_list;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_command_list_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_COMMAND_LIST_HPP
