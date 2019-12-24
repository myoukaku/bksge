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

#if defined(NTDDI_WIN10_19H1) && NTDDI_VERSION >= NTDDI_WIN10_19H1	// Windows 10 version 1903 (SDK 10.0.18362.0)
using ID3D12DeviceN              = ::ID3D12Device6;
using ID3D12FenceN               = ::ID3D12Fence1;
using ID3D12GraphicsCommandListN = ::ID3D12GraphicsCommandList5;
using ID3D12HeapN                = ::ID3D12Heap1;
using ID3D12PipelineLibraryN     = ::ID3D12PipelineLibrary1;
using ID3D12ResourceN            = ::ID3D12Resource1;
#elif defined(NTDDI_WIN10_RS5) && NTDDI_VERSION >= NTDDI_WIN10_RS5	// Windows 10 version 1809 (SDK 10.0.17763.0)
using ID3D12DeviceN              = ::ID3D12Device5;
using ID3D12FenceN               = ::ID3D12Fence1;
using ID3D12GraphicsCommandListN = ::ID3D12GraphicsCommandList4;
using ID3D12HeapN                = ::ID3D12Heap;
using ID3D12PipelineLibraryN     = ::ID3D12PipelineLibrary1;
using ID3D12ResourceN            = ::ID3D12Resource;
//#elif defined(NTDDI_WIN10_RS4) && NTDDI_VERSION >= NTDDI_WIN10_RS4	// Windows 10 version 1803 (SDK 10.0.17134.0)
#elif defined(NTDDI_WIN10_RS3) && NTDDI_VERSION >= NTDDI_WIN10_RS3	// Windows 10 version 1709 (SDK 10.0.16299.0)		Windows 10 Fall Creators Update
using ID3D12DeviceN              = ::ID3D12Device3;
using ID3D12FenceN               = ::ID3D12Fence1;
using ID3D12GraphicsCommandListN = ::ID3D12GraphicsCommandList2;
using ID3D12HeapN                = ::ID3D12Heap;
using ID3D12PipelineLibraryN     = ::ID3D12PipelineLibrary1;
using ID3D12ResourceN            = ::ID3D12Resource;
#elif defined(NTDDI_WIN10_RS2) && NTDDI_VERSION >= NTDDI_WIN10_RS2	// Windows 10 version 1703 (SDK 10.0.15063.0)		Windows 10 Creators Update
using ID3D12DeviceN              = ::ID3D12Device2;
using ID3D12FenceN               = ::ID3D12Fence;
using ID3D12GraphicsCommandListN = ::ID3D12GraphicsCommandList1;
using ID3D12HeapN                = ::ID3D12Heap;
using ID3D12PipelineLibraryN     = ::ID3D12PipelineLibrary1;
using ID3D12ResourceN            = ::ID3D12Resource;
#elif defined(NTDDI_WIN10_RS1) && NTDDI_VERSION >= NTDDI_WIN10_RS1	// Windows 10 version 1607 (SDK 10.0.14393.0)		Windows 10 Anniversary Update
using ID3D12DeviceN              = ::ID3D12Device1;
using ID3D12FenceN               = ::ID3D12Fence;
using ID3D12GraphicsCommandListN = ::ID3D12GraphicsCommandList;
using ID3D12HeapN                = ::ID3D12Heap;
using ID3D12PipelineLibraryN     = ::ID3D12PipelineLibrary;
using ID3D12ResourceN            = ::ID3D12Resource;
#else
using ID3D12DeviceN              = ::ID3D12Device;
using ID3D12FenceN               = ::ID3D12Fence;
using ID3D12GraphicsCommandListN = ::ID3D12GraphicsCommandList;
using ID3D12HeapN                = ::ID3D12Heap;
using ID3D12PipelineLibraryN     = ::ID3D12PipelineLibrary;
using ID3D12ResourceN            = ::ID3D12Resource;
#endif

}	// namespace render

}	// namespace bksge

#if defined(_MSC_VER)
#  pragma comment(lib, "d3d12.lib")
#endif

#endif // BKSGE_CORE_RENDER_D3D_COMMON_D3D12_HPP
