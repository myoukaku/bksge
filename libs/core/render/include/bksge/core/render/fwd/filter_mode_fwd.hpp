/**
 *	@file	filter_mode_fwd.hpp
 *
 *	@brief	FilterMode の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_FILTER_MODE_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_FILTER_MODE_FWD_HPP

#include <cstdint>

namespace bksge
{

namespace render
{

enum class FilterMode : std::uint32_t;

}	// namespace render

using render::FilterMode;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_FILTER_MODE_FWD_HPP
