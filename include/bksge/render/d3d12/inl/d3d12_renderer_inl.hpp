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
#include <bksge/render/d3d11/com_ptr.hpp>

#include <bksge/render/geometry.hpp>
#include <bksge/render/shader.hpp>

#include <bksge/window/window.hpp>
#include <bksge/detail/win32.hpp>
#include <bksge/assert.hpp>

#include <d3d12.h>
#include <dxgi1_5.h>
#include <d3dcompiler.h>
//#include <synchapi.h>
//#include <vector>
#include <unordered_map>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace bksge
{

namespace render
{

inline std::string HrToString(::HRESULT hr)
{
	char s_str[64] ={};
	sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<::UINT>(hr));
	return std::string(s_str);
}

class HrException : public std::runtime_error
{
public:
	HrException(::HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) {}
	::HRESULT Error() const { return m_hr; }
private:
	::HRESULT const m_hr;
};

inline void ThrowIfFailed(::HRESULT hr)
{
	if (FAILED(hr))
	{
		throw HrException(hr);
	}
}

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
	m_useWarpDevice = false;

	// Create Factory
	{
		::UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)
	// Enable the debug layer (requires the Graphics Tools "optional feature").
	// NOTE: Enabling the debug layer after device creation will invalidate the active device.
		{
			ComPtr<::ID3D12Debug> debugController;
			if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
			{
				debugController->EnableDebugLayer();

				// Enable additional debug layers.
				dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
			}
		}
#endif
		ThrowIfFailed(::CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));
	}

	// Create Device
	if (m_useWarpDevice)
	{
		ComPtr<::IDXGIAdapter> warpAdapter;
		ThrowIfFailed(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));

		ThrowIfFailed(::D3D12CreateDevice(
			warpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&m_device)
		));
	}
	else
	{
		ComPtr<::IDXGIAdapter1> hardwareAdapter;
		GetHardwareAdapter(factory.Get(), &hardwareAdapter);

		ThrowIfFailed(::D3D12CreateDevice(
			hardwareAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&m_device)
		));
	}

	// Create CommandQueue
	{
		::D3D12_COMMAND_QUEUE_DESC queueDesc ={};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		ThrowIfFailed(m_device->CreateCommandQueue(
			&queueDesc,
			IID_PPV_ARGS(&m_commandQueue)));
	}

	// Create CommandAllocator
	ThrowIfFailed(m_device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&m_commandAllocator)));

	// Create the command list.
	ThrowIfFailed(m_device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		m_commandAllocator.Get(),
		nullptr,//m_pipelineState.Get(),
		IID_PPV_ARGS(&m_commandList)));

	// Command lists are created in the recording state, but there is nothing
	// to record yet. The main loop expects it to be closed, so close it now.
	ThrowIfFailed(m_commandList->Close());
}

BKSGE_INLINE void
D3D12Renderer::Finalize(void)
{
	// Ensure that the GPU is no longer referencing resources that are about to be
	// cleaned up by the destructor.
	WaitForPreviousFrame();

	::CloseHandle(m_fenceEvent);
}

BKSGE_INLINE void
D3D12Renderer::GetHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter)
{
	ComPtr<::IDXGIAdapter1> adapter;
	*ppAdapter = nullptr;

	for (::UINT adapterIndex = 0;
		DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(adapterIndex, &adapter);
		++adapterIndex)
	{
		::DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			// Don't select the Basic Render Driver adapter.
			// If you want a software adapter, pass in "/warp" on the command line.
			continue;
		}

		// Check to see if the adapter supports Direct3D 12, but don't create the
		// actual device yet.
		if (SUCCEEDED(::D3D12CreateDevice(
			adapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			_uuidof(ID3D12Device),
			nullptr)))
		{
			break;
		}
	}

	*ppAdapter = adapter.Detach();
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

	// Describe and create the swap chain.
	::DXGI_SWAP_CHAIN_DESC1 swapChainDesc ={};
	swapChainDesc.BufferCount      = FrameCount;
	swapChainDesc.Width            = width;
	swapChainDesc.Height           = height;
	swapChainDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage      = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect       = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	ComPtr<::IDXGISwapChain1> swapChain;
	ThrowIfFailed(factory->CreateSwapChainForHwnd(
		m_commandQueue.Get(),        // Swap chain needs the queue so that it can force a flush on it.
		hwnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain
	));

	//// This sample does not support fullscreen transitions.
	//ThrowIfFailed(factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER));

	ThrowIfFailed(swapChain.As(&m_swapChain));
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

	// Create descriptor heaps.
	{
		// Describe and create a render target view (RTV) descriptor heap.
		::D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc ={};
		rtvHeapDesc.NumDescriptors = FrameCount;
		rtvHeapDesc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		ThrowIfFailed(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap)));

		m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	// Create frame resources.
	{
		::D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

		// Create a RTV for each frame.
		for (::UINT n = 0; n < FrameCount; n++)
		{
			ThrowIfFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n])));
			m_device->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvHandle);
			rtvHandle.ptr += m_rtvDescriptorSize;
		}
	}

	// Create synchronization objects and wait until assets have been uploaded to the GPU.
	{
		ThrowIfFailed(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
		m_fenceValue = 1;

		// Create an event handle to use for frame synchronization.
		m_fenceEvent = bksge::win32::CreateEvent(nullptr, FALSE, FALSE, (char const*)nullptr);
		if (m_fenceEvent == nullptr)
		{
			ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		}

		// Wait for the command list to execute; we are reusing the same command 
		// list in our main loop but for now, we just want to wait for setup to 
		// complete before continuing.
		WaitForPreviousFrame();
	}
}

