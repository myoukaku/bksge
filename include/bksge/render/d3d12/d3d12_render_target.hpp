/**
 *	@file	d3d12_render_target.hpp
 *
 *	@brief	D3D12RenderTarget クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_RENDER_TARGET_HPP
#define BKSGE_RENDER_D3D12_D3D12_RENDER_TARGET_HPP

#include <bksge/render/d3d12/fwd/d3d12_render_target_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>

namespace bksge
{

namespace render
{

class D3D12RenderTarget
{
public:
	D3D12RenderTarget(D3D12Device* device, DXGISwapChain* swap_chain);

	~D3D12RenderTarget();

	::ID3D12Resource* GetResource(::UINT index);

	::D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(::UINT index);

private:
	ComPtr<::ID3D12Resource>		m_resource[2/*FrameCount*/];
	ComPtr<::ID3D12DescriptorHeap>	m_descriptor_heap;
	::UINT							m_descriptor_size;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_render_target_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_RENDER_TARGET_HPP
