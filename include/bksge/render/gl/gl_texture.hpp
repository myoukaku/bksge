/**
 *	@file	gl_texture.hpp
 *
 *	@brief	GlTexture の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_TEXTURE_HPP
#define BKSGE_RENDER_GL_GL_TEXTURE_HPP

#include <bksge/render/gl/fwd/gl_texture_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/fwd/texture_fwd.hpp>
#include <bksge/render/texture_format.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	TextureをOpenGLで使えるように変換したクラス
 */
class GlTexture
{
public:
	explicit GlTexture(Texture const& texture);

	GlTexture(TextureFormat format, int width, int height, void const* data);

	~GlTexture();

	GLuint name(void) const;

	void Bind(void) const;

private:
	GLuint	m_name;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_texture_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_TEXTURE_HPP
