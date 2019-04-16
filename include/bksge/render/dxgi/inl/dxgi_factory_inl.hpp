/**
 *	@file	dxgi_factory_inl.hpp
 *
 *	@brief	DXGIFactory の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DXGI_INL_DXGI_FACTORY_INL_HPP
#define BKSGE_RENDER_DXGI_INL_DXGI_FACTORY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_DXGI

#include <bksge/render/dxgi/dxgi_factory.hpp>
#include <bksge/render/dxgi/dxgi.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>
#include <vector>

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

BKSGE_INLINE std::vector<ComPtr<::IDXGIAdapter1>>
DXGIFactory::EnumAdapters(void)
{
	std::vector<ComPtr<::IDXGIAdapter1>> result;

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

		result.push_back(adapter);
	}

	// Enum warp adapter
	ThrowIfFailed(m_factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter)));
	result.push_back(adapter);

	return result;
}

BKSGE_INLINE ComPtr<::IDXGISwapChain1>
DXGIFactory::CreateSwapChainForHwnd(
	::IUnknown*                              device,
	::HWND                                   hwnd,
	::DXGI_SWAP_CHAIN_DESC1 const*           desc,
	::DXGI_SWAP_CHAIN_FULLSCREEN_DESC const* fullscreen_desc,
	::IDXGIOutput*                           restrict_to_output)
{
	ComPtr<::IDXGISwapChain1> swap_chain;
	ThrowIfFailed(m_factory->CreateSwapChainForHwnd(
		device,
		hwnd,
		desc,
		fullscreen_desc,
		restrict_to_output,
		&swap_chain));
	return std::move(swap_chain);
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

#endif // BKSGE_RENDER_HAS_DXGI

#endif // BKSGE_RENDER_DXGI_INL_DXGI_FACTORY_INL_HPP
