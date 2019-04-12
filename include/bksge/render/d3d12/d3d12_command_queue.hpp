/**
 *	@file	d3d12_command_queue.hpp
 *
 *	@brief	D3D12CommandQueue クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_COMMAND_QUEUE_HPP
#define BKSGE_RENDER_D3D12_D3D12_COMMAND_QUEUE_HPP

#include <bksge/render/d3d12/fwd/d3d12_command_queue_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>

namespace bksge
{

namespace render
{

class D3D12CommandQueue
{
public:
	D3D12CommandQueue(D3D12Device* device);

	~D3D12CommandQueue();

	void ExecuteCommandLists(D3D12CommandList* command_list);

	::ID3D12CommandQueue* Get(void) { return m_command_queue.Get(); } // TODO

	void Signal(
		ID3D12Fence *pFence,
		UINT64      Value);

private:
	ComPtr<::ID3D12CommandQueue> m_command_queue;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_command_queue_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_COMMAND_QUEUE_HPP
