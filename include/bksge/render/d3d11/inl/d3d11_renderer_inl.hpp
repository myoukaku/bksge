﻿/**
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
#include <bksge/render/d3d11/d3d11_device.hpp>
#include <bksge/render/d3d11/d3d11_device_context.hpp>
#include <bksge/render/d3d11/d3d11_render_target.hpp>
#include <bksge/render/d3d11/d3d11_depth_stencil.hpp>
#include <bksge/render/d3d11/d3d11_texture.hpp>
#include <bksge/render/d3d11/d3d11_hlsl_program.hpp>
#include <bksge/render/d3d11/d3d11_geometry.hpp>
#include <bksge/render/d3d11/d3d11_sampler.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>
#include <bksge/render/dxgi/dxgi_factory.hpp>
#include <bksge/render/dxgi/dxgi_swap_chain.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/texture.hpp>
#include <bksge/render/sampler.hpp>
#include <bksge/window/window.hpp>
#include <bksge/memory/make_unique.hpp>
#include <bksge/assert.hpp>
#include <memory>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11Renderer::D3D11Renderer(void)
{
	Initialize();
}

BKSGE_INLINE
D3D11Renderer::~D3D11Renderer()
{
	Finalize();
}

BKSGE_INLINE void
D3D11Renderer::Initialize(void)
{
	m_factory = bksge::make_unique<DXGIFactory>();
	m_device = bksge::make_unique<D3D11Device>(m_factory->EnumAdapters());
	m_device_context = bksge::make_unique<D3D11DeviceContext>(m_device.get());
}

BKSGE_INLINE void
D3D11Renderer::Finalize(void)
{
	if (m_device_context)
	{
		m_device_context->ClearState();
	}
}

BKSGE_INLINE void
D3D11Renderer::VSetRenderTarget(Window const& window)
{
	::HWND const hwnd = window.Handle();

	if (hwnd == nullptr)
	{
		return;
	}

	::UINT const width  = 800;	// TODO
	::UINT const height = 600;	// TODO

	m_swap_chain = bksge::make_unique<DXGISwapChain>(
		m_factory.get(), m_device->Get(), width, height, hwnd);

	m_factory->MakeWindowAssociation(
		hwnd,
		DXGI_MWA_NO_WINDOW_CHANGES |
		DXGI_MWA_NO_ALT_ENTER      |
		DXGI_MWA_NO_PRINT_SCREEN);

	m_render_target = bksge::make_unique<D3D11RenderTarget>(
		m_device.get(), m_swap_chain.get());

	m_depth_stencil = bksge::make_unique<D3D11DepthStencil>(
		m_device.get(), width, height);

	m_device_context->OMSetRenderTargets(
		1,
		m_render_target->GetView().GetAddressOf(),
		m_depth_stencil->GetView());

	// Setup the viewport
	{
		::D3D11_VIEWPORT vp;
		vp.Width    = (::FLOAT)width;
		vp.Height   = (::FLOAT)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_device_context->RSSetViewports(1, &vp);
	}

	//
	{
		::D3D11_RASTERIZER_DESC rd;
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
		ComPtr<::ID3D11RasterizerState> state =
			m_device->CreateRasterizerState(&rd);

		m_device_context->RSSetState(state.Get());
	}
}

BKSGE_INLINE void
D3D11Renderer::VBegin(void)
{
	m_device_context->OMSetRenderTargets(
		1,
		m_render_target->GetView().GetAddressOf(),
		m_depth_stencil->GetView());
}

BKSGE_INLINE void
D3D11Renderer::VEnd(void)
{
	m_swap_chain->Present(1, 0);
}

BKSGE_INLINE void
D3D11Renderer::VClear(ClearFlag clear_flag, Color4f const& clear_color)
{
	if ((clear_flag & ClearFlag::kColor) != ClearFlag::kNone)
	{
		m_device_context->ClearRenderTargetView(
			m_render_target->GetView().Get(),
			clear_color.data());
	}

	::UINT mask = 0u;
	if ((clear_flag & ClearFlag::kDepth) != ClearFlag::kNone)
	{
		mask |= D3D11_CLEAR_DEPTH;
	}
	if ((clear_flag & ClearFlag::kStencil) != ClearFlag::kNone)
	{
		mask |= D3D11_CLEAR_STENCIL;
	}

	m_device_context->ClearDepthStencilView(
		m_depth_stencil->GetView(),
		mask,
		1.0f,
		0);
}

BKSGE_INLINE void
D3D11Renderer::VRender(Geometry const& geometry, Shader const& shader)
{
	auto d3d11_hlsl_program = GetD3D11HLSLProgram(shader);
	BKSGE_ASSERT(d3d11_hlsl_program != nullptr);

	auto d3d11_geometry = GetD3D11Geometry(geometry);
	d3d11_hlsl_program->Render(m_device_context.get(), d3d11_geometry.get());
}

namespace d3d11_detail
{

template <typename Ret, typename Map, typename Src>
inline typename Map::mapped_type
GetOrCreate(D3D11Device* device, Map& map, Src const& src)
{
	auto const& id = src.id();
	{
		auto const& it = map.find(id);

		if (it != map.end())
		{
			return it->second;
		}
	}

	auto p = std::make_shared<Ret>(device, src);
	map[id] = p;
	return p;
}

}	// namespace d3d11_detail

BKSGE_INLINE std::shared_ptr<D3D11HLSLProgram>
D3D11Renderer::GetD3D11HLSLProgram(Shader const& shader)
{
	return d3d11_detail::GetOrCreate<D3D11HLSLProgram>(m_device.get(), m_d3d11_hlsl_program_map, shader);
}

BKSGE_INLINE std::shared_ptr<D3D11Geometry>
D3D11Renderer::GetD3D11Geometry(Geometry const& geometry)
{
	return d3d11_detail::GetOrCreate<D3D11Geometry>(m_device.get(), m_d3d11_geometry_map, geometry);
}

//BKSGE_INLINE std::shared_ptr<D3D11Texture>
//D3D11Renderer::GetD3D11Texture(Texture const& texture)
//{
//	return d3d11_detail::GetOrCreate<D3D11Texture>(this, m_d3d11_texture_map, texture);
//}

//BKSGE_INLINE std::shared_ptr<D3D11Sampler>
//D3D11Renderer::GetD3D11Sampler(Sampler const& sampler)
//{
//	return d3d11_detail::GetOrCreate<D3D11Sampler>(this, m_d3d11_sampler_map, sampler);
//}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_RENDERER_INL_HPP
