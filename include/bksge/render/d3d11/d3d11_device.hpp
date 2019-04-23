/**
 *	@file	d3d11_device.hpp
 *
 *	@brief	D3D11Device クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_DEVICE_HPP
#define BKSGE_RENDER_D3D11_D3D11_DEVICE_HPP

#include <bksge/render/d3d11/fwd/d3d11_device_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D11Device
{
public:
	explicit D3D11Device(std::vector<ComPtr<::IDXGIAdapter1>> const& adapters);

	~D3D11Device();

	ComPtr<::ID3D11DeviceContext> GetImmediateContext(void);

	ComPtr<::ID3D11RenderTargetView> CreateRenderTargetView(
		::ID3D11Resource*                      resource,
		::D3D11_RENDER_TARGET_VIEW_DESC const* desc);

	ComPtr<::ID3D11DepthStencilView> CreateDepthStencilView(
		::ID3D11Resource*                      resource,
		::D3D11_DEPTH_STENCIL_VIEW_DESC const* desc);

	ComPtr<::ID3D11Buffer> CreateBuffer(
		::D3D11_BUFFER_DESC const&      desc,
		::D3D11_SUBRESOURCE_DATA const* subsource_data);

	ComPtr<::ID3D11SamplerState> CreateSamplerState(
		::D3D11_SAMPLER_DESC const& desc);

	ComPtr<::ID3D11Texture2D> CreateTexture2D(
		::D3D11_TEXTURE2D_DESC const&   desc,
		::D3D11_SUBRESOURCE_DATA const* init_data);

	ComPtr<::ID3D11VertexShader> CreateVertexShader(
		::ID3DBlob* micro_code);

	ComPtr<::ID3D11PixelShader> CreatePixelShader(
		::ID3DBlob* micro_code);

	ComPtr<::ID3D11ShaderResourceView> CreateShaderResourceView(
		::ID3D11Resource*                        resource,
		::D3D11_SHADER_RESOURCE_VIEW_DESC const& desc);

	ComPtr<::ID3D11InputLayout> CreateInputLayout(
		::D3D11_INPUT_ELEMENT_DESC const* desc,
		::UINT                            num_elements,
		void const*                       bytecode,
		::SIZE_T                          bytecode_length);

	ComPtr<::ID3D11RasterizerState> CreateRasterizerState(
		::D3D11_RASTERIZER_DESC const* rasterizer_desc);

	// TODO
	::ID3D11Device* Get(void) { return m_device.Get(); }

private:
	ComPtr<::ID3D11Device> m_device;
	::D3D_DRIVER_TYPE      m_driver_type   = ::D3D_DRIVER_TYPE_NULL;
	::D3D_FEATURE_LEVEL    m_feature_level = ::D3D_FEATURE_LEVEL_11_0;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_device_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_DEVICE_HPP
