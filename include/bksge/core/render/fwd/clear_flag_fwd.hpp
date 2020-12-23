/**
 *	@file	clear_flag_fwd.hpp
 *
 *	@brief	ClearFlag の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_CLEAR_FLAG_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_CLEAR_FLAG_FWD_HPP

#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

enum class ClearFlag : bksge::uint32_t;

}	// namespace render

using render::ClearFlag;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_CLEAR_FLAG_FWD_HPP
