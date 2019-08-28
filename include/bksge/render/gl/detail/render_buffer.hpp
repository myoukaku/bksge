/**
 *	@file	render_buffer.hpp
 *
 *	@brief	RenderBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_RENDER_BUFFER_HPP
#define BKSGE_RENDER_GL_DETAIL_RENDER_BUFFER_HPP

#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class RenderBuffer
{
public:
	RenderBuffer();

	~RenderBuffer();

	void Bind(void) const;

	void Unbind(void) const;

private:
	::GLuint m_id;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/render_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_RENDER_BUFFER_HPP
