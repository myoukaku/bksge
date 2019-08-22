/**
 *	@file	hlsl_shader.hpp
 *
 *	@brief	HLSLShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_HLSL_SHADER_HPP
#define BKSGE_RENDER_D3D11_DETAIL_HLSL_SHADER_HPP

#include <bksge/render/d3d11/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/constant_buffer_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/device_context_fwd.hpp>
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

namespace d3d11
{

/**
 *	@brief
 */
class HLSLShaderBase
{
public:
	HLSLShaderBase();

	virtual ~HLSLShaderBase() = 0;

	bool Compile(Device* device, std::string const& source);

	ComPtr<::ID3D11InputLayout> CreateInputLayout(Device* device);

	void SetEnable(DeviceContext* device_context);

	void LoadParameters(
		DeviceContext* device_context,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	void CreateConstantBuffer(Device* device);

	virtual const char* VGetTargetString() = 0;
	virtual void VCreateShader(Device* device, ::ID3DBlob* micro_code) = 0;
	virtual void VSetEnable(DeviceContext* device_context) = 0;
	virtual void VSetConstantBuffers(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers) = 0;

private:
	using ConstantBuffers = std::vector<std::unique_ptr<ConstantBuffer>>;

	ComPtr<::ID3DBlob>					m_micro_code;
	ComPtr<::ID3D11ShaderReflection>	m_reflection;
	ConstantBuffers						m_constant_buffers;
};

/**
 *	@brief
 */
class HLSLVertexShader : public HLSLShaderBase
{
public:
	HLSLVertexShader();

	virtual ~HLSLVertexShader();

private:
	const char* VGetTargetString() override;
	void VCreateShader(Device* device, ::ID3DBlob* micro_code) override;
	void VSetEnable(DeviceContext* device_context) override;
	void VSetConstantBuffers(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers) override;

private:
	ComPtr<::ID3D11VertexShader>	m_shader;
};

/**
 *	@brief
 */
class HLSLPixelShader : public HLSLShaderBase
{
public:
	HLSLPixelShader();

	virtual ~HLSLPixelShader();

private:
	const char* VGetTargetString() override;
	void VCreateShader(Device* device, ::ID3DBlob* micro_code) override;
	void VSetEnable(DeviceContext* device_context) override;
	void VSetConstantBuffers(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers) override;

private:
	ComPtr<::ID3D11PixelShader>		m_shader;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/hlsl_shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_HLSL_SHADER_HPP
