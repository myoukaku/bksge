/**
 *	@file	color_write_flag_fwd.hpp
 *
 *	@brief	ColorWriteFlag の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_COLOR_WRITE_FLAG_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_COLOR_WRITE_FLAG_FWD_HPP

#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

enum class ColorWriteFlag : bksge::uint32_t;

}	// namespace render

using render::ColorWriteFlag;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_COLOR_WRITE_FLAG_FWD_HPP