BKSGE_INLINE void
D3D12Renderer::VBegin(void)
{
	// Command list allocators can only be reset when the associated 
	// command lists have finished execution on the GPU; apps should use 
	// fences to determine GPU execution progress.
	ThrowIfFailed(m_commandAllocator->Reset());

	// However, when ExecuteCommandList() is called on a particular command 
	// list, that command list can then be reset at any time and must be before 
	// re-recording.
	ThrowIfFailed(m_commandList->Reset(m_commandAllocator.Get(), nullptr/*m_pipelineState.Get()*/));

	m_commandList->RSSetViewports(1, &m_viewport);
	m_commandList->RSSetScissorRects(1, &m_scissorRect);

	// Indicate that the back buffer will be used as a render target.
	{
		::D3D12_RESOURCE_BARRIER barrier;
		barrier.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;     // バリアはリソースの状態遷移に対して設置
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource   = m_renderTargets[m_frameIndex].Get();   // リソースは描画ターゲット
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;   // 遷移前はPresent
		barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_RENDER_TARGET;  // 遷移後は描画ターゲット
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		m_commandList->ResourceBarrier(1, &barrier);
	}

	// SetRenderTargets
	{
		::D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
		rtvHandle.ptr += m_rtvDescriptorSize * m_frameIndex;
		m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
	}
}

BKSGE_INLINE void
D3D12Renderer::VEnd(void)
{
	// Indicate that the back buffer will now be used to present.
	{
		::D3D12_RESOURCE_BARRIER barrier;
		barrier.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;     // バリアはリソースの状態遷移に対して設置
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource   = m_renderTargets[m_frameIndex].Get();   // リソースは描画ターゲット
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // 遷移前は描画ターゲット
		barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;   // 遷移後はPresent
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		m_commandList->ResourceBarrier(1, &barrier);
	}

	ThrowIfFailed(m_commandList->Close());

	// Execute the command list.
	::ID3D12CommandList* ppCommandLists[] ={m_commandList.Get()};
	m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// Present the frame.
	ThrowIfFailed(m_swapChain->Present(1, 0));

	WaitForPreviousFrame();
}

BKSGE_INLINE void
D3D12Renderer::VClear(ClearFlag clear_flag, Color4f const& clear_color)
{
	if ((clear_flag & ClearFlag::kColor) != ClearFlag::kNone)
	{
		::D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
		rtvHandle.ptr += m_frameIndex * m_rtvDescriptorSize;
		m_commandList->ClearRenderTargetView(rtvHandle, clear_color.data(), 0, nullptr);
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

	//m_commandList->ClearDepthStencilView(dsv_handle_, mask, 1.0f, 0, 0, nullptr);
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

			ComPtr<ID3DBlob> signature;
			ComPtr<ID3DBlob> error;
			ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
			ThrowIfFailed(m_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)));
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

		ThrowIfFailed(m_device->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&m_pipelineState)));
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

			ThrowIfFailed(m_device->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_vertexBuffer)));

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

				ThrowIfFailed(m_device->CreateCommittedResource(
					&prop,
					D3D12_HEAP_FLAG_NONE,
					&desc,
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr,
					IID_PPV_ARGS(&m_indexBuffer)));

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

	m_commandList->SetGraphicsRootSignature(m_rootSignature.Get());
	m_commandList->SetPipelineState(m_pipelineState.Get());

	m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	if (m_enable_index)
	{
		m_commandList->IASetIndexBuffer(&m_indexBufferView);
		m_commandList->DrawIndexedInstanced(m_numIndices, 1, 0, 0, 0);
	}
	else
	{
		m_commandList->DrawInstanced(3, 1, 0, 0);
	}
}

BKSGE_INLINE void
D3D12Renderer::WaitForPreviousFrame()
{
	// WAITING FOR THE FRAME TO COMPLETE BEFORE CONTINUING IS NOT BEST PRACTICE.
	// This is code implemented as such for simplicity. The D3D12HelloFrameBuffering
	// sample illustrates how to use fences for efficient resource usage and to
	// maximize GPU utilization.

	// Signal and increment the fence value.
	const ::UINT64 fence = m_fenceValue;
	ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), fence));
	m_fenceValue++;

	// Wait until the previous frame is finished.
	if (m_fence->GetCompletedValue() < fence)
	{
		ThrowIfFailed(m_fence->SetEventOnCompletion(fence, m_fenceEvent));
		WaitForSingleObject(m_fenceEvent, INFINITE);
	}

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_RENDERER_INL_HPP
