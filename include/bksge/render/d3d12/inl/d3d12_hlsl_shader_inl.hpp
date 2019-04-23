/**
 *	@file	d3d12_hlsl_shader_inl.hpp
 *
 *	@brief	D3D12HLSLShader クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_HLSL_SHADER_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_HLSL_SHADER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_hlsl_shader.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12_input_layout.hpp>
#include <bksge/render/d3d12/d3d12_constant_buffer.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/d3d_common/d3dcompiler.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <bksge/memory/make_unique.hpp>
#include <string>
#include <utility>
#include <iostream>

namespace bksge
{

namespace render
{

///////////////////////////////////////////////////////////////////////////////
//
//	D3D12HLSLShaderBase
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
D3D12HLSLShaderBase::D3D12HLSLShaderBase()
{
}

BKSGE_INLINE
D3D12HLSLShaderBase::~D3D12HLSLShaderBase()
{
}

BKSGE_INLINE bool
D3D12HLSLShaderBase::Compile(D3D12Device* /*device*/, std::string const& source)
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

	return true;
}

BKSGE_INLINE std::unique_ptr<D3D12InputLayout>
D3D12HLSLShaderBase::CreateInputLayout(void)
{
	ComPtr<::ID3D12ShaderReflection> reflection;
	ThrowIfFailed(::D3DReflect(
		m_micro_code->GetBufferPointer(),
		m_micro_code->GetBufferSize(),
		IID_PPV_ARGS(&reflection)));

	return bksge::make_unique<D3D12InputLayout>(reflection);
}

BKSGE_INLINE auto
D3D12HLSLShaderBase::CreateConstantBuffers(D3D12Device* device)
-> D3D12ConstantBuffers
{
	D3D12ConstantBuffers constant_buffers;

	ComPtr<::ID3D12ShaderReflection> reflection;
	ThrowIfFailed(::D3DReflect(
		m_micro_code->GetBufferPointer(),
		m_micro_code->GetBufferSize(),
		IID_PPV_ARGS(&reflection)));

	::D3D12_SHADER_DESC shader_desc;
	reflection->GetDesc(&shader_desc);

	for (::UINT i = 0; i < shader_desc.ConstantBuffers; i++)
	{
		auto cb = bksge::make_unique<D3D12ConstantBuffer>(
			device,
			reflection->GetConstantBufferByIndex(i));
		constant_buffers.push_back(std::move(cb));
	}

	return constant_buffers;
}

//BKSGE_INLINE void
//D3D12HLSLShaderBase::UpdateParameters(
//	ShaderParameterMap const& shader_parameter_map)
//{
//	for (auto&& constant_buffers : m_constant_buffers)
//	{
//		constant_buffers->UpdateParameters(shader_parameter_map);
//	}
//}
//
//BKSGE_INLINE void
//D3D12HLSLShaderBase::SetEnable(D3D12CommandList* command_list)
//{
//	for (auto&& constant_buffers : m_constant_buffers)
//	{
//		constant_buffers->SetEnable(command_list);
//	}
//}

BKSGE_INLINE ::UINT
D3D12HLSLShaderBase::GetConstantBufferCount(void) const
{
	ComPtr<::ID3D12ShaderReflection> reflection;
	ThrowIfFailed(::D3DReflect(
		m_micro_code->GetBufferPointer(),
		m_micro_code->GetBufferSize(),
		IID_PPV_ARGS(&reflection)));

	::D3D12_SHADER_DESC shader_desc;
	reflection->GetDesc(&shader_desc);

	return shader_desc.ConstantBuffers;
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
D3D12HLSLShaderBase::GetBytecode(void) const
{
	return {
		m_micro_code->GetBufferPointer(),
		m_micro_code->GetBufferSize()
	};
}

///////////////////////////////////////////////////////////////////////////////
//
//	D3D12HLSLVertexShader
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
D3D12HLSLVertexShader::D3D12HLSLVertexShader()
{
}

BKSGE_INLINE
D3D12HLSLVertexShader::~D3D12HLSLVertexShader()
{
}

BKSGE_INLINE const char*
D3D12HLSLVertexShader::VGetTargetString()
{
	return "vs_5_0";
}

///////////////////////////////////////////////////////////////////////////////
//
//	D3D12HLSLPixelShader
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
D3D12HLSLPixelShader::D3D12HLSLPixelShader()
{
}

BKSGE_INLINE
D3D12HLSLPixelShader::~D3D12HLSLPixelShader()
{
}

BKSGE_INLINE const char*
D3D12HLSLPixelShader::VGetTargetString()
{
	return "ps_5_0";
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_HLSL_SHADER_INL_HPP
