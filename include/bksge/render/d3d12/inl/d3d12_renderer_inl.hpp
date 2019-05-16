/**
 *	@file	d3d12_renderer_inl.hpp
 *
 *	@brief	D3D12Renderer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_RENDERER_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_RENDERER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_renderer.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12_command_queue.hpp>
#include <bksge/render/d3d12/d3d12_command_list.hpp>
#include <bksge/render/d3d12/d3d12_render_target.hpp>
#include <bksge/render/d3d12/d3d12_fence.hpp>
#include <bksge/render/d3d12/d3d12_geometry.hpp>
#include <bksge/render/d3d12/d3d12_root_signature.hpp>
#include <bksge/render/d3d12/d3d12_input_layout.hpp>
#include <bksge/render/d3d12/d3d12_rasterizer_state.hpp>
#include <bksge/render/d3d12/d3d12_blend_state.hpp>
#include <bksge/render/d3d12/d3d12_depth_stencil_state.hpp>
#include <bksge/render/d3d12/d3d12_hlsl_program.hpp>
#include <bksge/render/d3d12/d3d12_constant_buffer_descriptor.hpp>
#include <bksge/render/d3d12/d3d12_primitive_topology_type.hpp>
#include <bksge/render/d3d12/d3d12_pipeline_state.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <bksge/render/d3d_common/d3dcompiler.hpp>
#include <bksge/render/dxgi/dxgi_swap_chain.hpp>
#include <bksge/render/dxgi/dxgi_factory.hpp>
#include <bksge/render/d3d_common/dxgi.hpp>

#include <bksge/render/geometry.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/shader_parameter_map.hpp>
#include <bksge/render/shader_map.hpp>
#include <bksge/render/render_state.hpp>

#include <bksge/memory/make_unique.hpp>
#include <bksge/window/window.hpp>
#include <bksge/detail/win32.hpp>
#include <bksge/functional/hash_combine.hpp>
#include <bksge/assert.hpp>

#include <unordered_map>

namespace bksge
{

namespace render
{

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

	m_factory = bksge::make_unique<DXGIFactory>();

	m_device = bksge::make_unique<D3D12Device>(m_factory->EnumAdapters());

	m_command_queue = bksge::make_unique<D3D12CommandQueue>(m_device.get());

	m_command_list = bksge::make_unique<D3D12CommandList>(m_device.get());

	// Command lists are created in the recording state, but there is nothing
	// to record yet. The main loop expects it to be closed, so close it now.
	m_command_list->Close();
}

BKSGE_INLINE void
D3D12Renderer::Finalize(void)
{
	// Ensure that the GPU is no longer referencing resources that are about to be
	// cleaned up by the destructor.
	WaitForPreviousFrame();

	m_fence->Close();
}

BKSGE_INLINE void
D3D12Renderer::VSetRenderTarget(Window const& window)
{
	::HWND const hwnd = window.Handle();

	if (hwnd == nullptr)
	{
		return;
	}

	::UINT const width  = 800;	// TODO
	::UINT const height = 600;	// TODO

	m_swap_chain = bksge::make_unique<DXGISwapChain>(
		m_factory.get(), m_command_queue->Get(), width, height, hwnd);

	m_factory->MakeWindowAssociation(
		hwnd,
		DXGI_MWA_NO_WINDOW_CHANGES |
		DXGI_MWA_NO_ALT_ENTER      |
		DXGI_MWA_NO_PRINT_SCREEN);

	m_frameIndex = m_swap_chain->GetCurrentBackBufferIndex();

	m_render_target = bksge::make_unique<D3D12RenderTarget>(
		m_device.get(), m_swap_chain.get());

	m_fence = bksge::make_unique<D3D12Fence>(m_device.get());
	WaitForPreviousFrame();
}

BKSGE_INLINE void
D3D12Renderer::VBegin(void)
{
	m_command_list->Reset();

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

	if (m_scissor)
	{
		::D3D12_RECT scissor_rect;
		scissor_rect.left   = static_cast<::LONG>(m_scissor->left());
		scissor_rect.top    = static_cast<::LONG>(m_scissor->top());
		scissor_rect.right  = static_cast<::LONG>(m_scissor->right());
		scissor_rect.bottom = static_cast<::LONG>(m_scissor->bottom());
		m_command_list->RSSetScissorRects(1, &scissor_rect);
	}

	// Indicate that the back buffer will be used as a render target.
	m_command_list->ResourceBarrier(
		m_render_target->GetResource(m_frameIndex),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET);

	auto const handle = m_render_target->GetHandle(m_frameIndex);
	m_command_list->OMSetRenderTargets(1, &handle);
}

BKSGE_INLINE void
D3D12Renderer::VEnd(void)
{
	// Indicate that the back buffer will now be used to present.
	m_command_list->ResourceBarrier(
		m_render_target->GetResource(m_frameIndex),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT);

	m_command_list->Close();

	m_command_queue->ExecuteCommandLists(m_command_list.get());

	m_swap_chain->Present(1, 0);

	WaitForPreviousFrame();
}

BKSGE_INLINE void
D3D12Renderer::VClear(ClearFlag clear_flag, Color4f const& clear_color)
{
	if ((clear_flag & ClearFlag::kColor) != ClearFlag::kNone)
	{
		m_command_list->ClearRenderTargetView(
			m_render_target->GetHandle(m_frameIndex),
			clear_color.data());
	}

	::D3D12_CLEAR_FLAGS mask{};
	if ((clear_flag & ClearFlag::kDepth) != ClearFlag::kNone)
	{
		mask |= D3D12_CLEAR_FLAG_DEPTH;
	}
	if ((clear_flag & ClearFlag::kStencil) != ClearFlag::kNone)
	{
		mask |= D3D12_CLEAR_FLAG_STENCIL;
	}

	//m_command_list->ClearDepthStencilView(dsv_handle_, mask, 1.0f, 0, 0, nullptr);
}

BKSGE_INLINE void
D3D12Renderer::VRender(
	Geometry const& geometry,
	ShaderMap const& shader_map,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	// TODO
	(void)render_state;

	auto* shader = shader_map.GetShader(ShaderType::kHLSL);
	if (shader == nullptr)
	{
		return;
	}

	auto hlsl_program = GetD3D12HLSLProgram(*shader);

	auto pipeline_state = GetD3D12PipelineState(*shader, geometry.primitive());

	//if (!m_pipelineState)
	//{
	//	D3D12RasterizerState   raster_state;
	//	D3D12BlendState        blend_state;
	//	D3D12DepthStencilState depth_stencil_state;

	//	::D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
	//	desc.InputLayout           = hlsl_program->GetInputLayout();
	//	desc.pRootSignature        = hlsl_program->GetRootSignature();
	//	desc.VS                    = hlsl_program->GetVertexShaderBytecode();
	//	desc.PS                    = hlsl_program->GetPixelShaderBytecode();
	//	desc.RasterizerState       = raster_state;
	//	desc.BlendState            = blend_state;
	//	desc.DepthStencilState     = depth_stencil_state;
	//	desc.SampleMask            = UINT_MAX;
	//	desc.PrimitiveTopologyType = ToD3D12PrimitiveTopologyType(geometry.primitive());
	//	desc.NumRenderTargets      = 1;
	//	desc.RTVFormats[0]         = DXGI_FORMAT_R8G8B8A8_UNORM;
	//	desc.SampleDesc.Count      = 1;

	//	m_pipelineState = m_device->CreateGraphicsPipelineState(desc);
	//}

	m_command_list->SetGraphicsRootSignature(hlsl_program->GetRootSignature());
	//m_command_list->SetPipelineState(m_pipelineState.Get());
	pipeline_state->SetPipelineState(m_command_list.get());

	auto constant_buffer = GetD3D12ConstantBufferDescriptor(shader_parameter_map, hlsl_program.get());
	constant_buffer->UpdateParameters(shader_parameter_map);
	constant_buffer->SetEnable(m_command_list.get());

	auto d3d12_geometry = GetD3D12Geometry(geometry);
	d3d12_geometry->Draw(m_command_list.get());
}

BKSGE_INLINE void
D3D12Renderer::WaitForPreviousFrame()
{
	m_fence->WaitForPreviousFrame(m_command_queue.get());

	m_frameIndex = m_swap_chain->GetCurrentBackBufferIndex();
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

	auto p = std::make_shared<T>(std::forward<Args>(args)...);
	map[key] = p;
	return p;
}

}	// namespace d3d12_detail

BKSGE_INLINE std::shared_ptr<D3D12HLSLProgram>
D3D12Renderer::GetD3D12HLSLProgram(Shader const& shader)
{
	return d3d12_detail::GetOrCreate<D3D12HLSLProgram>(
		m_d3d12_hlsl_program_map, shader.id(), m_device.get(), shader);
}

BKSGE_INLINE std::shared_ptr<D3D12ConstantBufferDescriptor>
D3D12Renderer::GetD3D12ConstantBufferDescriptor(
	ShaderParameterMap const& shader_parameter_map,
	D3D12HLSLProgram* hlsl_program)
{
	return d3d12_detail::GetOrCreate<D3D12ConstantBufferDescriptor>(
		m_d3d12_constant_buffer_descriptor_map,
		shader_parameter_map.id(),
		m_device.get(),
		hlsl_program);
}

BKSGE_INLINE std::shared_ptr<D3D12Geometry>
D3D12Renderer::GetD3D12Geometry(Geometry const& geometry)
{
	return d3d12_detail::GetOrCreate<D3D12Geometry>(
		m_d3d12_geometry_map, geometry.id(), geometry, m_device.get());
}

BKSGE_INLINE std::shared_ptr<D3D12PipelineState>
D3D12Renderer::GetD3D12PipelineState(
	Shader const& shader,
	Primitive primitive)
{
	return d3d12_detail::GetOrCreate<D3D12PipelineState>(
		m_d3d12_pipeline_state,
		bksge::hash_combine(shader.id(), primitive),
		m_device.get(),
		*GetD3D12HLSLProgram(shader),
		primitive);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_RENDERER_INL_HPP
