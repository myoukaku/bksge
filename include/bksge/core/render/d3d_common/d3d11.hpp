/**
 *	@file	d3d11.hpp
 *
 *	@brief	d3d11_1.h をインクルード
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D_COMMON_D3D11_HPP
#define BKSGE_CORE_RENDER_D3D_COMMON_D3D11_HPP

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <d3d11_4.h>

namespace bksge
{

namespace render
{

using D3D11_BLEND_DESC_N                 = ::D3D11_BLEND_DESC1;
using D3D11_QUERY_DESC_N                 = ::D3D11_QUERY_DESC1;
using D3D11_RASTERIZER_DESC_N            = ::D3D11_RASTERIZER_DESC2;
using D3D11_RENDER_TARGET_BLEND_DESC_N   = ::D3D11_RENDER_TARGET_BLEND_DESC1;
using D3D11_RENDER_TARGET_VIEW_DESC_N    = ::D3D11_RENDER_TARGET_VIEW_DESC1;
using D3D11_SHADER_RESOURCE_VIEW_DESC_N  = ::D3D11_SHADER_RESOURCE_VIEW_DESC1;
using D3D11_TEX2D_ARRAY_RTV_N            = ::D3D11_TEX2D_ARRAY_RTV1;
using D3D11_TEX2D_ARRAY_SRV_N            = ::D3D11_TEX2D_ARRAY_SRV1;
using D3D11_TEX2D_ARRAY_UAV_N            = ::D3D11_TEX2D_ARRAY_UAV1;
using D3D11_TEX2D_RTV_N                  = ::D3D11_TEX2D_RTV1;
using D3D11_TEX2D_SRV_N                  = ::D3D11_TEX2D_SRV1;
using D3D11_TEX2D_UAV_N                  = ::D3D11_TEX2D_UAV1;
using D3D11_TEXTURE2D_DESC_N             = ::D3D11_TEXTURE2D_DESC1;
using D3D11_TEXTURE3D_DESC_N             = ::D3D11_TEXTURE3D_DESC1;
using D3D11_UNORDERED_ACCESS_VIEW_DESC_N = ::D3D11_UNORDERED_ACCESS_VIEW_DESC1;

using ID3D11BlendStateN               = ::ID3D11BlendState1;
using ID3D11DeviceN                   = ::ID3D11Device5;
using ID3D11DeviceContextN            = ::ID3D11DeviceContext4;
using ID3D11QueryN                    = ::ID3D11Query1;
using ID3D11RasterizerStateN          = ::ID3D11RasterizerState2;
using ID3D11RenderTargetViewN         = ::ID3D11RenderTargetView1;
using ID3D11ShaderResourceViewN       = ::ID3D11ShaderResourceView1;
using ID3D11Texture2DN                = ::ID3D11Texture2D1;
using ID3D11Texture3DN                = ::ID3D11Texture3D1;
using ID3D11UnorderedAccessViewN      = ::ID3D11UnorderedAccessView1;
using ID3D11VideoContextN             = ::ID3D11VideoContext3;
using ID3D11VideoDeviceN              = ::ID3D11VideoDevice2;
using ID3D11VideoProcessorEnumeratorN = ::ID3D11VideoProcessorEnumerator1;

}	// namespace render

}	// namespace bksge

#if defined(_MSC_VER)
#pragma comment(lib, "d3d11.lib")
#endif

#endif // BKSGE_CORE_RENDER_D3D_COMMON_D3D11_HPP
