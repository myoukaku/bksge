/**
 *	@file	root_signature_inl.hpp
 *
 *	@brief	RootSignature クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_ROOT_SIGNATURE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_ROOT_SIGNATURE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/root_signature.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_shader.hpp>
#include <bksge/core/render/d3d12/detail/root_parameters.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/d3d_common/throw_if_failed.hpp>

#include <iostream>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
RootSignature::RootSignature(
	Device* device,
	RootParameters const& root_parameters)
{
	//D3D12_STATIC_SAMPLER_DESC sampler = {};
	//sampler.Filter           = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	//sampler.AddressU         = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	//sampler.AddressV         = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	//sampler.AddressW         = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	//sampler.MipLODBias       = 0;
	//sampler.MaxAnisotropy    = 0;
	//sampler.ComparisonFunc   = D3D12_COMPARISON_FUNC_NEVER;
	//sampler.BorderColor      = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	//sampler.MinLOD           = 0.0f;
	//sampler.MaxLOD           = D3D12_FLOAT32_MAX;
	//sampler.ShaderRegister   = 0;
	//sampler.RegisterSpace    = 0;
	//sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	::D3D12_VERSIONED_ROOT_SIGNATURE_DESC desc;
	desc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
	desc.Desc_1_1.NumParameters     = root_parameters.GetSize();
	desc.Desc_1_1.pParameters       = root_parameters.GetData();
	desc.Desc_1_1.NumStaticSamplers = 0;
	desc.Desc_1_1.pStaticSamplers   = nullptr;
	desc.Desc_1_1.Flags             = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<::ID3DBlob> signature;
	ComPtr<::ID3DBlob> error;
	::HRESULT hr = ::D3D12SerializeVersionedRootSignature(
		&desc, &signature, &error);

	auto message =
		static_cast<const char*>(error ? error->GetBufferPointer() : nullptr);

	if (message)
	{
		std::cout << message << std::endl;
	}

	ThrowIfFailed(hr);

	m_root_signature = device->CreateRootSignature(
		0,	// node_mask
		signature->GetBufferPointer(),
		signature->GetBufferSize());
}

BKSGE_INLINE
RootSignature::~RootSignature()
{
}

BKSGE_INLINE ::ID3D12RootSignature*
RootSignature::Get(void) const
{
	return m_root_signature.Get();
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_ROOT_SIGNATURE_INL_HPP
