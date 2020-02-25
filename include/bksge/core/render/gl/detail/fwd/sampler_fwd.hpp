﻿/**
 *	@file	sampler_fwd.hpp
 *
 *	@brief	Sampler クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_SAMPLER_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_SAMPLER_FWD_HPP

#include <map>
#include <memory>
#include <cstddef>

namespace bksge
{

namespace render
{

namespace gl
{

class Sampler;
using SamplerShared = std::shared_ptr<Sampler>;
using SamplerMap = std::map<std::size_t, SamplerShared>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_SAMPLER_FWD_HPP