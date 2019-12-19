﻿/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INDEX_BUFFER_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INDEX_BUFFER_HPP

#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	OpenGL でのインデックスバッファ
 */
class IndexBuffer
{
public:
	explicit IndexBuffer(void const* src, std::size_t size);

	~IndexBuffer();

	void Bind(void) const;

	void Unbind(void) const;

	bool enable(void) const;

private:
	::GLuint	m_id;
	bool		m_enable;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/index_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INDEX_BUFFER_HPP