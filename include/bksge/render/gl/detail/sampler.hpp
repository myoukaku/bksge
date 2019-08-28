/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_SAMPLER_HPP
#define BKSGE_RENDER_GL_DETAIL_SAMPLER_HPP

#include <bksge/render/gl/detail/fwd/texture_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/render/gl/fwd/gl_renderer_fwd.hpp>
#include <bksge/render/fwd/sampler_fwd.hpp>
#include <bksge/math/color4.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	Sampler を OpenGL で使えるように変換したクラス
 */
class Sampler
{
public:
	Sampler(GlRenderer* renderer, bksge::Sampler const& sampler);

	TextureShared const& source(void) const;

	void Apply(void) const;

private:
	TextureShared	m_source;
	::GLint         m_min_filter;	///< 縮小フィルタの種類
	::GLint         m_mag_filter;	///< 拡大フィルタの種類
	::GLint         m_wrap_s;		///< テクスチャ座標sのラップモード
	::GLint         m_wrap_t;		///< テクスチャ座標tのラップモード
	::GLint         m_wrap_r;		///< テクスチャ座標rのラップモード
	bksge::Color4f  m_border_color; ///< 境界色
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/sampler_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_SAMPLER_HPP
