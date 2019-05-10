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
#include <bksge/render/d3d11/fwd/d3d11_constant_buffer_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_context_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/d3dcommon.hpp>
#include <bksge/render/d3d_common/d3d11shader.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <string>
#include <vector>
#include <memory>

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

	ComPtr<::ID3D11InputLayout> CreateInputLayout(D3D11Device* device);

	void SetEnable(D3D11DeviceContext* device_context);

	void LoadParameters(
		D3D11DeviceContext* device_context,
		ShaderParameterMap const& shader_parameter_map);

private:
	void CreateConstantBuffer(D3D11Device* device);

	virtual const char* VGetTargetString() = 0;
	virtual void VCreateShader(D3D11Device* device, ::ID3DBlob* micro_code) = 0;
	virtual void VSetEnable(D3D11DeviceContext* device_context) = 0;
	virtual void VSetConstantBuffers(
		D3D11DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers) = 0;

private:
	using D3D11ConstantBuffers = std::vector<std::unique_ptr<D3D11ConstantBuffer>>;

	ComPtr<::ID3DBlob>					m_micro_code;
	ComPtr<::ID3D11ShaderReflection>	m_reflection;
	D3D11ConstantBuffers				m_constant_buffers;
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
	void VCreateShader(D3D11Device* device, ::ID3DBlob* micro_code) override;
	void VSetEnable(D3D11DeviceContext* device_context) override;
	void VSetConstantBuffers(
		D3D11DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers) override;

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
	const char* VGetTargetString() override;
	void VCreateShader(D3D11Device* device, ::ID3DBlob* micro_code) override;
	void VSetEnable(D3D11DeviceContext* device_context) override;
	void VSetConstantBuffers(
		D3D11DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers) override;

private:
	ComPtr<::ID3D11PixelShader>		m_shader;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_hlsl_shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_HLSL_SHADER_HPP
