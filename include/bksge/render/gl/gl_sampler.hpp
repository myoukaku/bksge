/**
 *	@file	gl_sampler.hpp
 *
 *	@brief	GlSampler の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_SAMPLER_HPP
#define BKSGE_RENDER_GL_GL_SAMPLER_HPP

#include <bksge/render/gl/fwd/gl_texture_fwd.hpp>
#include <bksge/render/gl/fwd/gl_renderer_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/fwd/sampler_fwd.hpp>
#include <bksge/math/color4.hpp>
#include <memory>

namespace bksge
{

namespace render
{

/**
 *	@brief	SamplerをOpenGLで使えるように変換したクラス
 */
class GlSampler
{
public:
	GlSampler(GlRenderer* renderer, Sampler const& sampler);

	GlTextureShared const& source(void) const;

	void Apply(void) const;

private:
	GlTextureShared m_source;
	GLint           m_min_filter;	///< 縮小フィルタの種類
	GLint           m_mag_filter;	///< 拡大フィルタの種類
	GLint           m_wrap_s;		///< テクスチャ座標sのラップモード
	GLint           m_wrap_t;		///< テクスチャ座標tのラップモード
	GLint           m_wrap_r;		///< テクスチャ座標rのラップモード
	Color4f         m_border_color; ///< 境界色
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_sampler_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_SAMPLER_HPP
