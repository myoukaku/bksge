/**
 *	@file	query.hpp
 *
 *	@brief	Query クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_QUERY_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_QUERY_HPP

#include <bksge/core/render/gl/detail/fwd/query_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class Query
{
public:
	explicit Query();

	~Query();

	void QueryCounter(::GLenum target);

	void GetResult(::GLuint64* result);

private:
	// noncopyable
	Query(Query const&) = delete;
	Query& operator=(Query const&) = delete;

private:
	::GLuint	m_id;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/query_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_QUERY_HPP
