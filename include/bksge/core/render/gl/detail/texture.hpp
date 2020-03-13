/**
 *	@file	texture.hpp
 *
 *	@brief	Texture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_TEXTURE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_TEXTURE_HPP

#include <bksge/core/render/gl/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/fwd/texture_fwd.hpp>
#include <bksge/core/render/texture_format.hpp>
#include <cstdint>
#include <cstddef>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	Texture を OpenGL で使えるように変換したクラス
 */
class Texture
{
public:
	explicit Texture(bksge::Texture const& texture);

	Texture(
		bksge::TextureFormat format,
		std::uint32_t width,
		std::uint32_t height,
		std::size_t mipmap_count,
		std::uint8_t const* data);

	~Texture();

	::GLuint name(void) const;

	void Bind(GLint location) const;

private:
	// noncopyable
	Texture(Texture const&) = delete;
	Texture& operator=(Texture const&) = delete;

private:
	::GLuint	m_name;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_TEXTURE_HPP
