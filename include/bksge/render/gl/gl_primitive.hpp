/**
 *	@file	gl_primitive.hpp
 *
 *	@brief	ToGlPrimitive の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_PRIMITIVE_HPP
#define BKSGE_RENDER_GL_GL_PRIMITIVE_HPP

#include <bksge/render/fwd/primitive_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	PrimitiveをOpenGLのenumに変換
 */
GLenum ToGlPrimitive(Primitive primitive);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_primitive_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_PRIMITIVE_HPP
