﻿/**
 *	@file	sampler_fwd.hpp
 *
 *	@brief	Sampler の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_FWD_SAMPLER_FWD_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_FWD_SAMPLER_FWD_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <memory>
#include <map>

namespace bksge
{

namespace render
{

namespace d3d11
{

class Sampler;

using SamplerShared = std::shared_ptr<Sampler>;
using SamplerMap = std::map<bksge::size_t, SamplerShared>;

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_FWD_SAMPLER_FWD_HPP
