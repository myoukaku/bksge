﻿/**
 *	@file	config.hpp
 *
 *	@brief	Renderモジュールの設定
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_CONFIG_HPP
#define BKSGE_RENDER_CONFIG_HPP

#include <bksge/config.hpp>

/**
 *	BKSGE_RENDER_HAS_D3D12_RENDERER
 *
 *	TODO
 */
#if !defined(BKSGE_RENDER_HAS_D3D12_RENDERER)
#	if defined(BKSGE_PLATFORM_WIN32)
#		define BKSGE_RENDER_HAS_D3D12_RENDERER	1
#	else
#		define BKSGE_RENDER_HAS_D3D12_RENDERER	0
#	endif
#endif

/**
 *	BKSGE_RENDER_HAS_D3D11_RENDERER
 *
 *	TODO
 */
#if !defined(BKSGE_RENDER_HAS_D3D11_RENDERER)
#	if defined(BKSGE_PLATFORM_WIN32)
#		define BKSGE_RENDER_HAS_D3D11_RENDERER	1
#	else
#		define BKSGE_RENDER_HAS_D3D11_RENDERER	0
#	endif
#endif

/**
 *	BKSGE_RENDER_HAS_GL_RENDERER
 *
 *	TODO
 */
#if !defined(BKSGE_RENDER_HAS_GL_RENDERER)
#	if 1//defined(BKSGE_PLATFORM_WIN32)
#		define BKSGE_RENDER_HAS_GL_RENDERER	1
#	else
#		define BKSGE_RENDER_HAS_GL_RENDERER	0
#	endif
#endif

/**
 *	BKSGE_RENDER_HAS_NULL_RENDERER
 */
#if !defined(BKSGE_RENDER_HAS_NULL_RENDERER)
#	define BKSGE_RENDER_HAS_NULL_RENDERER	1
#endif

#endif // BKSGE_RENDER_CONFIG_HPP
