/**
 *	@file	d3d11_hlsl_shader.hpp
 *
 *	@brief	D3D11HLSLShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_HLSL_SHADER_HPP
#define BKSGE_RENDER_D3D11_D3D11_HLSL_SHADER_HPP

#include <bksge/render/d3d11/fwd/d3d11_hlsl_shader_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_renderer_fwd.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d11/com_ptr.hpp>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D11HLSLShaderBase
{
public:
	D3D11HLSLShaderBase();

	virtual ~D3D11HLSLShaderBase() = 0;

	bool Compile(D3D11Renderer* renderer, std::string const& source);

private:
	virtual const char* VGetTargetString() = 0;
	virtual bool VCompile(D3D11Renderer* renderer, ::ID3DBlob* micro_code) = 0;
};

/**
 *	@brief
 */
class D3D11HLSLVertexShader : public D3D11HLSLShaderBase
{
public:
	D3D11HLSLVertexShader();

	virtual ~D3D11HLSLVertexShader();

private:
	virtual const char* VGetTargetString();
	virtual bool VCompile(D3D11Renderer* renderer, ::ID3DBlob* micro_code);

private:
	ComPtr<::ID3D11VertexShader>	m_shader;
};

/**
 *	@brief
 */
class D3D11HLSLPixelShader : public D3D11HLSLShaderBase
{
public:
	D3D11HLSLPixelShader();

	virtual ~D3D11HLSLPixelShader();

private:
	virtual const char* VGetTargetString();
	virtual bool VCompile(D3D11Renderer* renderer, ::ID3DBlob* micro_code);

private:
	ComPtr<::ID3D11PixelShader>	m_shader;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_hlsl_shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_HLSL_SHADER_HPP
