/**
 *	@file	border_color_fwd.hpp
 *
 *	@brief	BorderColor の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_BORDER_COLOR_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_BORDER_COLOR_FWD_HPP

#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

enum class BorderColor : bksge::uint32_t;

}	// namespace render

using render::BorderColor;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_BORDER_COLOR_FWD_HPP
