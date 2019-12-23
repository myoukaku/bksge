/**
 *	@file	fence_inl.hpp
 *
 *	@brief	Fence クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_FENCE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_FENCE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/fence.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d12/detail/command_queue.hpp>
#include <bksge/core/render/d3d_common/throw_if_failed.hpp>
#include <bksge/core/detail/win32.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
Fence::Fence(Device* device, ::UINT frame_buffer_count)
{
	::UINT64 const initial_value = 0;
	m_fence = device->CreateFence(initial_value, D3D12_FENCE_FLAG_NONE);
	m_values.resize(frame_buffer_count, initial_value + 1);

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
Fence::WaitForGpu(CommandQueue* command_queue, ::UINT frame_index)
{
    // Schedule a Signal command in the queue.
	command_queue->Signal(m_fence.Get(), m_values[frame_index]);

	// Wait until the fence has been processed.
	ThrowIfFailed(m_fence->SetEventOnCompletion(m_values[frame_index], m_event));
	WaitForSingleObjectEx(m_event, INFINITE, FALSE);

	// Increment the fence value for the current frame.
	m_values[frame_index]++;
}

BKSGE_INLINE void
Fence::MoveToNextFrame(CommandQueue* command_queue, ::UINT frame_index)
{
    // Schedule a Signal command in the queue.
    ::UINT64 const current_value = m_values[frame_index];
    command_queue->Signal(m_fence.Get(), current_value);

    // Update the frame index.
	auto next_index = (frame_index + 1) % m_values.size();

    // If the next frame is not ready to be rendered yet, wait until it is ready.
    if (m_fence->GetCompletedValue() < m_values[next_index])
    {
        ThrowIfFailed(m_fence->SetEventOnCompletion(m_values[next_index], m_event));
        WaitForSingleObjectEx(m_event, INFINITE, FALSE);
    }

    // Set the fence value for the next frame.
    m_values[next_index] = current_value + 1;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_FENCE_INL_HPP
