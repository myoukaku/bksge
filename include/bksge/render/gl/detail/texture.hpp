/**
 *	@file	texture.hpp
 *
 *	@brief	Texture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_TEXTURE_HPP
#define BKSGE_RENDER_GL_DETAIL_TEXTURE_HPP

#include <bksge/render/gl/detail/fwd/texture_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/render/fwd/texture_fwd.hpp>
#include <bksge/render/texture_format.hpp>

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

	Texture(bksge::TextureFormat format, int width, int height, void const* data);

	~Texture();

	::GLuint name(void) const;

	void Bind(void) const;

private:
	::GLuint	m_name;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/texture_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_TEXTURE_HPP
