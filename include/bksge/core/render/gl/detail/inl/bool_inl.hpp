/**
 *	@file	bool_inl.hpp
 *
 *	@brief	Bool クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_BOOL_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_BOOL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/bool.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
Bool::Bool(bool b)
	: m_bool(b ? GL_TRUE : GL_FALSE)
{}

BKSGE_INLINE
Bool::operator ::GLboolean() const
{
	return m_bool;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_BOOL_INL_HPP
