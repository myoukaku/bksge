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
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(FrontFace const& front_face)
{
#define BKSGE_CORE_RENDER_MAKE_FRONT_FACE_KVP(x)	{ x, #x }

	static std::unordered_map<FrontFace, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_FRONT_FACE_KVP(FrontFace::kClockwise),
		BKSGE_CORE_RENDER_MAKE_FRONT_FACE_KVP(FrontFace::kCounterClockwise),
	};

	return m.at(front_face);

#undef BKSGE_CORE_RENDER_MAKE_FRONT_FACE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_FRONT_FACE_INL_HPP
