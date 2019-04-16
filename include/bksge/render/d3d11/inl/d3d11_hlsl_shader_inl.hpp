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
#include <bksge/render/d3d11/d3d11_renderer.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/d3dcompiler.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/shader_stage.hpp>
#include <bksge/assert.hpp>
#include <iostream>

namespace bksge
{

namespace render
{

///////////////////////////////////////////////////////////////////////////////
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
D3D11HLSLShaderBase::Compile(D3D11Renderer* renderer, std::string const& source)
{
	const char* target = VGetTargetString();
	::UINT compile_flags = 0;
	ComPtr<::ID3DBlob> micro_code;
	ComPtr<::ID3DBlob> errors;

	::HRESULT hr = ::D3DCompile(
		source.c_str(),      // [in] Pointer to the shader in memory. 
		source.size(),       // [in] Size of the shader in memory.  
		nullptr,			 // [in] Optional. You can use this parameter for strings that specify error messages.
		nullptr,             // [in] Optional. Pointer to a NULL-terminated array of macro definitions. See D3D_SHADER_MACRO. If not used, set this to NULL. 
		nullptr,			 // [in] Optional. Pointer to an ID3DInclude Interface interface for handling include files. Setting this to NULL will cause a compile error if a shader contains a #include. 
		"main",				 // [in] Name of the shader-entrypoint function where shader execution begins. 
		target,              // [in] A string that specifies the shader model; can be any profile in shader model 4 or higher. 
		compile_flags,       // [in] Effect compile flags - no D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY at the first try...
		0,                   // [in] Effect compile flags
		micro_code.GetAddressOf(),// [out] A pointer to an ID3DBlob Interface which contains the compiled shader, as well as any embedded debug and symbol-table information. 
		errors.GetAddressOf() // [out] A pointer to an ID3DBlob Interface which contains a listing of errors and warnings that occurred during compilation. These errors and warnings are identical to the the debug output from a debugger.
	);

	auto message = static_cast<const char*>(errors ? errors->GetBufferPointer() : nullptr);
	if (message)
	{
		std::cout << message << std::endl;
	}

	if (FAILED(hr))
	{
		return false;
	}

	return VCompile(renderer, micro_code.Get());
}

///////////////////////////////////////////////////////////////////////////////
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

BKSGE_INLINE bool
D3D11HLSLVertexShader::VCompile(D3D11Renderer* renderer, ::ID3DBlob* micro_code)
{
	m_shader = renderer->CreateVertexShader(micro_code);
	renderer->VSSetShader(m_shader.Get());

	const ::D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	auto input_layout = renderer->CreateInputLayout(
		ied,
		1u,
		micro_code->GetBufferPointer(),
		micro_code->GetBufferSize());

	// bind vertex layout
	renderer->SetInputLayout(input_layout.Get());

	return true;
}

///////////////////////////////////////////////////////////////////////////////
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

BKSGE_INLINE bool
D3D11HLSLPixelShader::VCompile(D3D11Renderer* renderer, ::ID3DBlob* micro_code)
{
	m_shader = renderer->CreatePixelShader(micro_code);
	renderer->PSSetShader(m_shader.Get());
	return true;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_HLSL_SHADER_INL_HPP
