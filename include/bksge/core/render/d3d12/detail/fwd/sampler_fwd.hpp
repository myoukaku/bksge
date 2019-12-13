/**
 *	@file	sampler_fwd.hpp
 *
 *	@brief	Sampler の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_SAMPLER_FWD_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_SAMPLER_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
{

class Sampler;

using SamplerShared = std::shared_ptr<Sampler>;
using SamplerMap = std::map<Identifier, SamplerShared>;

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_SAMPLER_FWD_HPP
