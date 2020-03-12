/**
 *	@file	hlsl_sampler_fwd.hpp
 *
 *	@brief	HlslSampler の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_FWD_HLSL_SAMPLER_FWD_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_FWD_HLSL_SAMPLER_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <memory>
#include <map>

namespace bksge
{

namespace render
{

namespace d3d11
{

class HlslSampler;

using HlslSamplerMap = std::map<Identifier, std::shared_ptr<HlslSampler>>;

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_FWD_HLSL_SAMPLER_FWD_HPP
