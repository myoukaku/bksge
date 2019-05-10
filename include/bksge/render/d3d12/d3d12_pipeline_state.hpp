/**
 *	@file	d3d12_pipeline_state.hpp
 *
 *	@brief	D3D12PipelineState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_PIPELINE_STATE_HPP
#define BKSGE_RENDER_D3D12_D3D12_PIPELINE_STATE_HPP

#include <bksge/render/d3d12/fwd/d3d12_pipeline_state_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_hlsl_program_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/fwd/primitive_fwd.hpp>

namespace bksge
{

namespace render
{

class D3D12PipelineState
{
public:
	D3D12PipelineState(
		D3D12Device* device,
		D3D12HLSLProgram const& hlsl_program,
		Primitive primitive);

	~D3D12PipelineState();

	void SetPipelineState(D3D12CommandList* command_list);

private:
	ComPtr<::ID3D12PipelineState> m_pipeline_state;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_pipeline_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_PIPELINE_STATE_HPP
