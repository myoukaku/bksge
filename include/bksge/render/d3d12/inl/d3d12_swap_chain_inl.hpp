/**
 *	@file	d3d12_swap_chain_inl.hpp
 *
 *	@brief	D3D12SwapChain クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_SWAP_CHAIN_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_SWAP_CHAIN_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_swap_chain.hpp>
#include <bksge/render/d3d12/d3d12_factory.hpp>
#include <bksge/render/d3d12/d3d12_command_queue.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12SwapChain::D3D12SwapChain(
	D3D12Factory* factory,
	D3D12CommandQueue* command_queue,
	UINT             Width,
	UINT             Height,
	HWND hwnd)
{
	// Describe and create the swap chain.
	::DXGI_SWAP_CHAIN_DESC1 swapChainDesc ={};
	swapChainDesc.BufferCount      = 2/*FrameCount*/;
	swapChainDesc.Width            = Width;
	swapChainDesc.Height           = Height;
	swapChainDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage      = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect       = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	ComPtr<::IDXGISwapChain1> swapChain;
	factory->CreateSwapChainForHwnd(
		command_queue->Get(),        // Swap chain needs the queue so that it can force a flush on it.
		hwnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain);

	ThrowIfFailed(swapChain.As(&m_swap_chain));
}

BKSGE_INLINE
D3D12SwapChain::~D3D12SwapChain()
{
}

BKSGE_INLINE UINT
D3D12SwapChain::GetCurrentBackBufferIndex()
{
	return m_swap_chain->GetCurrentBackBufferIndex();
}

BKSGE_INLINE void
D3D12SwapChain::Present(
	UINT SyncInterval,
	UINT Flags)
{
	ThrowIfFailed(m_swap_chain->Present(SyncInterval, Flags));
}

BKSGE_INLINE void
D3D12SwapChain::GetBuffer(
	UINT   Buffer,
	REFIID riid,
	void   **ppSurface)
{
	ThrowIfFailed(m_swap_chain->GetBuffer(
		Buffer,
		riid,
		ppSurface));
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_SWAP_CHAIN_INL_HPP
