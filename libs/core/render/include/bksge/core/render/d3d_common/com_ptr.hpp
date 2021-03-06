﻿/**
 *	@file	com_ptr.hpp
 *
 *	@brief	ComPtr の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D_COMMON_COM_PTR_HPP
#define BKSGE_CORE_RENDER_D3D_COMMON_COM_PTR_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <wrl/client.h>

namespace bksge
{

namespace render
{

template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D_COMMON_COM_PTR_HPP
