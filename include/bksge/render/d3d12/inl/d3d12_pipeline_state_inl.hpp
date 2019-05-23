/**
 *	@file	d3d12_pipeline_state_inl.hpp
 *
 *	@brief	D3D12PipelineState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_PIPELINE_STATE_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_PIPELINE_STATE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_pipeline_state.hpp>
#include <bksge/render/d3d12/d3d12_rasterizer_state.hpp>
#include <bksge/render/d3d12/d3d12_blend_state.hpp>
#include <bksge/render/d3d12/d3d12_depth_stencil_state.hpp>
#include <bksge/render/d3d12/d3d12_hlsl_program.hpp>
#include <bksge/render/d3d12/d3d12_primitive_topology_type.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12_command_list.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/dxgiformat.hpp>
#include <bksge/render/rasterizer_state.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12PipelineState::D3D12PipelineState(
	D3D12Device* device,
	D3D12HLSLProgram const& hlsl_program,
	RasterizerState const& rasterizer_state,
	Primitive primitive)
{
	D3D12RasterizerState   raster_state(rasterizer_state);
	D3D12BlendState        blend_state;
	D3D12DepthStencilState depth_stencil_state;

	::D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
	desc.InputLayout           = hlsl_program.GetInputLayout();
	desc.pRootSignature        = hlsl_program.GetRootSignature();
	desc.VS                    = hlsl_program.GetVertexShaderBytecode();
	desc.PS                    = hlsl_program.GetPixelShaderBytecode();
	desc.RasterizerState       = raster_state;
	desc.BlendState            = blend_state;
	desc.DepthStencilState     = depth_stencil_state;
	desc.SampleMask            = UINT_MAX;
	desc.PrimitiveTopologyType = ToD3D12PrimitiveTopologyType(primitive);
	desc.NumRenderTargets      = 1;
	desc.RTVFormats[0]         = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count      = 1;

	m_pipeline_state = device->CreateGraphicsPipelineState(desc);
}

BKSGE_INLINE
D3D12PipelineState::~D3D12PipelineState()
{
}

BKSGE_INLINE void
D3D12PipelineState::SetPipelineState(D3D12CommandList* command_list)
{
	command_list->SetPipelineState(m_pipeline_state.Get());
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_PIPELINE_STATE_INL_HPP
