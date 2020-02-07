/**
 *	@file	query_inl.hpp
 *
 *	@brief	Query クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_QUERY_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_QUERY_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/query.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
Query::Query()
{
	::glGenQueries(1, &m_id);
}

BKSGE_INLINE
Query::~Query()
{
	::glDeleteQueries(1, &m_id);
}

BKSGE_INLINE void
Query::QueryCounter(::GLenum target)
{
	::glQueryCounter(m_id, target);
}

BKSGE_INLINE void
Query::GetResult(::GLuint64* result)
{
	::glGetQueryObjectui64v(m_id, GL_QUERY_RESULT, result);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_QUERY_INL_HPP
