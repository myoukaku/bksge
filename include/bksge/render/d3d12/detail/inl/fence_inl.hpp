/**
 *	@file	fence_inl.hpp
 *
 *	@brief	Fence クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_FENCE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_FENCE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/fence.hpp>
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d12/detail/command_queue.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <bksge/detail/win32.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
Fence::Fence(Device* device)
{
	m_fence = device->CreateFence(0, D3D12_FENCE_FLAG_NONE);

	m_value = 1;

	// Create an event handle to use for frame synchronization.
	m_event = bksge::win32::CreateEvent(
		nullptr, FALSE, FALSE, (char const*)nullptr);
	if (m_event == nullptr)
	{
		ThrowIfFailed(HRESULT_FROM_WIN32(::GetLastError()));
	}
}

BKSGE_INLINE
Fence::~Fence()
{
}

BKSGE_INLINE void
Fence::Close(void)
{
	::CloseHandle(m_event);
}

BKSGE_INLINE void
Fence::WaitForPreviousFrame(CommandQueue* command_queue)
{
	// WAITING FOR THE FRAME TO COMPLETE BEFORE CONTINUING IS NOT BEST PRACTICE.
	// This is code implemented as such for simplicity. The D3D12HelloFrameBuffering
	// sample illustrates how to use fences for efficient resource usage and to
	// maximize GPU utilization.

	// Signal and increment the fence value.
	const ::UINT64 fence = m_value;
	command_queue->Signal(m_fence.Get(), fence);
	m_value++;

	// Wait until the previous frame is finished.
	if (m_fence->GetCompletedValue() < fence)
	{
		ThrowIfFailed(m_fence->SetEventOnCompletion(fence, m_event));
		WaitForSingleObject(m_event, INFINITE);
	}
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_FENCE_INL_HPP
