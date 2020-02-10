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
	: m_min_filter(gl::FilterMode(sampler.min_filter()))
	, m_mag_filter(gl::FilterMode(sampler.mag_filter()))
	, m_wrap_s(gl::AddressMode(sampler.address_mode_u()))
	, m_wrap_t(gl::AddressMode(sampler.address_mode_v()))
	, m_wrap_r(gl::AddressMode(sampler.address_mode_w()))
{
	auto const border_color = gl::BorderColor(sampler.border_color());
	m_border_color[0] = border_color[0];
	m_border_color[1] = border_color[1];
	m_border_color[2] = border_color[2];
	m_border_color[3] = border_color[3];
}

BKSGE_INLINE void
Sampler::Bind(GLint /*location*/) const
{
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_min_filter);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_mag_filter);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, m_wrap_r);
	::glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, m_border_color);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_SAMPLER_INL_HPP
