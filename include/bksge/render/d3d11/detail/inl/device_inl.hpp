﻿/**
 *	@file	device_inl.hpp
 *
 *	@brief	Device の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_DEVICE_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_DEVICE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/device.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/d3d_common/dxgi.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <vector>
#include <utility>	// std::move

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
Device::Device(std::vector<ComPtr<::IDXGIAdapter1>> const& adapters)
{
	::UINT create_device_flags = 0;
#if defined(_DEBUG)
	create_device_flags |= ::D3D11_CREATE_DEVICE_DEBUG;
#endif

	::D3D_DRIVER_TYPE const driver_types[] =
	{
		::D3D_DRIVER_TYPE_HARDWARE,
		::D3D_DRIVER_TYPE_WARP,
		::D3D_DRIVER_TYPE_REFERENCE,
	};

	::D3D_FEATURE_LEVEL const feature_levels[] =
	{
		::D3D_FEATURE_LEVEL_11_1,
		::D3D_FEATURE_LEVEL_11_0,
		::D3D_FEATURE_LEVEL_10_1,
		::D3D_FEATURE_LEVEL_10_0,
	};
	::UINT const num_feature_levels = ARRAYSIZE(feature_levels);

	::HRESULT hr = S_OK;
	for (auto driver_type : driver_types)
	{
		m_driver_type = driver_type;
		hr = ::D3D11CreateDevice(
			adapters[0].Get(),
			D3D_DRIVER_TYPE_UNKNOWN,	// m_driver_type
			nullptr,
			create_device_flags,
			feature_levels,
			num_feature_levels,
			D3D11_SDK_VERSION,
			&m_device,
			&m_feature_level,
			nullptr);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}

	ThrowIfFailed(hr);
}

BKSGE_INLINE
Device::~Device()
{
}

BKSGE_INLINE ComPtr<::ID3D11DeviceContext>
Device::GetImmediateContext(void)
{
	ComPtr<::ID3D11DeviceContext> device_context;
	m_device->GetImmediateContext(&device_context);
	return std::move(device_context);
}

BKSGE_INLINE ComPtr<::ID3D11RenderTargetView>
Device::CreateRenderTargetView(
	::ID3D11Resource*                      resource,
	::D3D11_RENDER_TARGET_VIEW_DESC const* desc)
{
	ComPtr<::ID3D11RenderTargetView> rtv;
	ThrowIfFailed(m_device->CreateRenderTargetView(resource, desc, &rtv));
	return std::move(rtv);
}

BKSGE_INLINE ComPtr<::ID3D11DepthStencilView>
Device::CreateDepthStencilView(
	::ID3D11Resource*                      resource,
	::D3D11_DEPTH_STENCIL_VIEW_DESC const* desc)
{
	ComPtr<::ID3D11DepthStencilView> dsv;
	ThrowIfFailed(m_device->CreateDepthStencilView(resource, desc, &dsv));
	return std::move(dsv);
}

BKSGE_INLINE ComPtr<::ID3D11Buffer>
Device::CreateBuffer(
	::D3D11_BUFFER_DESC const&      desc,
	::D3D11_SUBRESOURCE_DATA const* subsource_data)
{
	ComPtr<::ID3D11Buffer> buffer;
	ThrowIfFailed(m_device->CreateBuffer(&desc, subsource_data, &buffer));
	return std::move(buffer);
}

BKSGE_INLINE ComPtr<::ID3D11SamplerState>
Device::CreateSamplerState(::D3D11_SAMPLER_DESC const& desc)
{
	ComPtr<::ID3D11SamplerState> state;
	ThrowIfFailed(m_device->CreateSamplerState(&desc, &state));
	return std::move(state);
}

BKSGE_INLINE ComPtr<::ID3D11Texture2D>
Device::CreateTexture2D(
	::D3D11_TEXTURE2D_DESC const&   desc,
	::D3D11_SUBRESOURCE_DATA const* init_data)
{
	ComPtr<::ID3D11Texture2D> texture;
	ThrowIfFailed(m_device->CreateTexture2D(&desc, init_data, &texture));
	return std::move(texture);
}

BKSGE_INLINE ComPtr<::ID3D11VertexShader>
Device::CreateVertexShader(::ID3DBlob* micro_code)
{
	ComPtr<::ID3D11VertexShader> shader;
	ThrowIfFailed(m_device->CreateVertexShader(
		micro_code->GetBufferPointer(),
		micro_code->GetBufferSize(),
		nullptr,
		shader.GetAddressOf()));
	return std::move(shader);
}

BKSGE_INLINE ComPtr<::ID3D11PixelShader>
Device::CreatePixelShader(::ID3DBlob* micro_code)
{
	ComPtr<::ID3D11PixelShader> shader;
	ThrowIfFailed(m_device->CreatePixelShader(
		micro_code->GetBufferPointer(),
		micro_code->GetBufferSize(),
		nullptr,
		shader.GetAddressOf()));
	return std::move(shader);
}

BKSGE_INLINE ComPtr<::ID3D11ShaderResourceView>
Device::CreateShaderResourceView(
	::ID3D11Resource*                        resource,
	::D3D11_SHADER_RESOURCE_VIEW_DESC const& desc)
{
	ComPtr<::ID3D11ShaderResourceView> srv;
	ThrowIfFailed(m_device->CreateShaderResourceView(resource, &desc, &srv));
	return std::move(srv);
}

BKSGE_INLINE ComPtr<::ID3D11InputLayout>
Device::CreateInputLayout(
	::D3D11_INPUT_ELEMENT_DESC const* desc,
	::UINT num_elements,
	void const* bytecode,
	::SIZE_T bytecode_length)
{
	ComPtr<::ID3D11InputLayout> layout;
	ThrowIfFailed(m_device->CreateInputLayout(
		desc,
		num_elements,
		bytecode,
		bytecode_length,
		&layout));
	return std::move(layout);
}

BKSGE_INLINE ComPtr<::ID3D11RasterizerState>
Device::CreateRasterizerState(
	::D3D11_RASTERIZER_DESC const* rasterizer_desc)
{
	ComPtr<::ID3D11RasterizerState> state;
	ThrowIfFailed(m_device->CreateRasterizerState(rasterizer_desc, &state));
	return std::move(state);
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_DEVICE_INL_HPP