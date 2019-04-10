/**
 *	@file	clear_flag_fwd.hpp
 *
 *	@brief	ClearFlag の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_FWD_CLEAR_FLAG_FWD_HPP
#define BKSGE_RENDER_FWD_CLEAR_FLAG_FWD_HPP

#include <cstdint>

namespace bksge
{

namespace render
{

enum class ClearFlag : std::uint32_t;

}	// namespace render

using render::ClearFlag;

}	// namespace bksge

#endif // BKSGE_RENDER_FWD_CLEAR_FLAG_FWD_HPP
