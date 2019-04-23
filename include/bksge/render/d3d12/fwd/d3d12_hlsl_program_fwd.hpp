/**
 *	@file	d3d12_hlsl_program_fwd.hpp
 *
 *	@brief	D3D12HLSLProgram クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_FWD_D3D12_HLSL_PROGRAM_FWD_HPP
#define BKSGE_RENDER_D3D12_FWD_D3D12_HLSL_PROGRAM_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class D3D12HLSLProgram;

using D3D12HLSLProgramMap = std::map<Identifier, std::shared_ptr<D3D12HLSLProgram>>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D12_FWD_D3D12_HLSL_PROGRAM_FWD_HPP
