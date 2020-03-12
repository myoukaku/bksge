/**
 *	@file	fence.hpp
 *
 *	@brief	Fence クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FENCE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FENCE_HPP

#include <bksge/core/render/d3d12/detail/fwd/fence_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_queue_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

class Fence
{
public:
	explicit Fence(Device* device, ::UINT frame_buffer_count);

	~Fence();

	void Close(void);

	void WaitForGpu(CommandQueue* command_queue, ::UINT frame_index);
	void MoveToNextFrame(CommandQueue* command_queue, ::UINT frame_index);

private:
	// noncopyable
	Fence(Fence const&) = delete;
	Fence& operator=(Fence const&) = delete;

private:
	ComPtr<ID3D12FenceN>	m_fence;
	std::vector<::UINT64>	m_values;
	::HANDLE				m_event;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/fence_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FENCE_HPP
