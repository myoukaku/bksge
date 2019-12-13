/**
 *	@file	front_face_fwd.hpp
 *
 *	@brief	FrontFace の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_FRONT_FACE_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_FRONT_FACE_FWD_HPP

#include <cstdint>

namespace bksge
{

namespace render
{

enum class FrontFace : std::uint32_t;

}	// namespace render

using render::FrontFace;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_FRONT_FACE_FWD_HPP
