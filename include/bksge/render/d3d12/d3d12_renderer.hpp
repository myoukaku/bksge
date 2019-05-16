﻿/**
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
#include <bksge/render/d3d12/fwd/d3d12_hlsl_program_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_constant_buffer_descriptor_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_geometry_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_root_signature_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_pipeline_state_fwd.hpp>
#include <bksge/render/dxgi/fwd/dxgi_factory_fwd.hpp>
#include <bksge/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>

#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>

#include <bksge/render/renderer.hpp>
#include <bksge/render/fwd/clear_flag_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/render_state_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/primitive_fwd.hpp>
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
	void VRender(
		Geometry const& geometry,
		ShaderMap const& shader_map,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;

private:
	std::shared_ptr<D3D12HLSLProgram>
	GetD3D12HLSLProgram(Shader const& shader);

	std::shared_ptr<D3D12ConstantBufferDescriptor>
	GetD3D12ConstantBufferDescriptor(
		ShaderParameterMap const& shader_parameter_map,
		D3D12HLSLProgram* hlsl_program);

	std::shared_ptr<D3D12Geometry>
	GetD3D12Geometry(Geometry const& geometry);

	std::shared_ptr<D3D12PipelineState>
	GetD3D12PipelineState(Shader const& shader, Primitive primitive);

private:
//	static const ::UINT FrameCount = 2;

	std::unique_ptr<DXGIFactory>		m_factory;
	std::unique_ptr<DXGISwapChain>		m_swap_chain;
	std::unique_ptr<D3D12Device>		m_device;
	std::unique_ptr<D3D12CommandQueue>	m_command_queue;
	std::unique_ptr<D3D12CommandList>	m_command_list;
	std::unique_ptr<D3D12RenderTarget>	m_render_target;
	std::unique_ptr<D3D12Fence>			m_fence;

	D3D12HLSLProgramMap                 m_d3d12_hlsl_program_map;
	D3D12ConstantBufferDescriptorMap    m_d3d12_constant_buffer_descriptor_map;
	D3D12GeometryMap                    m_d3d12_geometry_map;
	D3D12PipelineStateMap               m_d3d12_pipeline_state;

	// TODO
	::UINT m_frameIndex;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_RENDERER_HPP
