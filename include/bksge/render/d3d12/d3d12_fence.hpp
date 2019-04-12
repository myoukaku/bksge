/**
 *	@file	d3d12_fence.hpp
 *
 *	@brief	D3D12Fence クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_FENCE_HPP
#define BKSGE_RENDER_D3D12_D3D12_FENCE_HPP

#include <bksge/render/d3d12/fwd/d3d12_fence_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_queue_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>

namespace bksge
{

namespace render
{

class D3D12Fence
{
public:
	D3D12Fence(D3D12Device* device);

	~D3D12Fence();

	void Close(void);

	void WaitForPreviousFrame(D3D12CommandQueue* command_queue);

private:
	ComPtr<::ID3D12Fence>	m_fence;
	::HANDLE				m_event;
	::UINT64				m_value;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_fence_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_FENCE_HPP
