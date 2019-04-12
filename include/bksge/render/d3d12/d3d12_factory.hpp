/**
 *	@file	d3d12_factory.hpp
 *
 *	@brief	D3D12Factory クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_FACTORY_HPP
#define BKSGE_RENDER_D3D12_D3D12_FACTORY_HPP

#include <bksge/render/d3d12/fwd/d3d12_factory_fwd.hpp>
#include <bksge/render/d3d12/d3d12_adapter.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/dxgi.hpp>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief	D3D12 ファクトリー
 */
class D3D12Factory
{
public:
	D3D12Factory(void);

	~D3D12Factory();

	std::vector<D3D12Adapter> EnumAdapters(void);

	void CreateSwapChainForHwnd(
		IUnknown                              *pDevice,
		HWND                                  hWnd,
		const DXGI_SWAP_CHAIN_DESC1           *pDesc,
		const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc,
		IDXGIOutput                           *pRestrictToOutput,
		IDXGISwapChain1                       **ppSwapChain
	);

private:
	ComPtr<::IDXGIFactory4> m_factory;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_factory_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_FACTORY_HPP
