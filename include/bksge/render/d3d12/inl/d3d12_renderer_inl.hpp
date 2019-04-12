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
#include <bksge/render/d3d12/d3d12_factory.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12_command_queue.hpp>
#include <bksge/render/d3d12/d3d12_command_list.hpp>
#include <bksge/render/d3d12/d3d12_swap_chain.hpp>
#include <bksge/render/d3d12/d3d12_render_target.hpp>
#include <bksge/render/d3d12/d3d12_fence.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/d3d_helper/dxgi.hpp>
#include <bksge/render/d3d_helper/throw_if_failed.hpp>

#include <bksge/render/geometry.hpp>
#include <bksge/render/shader.hpp>

#include <bksge/memory/make_unique.hpp>
#include <bksge/window/window.hpp>
#include <bksge/detail/win32.hpp>
#include <bksge/assert.hpp>

#include <unordered_map>

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

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
	m_factory = bksge::make_unique<D3D12Factory>();

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

	m_swap_chain = bksge::make_unique<D3D12SwapChain>(
		m_factory.get(), m_command_queue.get(), width, height, hwnd);

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

	m_command_list->OMSetRenderTargets(1, m_render_target->GetHandle(m_frameIndex));
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

inline DXGI_FORMAT ToD3D12Format(TypeEnum type)
{
	static std::unordered_map<TypeEnum, DXGI_FORMAT> const m =
	{
		{TypeEnum::kByte, DXGI_FORMAT_R8_SINT},
		{TypeEnum::kUnsignedByte, DXGI_FORMAT_R8_UINT},
		{TypeEnum::kShort, DXGI_FORMAT_R16_SINT},
		{TypeEnum::kUnsignedShort, DXGI_FORMAT_R16_UINT},
		{TypeEnum::kInt, DXGI_FORMAT_R32_SINT},
		{TypeEnum::kUnsignedInt, DXGI_FORMAT_R32_UINT},
		{TypeEnum::kFloat, DXGI_FORMAT_R32_FLOAT},
	};

	return m.at(type);
}

