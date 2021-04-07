/**
 *	@file	d3d11_renderer_inl.hpp
 *
 *	@brief	D3D11Renderer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_INL_D3D11_RENDERER_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_INL_D3D11_RENDERER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/d3d11_renderer.hpp>
#include <bksge/core/render/d3d11/detail/device.hpp>
#include <bksge/core/render/d3d11/detail/device_context.hpp>
#include <bksge/core/render/d3d11/detail/render_target.hpp>
#include <bksge/core/render/d3d11/detail/depth_stencil.hpp>
#include <bksge/core/render/d3d11/detail/hlsl_program.hpp>
#include <bksge/core/render/d3d11/detail/geometry.hpp>
#include <bksge/core/render/d3d11/detail/resource_pool.hpp>
#include <bksge/core/render/d3d11/detail/depth_stencil_state.hpp>
#include <bksge/core/render/d3d11/detail/blend_state.hpp>
#include <bksge/core/render/d3d11/detail/rasterizer_state.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/dxgi/dxgi_factory.hpp>
#include <bksge/core/render/dxgi/dxgi_swap_chain.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/core/render/render_pass_info.hpp>
#include <bksge/core/window/window.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11Renderer::D3D11Renderer(Window const& window)
{
	m_factory = bksge::make_unique<DXGIFactory>();
	m_device = bksge::make_unique<d3d11::Device>(m_factory->EnumAdapters());
	m_device_context = bksge::make_unique<d3d11::DeviceContext>(m_device.get());
	m_resource_pool = bksge::make_unique<d3d11::ResourcePool>();

	::HWND const hwnd = window.handle();

	if (hwnd == nullptr)
	{
		return;
	}

	::UINT const frame_buffer_count = 2;	// TODO
	::UINT const width  = window.client_size().width();
	::UINT const height = window.client_size().height();

	m_swap_chain = bksge::make_unique<DXGISwapChain>(
		m_factory.get(), m_device->Get(), frame_buffer_count, width, height, hwnd);

	m_factory->MakeWindowAssociation(
		hwnd,
		DXGI_MWA_NO_WINDOW_CHANGES |
		DXGI_MWA_NO_ALT_ENTER      |
		DXGI_MWA_NO_PRINT_SCREEN);

	m_render_target = bksge::make_unique<d3d11::RenderTarget>(
		m_device.get(), m_swap_chain.get());

	m_depth_stencil = bksge::make_unique<d3d11::DepthStencil>(
		m_device.get(), width, height);

	{
		auto rtv = m_render_target->GetView();
		m_device_context->OMSetRenderTargets(
			1,
			&rtv,
			m_depth_stencil->GetView());
	}
}

BKSGE_INLINE
D3D11Renderer::~D3D11Renderer()
{
	if (m_device_context)
	{
		m_device_context->ClearState();
	}
}

BKSGE_INLINE void
D3D11Renderer::VBegin(void)
{
	{
		auto rtv = m_render_target->GetView();
		m_device_context->OMSetRenderTargets(
			1,
			&rtv,
			m_depth_stencil->GetView());
	}
}

BKSGE_INLINE void
D3D11Renderer::VEnd(void)
{
	m_swap_chain->Present(1, 0);
}

BKSGE_INLINE void
D3D11Renderer::VBeginRenderPass(RenderPassInfo const& render_pass_info)
{
	{
		auto const& clear_state = render_pass_info.clear_state();
		auto const clear_flag    = clear_state.flag();
		auto const clear_color   = clear_state.color();
		auto const clear_depth   = clear_state.depth();
		auto const clear_stencil = clear_state.stencil();

		// Clear Color
		if (Test(clear_flag, ClearFlag::kColor))
		{
			m_device_context->ClearRenderTargetView(
				m_render_target->GetView(),
				clear_color.data());
		}

		// Clear Depth Stencil
		{
			::UINT mask = 0u;
			if (Test(clear_flag, ClearFlag::kDepth))
			{
				mask |= D3D11_CLEAR_DEPTH;
			}
			if (Test(clear_flag, ClearFlag::kStencil))
			{
				mask |= D3D11_CLEAR_STENCIL;
			}

			m_device_context->ClearDepthStencilView(
				m_depth_stencil->GetView(),
				mask,
				clear_depth,
				clear_stencil);
		}
	}

	// Setup the viewport
	{
		auto const& viewport = render_pass_info.viewport();

		::D3D11_VIEWPORT vp;
		vp.TopLeftX = viewport.rect().left();
		vp.TopLeftY = viewport.rect().top();
		vp.Width    = viewport.rect().width();
		vp.Height   = viewport.rect().height();
		vp.MinDepth = viewport.min_depth();
		vp.MaxDepth = viewport.max_depth();
		m_device_context->RSSetViewports(1, &vp);
	}

	//
	{
		auto const& scissor_state = render_pass_info.scissor_state();
		auto const rect =
			scissor_state.enable() ?
			scissor_state.rect() :
			render_pass_info.viewport().rect();

		::D3D11_RECT scissor_rect;
		scissor_rect.left   = static_cast<::LONG>(rect.left());
		scissor_rect.top    = static_cast<::LONG>(rect.top());
		scissor_rect.right  = static_cast<::LONG>(rect.right());
		scissor_rect.bottom = static_cast<::LONG>(rect.bottom());
		m_device_context->RSSetScissorRects(1, &scissor_rect);
	}
}

BKSGE_INLINE void
D3D11Renderer::VEndRenderPass(void)
{
}

BKSGE_INLINE bool
D3D11Renderer::VRender(
	Geometry const& geometry,
	Shader const& shader,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	// Set RasterizerState
	{
		auto state = m_device->CreateRasterizerState(
			d3d11::RasterizerState(render_state.rasterizer_state()));
		m_device_context->RSSetState(state.Get());
	}

	// Set BlendState
	{
		auto state = m_device->CreateBlendState(
			d3d11::BlendState(render_state.blend_state()));
		float const blend_factor[4] = {};
		::UINT const sample_mask = 0xffffffff;
		m_device_context->OMSetBlendState(state.Get(), blend_factor, sample_mask);
	}

	// Set DepthStencilState
	{
		auto state = m_device->CreateDepthStencilState(
			d3d11::DepthStencilState(
				render_state.depth_state(),
				render_state.stencil_state()));
		m_device_context->OMSetDepthStencilState(
			state.Get(),
			static_cast<::UINT>(render_state.stencil_state().reference()));
	}

	auto hlsl_program = m_resource_pool->GetD3D11HlslProgram(m_device.get(), shader);
	BKSGE_ASSERT(hlsl_program != nullptr);
	hlsl_program->Render(
		m_resource_pool.get(),
		m_device.get(),
		m_device_context.get(),
		shader_parameter_map);

	auto d3d11_geometry = m_resource_pool->GetD3D11Geometry(m_device.get(), geometry);
	BKSGE_ASSERT(d3d11_geometry != nullptr);
	d3d11_geometry->Draw(m_device_context.get());

	return true;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_INL_D3D11_RENDERER_INL_HPP
