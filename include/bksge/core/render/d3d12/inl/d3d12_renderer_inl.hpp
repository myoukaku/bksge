/**
 *	@file	d3d12_renderer_inl.hpp
 *
 *	@brief	D3D12Renderer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_INL_D3D12_RENDERER_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_INL_D3D12_RENDERER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/d3d12_renderer.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d12/detail/command_queue.hpp>
#include <bksge/core/render/d3d12/detail/command_list.hpp>
#include <bksge/core/render/d3d12/detail/render_target.hpp>
#include <bksge/core/render/d3d12/detail/fence.hpp>
#include <bksge/core/render/d3d12/detail/geometry.hpp>
#include <bksge/core/render/d3d12/detail/root_signature.hpp>
#include <bksge/core/render/d3d12/detail/input_layout.hpp>
#include <bksge/core/render/d3d12/detail/rasterizer_state.hpp>
#include <bksge/core/render/d3d12/detail/blend_state.hpp>
#include <bksge/core/render/d3d12/detail/depth_stencil_state.hpp>
#include <bksge/core/render/d3d12/detail/hlsl_program.hpp>
#include <bksge/core/render/d3d12/detail/primitive_topology_type.hpp>
#include <bksge/core/render/d3d12/detail/pipeline_state.hpp>
#include <bksge/core/render/d3d12/detail/resource_cache.hpp>
#include <bksge/core/render/d3d12/detail/descriptor_heaps.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/d3d_common/throw_if_failed.hpp>
#include <bksge/core/render/d3d_common/d3dcompiler.hpp>
#include <bksge/core/render/dxgi/dxgi_swap_chain.hpp>
#include <bksge/core/render/dxgi/dxgi_factory.hpp>
#include <bksge/core/render/d3d_common/dxgi.hpp>

#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/render_state.hpp>

#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/core/window/window.hpp>
#include <bksge/core/detail/win32.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/core/math/rect.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/size2.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/assert.hpp>

#include <memory>
#include <unordered_map>
#include <utility>

namespace bksge
{

namespace render
{

namespace
{

static ::UINT const frame_buffer_count = 2;	// TODO

}	// namespace

BKSGE_INLINE
D3D12Renderer::D3D12Renderer(void)
{
	Initialize();
}

BKSGE_INLINE
D3D12Renderer::~D3D12Renderer()
{
	Finalize();
}

BKSGE_INLINE void
D3D12Renderer::Initialize(void)
{
#if defined(_DEBUG)
	// Enable the debug layer (requires the Graphics Tools "optional feature").
	// NOTE: Enabling the debug layer after device creation will invalidate the active device.
	{
		ComPtr<::ID3D12Debug> debug;
		if (SUCCEEDED(::D3D12GetDebugInterface(IID_PPV_ARGS(&debug))))
		{
			debug->EnableDebugLayer();
		}
	}
#endif

	m_factory        = bksge::make_unique<DXGIFactory>();
	m_device         = bksge::make_unique<d3d12::Device>(m_factory->EnumAdapters());
	m_command_queue  = bksge::make_unique<d3d12::CommandQueue>(m_device.get());
	m_command_list   = bksge::make_unique<d3d12::CommandList>(m_device.get(), frame_buffer_count);
	m_fence          = bksge::make_unique<d3d12::Fence>(m_device.get(), frame_buffer_count);
	m_resource_cache = bksge::make_unique<d3d12::ResourceCache>(m_device.get());
	m_descriptor_heaps = bksge::make_unique<d3d12::DescriptorHeaps>(
		m_device.get(),
		1000,
		100,
		0,
		0);

	// Command lists are created in the recording state, but there is nothing
	// to record yet. The main loop expects it to be closed, so close it now.
	m_command_list->Close();
}

BKSGE_INLINE void
D3D12Renderer::Finalize(void)
{
	// Ensure that the GPU is no longer referencing resources that are about to be
	// cleaned up by the destructor.
	m_fence->WaitForGpu(m_command_queue.get(), m_frame_index);
	m_fence->Close();
}

BKSGE_INLINE void
D3D12Renderer::VSetRenderTarget(Window const& window)
{
	::HWND const hwnd = window.handle();

	if (hwnd == nullptr)
	{
		return;
	}

	::UINT const width  = 800;	// TODO
	::UINT const height = 600;	// TODO

	m_swap_chain = bksge::make_unique<DXGISwapChain>(
		m_factory.get(), m_command_queue->Get(), frame_buffer_count, width, height, hwnd);
	m_frame_index = m_swap_chain->GetCurrentBackBufferIndex();

	m_factory->MakeWindowAssociation(
		hwnd,
		DXGI_MWA_NO_WINDOW_CHANGES |
		DXGI_MWA_NO_ALT_ENTER      |
		DXGI_MWA_NO_PRINT_SCREEN);

	m_render_target = bksge::make_unique<d3d12::RenderTarget>(
		m_device.get(), m_swap_chain.get(), frame_buffer_count);

	m_fence->WaitForGpu(m_command_queue.get(), m_frame_index);
}

BKSGE_INLINE void
D3D12Renderer::VBegin(void)
{
	m_frame_index = m_swap_chain->GetCurrentBackBufferIndex();

	m_command_list->Reset(m_frame_index);

	if (m_viewport)
	{
		::D3D12_VIEWPORT viewport;
		viewport.TopLeftX = m_viewport->left();
		viewport.TopLeftY = m_viewport->top();
		viewport.Width    = m_viewport->width();
		viewport.Height   = m_viewport->height();
		viewport.MinDepth = D3D12_MIN_DEPTH;
		viewport.MaxDepth = D3D12_MAX_DEPTH;
		m_command_list->RSSetViewports(1, &viewport);
	}

	// Indicate that the back buffer will be used as a render target.
	m_command_list->ResourceBarrier(
		m_render_target->GetResource(m_frame_index),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET);

	auto const rtv_handle = m_render_target->GetHandle(m_frame_index);
	m_command_list->OMSetRenderTargets(1, &rtv_handle, FALSE, nullptr);

	// Clear Color
	if ((m_clear_flag & ClearFlag::kColor) != ClearFlag::kNone)
	{
		m_command_list->ClearRenderTargetView(
			rtv_handle,
			m_clear_color.data());
	}

	// Clear Depth Stencil
	{
		::D3D12_CLEAR_FLAGS mask{};
		if ((m_clear_flag & ClearFlag::kDepth) != ClearFlag::kNone)
		{
			mask |= D3D12_CLEAR_FLAG_DEPTH;
		}
		if ((m_clear_flag & ClearFlag::kStencil) != ClearFlag::kNone)
		{
			mask |= D3D12_CLEAR_FLAG_STENCIL;
		}

		//m_command_list->ClearDepthStencilView(dsv_handle_, mask, 1.0f, 0, 0, nullptr);
	}

	m_descriptor_heaps->SetEnable(m_command_list.get());
	m_descriptor_heaps->BeginFrame();
}

BKSGE_INLINE void
D3D12Renderer::VEnd(void)
{
	// Indicate that the back buffer will now be used to present.
	m_command_list->ResourceBarrier(
		m_render_target->GetResource(m_frame_index),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT);

	m_command_list->Close();

	m_command_queue->ExecuteCommandLists(m_command_list.get());

	m_swap_chain->Present(1, 0);

	m_fence->MoveToNextFrame(m_command_queue.get(), m_frame_index);
}

BKSGE_INLINE bool
D3D12Renderer::VRender(
	Geometry const& geometry,
	Shader const& shader,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	if (shader.type() != ShaderType::kHLSL)
	{
		return false;
	}

	{
		auto const& scissor = render_state.scissor_state();
		auto const rect =
			scissor.enable() ?
			scissor.rect() :
			m_viewport ?
			*m_viewport :
			Rectf(Vector2f{0, 0}, Size2f{100000, 100000});	// TODO フレームバッファの解像度にする
		::D3D12_RECT scissor_rect;
		scissor_rect.left   = static_cast<::LONG>(rect.left());
		scissor_rect.top    = static_cast<::LONG>(rect.top());
		scissor_rect.right  = static_cast<::LONG>(rect.right());
		scissor_rect.bottom = static_cast<::LONG>(rect.bottom());
		m_command_list->RSSetScissorRects(1, &scissor_rect);
	}

	auto hlsl_program = GetD3D12HlslProgram(shader);

	// TODO
	// hlsl_program->SetRootSignature(m_command_list.get());
	m_command_list->SetGraphicsRootSignature(hlsl_program->GetRootSignature());

	hlsl_program->SetDescriptorTables(
		m_command_list.get(),
		m_descriptor_heaps.get());

	hlsl_program->UpdateParameters(
		m_device.get(),
		m_descriptor_heaps.get(),
		m_resource_cache.get(),
		shader_parameter_map);

	auto pipeline_state = GetD3D12PipelineState(shader, render_state, geometry.primitive());
	pipeline_state->SetPipelineState(m_command_list.get());

	auto d3d12_geometry = GetD3D12Geometry(geometry);
	d3d12_geometry->Draw(m_command_list.get());

	return true;
}

namespace d3d12_detail
{

template <typename T, typename Map, typename Key, typename... Args>
inline typename Map::mapped_type
GetOrCreate(Map& map, Key const& key, Args&&... args)
{
	auto const& it = map.find(key);
	if (it != map.end())
	{
		return it->second;
	}

	auto p = std::make_shared<T>(bksge::forward<Args>(args)...);
	map[key] = p;
	return p;
}

}	// namespace d3d12_detail

BKSGE_INLINE std::shared_ptr<d3d12::HlslProgram>
D3D12Renderer::GetD3D12HlslProgram(Shader const& shader)
{
	return d3d12_detail::GetOrCreate<d3d12::HlslProgram>(
		m_d3d12_hlsl_program_map, shader.id(), m_device.get(), shader);
}

BKSGE_INLINE std::shared_ptr<d3d12::Geometry>
D3D12Renderer::GetD3D12Geometry(Geometry const& geometry)
{
	return d3d12_detail::GetOrCreate<d3d12::Geometry>(
		m_d3d12_geometry_map, geometry.id(), m_device.get(), geometry);
}

BKSGE_INLINE std::shared_ptr<d3d12::PipelineState>
D3D12Renderer::GetD3D12PipelineState(
	Shader const& shader,
	RenderState const& render_state,
	Primitive primitive)
{
	auto const id = bksge::hash_combine(shader.id(), render_state, primitive);
	return d3d12_detail::GetOrCreate<d3d12::PipelineState>(
		m_d3d12_pipeline_state,
		id,
		m_device.get(),
		*GetD3D12HlslProgram(shader),
		render_state,
		primitive);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_INL_D3D12_RENDERER_INL_HPP
