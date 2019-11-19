/**
 *	@file	pipeline_state.hpp
 *
 *	@brief	PipelineState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_PIPELINE_STATE_HPP
#define BKSGE_RENDER_D3D12_DETAIL_PIPELINE_STATE_HPP

#include <bksge/render/d3d12/detail/fwd/pipeline_state_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_program_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/fwd/rasterizer_state_fwd.hpp>
#include <bksge/render/fwd/primitive_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class PipelineState
{
public:
	PipelineState(
		Device* device,
		HlslProgram const& hlsl_program,
		bksge::RasterizerState const& rasterizer_state,
		bksge::Primitive primitive);

	~PipelineState();

	void SetPipelineState(CommandList* command_list);

private:
	ComPtr<::ID3D12PipelineState> m_pipeline_state;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/pipeline_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_PIPELINE_STATE_HPP
