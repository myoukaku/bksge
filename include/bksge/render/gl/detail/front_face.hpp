/**
 *	@file	front_face.hpp
 *
 *	@brief	FrontFace クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_FRONT_FACE_HPP
#define BKSGE_RENDER_GL_DETAIL_FRONT_FACE_HPP

#include <bksge/render/fwd/front_face_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	FrontFace を OpenGL の enum に変換
 */
class FrontFace
{
public:
	FrontFace(bksge::FrontFace front_face);

	operator ::GLenum() const;

private:
	::GLenum	m_front_face;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/front_face_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_FRONT_FACE_HPP
