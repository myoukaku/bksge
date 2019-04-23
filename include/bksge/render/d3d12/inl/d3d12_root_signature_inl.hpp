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
#include <bksge/render/d3d12/d3d12_hlsl_shader.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <map>
#include <memory>
#include <vector>

#include <iostream>

namespace bksge
{

namespace render
{

inline D3D12_SHADER_VISIBILITY
ToShaderVisibility(ShaderStage stage)
{
	switch (stage)
	{
	case ShaderStage::kVertex:                 return D3D12_SHADER_VISIBILITY_VERTEX;
	case ShaderStage::kTessellationControl:    return D3D12_SHADER_VISIBILITY_HULL;
	case ShaderStage::kTessellationEvaluation: return D3D12_SHADER_VISIBILITY_DOMAIN;
	case ShaderStage::kGeometry:               return D3D12_SHADER_VISIBILITY_GEOMETRY;
	case ShaderStage::kFragment:               return D3D12_SHADER_VISIBILITY_PIXEL;
	}
	return D3D12_SHADER_VISIBILITY_ALL;
}

BKSGE_INLINE
D3D12RootSignature::D3D12RootSignature(
	D3D12Device* device,
	D3D12HLSLShaderMap const& shader_map)
{
	std::vector<D3D12_DESCRIPTOR_RANGE> ranges;
	for (auto&& it : shader_map)
	{
		auto const& shader = it.second;
		if (shader->GetConstantBufferCount() != 0)
		{
			D3D12_DESCRIPTOR_RANGE range;
			range.RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			range.NumDescriptors     = shader->GetConstantBufferCount();
			range.BaseShaderRegister = 0;
			range.RegisterSpace      = 0;
			range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
			ranges.push_back(range);
		}
	}

	std::size_t i = 0;
	std::vector<D3D12_ROOT_PARAMETER> root_parameters;
	for (auto&& it : shader_map)
	{
		auto const& stage = it.first;
		auto const& shader = it.second;
		if (shader->GetConstantBufferCount() != 0)
		{
			D3D12_ROOT_PARAMETER root_parameter;
			root_parameter.ParameterType    = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			root_parameter.ShaderVisibility = ToShaderVisibility(stage);
			root_parameter.DescriptorTable  = { 1, &ranges[i] };
			root_parameters.push_back(root_parameter);

			++i;
		}
	}

	m_root_parameter_count = static_cast<::UINT>(root_parameters.size());

	::D3D12_ROOT_SIGNATURE_DESC desc;
	desc.NumParameters     = m_root_parameter_count;
	desc.pParameters       = root_parameters.empty() ? nullptr : root_parameters.data();
	desc.NumStaticSamplers = 0;
	desc.pStaticSamplers   = nullptr;
	desc.Flags             = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<::ID3DBlob> signature;
	ComPtr<::ID3DBlob> error;
	::HRESULT hr = ::D3D12SerializeRootSignature(
		&desc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);

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
D3D12RootSignature::~D3D12RootSignature()
{
}

BKSGE_INLINE ::ID3D12RootSignature*
D3D12RootSignature::Get(void) const
{
	return m_root_signature.Get();
}

BKSGE_INLINE ::UINT
D3D12RootSignature::GetRootParameterCount(void) const
{
	return m_root_parameter_count;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_ROOT_SIGNATURE_INL_HPP
