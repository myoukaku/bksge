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
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_queue_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_render_target_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_fence_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_geometry_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_root_signature_fwd.hpp>
#include <bksge/render/dxgi/fwd/dxgi_factory_fwd.hpp>
#include <bksge/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>

#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/dxgi/dxgi.hpp>
#include <bksge/render/renderer.hpp>
#include <bksge/render/fwd/clear_flag_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/render_state_fwd.hpp>
#include <bksge/math/fwd/color4_fwd.hpp>
#include <bksge/window/fwd/window_fwd.hpp>

#include <memory>

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

	void WaitForPreviousFrame();

	void VSetRenderTarget(Window const& window) override;
	void VBegin(void) override;
	void VEnd(void) override;
	void VClear(ClearFlag clear_flag, Color4f const& clear_color) override;
	void VRender(Geometry const& geometry, RenderState const& render_state) override;

private:
//	static const ::UINT FrameCount = 2;

	std::unique_ptr<DXGIFactory>		m_factory;
	std::unique_ptr<D3D12Device>		m_device;
	std::unique_ptr<D3D12CommandQueue>	m_command_queue;
	std::unique_ptr<D3D12CommandList>	m_command_list;
	std::unique_ptr<DXGISwapChain>		m_swap_chain;
	std::unique_ptr<D3D12RenderTarget>	m_render_target;
	std::unique_ptr<D3D12Fence>			m_fence;

	// TODO
	std::unique_ptr<D3D12RootSignature>	m_root_signature;

	// TODO
	std::unique_ptr<D3D12Geometry>		m_geometry;

	::UINT m_frameIndex;

	::D3D12_VIEWPORT m_viewport;
	::D3D12_RECT m_scissorRect;

	// TODO
	//ComPtr<::ID3D12RootSignature> m_rootSignature;
	ComPtr<::ID3D12PipelineState> m_pipelineState;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_RENDERER_HPP
