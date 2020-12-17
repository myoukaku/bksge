/**
 *	@file	front_face_inl.hpp
 *
 *	@brief	FrontFace の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_FRONT_FACE_INL_HPP
#define BKSGE_CORE_RENDER_INL_FRONT_FACE_INL_HPP

#include <bksge/core/render/front_face.hpp>
#include <bksge/fnd/config.hpp>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(FrontFace const& front_face)
{
#define BKSGE_CORE_RENDER_FRONT_FACE_KVP(x)	case x: return #x

	switch (front_face)
	{
		BKSGE_CORE_RENDER_FRONT_FACE_KVP(FrontFace::kClockwise);
		BKSGE_CORE_RENDER_FRONT_FACE_KVP(FrontFace::kCounterClockwise);
	}

	return "";

#undef BKSGE_CORE_RENDER_FRONT_FACE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_FRONT_FACE_INL_HPP
