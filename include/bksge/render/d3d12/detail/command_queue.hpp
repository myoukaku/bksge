/**
 *	@file	command_queue.hpp
 *
 *	@brief	CommandQueue クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_COMMAND_QUEUE_HPP
#define BKSGE_RENDER_D3D12_DETAIL_COMMAND_QUEUE_HPP

#include <bksge/render/d3d12/detail/fwd/command_queue_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class CommandQueue
{
public:
	explicit CommandQueue(Device* device);

	~CommandQueue();

	void ExecuteCommandLists(CommandList* command_list);

	::ID3D12CommandQueue* Get(void) { return m_command_queue.Get(); } // TODO

	void Signal(
		::ID3D12Fence* fence,
		::UINT64       value);

private:
	ComPtr<::ID3D12CommandQueue> m_command_queue;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/command_queue_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_COMMAND_QUEUE_HPP
