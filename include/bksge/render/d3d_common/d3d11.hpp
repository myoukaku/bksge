/**
 *	@file	d3d11.hpp
 *
 *	@brief	d3d11_1.h をインクルード
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D_COMMON_D3D11_HPP
#define BKSGE_RENDER_D3D_COMMON_D3D11_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <d3d11_1.h>

#if defined(_MSC_VER)
#pragma comment(lib, "d3d11.lib")
#endif

#endif // BKSGE_RENDER_D3D_COMMON_D3D11_HPP
