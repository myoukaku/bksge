/**
 *	@file	d3d12_adapter_inl.hpp
 *
 *	@brief	D3D12Adapter クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_ADAPTER_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_ADAPTER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_adapter.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/dxgi.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12Adapter::D3D12Adapter(ComPtr<::IDXGIAdapter1> adapter)
	: m_adapter(adapter)
	, m_feature_level()
{
	::D3D_FEATURE_LEVEL const feature_level_tbl[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	for (auto feature_level : feature_level_tbl)
	{
		// Check to see if the adapter supports Direct3D 12, but don't create the
		// actual device yet.
		if (SUCCEEDED(::D3D12CreateDevice(
			adapter.Get(),
			feature_level,
			_uuidof(ID3D12Device),
			nullptr)))
		{
			m_feature_level = feature_level;
			break;
		}
	}
}

BKSGE_INLINE
D3D12Adapter::~D3D12Adapter()
{
}

BKSGE_INLINE ComPtr<::ID3D12Device>
D3D12Adapter::CreateDevice(void) const
{
	ComPtr<::ID3D12Device> device;
	ThrowIfFailed(::D3D12CreateDevice(
		m_adapter.Get(),
		m_feature_level,
		IID_PPV_ARGS(&device)));
	return std::move(device);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_ADAPTER_INL_HPP
