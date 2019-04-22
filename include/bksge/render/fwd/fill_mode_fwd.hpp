/**
 *	@file	fill_mode_fwd.hpp
 *
 *	@brief	FillMode の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_FWD_FILL_MODE_FWD_HPP
#define BKSGE_RENDER_FWD_FILL_MODE_FWD_HPP

#include <cstdint>

namespace bksge
{

namespace render
{

enum class FillMode : std::uint32_t;

}	// namespace render

using render::FillMode;

}	// namespace bksge

#endif // BKSGE_RENDER_FWD_FILL_MODE_FWD_HPP
