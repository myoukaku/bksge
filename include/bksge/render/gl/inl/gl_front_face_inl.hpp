/**
 *	@file	gl_front_face_inl.hpp
 *
 *	@brief	ToGlFrontFace の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_FRONT_FACE_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_FRONT_FACE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_front_face.hpp>
#include <bksge/render/front_face.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GLenum ToGlFrontFace(FrontFace mode)
{
	static std::unordered_map<FrontFace, GLenum> const m =
	{
		{ FrontFace::kClockwise,		GL_CW },
		{ FrontFace::kCounterClockwise,	GL_CCW },
	};

	return m.at(mode);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_FRONT_FACE_INL_HPP
