/**
 *	@file	gl_primitive_inl.hpp
 *
 *	@brief	ToGlPrimitive の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_PRIMITIVE_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_PRIMITIVE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_primitive.hpp>
#include <bksge/render/primitive.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GLenum ToGlPrimitive(Primitive primitive)
{
	static std::unordered_map<Primitive, GLenum> const m =
	{
		{ Primitive::kPoints,    GL_POINTS },
		{ Primitive::kLines,     GL_LINES },
		{ Primitive::kTriangles, GL_TRIANGLES },
	};

	return m.at(primitive);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_PRIMITIVE_INL_HPP
