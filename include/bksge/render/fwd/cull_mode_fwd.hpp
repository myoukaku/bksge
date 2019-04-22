/**
 *	@file	cull_mode_fwd.hpp
 *
 *	@brief	CullMode の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_FWD_CULL_MODE_FWD_HPP
#define BKSGE_RENDER_FWD_CULL_MODE_FWD_HPP

#include <cstdint>

namespace bksge
{

namespace render
{

enum class CullMode : std::uint32_t;

}	// namespace render

using render::CullMode;

}	// namespace bksge

#endif // BKSGE_RENDER_FWD_CULL_MODE_FWD_HPP
