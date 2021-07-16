/**
 *	@file	hlsl_shader_inl.hpp
 *
 *	@brief	HlslShader クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_SHADER_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_SHADER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/hlsl_shader.hpp>
#include <bksge/core/render/d3d11/detail/constant_buffer.hpp>
#include <bksge/core/render/d3d11/detail/hlsl_sampler.hpp>
#include <bksge/core/render/d3d11/detail/hlsl_texture.hpp>
#include <bksge/core/render/d3d11/detail/device.hpp>
#include <bksge/core/render/d3d11/detail/device_context.hpp>
#include <bksge/core/render/d3d11/detail/resource_pool.hpp>
#include <bksge/core/render/d3d_common/dxgiformat.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/d3d11shader.hpp>
#include <bksge/core/render/d3d_common/d3dcommon.hpp>
#include <bksge/core/render/d3d_common/d3dcompiler.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/d3d_common/throw_if_failed.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/assert.hpp>
#include <utility>

#include <iostream>		// TODO

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::DXGI_FORMAT
GetElementDescFormat(::D3D11_SIGNATURE_PARAMETER_DESC const& param_desc)
{
	auto const mask = param_desc.Mask;
	auto const component_type = param_desc.ComponentType;

	if (mask == 1)
	{
		switch (component_type)
		{
		case D3D_REGISTER_COMPONENT_UINT32:  return DXGI_FORMAT_R32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:  return DXGI_FORMAT_R32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32_FLOAT;
		default: break;
		}
	}
	else if (mask <= 3)
	{
		switch (component_type)
		{
		case D3D_REGISTER_COMPONENT_UINT32:  return DXGI_FORMAT_R32G32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:  return DXGI_FORMAT_R32G32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32G32_FLOAT;
		default: break;
		}
	}
	else if (mask <= 7)
	{
		switch (component_type)
		{
		case D3D_REGISTER_COMPONENT_UINT32:  return DXGI_FORMAT_R32G32B32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:  return DXGI_FORMAT_R32G32B32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32G32B32_FLOAT;
		default: break;
		}
	}
	else if (mask <= 15)
	{
		switch (component_type)
		{
		case D3D_REGISTER_COMPONENT_UINT32:  return DXGI_FORMAT_R32G32B32A32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:  return DXGI_FORMAT_R32G32B32A32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		default: break;
		}
	}

	return DXGI_FORMAT_UNKNOWN;
}

}	// namespace detail

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
HlslShaderBase::Compile(Device* device, bksge::string const& source)
{
	const char* target = VGetTargetString();
	::UINT compile_flags = 0;
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

	VCreateShader(device, m_micro_code.Get());

	ThrowIfFailed(::D3DReflect(
		m_micro_code->GetBufferPointer(),
		m_micro_code->GetBufferSize(),
		IID_PPV_ARGS(&m_reflection)));

	CreateConstantBuffer(device);
	CreateShaderResources(device);

	return true;
}

BKSGE_INLINE void
HlslShaderBase::SetEnable(
	DeviceContext* device_context)
{
	VSetEnable(device_context);
}

BKSGE_INLINE void
HlslShaderBase::LoadParameters(
	ResourcePool* resource_pool,
	Device* device,
	DeviceContext* device_context,
	bksge::ShaderParameterMap const& shader_parameter_map)
{
	::UINT slot = 0;
	for (auto&& constant_buffer : m_constant_buffers)
	{
		constant_buffer->LoadParameters(
			device_context,
			shader_parameter_map);
		this->VSetConstantBuffers(
			device_context,
			slot,
			1,
			constant_buffer->buffer().GetAddressOf());
		++slot;
	}

	slot = 0;
	for (auto&& hlsl_sampler : m_hlsl_samplers)
	{
		hlsl_sampler->Load(
			resource_pool,
			device,
			device_context,
			shader_parameter_map,
			this,
			slot);

		++slot;
	}

	slot = 0;
	for (auto&& hlsl_texture : m_hlsl_textures)
	{
		hlsl_texture->Load(
			resource_pool,
			device,
			device_context,
			shader_parameter_map,
			this,
			slot);

		++slot;
	}
}

BKSGE_INLINE void
HlslShaderBase::CreateConstantBuffer(Device* device)
{
	::D3D11_SHADER_DESC shader_desc;
	ThrowIfFailed(m_reflection->GetDesc(&shader_desc));

	for (::UINT i = 0; i < shader_desc.ConstantBuffers; i++)
	{
		auto cb = bksge::make_unique<ConstantBuffer>(
			device,
			m_reflection->GetConstantBufferByIndex(i));
		m_constant_buffers.push_back(std::move(cb));
	}
}

BKSGE_INLINE void
HlslShaderBase::CreateShaderResources(Device* /*device*/)
{
	::D3D11_SHADER_DESC shader_desc;
	ThrowIfFailed(m_reflection->GetDesc(&shader_desc));

	for (::UINT i = 0; i < shader_desc.BoundResources; i++)
	{
		::D3D11_SHADER_INPUT_BIND_DESC bind_desc;
		ThrowIfFailed(m_reflection->GetResourceBindingDesc(i, &bind_desc));

		switch (bind_desc.Type)
		{
		case D3D_SIT_TEXTURE:
			{
				auto hlsl_texture = bksge::make_unique<HlslTexture>(bind_desc);
				m_hlsl_textures.push_back(std::move(hlsl_texture));
			}
			break;
		case D3D_SIT_SAMPLER:
			{
				auto hlsl_sampler = bksge::make_unique<HlslSampler>(bind_desc);
				m_hlsl_samplers.push_back(std::move(hlsl_sampler));
			}
			break;
		default:
			//BKSGE_ASSERT(false);
			break;
		}
	}
}

