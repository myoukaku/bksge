/**
 *	@file	dxgi.hpp
 *
 *	@brief	dxgi1_N.h をインクルード
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D_COMMON_DXGI_HPP
#define BKSGE_CORE_RENDER_D3D_COMMON_DXGI_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <dxgi1_6.h>

namespace bksge
{

namespace render
{

using IDXGIAdapterN   = ::IDXGIAdapter4;
using IDXGIDeviceN    = ::IDXGIDevice4;
using IDXGIFactoryN   = ::IDXGIFactory7;
using IDXGIOutputN    = ::IDXGIOutput6;
using IDXGIResourceN  = ::IDXGIResource1;
using IDXGISurfaceN   = ::IDXGISurface2;
using IDXGISwapChainN = ::IDXGISwapChain4;

}	// namespace render

}	// namespace bksge

#if defined(_MSC_VER)
#  pragma comment(lib, "dxgi.lib")
#endif

#endif // BKSGE_CORE_RENDER_D3D_COMMON_DXGI_HPP
