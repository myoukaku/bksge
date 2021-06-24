/**
 *	@file	d3dcompiler.hpp
 *
 *	@brief	d3dcompiler.h をインクルード
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D_COMMON_D3DCOMPILER_HPP
#define BKSGE_CORE_RENDER_D3D_COMMON_D3DCOMPILER_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <d3dcompiler.h>

#if defined(_MSC_VER)
#  pragma comment(lib, "d3dcompiler.lib")
#  pragma comment(lib, "dxguid.lib")
#endif

#endif // BKSGE_CORE_RENDER_D3D_COMMON_D3DCOMPILER_HPP