BKSGE_INLINE ComPtr<::ID3D11InputLayout>
HlslShaderBase::CreateInputLayout(Device* device)
{
	::D3D11_SHADER_DESC shader_desc;
	ThrowIfFailed(m_reflection->GetDesc(&shader_desc));

	bksge::vector<::D3D11_INPUT_ELEMENT_DESC> input_layout_desc;
	for (::UINT i = 0; i < shader_desc.InputParameters; i++)
	{
		::D3D11_SIGNATURE_PARAMETER_DESC param_desc;
		ThrowIfFailed(m_reflection->GetInputParameterDesc(i, &param_desc));

		::D3D11_INPUT_ELEMENT_DESC element_desc;
		element_desc.SemanticName         = param_desc.SemanticName;
		element_desc.SemanticIndex        = param_desc.SemanticIndex;
		element_desc.InputSlot            = 0;
		element_desc.AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
		element_desc.InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
		element_desc.InstanceDataStepRate = 0;
		element_desc.Format               = detail::GetElementDescFormat(param_desc);

		input_layout_desc.push_back(element_desc);
	}

	return device->CreateInputLayout(
		&input_layout_desc[0],
		static_cast<::UINT>(input_layout_desc.size()),
		m_micro_code->GetBufferPointer(),
		m_micro_code->GetBufferSize());
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
	return "vs_4_0";
}

BKSGE_INLINE void
HlslVertexShader::VCreateShader(
	Device* device, ::ID3DBlob* micro_code)
{
	m_shader = device->CreateVertexShader(micro_code);
}

BKSGE_INLINE void
HlslVertexShader::VSetEnable(
	DeviceContext* device_context)
{
	device_context->VSSetShader(m_shader.Get());
}

BKSGE_INLINE void
HlslVertexShader::VSetConstantBuffers(
	DeviceContext* device_context,
	::UINT         start_slot,
	::UINT         num_buffers,
	::ID3D11Buffer* const* constant_buffers)
{
	device_context->VSSetConstantBuffers(
		start_slot, num_buffers, constant_buffers);
}

BKSGE_INLINE void
HlslVertexShader::VSetSamplers(
	DeviceContext* device_context,
	::UINT         start_slot,
	::UINT         num_samplers,
	::ID3D11SamplerState* const* samplers)
{
	device_context->VSSetSamplers(
		start_slot, num_samplers, samplers);
}

BKSGE_INLINE void
HlslVertexShader::VSetShaderResources(
	DeviceContext* device_context,
	::UINT         start_slot,
	::UINT         num_views,
	::ID3D11ShaderResourceView* const* shader_resource_views)
{
	device_context->VSSetShaderResources(
		start_slot, num_views, shader_resource_views);
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
	return "ps_4_0";
}

BKSGE_INLINE void
HlslPixelShader::VCreateShader(
	Device* device, ::ID3DBlob* micro_code)
{
	m_shader = device->CreatePixelShader(micro_code);
}

BKSGE_INLINE void
HlslPixelShader::VSetEnable(
	DeviceContext* device_context)
{
	device_context->PSSetShader(m_shader.Get());
}

BKSGE_INLINE void
HlslPixelShader::VSetConstantBuffers(
	DeviceContext* device_context,
	::UINT         start_slot,
	::UINT         num_buffers,
	::ID3D11Buffer* const* constant_buffers)
{
	device_context->PSSetConstantBuffers(
		start_slot, num_buffers, constant_buffers);
}

BKSGE_INLINE void
HlslPixelShader::VSetSamplers(
	DeviceContext* device_context,
	::UINT         start_slot,
	::UINT         num_samplers,
	::ID3D11SamplerState* const* samplers)
{
	device_context->PSSetSamplers(
		start_slot, num_samplers, samplers);
}

BKSGE_INLINE void
HlslPixelShader::VSetShaderResources(
	DeviceContext* device_context,
	::UINT         start_slot,
	::UINT         num_views,
	::ID3D11ShaderResourceView* const* shader_resource_views)
{
	device_context->PSSetShaderResources(
		start_slot, num_views, shader_resource_views);
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_SHADER_INL_HPP
