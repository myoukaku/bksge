/**
 *	@file	d3d12_pipeline_state_fwd.hpp
 *
 *	@brief	D3D12PipelineState クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_FWD_D3D12_PIPELINE_STATE_FWD_HPP
#define BKSGE_RENDER_D3D12_FWD_D3D12_PIPELINE_STATE_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class D3D12PipelineState;

using D3D12PipelineStateShared = std::shared_ptr<D3D12PipelineState>;
using D3D12PipelineStateMap = std::map<std::size_t, D3D12PipelineStateShared>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D12_FWD_D3D12_PIPELINE_STATE_FWD_HPP
