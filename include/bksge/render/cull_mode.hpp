/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_CULL_MODE_HPP
#define BKSGE_RENDER_CULL_MODE_HPP

#include <bksge/render/fwd/cull_mode_fwd.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンのカリングモード
 */
enum class CullMode : std::uint32_t
{
	kNone,
	kFront,
	kBack,
};

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_CULL_MODE_HPP
