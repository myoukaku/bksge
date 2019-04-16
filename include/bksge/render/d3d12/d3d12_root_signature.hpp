/**
 *	@file	d3d12_root_signature.hpp
 *
 *	@brief	D3D12RootSignature クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_ROOT_SIGNATURE_HPP
#define BKSGE_RENDER_D3D12_D3D12_ROOT_SIGNATURE_HPP

#include <bksge/render/d3d12/fwd/d3d12_root_signature_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>

namespace bksge
{

namespace render
{

class D3D12RootSignature
{
public:
	explicit D3D12RootSignature(D3D12Device* device);

	~D3D12RootSignature();

	::ID3D12RootSignature* Get(void) const;

private:
	ComPtr<::ID3D12RootSignature> m_root_signature;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_root_signature_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_ROOT_SIGNATURE_HPP
