/**
 *	@file	hlsl_program_fwd.hpp
 *
 *	@brief	HlslProgram クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_HLSL_PROGRAM_FWD_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_HLSL_PROGRAM_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
{

class HlslProgram;

using HlslProgramMap = std::map<Identifier, std::shared_ptr<HlslProgram>>;

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_HLSL_PROGRAM_FWD_HPP
