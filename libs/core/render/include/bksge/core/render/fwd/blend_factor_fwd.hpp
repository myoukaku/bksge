/**
 *	@file	blend_factor_fwd.hpp
 *
 *	@brief	BlendFactor の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_BLEND_FACTOR_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_BLEND_FACTOR_FWD_HPP

#include <cstdint>

namespace bksge
{

namespace render
{

enum class BlendFactor : std::uint32_t;

}	// namespace render

using render::BlendFactor;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_BLEND_FACTOR_FWD_HPP
