/**
 *	@file	d3d12_factory_inl.hpp
 *
 *	@brief	D3D12Factory クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_FACTORY_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_FACTORY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_factory.hpp>
#include <bksge/render/d3d12/d3d12_adapter.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/dxgi.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>
#include <vector>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12Factory::D3D12Factory(void)
{
	::UINT flags = 0;
#if defined(_DEBUG)
	// Enable the debug layer (requires the Graphics Tools "optional feature").
	// NOTE: Enabling the debug layer after device creation will invalidate the active device.
	{
		ComPtr<::ID3D12Debug> debug;
		if (SUCCEEDED(::D3D12GetDebugInterface(IID_PPV_ARGS(&debug))))
		{
			debug->EnableDebugLayer();

			// Enable additional debug layers.
			flags |= DXGI_CREATE_FACTORY_DEBUG;
		}
	}
#endif
	ThrowIfFailed(::CreateDXGIFactory2(flags, IID_PPV_ARGS(&m_factory)));
}

BKSGE_INLINE
D3D12Factory::~D3D12Factory()
{
}

BKSGE_INLINE std::vector<D3D12Adapter>
D3D12Factory::EnumAdapters(void)
{
	std::vector<D3D12Adapter> result;

	ComPtr<::IDXGIAdapter1> adapter;

	// Enum hardware adapters
	for (::UINT i = 0;
		m_factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND;
		++i)
	{
		::DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			continue;
		}

		result.emplace_back(adapter);
	}

	// Enum warp adapter
	ThrowIfFailed(m_factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter)));
	result.emplace_back(adapter);

	return result;
}

BKSGE_INLINE void
D3D12Factory::CreateSwapChainForHwnd(
	IUnknown                              *pDevice,
	HWND                                  hWnd,
	const DXGI_SWAP_CHAIN_DESC1           *pDesc,
	const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc,
	IDXGIOutput                           *pRestrictToOutput,
	IDXGISwapChain1                       **ppSwapChain)
{
	ThrowIfFailed(m_factory->CreateSwapChainForHwnd(
		pDevice,
		hWnd,
		pDesc,
		pFullscreenDesc,
		pRestrictToOutput,
		ppSwapChain
	));

	ThrowIfFailed(m_factory->MakeWindowAssociation(
		hWnd, DXGI_MWA_NO_ALT_ENTER));
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_FACTORY_INL_HPP
