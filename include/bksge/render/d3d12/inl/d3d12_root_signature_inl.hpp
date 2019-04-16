/**
 *	@file	d3d12_root_signature_inl.hpp
 *
 *	@brief	D3D12RootSignature クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_ROOT_SIGNATURE_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_ROOT_SIGNATURE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_root_signature.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12RootSignature::D3D12RootSignature(D3D12Device* device)
{
	::D3D12_ROOT_SIGNATURE_DESC desc;
	desc.NumParameters     = 0;
	desc.pParameters       = nullptr;
	desc.NumStaticSamplers = 0;
	desc.pStaticSamplers   = nullptr;
	desc.Flags             = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<::ID3DBlob> signature;
	ComPtr<::ID3DBlob> error;
	ThrowIfFailed(::D3D12SerializeRootSignature(
		&desc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
	m_root_signature = device->CreateRootSignature(
		0, signature->GetBufferPointer(), signature->GetBufferSize());
}

BKSGE_INLINE
D3D12RootSignature::~D3D12RootSignature()
{
}

BKSGE_INLINE ::ID3D12RootSignature*
D3D12RootSignature::Get(void) const
{
	return m_root_signature.Get();
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_ROOT_SIGNATURE_INL_HPP
