/**
 *	@file	dxgi_factory.hpp
 *
 *	@brief	DXGIFactory クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DXGI_DXGI_FACTORY_HPP
#define BKSGE_RENDER_DXGI_DXGI_FACTORY_HPP

#include <bksge/render/dxgi/fwd/dxgi_factory_fwd.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/dxgi/dxgi.hpp>
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

	std::vector<ComPtr<::IDXGIAdapter1>> EnumAdapters(void);

	ComPtr<::IDXGISwapChain1> CreateSwapChainForHwnd(
		::IUnknown*                              device,
		::HWND                                   hwnd,
		::DXGI_SWAP_CHAIN_DESC1 const*           desc,
		::DXGI_SWAP_CHAIN_FULLSCREEN_DESC const* fullscreen_desc,
		::IDXGIOutput*                           restrict_to_output);

	void MakeWindowAssociation(
		::HWND hwnd,
		::UINT flags);

private:
	ComPtr<::IDXGIFactory4> m_factory;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/dxgi/inl/dxgi_factory_inl.hpp>
#endif

#endif // BKSGE_RENDER_DXGI_DXGI_FACTORY_HPP
