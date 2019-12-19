/**
 *	@file	d3d12.hpp
 *
 *	@brief	d3d12.h をインクルード
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D_COMMON_D3D12_HPP
#define BKSGE_CORE_RENDER_D3D_COMMON_D3D12_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <d3d12.h>

namespace bksge
{

namespace render
{

using ID3D12DeviceN              = ::ID3D12Device6;
using ID3D12FenceN               = ::ID3D12Fence1;
using ID3D12GraphicsCommandListN = ::ID3D12GraphicsCommandList5;
using ID3D12HeapN                = ::ID3D12Heap1;
using ID3D12PipelineLibraryN     = ::ID3D12PipelineLibrary1;
using ID3D12ResourceN            = ::ID3D12Resource1;

}	// namespace render

}	// namespace bksge

#if defined(_MSC_VER)
#  pragma comment(lib, "d3d12.lib")
#endif

#endif // BKSGE_CORE_RENDER_D3D_COMMON_D3D12_HPP
