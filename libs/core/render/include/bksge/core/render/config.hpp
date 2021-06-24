/**
 *	@file	config.hpp
 *
 *	@brief	Renderモジュールの設定
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_CONFIG_HPP
#define BKSGE_CORE_RENDER_CONFIG_HPP

#include <bksge/fnd/config.hpp>

/**
 *	BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
 *
 *	TODO
 */
#if !defined(BKSGE_CORE_RENDER_HAS_D3D12_RENDERER)
#	if defined(BKSGE_PLATFORM_WIN32) && BKSGE_HAS_INCLUDE(<d3d12.h>) && !defined(__MINGW32__)
#		define BKSGE_CORE_RENDER_HAS_D3D12_RENDERER	1
#	else
#		define BKSGE_CORE_RENDER_HAS_D3D12_RENDERER	0
#	endif
#endif

/**
 *	BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
 *
 *	TODO
 */
#if !defined(BKSGE_CORE_RENDER_HAS_D3D11_RENDERER)
#	if defined(BKSGE_PLATFORM_WIN32) && BKSGE_HAS_INCLUDE(<d3d11_1.h>) && !defined(__MINGW32__)
#		define BKSGE_CORE_RENDER_HAS_D3D11_RENDERER	1
#	else
#		define BKSGE_CORE_RENDER_HAS_D3D11_RENDERER	0
#	endif
#endif

/**
 *	BKSGE_CORE_RENDER_HAS_DXGI
 *
 *	TODO
 */
#if !defined(BKSGE_CORE_RENDER_HAS_DXGI)
#	if defined(BKSGE_PLATFORM_WIN32) && BKSGE_HAS_INCLUDE(<dxgi1_5.h>) && !defined(__MINGW32__)
#		define BKSGE_CORE_RENDER_HAS_DXGI	1
#	else
#		define BKSGE_CORE_RENDER_HAS_DXGI	0
#	endif
#endif

/**
 *	BKSGE_CORE_RENDER_HAS_GL_RENDERER
 *
 *	TODO
 */
#if !defined(BKSGE_CORE_RENDER_HAS_GL_RENDERER)
#	if 1//defined(BKSGE_PLATFORM_WIN32)
#		define BKSGE_CORE_RENDER_HAS_GL_RENDERER	1
#	else
#		define BKSGE_CORE_RENDER_HAS_GL_RENDERER	0
#	endif
#endif

/**
 *	BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
 */
#if !defined(BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER)
#	define BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER	1
#endif

/**
 *	BKSGE_CORE_RENDER_HAS_NULL_RENDERER
 */
#if !defined(BKSGE_CORE_RENDER_HAS_NULL_RENDERER)
#	define BKSGE_CORE_RENDER_HAS_NULL_RENDERER	1
#endif

#endif // BKSGE_CORE_RENDER_CONFIG_HPP
