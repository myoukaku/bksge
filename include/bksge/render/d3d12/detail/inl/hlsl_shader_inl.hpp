/**
 *	@file	hlsl_shader_inl.hpp
 *
 *	@brief	HLSLShader クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_SHADER_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_SHADER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/hlsl_shader.hpp>
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d12/detail/input_layout.hpp>
#include <bksge/render/d3d12/detail/constant_buffer.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/d3d_common/d3dcompiler.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <bksge/memory/make_unique.hpp>
#include <memory>
#include <string>
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
//	HLSLShaderBase
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
HLSLShaderBase::HLSLShaderBase()
{
}

BKSGE_INLINE
HLSLShaderBase::~HLSLShaderBase()
{
}

BKSGE_INLINE bool
HLSLShaderBase::Compile(Device* /*device*/, std::string const& source)
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

	return true;
}

BKSGE_INLINE std::unique_ptr<InputLayout>
HLSLShaderBase::CreateInputLayout(void)
{
	return bksge::make_unique<InputLayout>(m_reflection);
}

BKSGE_INLINE auto
HLSLShaderBase::CreateConstantBuffers(Device* device)
-> ConstantBuffers
{
	ConstantBuffers constant_buffers;

	::D3D12_SHADER_DESC shader_desc;
	m_reflection->GetDesc(&shader_desc);

	for (::UINT i = 0; i < shader_desc.ConstantBuffers; i++)
	{
		auto cb = bksge::make_unique<ConstantBuffer>(
			device,
			m_reflection->GetConstantBufferByIndex(i));
		constant_buffers.push_back(std::move(cb));
	}

	return constant_buffers;
}

BKSGE_INLINE ::UINT
HLSLShaderBase::GetConstantBufferCount(void) const
{
	::D3D12_SHADER_DESC shader_desc;
	m_reflection->GetDesc(&shader_desc);

	return shader_desc.ConstantBuffers;
}

BKSGE_INLINE ::D3D12_SHADER_BYTECODE
HLSLShaderBase::GetBytecode(void) const
{
	return {
		m_micro_code->GetBufferPointer(),
		m_micro_code->GetBufferSize()
	};
}

///////////////////////////////////////////////////////////////////////////////
//
//	HLSLVertexShader
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
HLSLVertexShader::HLSLVertexShader()
{
}

BKSGE_INLINE
HLSLVertexShader::~HLSLVertexShader()
{
}

BKSGE_INLINE const char*
HLSLVertexShader::VGetTargetString()
{
	return "vs_5_0";
}

///////////////////////////////////////////////////////////////////////////////
//
//	HLSLPixelShader
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
HLSLPixelShader::HLSLPixelShader()
{
}

BKSGE_INLINE
HLSLPixelShader::~HLSLPixelShader()
{
}

BKSGE_INLINE const char*
HLSLPixelShader::VGetTargetString()
{
	return "ps_5_0";
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_SHADER_INL_HPP
