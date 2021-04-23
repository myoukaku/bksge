/**
 *	@file	render_buffer.hpp
 *
 *	@brief	RenderBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_RENDER_BUFFER_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_RENDER_BUFFER_HPP

#include <bksge/core/render/fwd/render_texture_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/texture_format.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

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
	explicit RenderBuffer(
		bksge::TextureFormat texture_format,
		bksge::uint32_t width,
		bksge::uint32_t height);

	explicit RenderBuffer(
		bksge::RenderTexture const& texture);

	~RenderBuffer();

	void Bind(void) const;

	void Unbind(void) const;

	::GLuint name(void) const;

private:
	// noncopyable
	RenderBuffer(RenderBuffer const&) = delete;
	RenderBuffer& operator=(RenderBuffer const&) = delete;

private:
	::GLuint m_id;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/render_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_RENDER_BUFFER_HPP
