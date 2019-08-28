/**
 *	@file	sampler_inl.hpp
 *
 *	@brief	Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_SAMPLER_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_SAMPLER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/sampler.hpp>
#include <bksge/render/gl/detail/filter_mode.hpp>
#include <bksge/render/gl/detail/wrap_mode.hpp>
#include <bksge/render/gl/detail/texture.hpp>
#include <bksge/render/gl/gl_renderer.hpp>
#include <bksge/render/sampler.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
Sampler::Sampler(GlRenderer* renderer, bksge::Sampler const& sampler)
	: m_source(renderer->GetGlTexture(sampler.source()))
	, m_min_filter(gl::FilterMode(sampler.min_filter()))
	, m_mag_filter(gl::FilterMode(sampler.mag_filter()))
	, m_wrap_s(gl::WrapMode(sampler.wrap_s()))
	, m_wrap_t(gl::WrapMode(sampler.wrap_t()))
	, m_wrap_r(gl::WrapMode(sampler.wrap_r()))
	, m_border_color(sampler.border_color())
{}

BKSGE_INLINE TextureShared const&
Sampler::source(void) const
{
	return m_source;
}

BKSGE_INLINE void
Sampler::Apply(void) const
{
	m_source->Bind();
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_min_filter);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_mag_filter);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, m_wrap_r);
	::glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, m_border_color.data());
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_SAMPLER_INL_HPP
