/**
 *	@file	gl_type_enum.hpp
 *
 *	@brief	ToGlTypeEnum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_TYPE_ENUM_HPP
#define BKSGE_RENDER_GL_GL_TYPE_ENUM_HPP

#include <bksge/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	TypeEnumをOpenGLのenumに変換
 */
GLenum ToGlTypeEnum(TypeEnum type);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_type_enum_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_TYPE_ENUM_HPP
