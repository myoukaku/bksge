/**
 *	@file	hlsl_shader.hpp
 *
 *	@brief	HlslShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_SHADER_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_SHADER_HPP

#include <bksge/core/render/d3d11/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/constant_buffer_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/hlsl_sampler_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/hlsl_texture_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/d3dcommon.hpp>
#include <bksge/core/render/d3d_common/d3d11shader.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
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
class HlslShaderBase
{
public:
	HlslShaderBase();

	virtual ~HlslShaderBase() = 0;

	bool Compile(Device* device, std::string const& source);

	ComPtr<::ID3D11InputLayout> CreateInputLayout(Device* device);

	void SetEnable(DeviceContext* device_context);

	void LoadParameters(
		ResourceCache* resource_cache,
		DeviceContext* device_context,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	void CreateConstantBuffer(Device* device);
	void CreateShaderResources(Device* device);

	virtual const char* VGetTargetString() = 0;
	virtual void VCreateShader(Device* device, ::ID3DBlob* micro_code) = 0;
	virtual void VSetEnable(DeviceContext* device_context) = 0;
	virtual void VSetConstantBuffers(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers) = 0;

public:
	virtual void VSetSamplers(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_samplers,
		::ID3D11SamplerState* const* samplers) = 0;
	virtual void VSetShaderResources(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) = 0;

private:
	using ConstantBuffers = std::vector<std::unique_ptr<ConstantBuffer>>;
	using HlslSamplers = std::vector<std::unique_ptr<HlslSampler>>;
	using HlslTextures = std::vector<std::unique_ptr<HlslTexture>>;

	ComPtr<::ID3DBlob>					m_micro_code;
	ComPtr<::ID3D11ShaderReflection>	m_reflection;
	ConstantBuffers						m_constant_buffers;
	HlslSamplers						m_hlsl_samplers;
	HlslTextures						m_hlsl_textures;
};

/**
 *	@brief
 */
class HlslVertexShader : public HlslShaderBase
{
public:
	HlslVertexShader();

	virtual ~HlslVertexShader();

private:
	const char* VGetTargetString() override;
	void VCreateShader(Device* device, ::ID3DBlob* micro_code) override;
	void VSetEnable(DeviceContext* device_context) override;
	void VSetConstantBuffers(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers) override;
	void VSetSamplers(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_samplers,
		::ID3D11SamplerState* const* samplers) override;
	void VSetShaderResources(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) override;

private:
	ComPtr<::ID3D11VertexShader>	m_shader;
};

/**
 *	@brief
 */
class HlslPixelShader : public HlslShaderBase
{
public:
	HlslPixelShader();

	virtual ~HlslPixelShader();

private:
	const char* VGetTargetString() override;
	void VCreateShader(Device* device, ::ID3DBlob* micro_code) override;
	void VSetEnable(DeviceContext* device_context) override;
	void VSetConstantBuffers(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers) override;
	void VSetSamplers(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_samplers,
		::ID3D11SamplerState* const* samplers) override;
	void VSetShaderResources(
		DeviceContext* device_context,
		::UINT         start_slot,
		::UINT         num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views) override;

private:
	ComPtr<::ID3D11PixelShader>		m_shader;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/hlsl_shader_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_SHADER_HPP
