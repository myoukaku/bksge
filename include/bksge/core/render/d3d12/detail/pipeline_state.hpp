/**
 *	@file	pipeline_state.hpp
 *
 *	@brief	PipelineState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_PIPELINE_STATE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_PIPELINE_STATE_HPP

#include <bksge/core/render/d3d12/detail/fwd/pipeline_state_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/hlsl_program_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>
#include <bksge/core/render/fwd/primitive_topology_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class PipelineState
{
public:
	explicit PipelineState(
		Device* device,
		HlslProgram const& hlsl_program,
		bksge::RenderState const& render_state,
		bksge::PrimitiveTopology primitive_topology);

	~PipelineState();

	void SetPipelineState(CommandList* command_list);

private:
	ComPtr<::ID3D12PipelineState> m_pipeline_state;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/pipeline_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_PIPELINE_STATE_HPP
