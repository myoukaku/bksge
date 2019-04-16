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
#include <bksge/render/d3d11/fwd/d3d11_device_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_context_fwd.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
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

	bool Compile(D3D11Device* device, std::string const& source);

	void Draw(D3D11DeviceContext* device_context);

private:
	virtual const char* VGetTargetString() = 0;
	virtual bool VCompile(D3D11Device* device, ::ID3DBlob* micro_code) = 0;
	virtual void VDraw(D3D11DeviceContext* device_context) = 0;
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
	const char* VGetTargetString() override;
	bool VCompile(D3D11Device* device, ::ID3DBlob* micro_code) override;
	void VDraw(D3D11DeviceContext* device_context) override;

private:
	ComPtr<::ID3D11VertexShader>	m_shader;
	ComPtr<::ID3D11InputLayout>		m_input_layout;
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
	const char* VGetTargetString() override;
	bool VCompile(D3D11Device* device, ::ID3DBlob* micro_code) override;
	void VDraw(D3D11DeviceContext* device_context) override;

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
