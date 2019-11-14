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
#include <bksge/render/d3d11/detail/device.hpp>
#include <bksge/render/d3d11/detail/device_context.hpp>
#include <bksge/render/d3d11/detail/render_target.hpp>
#include <bksge/render/d3d11/detail/depth_stencil.hpp>
#include <bksge/render/d3d11/detail/hlsl_program.hpp>
//#include <bksge/render/d3d11/detail/geometry.hpp>
#include <bksge/render/d3d11/detail/fill_mode.hpp>
#include <bksge/render/d3d11/detail/cull_mode.hpp>
////#include <bksge/render/d3d11/detail/texture.hpp>
////#include <bksge/render/d3d11/detail/sampler.hpp>
#include <bksge/render/d3d11/detail/resource_cache.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/dxgi/dxgi_factory.hpp>
#include <bksge/render/dxgi/dxgi_swap_chain.hpp>
#include <bksge/render/clear_flag.hpp>
#include <bksge/render/front_face.hpp>
#include <bksge/render/shader.hpp>
//#include <bksge/render/geometry.hpp>
#include <bksge/render/render_state.hpp>
//#include <bksge/render/texture.hpp>
////#include <bksge/render/sampler.hpp>
#include <bksge/math/color4.hpp>
#include <bksge/memory/make_unique.hpp>
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
	m_device = bksge::make_unique<d3d11::Device>(m_factory->EnumAdapters());
	m_device_context = bksge::make_unique<d3d11::DeviceContext>(m_device.get());
	m_resource_cache = bksge::make_unique<d3d11::ResourceCache>(m_device.get());
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
	::HWND const hwnd = window.handle();

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

	m_render_target = bksge::make_unique<d3d11::RenderTarget>(
		m_device.get(), m_swap_chain.get());

	m_depth_stencil = bksge::make_unique<d3d11::DepthStencil>(
		m_device.get(), width, height);

	m_device_context->OMSetRenderTargets(
		1,
		m_render_target->GetView().GetAddressOf(),
		nullptr/*m_depth_stencil->GetView()*/);
}

BKSGE_INLINE void
D3D11Renderer::VBegin(void)
{
	// Setup the viewport
	if (m_viewport)
	{
		::D3D11_VIEWPORT vp;
		vp.TopLeftX = m_viewport->left();
		vp.TopLeftY = m_viewport->top();
		vp.Width    = m_viewport->width();
		vp.Height   = m_viewport->height();
		vp.MinDepth = D3D11_MIN_DEPTH;
		vp.MaxDepth = D3D11_MAX_DEPTH;
		m_device_context->RSSetViewports(1, &vp);
	}

	m_device_context->OMSetRenderTargets(
		1,
		m_render_target->GetView().GetAddressOf(),
		nullptr/*m_depth_stencil->GetView()*/);

	// Clear Color
	if ((m_clear_flag & ClearFlag::kColor) != ClearFlag::kNone)
	{
		m_device_context->ClearRenderTargetView(
			m_render_target->GetView().Get(),
			m_clear_color.data());
	}

	// Clear Depth Stencil
	{
		::UINT mask = 0u;
		if ((m_clear_flag & ClearFlag::kDepth) != ClearFlag::kNone)
		{
			mask |= D3D11_CLEAR_DEPTH;
		}
		if ((m_clear_flag & ClearFlag::kStencil) != ClearFlag::kNone)
		{
			mask |= D3D11_CLEAR_STENCIL;
		}

		//m_device_context->ClearDepthStencilView(
		//	m_depth_stencil->GetView(),
		//	mask,
		//	1.0f,
		//	0);
	}
}

BKSGE_INLINE void
D3D11Renderer::VEnd(void)
{
	m_swap_chain->Present(1, 0);
}

BKSGE_INLINE bool
D3D11Renderer::VRender(
	Geometry const& geometry,
	Shader const& shader,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	if (shader.type() != ShaderType::kHLSL)
	{
		return false;
	}

	//
	{
		auto const& rasterizer_state = render_state.rasterizer_state();
		auto const& scissor_state = render_state.scissor_state();

		::D3D11_RASTERIZER_DESC rd;
		rd.FillMode              = d3d11::FillMode(rasterizer_state.fill_mode());
		rd.CullMode              = d3d11::CullMode(rasterizer_state.cull_mode());
		rd.FrontCounterClockwise = (rasterizer_state.front_face() == FrontFace::kCounterClockwise);
		rd.DepthBias             = 0;
		rd.DepthBiasClamp        = 0;
		rd.SlopeScaledDepthBias  = 0;
		rd.ScissorEnable         = scissor_state.enable() ? TRUE : FALSE;
		rd.MultisampleEnable     = FALSE;
		rd.AntialiasedLineEnable = FALSE;

		// ラスタライザーステートを生成して設定
		ComPtr<::ID3D11RasterizerState> state =
			m_device->CreateRasterizerState(&rd);

		m_device_context->RSSetState(state.Get());
	}

	{
		auto const& scissor = render_state.scissor_state();
		::D3D11_RECT scissor_rect;
		scissor_rect.left   = static_cast<::LONG>(scissor.rect().left());
		scissor_rect.top    = static_cast<::LONG>(scissor.rect().top());
		scissor_rect.right  = static_cast<::LONG>(scissor.rect().right());
		scissor_rect.bottom = static_cast<::LONG>(scissor.rect().bottom());
		m_device_context->RSSetScissorRects(1, &scissor_rect);
	}

	auto hlsl_program = m_resource_cache->GetD3D11HlslProgram(shader);
	BKSGE_ASSERT(hlsl_program != nullptr);

	auto d3d11_geometry = m_resource_cache->GetD3D11Geometry(geometry);
	hlsl_program->Render(
		m_resource_cache.get(),
		m_device_context.get(),
		d3d11_geometry.get(),
		shader_parameter_map);

	return true;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_RENDERER_INL_HPP
