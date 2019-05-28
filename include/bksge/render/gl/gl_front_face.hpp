/**
 *	@file	gl_front_face.hpp
 *
 *	@brief	ToGlFrontFace の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_FRONT_FACE_HPP
#define BKSGE_RENDER_GL_GL_FRONT_FACE_HPP

#include <bksge/render/fwd/front_face_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	FrontFaceをOpenGLのenumに変換
 */
GLenum ToGlFrontFace(FrontFace front_face);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_front_face_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_FRONT_FACE_HPP
