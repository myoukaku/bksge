/**
 *	@file	d3d12_renderer.hpp
 *
 *	@brief	D3D12Renderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_D3D12_RENDERER_HPP
#define BKSGE_CORE_RENDER_D3D12_D3D12_RENDERER_HPP

#include <bksge/core/render/d3d12/fwd/d3d12_renderer_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_queue_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/depth_stencil_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/descriptor_heaps_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/fence_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/render_target_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/dxgi/fwd/dxgi_factory_fwd.hpp>
#include <bksge/core/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/core/render/renderer.hpp>
#include <bksge/core/window/fwd/window_fwd.hpp>
#include <memory>	// std::unique_ptr

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
	D3D12Renderer(Window const& window);

	virtual ~D3D12Renderer();

private:
	void VBegin(void) override;
	void VEnd(void) override;
	bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;

private:
	std::unique_ptr<DXGIFactory>			m_factory;
	std::unique_ptr<DXGISwapChain>			m_swap_chain;
	std::unique_ptr<d3d12::Device>			m_device;
	std::unique_ptr<d3d12::CommandQueue>	m_command_queue;
	std::unique_ptr<d3d12::CommandList>		m_command_list;
	std::unique_ptr<d3d12::RenderTarget>	m_render_target;
	std::unique_ptr<d3d12::DepthStencil>	m_depth_stencil;
	std::unique_ptr<d3d12::Fence>			m_fence;
	std::unique_ptr<d3d12::DescriptorHeaps>	m_descriptor_heaps;
	std::unique_ptr<d3d12::ResourcePool>	m_resource_pool;
	::UINT									m_frame_index;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/inl/d3d12_renderer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_D3D12_RENDERER_HPP
