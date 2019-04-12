/**
 *	@file	d3d12_renderer.hpp
 *
 *	@brief	D3D12Renderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_RENDERER_HPP
#define BKSGE_RENDER_D3D12_D3D12_RENDERER_HPP

#include <bksge/render/d3d12/fwd/d3d12_renderer_fwd.hpp>
#include <bksge/render/renderer.hpp>
#include <bksge/render/fwd/clear_flag_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/math/fwd/color4_fwd.hpp>
#include <bksge/window/fwd/window_fwd.hpp>

#include <bksge/render/d3d11/com_ptr.hpp>
#include <d3d12.h>
#include <dxgi1_5.h>

namespace bksge
{

namespace render
{

/**
 *	@brief	D3D12 レンダラー
 */
class D3D12Renderer : public Renderer
{
public:
	D3D12Renderer(void);

	virtual ~D3D12Renderer();

private:
	void Initialize(void);
	void Finalize(void);

	void GetHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter);
	void WaitForPreviousFrame();

	virtual void VSetRenderTarget(Window const& window) override;
	virtual void VBegin(void) override;
	virtual void VEnd(void) override;
	virtual void VClear(ClearFlag clear_flag, Color4f const& clear_color) override;
	virtual void VRender(Geometry const& geometry, Shader const& shader) override;

private:
	static const ::UINT FrameCount = 2;

	bool m_useWarpDevice;
	ComPtr<::IDXGIFactory4> factory;
	ComPtr<::ID3D12Device> m_device;
	ComPtr<::ID3D12CommandQueue> m_commandQueue;
	ComPtr<::ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<::ID3D12GraphicsCommandList> m_commandList;
	ComPtr<::IDXGISwapChain3> m_swapChain;
	ComPtr<::ID3D12DescriptorHeap> m_rtvHeap;
	::UINT m_rtvDescriptorSize;
	ComPtr<::ID3D12Resource> m_renderTargets[FrameCount];

	::UINT m_frameIndex;
	::HANDLE m_fenceEvent;
	ComPtr<::ID3D12Fence> m_fence;
	::UINT64 m_fenceValue;

	D3D12_VIEWPORT m_viewport;
	D3D12_RECT m_scissorRect;

	// TODO
	ComPtr<::ID3D12RootSignature> m_rootSignature;
	ComPtr<::ID3D12PipelineState> m_pipelineState;

	// TODO
	ComPtr<::ID3D12Resource> m_vertexBuffer;
	::D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	// TODO
	bool	m_enable_index = false;
	::UINT m_numIndices;
	ComPtr<::ID3D12Resource> m_indexBuffer;
	::D3D12_INDEX_BUFFER_VIEW m_indexBufferView;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_RENDERER_HPP
