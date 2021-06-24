/**
 *	@file	mipmap_mode_fwd.hpp
 *
 *	@brief	MipmapMode の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_MIPMAP_MODE_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_MIPMAP_MODE_FWD_HPP

#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

enum class MipmapMode : bksge::uint32_t;

}	// namespace render

using render::MipmapMode;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_MIPMAP_MODE_FWD_HPP
