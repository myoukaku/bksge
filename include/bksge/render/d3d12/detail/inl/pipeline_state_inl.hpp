/**
 *	@file	pipeline_state_inl.hpp
 *
 *	@brief	PipelineState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_PIPELINE_STATE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_PIPELINE_STATE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/pipeline_state.hpp>
#include <bksge/render/d3d12/detail/rasterizer_state.hpp>
#include <bksge/render/d3d12/detail/blend_state.hpp>
#include <bksge/render/d3d12/detail/depth_stencil_state.hpp>
#include <bksge/render/d3d12/detail/hlsl_program.hpp>
#include <bksge/render/d3d12/detail/primitive_topology_type.hpp>
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/dxgiformat.hpp>
#include <bksge/render/rasterizer_state.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
PipelineState::PipelineState(
	Device* device,
	HlslProgram const& hlsl_program,
	bksge::RasterizerState const& rasterizer_state,
	bksge::Primitive primitive)
{
	RasterizerState   raster_state(rasterizer_state);
	BlendState        blend_state;
	DepthStencilState depth_stencil_state;

	::D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
	desc.InputLayout           = hlsl_program.GetInputLayout();
	desc.pRootSignature        = hlsl_program.GetRootSignature();
	desc.VS                    = hlsl_program.GetVertexShaderBytecode();
	desc.PS                    = hlsl_program.GetPixelShaderBytecode();
	desc.RasterizerState       = raster_state;
	desc.BlendState            = blend_state;
	desc.DepthStencilState     = depth_stencil_state;
	desc.SampleMask            = UINT_MAX;
	desc.PrimitiveTopologyType = PrimitiveTopologyType(primitive);
	desc.NumRenderTargets      = 1;
	desc.RTVFormats[0]         = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count      = 1;

	m_pipeline_state = device->CreateGraphicsPipelineState(desc);
}

BKSGE_INLINE
PipelineState::~PipelineState()
{
}

BKSGE_INLINE void
PipelineState::SetPipelineState(CommandList* command_list)
{
	command_list->SetPipelineState(m_pipeline_state.Get());
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_PIPELINE_STATE_INL_HPP
