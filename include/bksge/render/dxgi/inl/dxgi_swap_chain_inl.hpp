/**
 *	@file	dxgi_swap_chain_inl.hpp
 *
 *	@brief	DXGISwapChain クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DXGI_INL_DXGI_SWAP_CHAIN_INL_HPP
#define BKSGE_RENDER_DXGI_INL_DXGI_SWAP_CHAIN_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_DXGI

#include <bksge/render/dxgi/dxgi_swap_chain.hpp>
#include <bksge/render/dxgi/dxgi_factory.hpp>
#include <bksge/render/dxgi/dxgi.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
DXGISwapChain::DXGISwapChain(
	DXGIFactory* factory,
	IUnknown*    device,
	::UINT       width,
	::UINT       height,
	::HWND       hwnd)
{
	::DXGI_SWAP_CHAIN_DESC1 desc = {};
	desc.BufferCount      = 2/*FrameCount*/;
	desc.Width            = width;
	desc.Height           = height;
	desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferUsage      = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SwapEffect       = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.SampleDesc.Count = 1;

	auto swap_chain = factory->CreateSwapChainForHwnd(
		device,
		hwnd,
		&desc,
		nullptr,
		nullptr);

	ThrowIfFailed(swap_chain.As(&m_swap_chain));
}

BKSGE_INLINE
DXGISwapChain::~DXGISwapChain()
{
}

BKSGE_INLINE UINT
DXGISwapChain::GetCurrentBackBufferIndex()
{
	return m_swap_chain->GetCurrentBackBufferIndex();
}

BKSGE_INLINE void
DXGISwapChain::Present(::UINT sync_interval, ::UINT flags)
{
	ThrowIfFailed(m_swap_chain->Present(sync_interval, flags));
}

BKSGE_INLINE void
DXGISwapChain::GetBuffer(::UINT buffer, REFIID riid, void** surface)
{
	ThrowIfFailed(m_swap_chain->GetBuffer(buffer, riid, surface));
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_DXGI

#endif // BKSGE_RENDER_DXGI_INL_DXGI_SWAP_CHAIN_INL_HPP
