/**
 *	@file	sampler_inl.hpp
 *
 *	@brief	Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_SAMPLER_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_SAMPLER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/sampler.hpp>
#include <bksge/core/render/gl/detail/filter_mode.hpp>
#include <bksge/core/render/gl/detail/address_mode.hpp>
#include <bksge/core/render/gl/detail/border_color.hpp>
#include <bksge/core/render/filter_mode.hpp>
#include <bksge/core/render/address_mode.hpp>
#include <bksge/core/render/sampler.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
Sampler::Sampler(bksge::Sampler const& sampler)
{
	::glGenSamplers(1, &m_id);
	::glSamplerParameteri(m_id, GL_TEXTURE_MIN_FILTER, gl::FilterMode(sampler.min_filter()));
	::glSamplerParameteri(m_id, GL_TEXTURE_MAG_FILTER, gl::FilterMode(sampler.mag_filter()));
	::glSamplerParameteri(m_id, GL_TEXTURE_WRAP_S, gl::AddressMode(sampler.address_mode_u()));
	::glSamplerParameteri(m_id, GL_TEXTURE_WRAP_T, gl::AddressMode(sampler.address_mode_v()));
	::glSamplerParameteri(m_id, GL_TEXTURE_WRAP_R, gl::AddressMode(sampler.address_mode_w()));
	::glSamplerParameterfv(m_id, GL_TEXTURE_BORDER_COLOR, gl::BorderColor(sampler.border_color()));
}

BKSGE_INLINE
Sampler::~Sampler()
{
	::glDeleteSamplers(1, &m_id);
}

BKSGE_INLINE void
Sampler::Bind(GLint location) const
{
	::glBindSampler(location, m_id);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_SAMPLER_INL_HPP
