/**
 *	@file	primitive_inl.hpp
 *
 *	@brief	Primitive クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_PRIMITIVE_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_PRIMITIVE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/primitive.hpp>
#include <bksge/render/primitive.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
GlPrimitive(bksge::Primitive primitive)
{
	static std::unordered_map<bksge::Primitive, ::GLenum> const m =
	{
		{ bksge::Primitive::kPoints,    GL_POINTS },
		{ bksge::Primitive::kLines,     GL_LINES },
		{ bksge::Primitive::kTriangles, GL_TRIANGLES },
	};

	return m.at(primitive);
}

}	// namespace detail

BKSGE_INLINE
Primitive::Primitive(bksge::Primitive primitive)
	: m_primitive(detail::GlPrimitive(primitive))
{}

BKSGE_INLINE
Primitive::operator ::GLenum() const
{
	return m_primitive;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_PRIMITIVE_INL_HPP
