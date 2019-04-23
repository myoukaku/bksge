/**
 *	@file	d3d12_command_queue_inl.hpp
 *
 *	@brief	D3D12CommandQueue クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_COMMAND_QUEUE_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_COMMAND_QUEUE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_command_queue.hpp>
#include <bksge/render/d3d12/d3d12_command_list.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12CommandQueue::D3D12CommandQueue(D3D12Device* device)
{
	::D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.Type  = D3D12_COMMAND_LIST_TYPE_DIRECT;

	m_command_queue = device->CreateCommandQueue(desc);
}

BKSGE_INLINE
D3D12CommandQueue::~D3D12CommandQueue()
{
}

BKSGE_INLINE void
D3D12CommandQueue::ExecuteCommandLists(D3D12CommandList* command_list)
{
	command_list->Execute(m_command_queue.Get());
}

BKSGE_INLINE void
D3D12CommandQueue::Signal(
	::ID3D12Fence* fence,
	::UINT64       value)
{
	ThrowIfFailed(m_command_queue->Signal(fence, value));
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_COMMAND_QUEUE_INL_HPP
