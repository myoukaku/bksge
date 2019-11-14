/**
 *	@file	sampler_fwd.hpp
 *
 *	@brief	Sampler の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_FWD_SAMPLER_FWD_HPP
#define BKSGE_RENDER_D3D11_DETAIL_FWD_SAMPLER_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d11
{

class Sampler;

using SamplerShared = std::shared_ptr<Sampler>;
using SamplerMap = std::map<Identifier, SamplerShared>;

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D11_DETAIL_FWD_SAMPLER_FWD_HPP
