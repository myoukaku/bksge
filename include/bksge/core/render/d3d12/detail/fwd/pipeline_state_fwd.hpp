/**
 *	@file	pipeline_state_fwd.hpp
 *
 *	@brief	PipelineState クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_PIPELINE_STATE_FWD_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_PIPELINE_STATE_FWD_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
{

class PipelineState;

using PipelineStateShared = std::shared_ptr<PipelineState>;
using PipelineStateMap = std::map<bksge::size_t, PipelineStateShared>;

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_PIPELINE_STATE_FWD_HPP
