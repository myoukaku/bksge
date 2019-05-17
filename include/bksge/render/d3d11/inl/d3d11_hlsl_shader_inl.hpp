/**
 *	@file	d3d11_hlsl_shader_inl.hpp
 *
 *	@brief	D3D11HLSLShader クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_HLSL_SHADER_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_HLSL_SHADER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_hlsl_shader.hpp>
#include <bksge/render/d3d11/d3d11_constant_buffer.hpp>
#include <bksge/render/d3d11/d3d11_device.hpp>
#include <bksge/render/d3d11/d3d11_device_context.hpp>
#include <bksge/render/d3d_common/dxgiformat.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/d3d11shader.hpp>
#include <bksge/render/d3d_common/d3dcommon.hpp>
#include <bksge/render/d3d_common/d3dcompiler.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <bksge/memory/make_unique.hpp>
#include <string>
#include <vector>
#include <memory>
#include <utility>	// std::move

#include <iostream>

namespace bksge
{

namespace render
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

///////////////////////////////////////////////////////////////////////////////
//
//	D3D11HLSLShaderBase
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
D3D11HLSLShaderBase::D3D11HLSLShaderBase()
{
}

BKSGE_INLINE
D3D11HLSLShaderBase::~D3D11HLSLShaderBase()
{
}

BKSGE_INLINE bool
D3D11HLSLShaderBase::Compile(D3D11Device* device, std::string const& source)
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

	return true;
}

BKSGE_INLINE void
D3D11HLSLShaderBase::SetEnable(
	D3D11DeviceContext* device_context)
{
	VSetEnable(device_context);
}

BKSGE_INLINE void
D3D11HLSLShaderBase::LoadParameters(
	D3D11DeviceContext* device_context,
	ShaderParameterMap const& shader_parameter_map)
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
}

BKSGE_INLINE void
D3D11HLSLShaderBase::CreateConstantBuffer(D3D11Device* device)
{
	::D3D11_SHADER_DESC shader_desc;
	m_reflection->GetDesc(&shader_desc);

	for (::UINT i = 0; i < shader_desc.ConstantBuffers; i++)
	{
		auto cb = bksge::make_unique<D3D11ConstantBuffer>(
			device,
			m_reflection->GetConstantBufferByIndex(i));
		m_constant_buffers.push_back(std::move(cb));
	}
}

BKSGE_INLINE ComPtr<::ID3D11InputLayout>
D3D11HLSLShaderBase::CreateInputLayout(D3D11Device* device)
{
	::D3D11_SHADER_DESC shader_desc;
	m_reflection->GetDesc(&shader_desc);

	std::vector<::D3D11_INPUT_ELEMENT_DESC> input_layout_desc;
	for (::UINT i = 0; i < shader_desc.InputParameters; i++)
	{
		::D3D11_SIGNATURE_PARAMETER_DESC param_desc;
		m_reflection->GetInputParameterDesc(i, &param_desc);

		::D3D11_INPUT_ELEMENT_DESC element_desc;
		element_desc.SemanticName         = param_desc.SemanticName;
		element_desc.SemanticIndex        = param_desc.SemanticIndex;
		element_desc.InputSlot            = 0;
		element_desc.AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
		element_desc.InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
		element_desc.InstanceDataStepRate = 0;
		element_desc.Format               = GetElementDescFormat(param_desc);

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
//	D3D11HLSLVertexShader
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
D3D11HLSLVertexShader::D3D11HLSLVertexShader()
{
}

BKSGE_INLINE
D3D11HLSLVertexShader::~D3D11HLSLVertexShader()
{
}

BKSGE_INLINE const char*
D3D11HLSLVertexShader::VGetTargetString()
{
	return "vs_4_0";
}

BKSGE_INLINE void
D3D11HLSLVertexShader::VCreateShader(
	D3D11Device* device, ::ID3DBlob* micro_code)
{
	m_shader = device->CreateVertexShader(micro_code);
}

BKSGE_INLINE void
D3D11HLSLVertexShader::VSetEnable(
	D3D11DeviceContext* device_context)
{
	device_context->VSSetShader(m_shader.Get());
}

BKSGE_INLINE void
D3D11HLSLVertexShader::VSetConstantBuffers(
	D3D11DeviceContext* device_context,
	::UINT         start_slot,
	::UINT         num_buffers,
	::ID3D11Buffer* const* constant_buffers)
{
	device_context->VSSetConstantBuffers(
		start_slot, num_buffers, constant_buffers);
}

///////////////////////////////////////////////////////////////////////////////
//
//	D3D11HLSLPixelShader
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
D3D11HLSLPixelShader::D3D11HLSLPixelShader()
{
}

BKSGE_INLINE
D3D11HLSLPixelShader::~D3D11HLSLPixelShader()
{
}

BKSGE_INLINE const char*
D3D11HLSLPixelShader::VGetTargetString()
{
	return "ps_4_0";
}

BKSGE_INLINE void
D3D11HLSLPixelShader::VCreateShader(
	D3D11Device* device, ::ID3DBlob* micro_code)
{
	m_shader = device->CreatePixelShader(micro_code);
}

BKSGE_INLINE void
D3D11HLSLPixelShader::VSetEnable(
	D3D11DeviceContext* device_context)
{
	device_context->PSSetShader(m_shader.Get());
}

BKSGE_INLINE void
D3D11HLSLPixelShader::VSetConstantBuffers(
	D3D11DeviceContext* device_context,
	::UINT         start_slot,
	::UINT         num_buffers,
	::ID3D11Buffer* const* constant_buffers)
{
	device_context->PSSetConstantBuffers(
		start_slot, num_buffers, constant_buffers);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_HLSL_SHADER_INL_HPP
