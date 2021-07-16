/**
 *	@file	hlsl_shader_inl.hpp
 *
 *	@brief	HlslShader クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_HLSL_SHADER_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_HLSL_SHADER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/hlsl_shader.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d12/detail/input_layout.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_constant_buffer.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_texture.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_sampler.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/d3d_common/d3dcompiler.hpp>
#include <bksge/core/render/d3d_common/throw_if_failed.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/assert.hpp>
#include <utility>
#include <iostream>

namespace bksge
{

namespace render
{

namespace d3d12
{

///////////////////////////////////////////////////////////////////////////////
//
//	HlslShaderBase
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
HlslShaderBase::HlslShaderBase()
{
}

BKSGE_INLINE
HlslShaderBase::~HlslShaderBase()
{
}

BKSGE_INLINE bool
HlslShaderBase::Compile(Device* /*device*/, bksge::string const& source)
{
	const char* target = VGetTargetString();
#if defined(_DEBUG)
	::UINT compile_flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	::UINT compile_flags = 0;
#endif

	ComPtr<::ID3DBlob> errors;
	::HRESULT hr = ::D3DCompile(
		source.c_str(),
		source.size(),
		nullptr,
		nullptr,
		nullptr,
		"main",
		target,
		compile_flags,
		0,
		m_micro_code.ReleaseAndGetAddressOf(),
		errors.GetAddressOf());

	auto message =
		static_cast<const char*>(errors ? errors->GetBufferPointer() : nullptr);
	if (message)
	{
		std::cout << message << std::endl;
	}

	if (FAILED(hr))
	{
		return false;
	}

	ThrowIfFailed(::D3DReflect(
		m_micro_code->GetBufferPointer(),
		m_micro_code->GetBufferSize(),
		IID_PPV_ARGS(&m_reflection)));

	CreateDescriptorRanges();

	return true;
}

BKSGE_INLINE void
HlslShaderBase::CreateDescriptorRanges(void)
{
	::D3D12_SHADER_DESC shader_desc;
	ThrowIfFailed(m_reflection->GetDesc(&shader_desc));

	::UINT cbv_count = shader_desc.ConstantBuffers;

	::UINT srv_count = 0;
	::UINT sampler_count = 0;
	for (::UINT i = 0; i < shader_desc.BoundResources; i++)
	{
		::D3D12_SHADER_INPUT_BIND_DESC bind_desc;
		ThrowIfFailed(m_reflection->GetResourceBindingDesc(i, &bind_desc));

		switch (bind_desc.Type)
		{
		case D3D_SIT_TEXTURE:
			++srv_count;
			// FALLTHROUGH ? TODO
		case D3D_SIT_SAMPLER:
			++sampler_count;
			break;
		default:
			//BKSGE_ASSERT(false);
			break;
		}
	}

	if (cbv_count != 0)
	{
		::D3D12_DESCRIPTOR_RANGE1 range;
		range.RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		range.NumDescriptors     = cbv_count;
		range.BaseShaderRegister = 0;
		range.RegisterSpace      = 0;
		range.Flags              = D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE;
		range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		m_descriptor_ranges.push_back(range);
	}

	if (srv_count != 0)
	{
		::D3D12_DESCRIPTOR_RANGE1 range;
		range.RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		range.NumDescriptors     = srv_count;
		range.BaseShaderRegister = 0;
		range.RegisterSpace      = 0;
		range.Flags              = D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE;
		range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		m_descriptor_ranges.push_back(range);
	}

	if (sampler_count != 0)
	{
		::D3D12_DESCRIPTOR_RANGE1 range;
		range.RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
		range.NumDescriptors     = sampler_count;
		range.BaseShaderRegister = 0;
		range.RegisterSpace      = 0;
		range.Flags              = D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE;
		range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		m_sampler_descriptor_ranges.push_back(range);
	}
}

BKSGE_INLINE bksge::unique_ptr<InputLayout>
HlslShaderBase::CreateInputLayout(void)
{
	return bksge::make_unique<InputLayout>(m_reflection);
}

BKSGE_INLINE void
HlslShaderBase::CreateHlslConstantBuffers(/*Device* device, */HlslConstantBuffers* hlsl_constant_buffers)
{
	::D3D12_SHADER_DESC shader_desc;
	ThrowIfFailed(m_reflection->GetDesc(&shader_desc));

	for (::UINT i = 0; i < shader_desc.ConstantBuffers; i++)
	{
		auto cb = bksge::make_unique<HlslConstantBuffer>(
//			device,
			m_reflection->GetConstantBufferByIndex(i));
		hlsl_constant_buffers->push_back(std::move(cb));
	}
}

BKSGE_INLINE void
HlslShaderBase::CreateHlslTextures(HlslTextures* hlsl_textures)
{
	::D3D12_SHADER_DESC shader_desc;
	ThrowIfFailed(m_reflection->GetDesc(&shader_desc));

	for (::UINT i = 0; i < shader_desc.BoundResources; i++)
	{
		::D3D12_SHADER_INPUT_BIND_DESC bind_desc;
		ThrowIfFailed(m_reflection->GetResourceBindingDesc(i, &bind_desc));

		switch (bind_desc.Type)
		{
		case D3D_SIT_TEXTURE:
			hlsl_textures->push_back(bksge::make_unique<HlslTexture>(bind_desc));
			break;
		default:
			//BKSGE_ASSERT(false);
			break;
		}
	}
}

BKSGE_INLINE void
HlslShaderBase::CreateHlslSamplers(HlslSamplers* hlsl_samplers)
{
	::D3D12_SHADER_DESC shader_desc;
	ThrowIfFailed(m_reflection->GetDesc(&shader_desc));

	for (::UINT i = 0; i < shader_desc.BoundResources; i++)
	{
		::D3D12_SHADER_INPUT_BIND_DESC bind_desc;
		ThrowIfFailed(m_reflection->GetResourceBindingDesc(i, &bind_desc));

		switch (bind_desc.Type)
		{
		case D3D_SIT_SAMPLER:
			hlsl_samplers->push_back(bksge::make_unique<HlslSampler>(bind_desc));
			break;
		default:
			//BKSGE_ASSERT(false);
			break;
		}
	}
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
HlslShaderBase::GetBytecode(void) const
{
	return
	{
		m_micro_code->GetBufferPointer(),
		m_micro_code->GetBufferSize()
	};
}

BKSGE_INLINE bksge::vector<::D3D12_DESCRIPTOR_RANGE1> const&
HlslShaderBase::GetDescriptorRanges(void) const
{
	return m_descriptor_ranges;
}

BKSGE_INLINE bksge::vector<::D3D12_DESCRIPTOR_RANGE1> const&
HlslShaderBase::GetSamplerDescriptorRanges(void) const
{
	return m_sampler_descriptor_ranges;
}

///////////////////////////////////////////////////////////////////////////////
//
//	HlslVertexShader
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
HlslVertexShader::HlslVertexShader()
{
}

BKSGE_INLINE
HlslVertexShader::~HlslVertexShader()
{
}

BKSGE_INLINE const char*
HlslVertexShader::VGetTargetString()
{
	return "vs_5_0";
}

///////////////////////////////////////////////////////////////////////////////
//
//	HlslPixelShader
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
HlslPixelShader::HlslPixelShader()
{
}

BKSGE_INLINE
HlslPixelShader::~HlslPixelShader()
{
}

BKSGE_INLINE const char*
HlslPixelShader::VGetTargetString()
{
	return "ps_5_0";
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_HLSL_SHADER_INL_HPP
