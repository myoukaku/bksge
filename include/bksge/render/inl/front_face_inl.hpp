/**
 *	@file	front_face_inl.hpp
 *
 *	@brief	FrontFace の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_front_face_INL_HPP
#define BKSGE_RENDER_INL_front_face_INL_HPP

#include <bksge/render/front_face.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(FrontFace const& front_face)
{
#define BKSGE_RENDER_MAKE_FRONT_FACE_KVP(x)	{ x, #x }

	static std::unordered_map<FrontFace, std::string> const m =
	{
		BKSGE_RENDER_MAKE_FRONT_FACE_KVP(FrontFace::kClockwise),
		BKSGE_RENDER_MAKE_FRONT_FACE_KVP(FrontFace::kCounterClockwise),
	};

	return m.at(front_face);

#undef BKSGE_RENDER_MAKE_front_face_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_front_face_INL_HPP
