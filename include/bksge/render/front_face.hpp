/**
 *	@file	front_face.hpp
 *
 *	@brief	FrontFace の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_FRONT_FACE_HPP
#define BKSGE_RENDER_FRONT_FACE_HPP

#include <bksge/render/fwd/front_face_fwd.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンの表面
 */
enum class FrontFace : std::uint32_t
{
	kClockwise,
	kCounterClockwise,
};

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_FRONT_FACE_HPP
