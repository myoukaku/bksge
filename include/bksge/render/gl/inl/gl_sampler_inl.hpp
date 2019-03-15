/**
 *	@file	gl_sampler_inl.hpp
 *
 *	@brief	GlSampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_SAMPLER_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_SAMPLER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_sampler.hpp>
#include <bksge/render/gl/gl_renderer.hpp>
#include <bksge/render/gl/gl_filter_mode.hpp>
#include <bksge/render/gl/gl_wrap_mode.hpp>
#include <bksge/render/gl/gl_texture.hpp>
#include <bksge/render/sampler.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlSampler::GlSampler(GlRenderer* renderer, Sampler const& sampler)
	: m_source(renderer->GetGlTexture(sampler.source()))
	, m_min_filter(ToGlFilterMode(sampler.min_filter()))
	, m_mag_filter(ToGlFilterMode(sampler.mag_filter()))
	, m_wrap_s(ToGlWrapMode(sampler.wrap_s()))
	, m_wrap_t(ToGlWrapMode(sampler.wrap_t()))
	, m_wrap_r(ToGlWrapMode(sampler.wrap_r()))
	, m_border_color(sampler.border_color())
{}

BKSGE_INLINE
GlTextureShared const& GlSampler::source(void) const
{
	return m_source;
}

BKSGE_INLINE
void GlSampler::Apply(void) const
{
	m_source->Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, m_wrap_r);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, m_border_color.data());
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_SAMPLER_INL_HPP
