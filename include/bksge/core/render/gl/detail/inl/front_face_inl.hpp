/**
 *	@file	front_face_inl.hpp
 *
 *	@brief	FrontFace クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_FRONT_FACE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_FRONT_FACE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/front_face.hpp>
#include <bksge/core/render/front_face.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlFrontFace(bksge::FrontFace front_face)
{
	switch (front_face)
	{
	case bksge::FrontFace::kClockwise:        return GL_CW;
	case bksge::FrontFace::kCounterClockwise: return GL_CCW;
	}
	return GL_CW;
}

}	// namespace detail

BKSGE_INLINE
FrontFace::FrontFace(bksge::FrontFace front_face)
	: m_front_face(detail::ToGlFrontFace(front_face))
{}

BKSGE_INLINE
FrontFace::operator ::GLenum() const
{
	return m_front_face;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_FRONT_FACE_INL_HPP
