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

#include <windows.h>

#if defined(NTDDI_WIN10_RS2) && NTDDI_VERSION >= NTDDI_WIN10_RS2	// Windows 10 version 1703 (SDK 10.0.15063.0)		Windows 10 Creators Update
#include <dxgi1_6.h>
#else
#include <dxgi1_5.h>
#endif

namespace bksge
{

namespace render
{

#if defined(NTDDI_WIN10_RS5) && NTDDI_VERSION >= NTDDI_WIN10_RS5	// Windows 10 version 1809 (SDK 10.0.17763.0)
using IDXGIFactoryN   = ::IDXGIFactory7;
#elif defined(NTDDI_WIN10_RS4) && NTDDI_VERSION >= NTDDI_WIN10_RS4	// Windows 10 version 1803 (SDK 10.0.17134.0)
using IDXGIFactoryN   = ::IDXGIFactory6;
#else
using IDXGIFactoryN   = ::IDXGIFactory5;
#endif

using IDXGIAdapterN   = ::IDXGIAdapter4;
using IDXGIDeviceN    = ::IDXGIDevice4;
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
