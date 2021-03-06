﻿/**
 *	@file	dxgi_swap_chain.hpp
 *
 *	@brief	DXGISwapChain クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DXGI_DXGI_SWAP_CHAIN_HPP
#define BKSGE_CORE_RENDER_DXGI_DXGI_SWAP_CHAIN_HPP

#include <bksge/core/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>
#include <bksge/core/render/dxgi/fwd/dxgi_factory_fwd.hpp>
#include <bksge/core/render/d3d_common/dxgi.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

class DXGISwapChain
{
public:
	DXGISwapChain(
		DXGIFactory* factory,
		IUnknown*    device,
		::UINT       buffer_count,
		::UINT       width,
		::UINT       height,
		::HWND       hwnd);

	~DXGISwapChain();

	::UINT GetBufferCount(void) const;

	::UINT GetCurrentBackBufferIndex(void) const;

	void Present(::UINT sync_interval, ::UINT flags);

	void GetBuffer(::UINT buffer, REFIID riid, void** surface) const;

private:
	ComPtr<IDXGISwapChainN> m_swap_chain;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/dxgi/inl/dxgi_swap_chain_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_DXGI_DXGI_SWAP_CHAIN_HPP
