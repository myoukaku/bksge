/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_FILL_MODE_HPP
#define BKSGE_RENDER_FILL_MODE_HPP

#include <bksge/render/fwd/fill_mode_fwd.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンの塗りつぶしモード
 */
enum class FillMode : std::uint32_t
{
	kSolid,
	kWireframe,
};

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_FILL_MODE_HPP
