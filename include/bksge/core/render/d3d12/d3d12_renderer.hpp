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
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_queue_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/render_target_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/fence_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/hlsl_program_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/root_signature_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/pipeline_state_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/descriptor_heaps_fwd.hpp>
#include <bksge/core/render/dxgi/fwd/dxgi_factory_fwd.hpp>
#include <bksge/core/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>

#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>

#include <bksge/core/render/renderer.hpp>
#include <bksge/core/render/fwd/clear_flag_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/primitive_fwd.hpp>
#include <bksge/core/math/fwd/color4_fwd.hpp>
#include <bksge/core/window/fwd/window_fwd.hpp>

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

	void VSetRenderTarget(Window const& window) override;
	void VBegin(void) override;
	void VEnd(void) override;
	bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;

private:
	std::shared_ptr<d3d12::HlslProgram>
	GetD3D12HlslProgram(Shader const& shader);

	std::shared_ptr<d3d12::Geometry>
	GetD3D12Geometry(Geometry const& geometry);

	std::shared_ptr<d3d12::PipelineState>
	GetD3D12PipelineState(
		Shader const& shader,
		RenderState const& render_state,
		Primitive primitive);

private:
	std::unique_ptr<DXGIFactory>			m_factory;
	std::unique_ptr<DXGISwapChain>			m_swap_chain;
	std::unique_ptr<d3d12::Device>			m_device;
	std::unique_ptr<d3d12::CommandQueue>	m_command_queue;
	std::unique_ptr<d3d12::CommandList>		m_command_list;
	std::unique_ptr<d3d12::RenderTarget>	m_render_target;
	std::unique_ptr<d3d12::Fence>			m_fence;
	std::unique_ptr<d3d12::DescriptorHeaps>	m_descriptor_heaps;

	d3d12::HlslProgramMap                 m_d3d12_hlsl_program_map;
	d3d12::GeometryMap                    m_d3d12_geometry_map;
	d3d12::PipelineStateMap               m_d3d12_pipeline_state;

	std::unique_ptr<d3d12::ResourceCache>	m_resource_cache;

	::UINT									m_frame_index;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/inl/d3d12_renderer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_D3D12_RENDERER_HPP
