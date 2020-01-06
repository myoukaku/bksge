/**
 *	@file	primitive_inl.hpp
 *
 *	@brief	Primitive クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_PRIMITIVE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_PRIMITIVE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/primitive.hpp>
#include <bksge/core/render/primitive.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlPrimitive(bksge::Primitive primitive)
{
	switch (primitive)
	{
	case bksge::Primitive::kPoints:    return GL_POINTS;
	case bksge::Primitive::kLines:     return GL_LINES;
	case bksge::Primitive::kTriangles: return GL_TRIANGLES;
	}
	return GL_POINTS;
}

}	// namespace detail

BKSGE_INLINE
Primitive::Primitive(bksge::Primitive primitive)
	: m_primitive(detail::ToGlPrimitive(primitive))
{}

BKSGE_INLINE
Primitive::operator ::GLenum() const
{
	return m_primitive;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_PRIMITIVE_INL_HPP
