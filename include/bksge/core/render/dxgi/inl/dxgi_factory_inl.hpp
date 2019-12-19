/**
 *	@file	dxgi_factory_inl.hpp
 *
 *	@brief	DXGIFactory の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DXGI_INL_DXGI_FACTORY_INL_HPP
#define BKSGE_CORE_RENDER_DXGI_INL_DXGI_FACTORY_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_DXGI

#include <bksge/core/render/dxgi/dxgi_factory.hpp>
#include <bksge/core/render/d3d_common/dxgi.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/d3d_common/throw_if_failed.hpp>
#include <vector>
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
DXGIFactory::DXGIFactory(void)
{
	::UINT flags = 0;
#if defined(_DEBUG)
	flags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
	ThrowIfFailed(::CreateDXGIFactory2(flags, IID_PPV_ARGS(&m_factory)));
}

BKSGE_INLINE
DXGIFactory::~DXGIFactory()
{
}

BKSGE_INLINE std::vector<ComPtr<IDXGIAdapterN>>
DXGIFactory::EnumAdapters(void)
{
	std::vector<ComPtr<IDXGIAdapterN>> result;

	ComPtr<IDXGIAdapter1> adapter;

	// Enum hardware adapters
	for (::UINT i = 0;
		m_factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND;
		++i)
	{
		::DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

#if !defined(__MINGW32__)
		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			continue;
		}
#endif

		ComPtr<IDXGIAdapterN> adapter_n;
		ThrowIfFailed(adapter.As(&adapter_n));
		result.push_back(adapter_n);
	}

	// Enum warp adapter
	ThrowIfFailed(m_factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter)));
	ComPtr<IDXGIAdapterN> adapter_n;
	ThrowIfFailed(adapter.As(&adapter_n));
	result.push_back(adapter_n);

	return result;
}

BKSGE_INLINE ComPtr<IDXGISwapChainN>
DXGIFactory::CreateSwapChainForHwnd(
	::IUnknown*                              device,
	::HWND                                   hwnd,
	::DXGI_SWAP_CHAIN_DESC1 const*           desc,
	::DXGI_SWAP_CHAIN_FULLSCREEN_DESC const* fullscreen_desc,
	IDXGIOutputN*                            restrict_to_output)
{
	ComPtr<IDXGISwapChain1> swap_chain;
	ThrowIfFailed(m_factory->CreateSwapChainForHwnd(
		device,
		hwnd,
		desc,
		fullscreen_desc,
		restrict_to_output,
		&swap_chain));

	ComPtr<IDXGISwapChainN> swap_chain_n;
	ThrowIfFailed(swap_chain.As(&swap_chain_n));
	return std::move(swap_chain_n);
}

BKSGE_INLINE void
DXGIFactory::MakeWindowAssociation(
	::HWND hwnd,
	::UINT flags)
{
	ThrowIfFailed(m_factory->MakeWindowAssociation(
		hwnd,
		flags));
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_DXGI

#endif // BKSGE_CORE_RENDER_DXGI_INL_DXGI_FACTORY_INL_HPP
