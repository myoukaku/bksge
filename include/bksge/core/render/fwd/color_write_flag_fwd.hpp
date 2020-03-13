/**
 *	@file	color_write_flag_fwd.hpp
 *
 *	@brief	ColorWriteFlag の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_COLOR_WRITE_FLAG_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_COLOR_WRITE_FLAG_FWD_HPP

#include <cstdint>

namespace bksge
{

namespace render
{

enum class ColorWriteFlag : std::uint32_t;

}	// namespace render

using render::ColorWriteFlag;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_COLOR_WRITE_FLAG_FWD_HPP
