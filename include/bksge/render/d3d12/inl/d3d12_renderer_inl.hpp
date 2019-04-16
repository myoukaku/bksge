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
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>
#include <bksge/render/d3d_helper/d3dcompiler.hpp>
#include <bksge/render/dxgi/dxgi_swap_chain.hpp>
#include <bksge/render/dxgi/dxgi_factory.hpp>
#include <bksge/render/dxgi/dxgi.hpp>

#include <bksge/render/geometry.hpp>
#include <bksge/render/shader.hpp>

#include <bksge/memory/make_unique.hpp>
#include <bksge/window/window.hpp>
#include <bksge/detail/win32.hpp>
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

	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;
	m_viewport.Width    = width;
	m_viewport.Height   = height;
	m_viewport.MinDepth = D3D12_MIN_DEPTH;
	m_viewport.MaxDepth = D3D12_MAX_DEPTH;

	m_scissorRect.left   = 0;
	m_scissorRect.top    = 0;
	m_scissorRect.right  = width;
	m_scissorRect.bottom = height;

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

	m_command_list->RSSetViewports(1, &m_viewport);
	m_command_list->RSSetScissorRects(1, &m_scissorRect);

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
D3D12Renderer::VRender(Geometry const& geometry, Shader const& shader)
{
	if (!m_pipelineState)
	{
		// Create an empty root signature
		m_root_signature =
			bksge::make_unique<D3D12RootSignature>(m_device.get());

		// Create the pipeline state
		D3D12InputLayout       input_layout(geometry);
		D3D12RasterizerState   raster_state;
		D3D12BlendState        blend_state;
		D3D12DepthStencilState depth_stencil_state;

#if defined(_DEBUG)
		// Enable better shader debugging with the graphics debugging tools.
		::UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		::UINT compileFlags = 0;
#endif
		auto const& vs_src = shader.program_map().at(ShaderStage::kVertex);
		ComPtr<::ID3DBlob> vertexShader;
		ThrowIfFailed(::D3DCompile(
			vs_src.c_str(),      // [in] Pointer to the shader in memory.
			vs_src.size(),       // [in] Size of the shader in memory.
			nullptr,			 // [in] Optional. You can use this parameter for strings that specify error messages.
			nullptr,             // [in] Optional. Pointer to a NULL-terminated array of macro definitions. See D3D_SHADER_MACRO. If not used, set this to NULL.
			nullptr,			 // [in] Optional. Pointer to an ID3DInclude Interface interface for handling include files. Setting this to NULL will cause a compile error if a shader contains a #include.
			"main",				 // [in] Name of the shader-entrypoint function where shader execution begins.
			"vs_5_0",              // [in] A string that specifies the shader model; can be any profile in shader model 4 or higher.
			compileFlags,       // [in] Effect compile flags - no D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY at the first try...
			0,                   // [in] Effect compile flags
			vertexShader.GetAddressOf(),// [out] A pointer to an ID3DBlob Interface which contains the compiled shader, as well as any embedded debug and symbol-table information.
			nullptr // [out] A pointer to an ID3DBlob Interface which contains a listing of errors and warnings that occurred during compilation. These errors and warnings are identical to the the debug output from a debugger.
		));

		auto const& ps_src = shader.program_map().at(ShaderStage::kFragment);
		ComPtr<::ID3DBlob> pixelShader;
		ThrowIfFailed(::D3DCompile(
			ps_src.c_str(),      // [in] Pointer to the shader in memory.
			ps_src.size(),       // [in] Size of the shader in memory.
			nullptr,			 // [in] Optional. You can use this parameter for strings that specify error messages.
			nullptr,             // [in] Optional. Pointer to a NULL-terminated array of macro definitions. See D3D_SHADER_MACRO. If not used, set this to NULL.
			nullptr,			 // [in] Optional. Pointer to an ID3DInclude Interface interface for handling include files. Setting this to NULL will cause a compile error if a shader contains a #include.
			"main",				 // [in] Name of the shader-entrypoint function where shader execution begins.
			"ps_5_0",              // [in] A string that specifies the shader model; can be any profile in shader model 4 or higher.
			compileFlags,       // [in] Effect compile flags - no D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY at the first try...
			0,                   // [in] Effect compile flags
			pixelShader.GetAddressOf(),// [out] A pointer to an ID3DBlob Interface which contains the compiled shader, as well as any embedded debug and symbol-table information.
			nullptr // [out] A pointer to an ID3DBlob Interface which contains a listing of errors and warnings that occurred during compilation. These errors and warnings are identical to the the debug output from a debugger.
		));

		::D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
		desc.InputLayout           = input_layout;
		desc.pRootSignature        = m_root_signature->Get();
		desc.VS                    ={vertexShader->GetBufferPointer(), vertexShader->GetBufferSize()};
		desc.PS                    ={pixelShader->GetBufferPointer(), pixelShader->GetBufferSize()};
		desc.RasterizerState       = raster_state;
		desc.BlendState            = blend_state;
		desc.DepthStencilState     = depth_stencil_state;
		desc.SampleMask            = UINT_MAX;
		desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		desc.NumRenderTargets      = 1;
		desc.RTVFormats[0]         = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count      = 1;

		m_pipelineState = m_device->CreateGraphicsPipelineState(desc);
	}

	if (!m_geometry)
	{
		m_geometry = bksge::make_unique<D3D12Geometry>(
			geometry, m_device.get());
	}

	m_command_list->SetGraphicsRootSignature(m_root_signature->Get());
	m_command_list->SetPipelineState(m_pipelineState.Get());

	m_geometry->Draw(m_command_list.get());
}

BKSGE_INLINE void
D3D12Renderer::WaitForPreviousFrame()
{
	m_fence->WaitForPreviousFrame(m_command_queue.get());

	m_frameIndex = m_swap_chain->GetCurrentBackBufferIndex();
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_RENDERER_INL_HPP
