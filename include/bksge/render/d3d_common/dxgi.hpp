/**
 *	@file	dxgi.hpp
 *
 *	@brief	dxgi1_N.h をインクルード
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D_COMMON_DXGI_HPP
#define BKSGE_RENDER_D3D_COMMON_DXGI_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <dxgi1_5.h>

#if defined(_MSC_VER)
#  pragma comment(lib, "dxgi.lib")
#endif

#endif // BKSGE_RENDER_D3D_COMMON_DXGI_HPP
