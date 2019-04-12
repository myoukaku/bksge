/**
 *	@file	d3d12_swap_chain.hpp
 *
 *	@brief	D3D12SwapChain クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_SWAP_CHAIN_HPP
#define BKSGE_RENDER_D3D12_D3D12_SWAP_CHAIN_HPP

#include <bksge/render/d3d12/fwd/d3d12_swap_chain_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_factory_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_queue_fwd.hpp>
#include <bksge/render/d3d_helper/dxgi.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>

namespace bksge
{

namespace render
{

class D3D12SwapChain
{
public:
	D3D12SwapChain(
		D3D12Factory* factory,
		D3D12CommandQueue* command_queue,
		UINT             Width,
		UINT             Height,
		HWND hwnd);

	~D3D12SwapChain();

	UINT GetCurrentBackBufferIndex();

	void Present(
		UINT SyncInterval,
		UINT Flags);

	void GetBuffer(
		UINT   Buffer,
		REFIID riid,
		void   **ppSurface);

private:
	ComPtr<::IDXGISwapChain3> m_swap_chain;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_swap_chain_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_SWAP_CHAIN_HPP
