/**
 *	@file	command_queue_inl.hpp
 *
 *	@brief	CommandQueue クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_COMMAND_QUEUE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_COMMAND_QUEUE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/command_queue.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
CommandQueue::CommandQueue(Device* device)
{
	::D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.Type  = D3D12_COMMAND_LIST_TYPE_DIRECT;

	m_command_queue = device->CreateCommandQueue(desc);
}

BKSGE_INLINE
CommandQueue::~CommandQueue()
{
}

BKSGE_INLINE void
CommandQueue::ExecuteCommandLists(CommandList* command_list)
{
	command_list->Execute(m_command_queue.Get());
}

BKSGE_INLINE void
CommandQueue::Signal(
	::ID3D12Fence* fence,
	::UINT64       value)
{
	ThrowIfFailed(m_command_queue->Signal(fence, value));
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_COMMAND_QUEUE_INL_HPP
