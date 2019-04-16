/**
 *	@file	d3d12_adapter.hpp
 *
 *	@brief	D3D12Adapter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_ADAPTER_HPP
#define BKSGE_RENDER_D3D12_D3D12_ADAPTER_HPP

#include <bksge/render/d3d12/fwd/d3d12_adapter_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/dxgi.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	D3D12 アダプター
 */
class D3D12Adapter
{
public:
	explicit D3D12Adapter(ComPtr<::IDXGIAdapter1> adapter);

	~D3D12Adapter();

	ComPtr<::ID3D12Device> CreateDevice(void) const;

private:
	ComPtr<::IDXGIAdapter1> m_adapter;
	::D3D_FEATURE_LEVEL		m_feature_level;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_adapter_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_ADAPTER_HPP
