/**
 *	@file	d3d11_renderer_inl.hpp
 *
 *	@brief	D3D11Renderer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_RENDERER_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_RENDERER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_renderer.hpp>
#include <bksge/render/d3d11/d3d11_texture.hpp>
#include <bksge/render/d3d11/d3d11_shader.hpp>
#include <bksge/render/d3d11/d3d11_geometry.hpp>
#include <bksge/render/d3d11/d3d11_sampler.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d11/com_ptr.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/texture.hpp>
#include <bksge/render/sampler.hpp>
#include <bksge/window/window.hpp>
#include <bksge/assert.hpp>
#include <memory>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11Renderer::D3D11Renderer(void)
{
	CreateDevice();
}

BKSGE_INLINE
D3D11Renderer::~D3D11Renderer()
{
	Finalize();
}

BKSGE_INLINE
void D3D11Renderer::CreateDevice(void)
{
	HRESULT hr = S_OK;

	UINT create_device_flags = 0;
#if defined(BKSGE_DEBUG)
	create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++)
	{
		m_driver_type = driver_types[driver_type_index];
		hr = D3D11CreateDevice(
			nullptr,
			m_driver_type,
			nullptr,
			create_device_flags,
			feature_levels,
			num_feature_levels,
			D3D11_SDK_VERSION,
			&m_device,
			&m_feature_level,
			&m_device_context);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}

	BKSGE_ASSERT(SUCCEEDED(hr));
}

BKSGE_INLINE
void D3D11Renderer::Finalize(void)
{
	if (m_device_context)
	{
		m_device_context->ClearState();
	}
}

BKSGE_INLINE
void D3D11Renderer::VSetRenderTarget(Window const& window)
{
	HWND const hwnd = window.Handle();

	if (hwnd == nullptr)
	{
		return;
	}

    UINT const width  = 800;	// TODO
    UINT const height = 600;	// TODO

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	ComPtr<IDXGIFactory1> dxgi_factory;
	{
		ComPtr<IDXGIDevice> dxgi_device;
		{
			auto const hr = m_device.Get()->QueryInterface(IID_PPV_ARGS(&dxgi_device));
			BKSGE_ASSERT(SUCCEEDED(hr));
			(void)hr;
		}
		ComPtr<IDXGIAdapter> adapter;
		{
			auto const hr = dxgi_device->GetAdapter(&adapter);
			BKSGE_ASSERT(SUCCEEDED(hr));
			(void)hr;
		}
		{
			auto const hr = adapter->GetParent(IID_PPV_ARGS(&dxgi_factory));
			BKSGE_ASSERT(SUCCEEDED(hr));
			(void)hr;
		}
	}

	{
		// DirectX 11.0 systems
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount                        = 1;
		sd.BufferDesc.Width                   = width;
		sd.BufferDesc.Height                  = height;
		sd.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator   = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow                       = hwnd;
		sd.SampleDesc.Count                   = 1;
		sd.SampleDesc.Quality                 = 0;
		sd.Windowed                           = TRUE;

		auto const hr = dxgi_factory->CreateSwapChain(m_device.Get(), &sd, m_swap_chain.ReleaseAndGetAddressOf());
		BKSGE_ASSERT(SUCCEEDED(hr));
		(void)hr;
	}

	// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
	{
		auto const hr = dxgi_factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_PRINT_SCREEN);
		BKSGE_ASSERT(SUCCEEDED(hr));
		(void)hr;
	}

	// Create a render target view
	{
		ComPtr<ID3D11Texture2D> back_buffer;
		{
			auto const hr = m_swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
			BKSGE_ASSERT(SUCCEEDED(hr));
			(void)hr;
		}
		{
			auto const hr = m_device->CreateRenderTargetView(back_buffer.Get(), nullptr, m_render_target_view.ReleaseAndGetAddressOf());
			BKSGE_ASSERT(SUCCEEDED(hr));
			(void)hr;
		}
	}

	// Create depth stencil texture
	{
		D3D11_TEXTURE2D_DESC desc_depth;
		ZeroMemory(&desc_depth, sizeof(desc_depth));
		desc_depth.Width              = width;
		desc_depth.Height             = height;
		desc_depth.MipLevels          = 1;
		desc_depth.ArraySize          = 1;
		desc_depth.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc_depth.SampleDesc.Count   = 1;
		desc_depth.SampleDesc.Quality = 0;
		desc_depth.Usage              = D3D11_USAGE_DEFAULT;
		desc_depth.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
		desc_depth.CPUAccessFlags     = 0;
		desc_depth.MiscFlags          = 0;
		{
			auto const hr = m_device->CreateTexture2D(&desc_depth, nullptr, m_depth_stencil.ReleaseAndGetAddressOf());
			BKSGE_ASSERT(SUCCEEDED(hr));
			(void)hr;
		}

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC desc_dsv;
		ZeroMemory(&desc_dsv, sizeof(desc_dsv));
		desc_dsv.Format             = desc_depth.Format;
		desc_dsv.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc_dsv.Texture2D.MipSlice = 0;
		{
			auto const hr = m_device->CreateDepthStencilView(m_depth_stencil.Get(), &desc_dsv, m_depth_stencil_view.ReleaseAndGetAddressOf());
			BKSGE_ASSERT(SUCCEEDED(hr));
			(void)hr;
		}
	}

	m_device_context->OMSetRenderTargets(
		1,
		m_render_target_view.GetAddressOf(),
		m_depth_stencil_view.Get());

	// Setup the viewport
	{
		D3D11_VIEWPORT vp;
		vp.Width    = (FLOAT)width;
		vp.Height   = (FLOAT)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_device_context->RSSetViewports(1, &vp);
	}

	//
	{
		D3D11_RASTERIZER_DESC rd;
		rd.FillMode              = D3D11_FILL_SOLID;
		rd.CullMode              = D3D11_CULL_BACK;
		rd.FrontCounterClockwise = TRUE;
		rd.DepthBias             = 0;
		rd.DepthBiasClamp        = 0;
		rd.SlopeScaledDepthBias  = 0;
		rd.ScissorEnable         = FALSE;
		rd.MultisampleEnable     = FALSE;
		rd.AntialiasedLineEnable = FALSE;

		// ラスタライザーステートを生成して設定
		ComPtr<ID3D11RasterizerState> state;
		{
			auto const hr = m_device->CreateRasterizerState(&rd, &state);
			BKSGE_ASSERT(SUCCEEDED(hr));
			(void)hr;
		}

		m_device_context->RSSetState(state.Get());
	}
}

BKSGE_INLINE
void D3D11Renderer::VBegin(void)
{
}

BKSGE_INLINE
void D3D11Renderer::VEnd(void)
{
	m_swap_chain->Present(1, 0);
}

BKSGE_INLINE
void D3D11Renderer::VClear(ClearFlag clear_flag, Color4f const& clear_color)
{
	if ((clear_flag & ClearFlag::kColor) != ClearFlag::kNone)
	{
		m_device_context->ClearRenderTargetView(m_render_target_view.Get(), clear_color.data());
	}

	UINT const mask =
		(((clear_flag & ClearFlag::kDepth)   != ClearFlag::kNone) ? D3D11_CLEAR_DEPTH   : 0) |
		(((clear_flag & ClearFlag::kStencil) != ClearFlag::kNone) ? D3D11_CLEAR_STENCIL : 0);

	m_device_context->ClearDepthStencilView(m_depth_stencil_view.Get(), mask, 1.0f, 0);
}

BKSGE_INLINE
void D3D11Renderer::VRender(Geometry const& geometry, Shader const& shader)
{
	auto d3d11_shader = GetD3D11Shader(shader);
	BKSGE_ASSERT(d3d11_shader != nullptr);

	d3d11_shader->Render(this, geometry, shader);
}

namespace d3d11_detail
{

template <typename Ret, typename Map, typename Src>
inline typename Map::mapped_type
GetOrCreate(D3D11Renderer* renderer, Map& map, Src const& src)
{
	auto const& id = src.id();
	{
		auto const& it = map.find(id);

		if (it != map.end())
		{
			return it->second;
		}
	}

	auto p = std::make_shared<Ret>(renderer, src);
	map[id] = p;
	return p;
}

}	// namespace d3d11_detail

BKSGE_INLINE
std::shared_ptr<D3D11Shader>
D3D11Renderer::GetD3D11Shader(Shader const& shader)
{
	return d3d11_detail::GetOrCreate<D3D11Shader>(this, m_d3d11_shader_map, shader);
}

BKSGE_INLINE
std::shared_ptr<D3D11Geometry>
D3D11Renderer::GetD3D11Geometry(Geometry const& geometry)
{
	return d3d11_detail::GetOrCreate<D3D11Geometry>(this, m_d3d11_geometry_map, geometry);
}

BKSGE_INLINE
std::shared_ptr<D3D11Texture>
D3D11Renderer::GetD3D11Texture(Texture const& texture)
{
	return d3d11_detail::GetOrCreate<D3D11Texture>(this, m_d3d11_texture_map, texture);
}

BKSGE_INLINE
std::shared_ptr<D3D11Sampler>
D3D11Renderer::GetD3D11Sampler(Sampler const& sampler)
{
	return d3d11_detail::GetOrCreate<D3D11Sampler>(this, m_d3d11_sampler_map, sampler);
}

BKSGE_INLINE
ComPtr<ID3D11Buffer>
D3D11Renderer::CreateBuffer(D3D11_BUFFER_DESC const& desc, D3D11_SUBRESOURCE_DATA const& subsource_data)
{
	ComPtr<ID3D11Buffer> buffer;
	auto hr = m_device->CreateBuffer(&desc, &subsource_data, &buffer);
	BKSGE_ASSERT(SUCCEEDED(hr));
	(void)hr;
	return buffer;
}

BKSGE_INLINE
ComPtr<ID3D11SamplerState>
D3D11Renderer::CreateSamplerState(D3D11_SAMPLER_DESC const& desc)
{
	ComPtr<ID3D11SamplerState> state;
	auto hr = m_device->CreateSamplerState(&desc, &state);
	BKSGE_ASSERT(SUCCEEDED(hr));
	(void)hr;
	return state;
}

BKSGE_INLINE
ComPtr<ID3D11Texture2D>
D3D11Renderer::CreateTexture2D(D3D11_TEXTURE2D_DESC const& desc, D3D11_SUBRESOURCE_DATA const& init_data)
{
	ComPtr<ID3D11Texture2D> texture;
	auto hr = m_device->CreateTexture2D(&desc, &init_data, &texture);
	BKSGE_ASSERT(SUCCEEDED(hr));
	(void)hr;
	return texture;
}

BKSGE_INLINE
ComPtr<ID3D11ShaderResourceView>
D3D11Renderer::CreateShaderResourceView(ID3D11Resource* resource, D3D11_SHADER_RESOURCE_VIEW_DESC const& desc)
{
	ComPtr<ID3D11ShaderResourceView> srv;
	auto hr = m_device->CreateShaderResourceView(resource, &desc, &srv);
	BKSGE_ASSERT(SUCCEEDED(hr));
	(void)hr;
	return srv;
}

BKSGE_INLINE
ComPtr<ID3D11InputLayout>
D3D11Renderer::CreateInputLayout( 
	D3D11_INPUT_ELEMENT_DESC const* desc,
	UINT num_elements,
	void const* bytecode,
	SIZE_T bytecode_length)
{
	ComPtr<ID3D11InputLayout> layout;
	auto const hr = m_device->CreateInputLayout(desc, num_elements, bytecode, bytecode_length, &layout);
	BKSGE_ASSERT(SUCCEEDED(hr));
	(void)hr;
	return layout;
}

BKSGE_INLINE
void D3D11Renderer::SetIndexBuffer(ID3D11Buffer* index_buffer, DXGI_FORMAT format, UINT offset)
{
	m_device_context->IASetIndexBuffer(index_buffer, format, offset);
}

BKSGE_INLINE
void D3D11Renderer::SetVertexBuffers(
		UINT start_slot,
		UINT num_buffers,
		ID3D11Buffer* const* vertex_buffers,
		UINT const* strides,
		UINT const* offsets)
{
	m_device_context->IASetVertexBuffers(
		start_slot,
		num_buffers,
		vertex_buffers,
		strides,
		offsets);
}

BKSGE_INLINE
void D3D11Renderer::SetInputLayout(ID3D11InputLayout* input_layout)
{
	m_device_context->IASetInputLayout(input_layout);
}

BKSGE_INLINE
void D3D11Renderer::PSSetSamplers(UINT start_slot, UINT num_samplers, ID3D11SamplerState* const* samplers)
{
	m_device_context->PSSetSamplers(start_slot, num_samplers, samplers);
}

BKSGE_INLINE
void D3D11Renderer::PSSetShaderResources(UINT start_slot, UINT num_views, ID3D11ShaderResourceView* const* shader_resource_views)
{
	m_device_context->PSSetShaderResources(start_slot, num_views, shader_resource_views);
}

BKSGE_INLINE
void D3D11Renderer::SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	m_device_context->IASetPrimitiveTopology(topology);
}

BKSGE_INLINE
void D3D11Renderer::DrawIndexed(UINT index_count, UINT start_index_location, INT base_vertex_location)
{
	m_device_context->DrawIndexed(index_count, start_index_location, base_vertex_location);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_RENDERER_INL_HPP
