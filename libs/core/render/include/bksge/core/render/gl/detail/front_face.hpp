/**
 *	@file	front_face.hpp
 *
 *	@brief	FrontFace クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FRONT_FACE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FRONT_FACE_HPP

#include <bksge/core/render/fwd/front_face_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

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
	explicit FrontFace(bksge::FrontFace front_face);

	operator ::GLenum() const;

private:
	::GLenum const	m_front_face;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/front_face_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FRONT_FACE_HPP