BKSGE_INLINE void
D3D12Renderer::VRender(Geometry const& geometry, Shader const& shader)
{
	if (!m_pipelineState)
	{
		// Create an empty root signature
		{
			D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
			rootSignatureDesc.NumParameters     = 0;
			rootSignatureDesc.pParameters       = nullptr;
			rootSignatureDesc.NumStaticSamplers = 0;
			rootSignatureDesc.pStaticSamplers   = nullptr;
			rootSignatureDesc.Flags             = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

			ComPtr<::ID3DBlob> signature;
			ComPtr<::ID3DBlob> error;
			ThrowIfFailed(::D3D12SerializeRootSignature(
				&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
			m_rootSignature = m_device->CreateRootSignature(
				0, signature->GetBufferPointer(), signature->GetBufferSize());
		}

		// Create the pipeline state
		::D3D12_INPUT_ELEMENT_DESC elementDescs[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		};

		::D3D12_RASTERIZER_DESC rasterDesc ={};
		rasterDesc.FillMode              = D3D12_FILL_MODE_SOLID;
		rasterDesc.CullMode              = D3D12_CULL_MODE_NONE;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.DepthBias             = D3D12_DEFAULT_DEPTH_BIAS;
		rasterDesc.DepthBiasClamp        = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		rasterDesc.SlopeScaledDepthBias  = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		rasterDesc.DepthClipEnable       = true;
		rasterDesc.MultisampleEnable     = false;
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.ForcedSampleCount     = 0;
		rasterDesc.ConservativeRaster    = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

		::D3D12_BLEND_DESC blendDesc ={};
		blendDesc.AlphaToCoverageEnable  = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable           = false;
		blendDesc.RenderTarget[0].LogicOpEnable         = false;
		blendDesc.RenderTarget[0].SrcBlend              = D3D12_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend             = D3D12_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOp               = D3D12_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D12_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha        = D3D12_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha          = D3D12_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].LogicOp               = D3D12_LOGIC_OP_NOOP;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

#if defined(_DEBUG)
	   // Enable better shader debugging with the graphics debugging tools.
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
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

		::D3D12_GRAPHICS_PIPELINE_STATE_DESC desc ={};
		desc.InputLayout                     ={elementDescs, _countof(elementDescs)};
		desc.pRootSignature                  = m_rootSignature.Get();
		desc.VS                              ={vertexShader->GetBufferPointer(), vertexShader->GetBufferSize()};
		desc.PS                              ={pixelShader->GetBufferPointer(), pixelShader->GetBufferSize()};
		desc.RasterizerState                 = rasterDesc;
		desc.BlendState                      = blendDesc;
		desc.DepthStencilState.DepthEnable   = FALSE;
		desc.DepthStencilState.StencilEnable = FALSE;
		desc.SampleMask                      = UINT_MAX;
		desc.PrimitiveTopologyType           = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		desc.NumRenderTargets                = 1;
		desc.RTVFormats[0]                   = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count                = 1;

		m_pipelineState = m_device->CreateGraphicsPipelineState(desc);
	}

	if (!m_vertexBuffer)
	{
		// Create the vertex buffer.
		{
			auto const vertices = geometry.vertex_array_data();
			auto const size     = geometry.vertex_array_bytes();
			auto const stride   = geometry.vertex_layout().total_bytes();

			::D3D12_HEAP_PROPERTIES prop ={};
			prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
			prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			prop.CreationNodeMask     = 1;
			prop.VisibleNodeMask      = 1;

			D3D12_RESOURCE_DESC desc ={};
			desc.Dimension        = D3D12_RESOURCE_DIMENSION_BUFFER;
			desc.Alignment        = 0;
			desc.Width            = size;
			desc.Height           = 1;
			desc.DepthOrArraySize = 1;
			desc.MipLevels        = 1;
			desc.Format           = DXGI_FORMAT_UNKNOWN;
			desc.SampleDesc.Count = 1;
			desc.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			desc.Flags            = D3D12_RESOURCE_FLAG_NONE;

			m_vertexBuffer = m_device->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr);

			// バッファにコピー
			UINT8* p;
			ThrowIfFailed(m_vertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&p)));
			std::memcpy(p, vertices, size);
			m_vertexBuffer->Unmap(0, nullptr);

			// Viewの初期化
			m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
			m_vertexBufferView.SizeInBytes = static_cast<::UINT>(size);
			m_vertexBufferView.StrideInBytes = static_cast<::UINT>(stride);
		}

		// Create the index buffer.
		{
			auto const src    = geometry.index_array_data();
			auto const size   = geometry.index_array_bytes();

			if (src != nullptr && size != 0u)
			{
				m_enable_index = true;

				::D3D12_HEAP_PROPERTIES prop = {};
				prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
				prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
				prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
				prop.CreationNodeMask     = 1;
				prop.VisibleNodeMask      = 1;

				D3D12_RESOURCE_DESC desc ={};
				desc.Dimension        = D3D12_RESOURCE_DIMENSION_BUFFER;
				desc.Alignment        = 0;
				desc.Width            = size;
				desc.Height           = 1;
				desc.DepthOrArraySize = 1;
				desc.MipLevels        = 1;
				desc.Format           = DXGI_FORMAT_UNKNOWN;
				desc.SampleDesc.Count = 1;
				desc.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
				desc.Flags            = D3D12_RESOURCE_FLAG_NONE;

				m_indexBuffer = m_device->CreateCommittedResource(
					&prop,
					D3D12_HEAP_FLAG_NONE,
					&desc,
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr);

				// バッファにコピー
				UINT8* p;
				ThrowIfFailed(m_indexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&p)));
				std::memcpy(p, src, size);
				m_indexBuffer->Unmap(0, nullptr);

				// Describe the index buffer view.
				m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
				m_indexBufferView.Format = ToD3D12Format(geometry.index_array_type());
				m_indexBufferView.SizeInBytes = static_cast<::UINT>(size);

				m_numIndices = static_cast<::UINT>(geometry.index_array_count());
			}
		}
	}

	m_command_list->SetGraphicsRootSignature(m_rootSignature.Get());
	m_command_list->SetPipelineState(m_pipelineState.Get());

	m_command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_command_list->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	if (m_enable_index)
	{
		m_command_list->IASetIndexBuffer(&m_indexBufferView);
		m_command_list->DrawIndexedInstanced(m_numIndices, 1, 0, 0, 0);
	}
	else
	{
		m_command_list->DrawInstanced(3, 1, 0, 0);
	}
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
