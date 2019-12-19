/**
 *	@file	dxgi_factory.hpp
 *
 *	@brief	DXGIFactory クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DXGI_DXGI_FACTORY_HPP
#define BKSGE_CORE_RENDER_DXGI_DXGI_FACTORY_HPP

#include <bksge/core/render/dxgi/fwd/dxgi_factory_fwd.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/d3d_common/dxgi.hpp>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class DXGIFactory
{
public:
	DXGIFactory();

	~DXGIFactory();

	std::vector<ComPtr<IDXGIAdapterN>> EnumAdapters(void);

	ComPtr<IDXGISwapChainN> CreateSwapChainForHwnd(
		::IUnknown*                              device,
		::HWND                                   hwnd,
		::DXGI_SWAP_CHAIN_DESC1 const*           desc,
		::DXGI_SWAP_CHAIN_FULLSCREEN_DESC const* fullscreen_desc,
		IDXGIOutputN*                            restrict_to_output);

	void MakeWindowAssociation(
		::HWND hwnd,
		::UINT flags);

private:
	ComPtr<IDXGIFactoryN> m_factory;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/dxgi/inl/dxgi_factory_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_DXGI_DXGI_FACTORY_HPP
