﻿/**
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

namespace bksge
{

namespace render
{

namespace d3d12
{

class Fence
{
public:
	explicit Fence(Device* device);

	~Fence();

	void Close(void);

	void WaitForPreviousFrame(CommandQueue* command_queue);

private:
	ComPtr<ID3D12FenceN>	m_fence;
	::HANDLE				m_event;
	::UINT64				m_value;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/fence_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FENCE_HPP
