﻿/**
 *	@file	render_target.hpp
 *
 *	@brief	RenderTarget クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_RENDER_TARGET_HPP
#define BKSGE_RENDER_D3D12_DETAIL_RENDER_TARGET_HPP

#include <bksge/render/d3d12/detail/fwd/render_target_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class RenderTarget
{
public:
	RenderTarget(Device* device, DXGISwapChain* swap_chain);

	~RenderTarget();

	::ID3D12Resource* GetResource(::UINT index);

	::D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(::UINT index);

private:
	ComPtr<::ID3D12Resource>		m_resource[2/*FrameCount*/];
	ComPtr<::ID3D12DescriptorHeap>	m_descriptor_heap;
	::UINT							m_descriptor_size;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/render_target_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_RENDER_TARGET_HPP