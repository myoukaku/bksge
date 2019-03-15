/**
 *	@file	sampler_inl.hpp
 *
 *	@brief	Sampler の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_SAMPLER_INL_HPP
#define BKSGE_RENDER_INL_SAMPLER_INL_HPP

#include <bksge/render/sampler.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Sampler::Sampler(void)
	: m_source()
	, m_min_filter(FilterMode::kNearest)
	, m_mag_filter(FilterMode::kNearest)
	, m_wrap_s(WrapMode::kRepeat)
	, m_wrap_t(WrapMode::kRepeat)
	, m_wrap_r(WrapMode::kRepeat)
	, m_border_color(0, 0, 0, 0)
{}

BKSGE_INLINE
Sampler::Sampler(Texture const& source)
	: Sampler()
{
	m_source = source;
}

BKSGE_INLINE
void Sampler::SetSource(Texture const& source)
{
	m_source = source;
}

BKSGE_INLINE
void Sampler::SetMinFilter(FilterMode min_filter)
{
	m_min_filter = min_filter;
}

BKSGE_INLINE
void Sampler::SetMagFilter(FilterMode mag_filter)
{
	m_mag_filter = mag_filter;
}

BKSGE_INLINE
void Sampler::SetWrapS(WrapMode wrap_s)
{
	m_wrap_s = wrap_s;
}

BKSGE_INLINE
void Sampler::SetWrapT(WrapMode wrap_t)
{
	m_wrap_t = wrap_t;
}

BKSGE_INLINE
void Sampler::SetWrapR(WrapMode wrap_r)
{
	m_wrap_r = wrap_r;
}

BKSGE_INLINE
void Sampler::SetBorderColor(Color4f const& border_color)
{
	m_border_color = border_color;
}

BKSGE_INLINE
Texture const& Sampler::source(void) const
{
	return m_source;
}

BKSGE_INLINE
FilterMode Sampler::min_filter(void) const
{
	return m_min_filter;
}

BKSGE_INLINE
FilterMode Sampler::mag_filter(void) const
{
	return m_mag_filter;
}

BKSGE_INLINE
WrapMode Sampler::wrap_s(void) const
{
	return m_wrap_s;
}

BKSGE_INLINE
WrapMode Sampler::wrap_t(void) const
{
	return m_wrap_t;
}

BKSGE_INLINE
WrapMode Sampler::wrap_r(void) const
{
	return m_wrap_r;
}

BKSGE_INLINE
Color4f const& Sampler::border_color(void) const
{
	return m_border_color;
}

BKSGE_INLINE
bool operator==(Sampler const& lhs, Sampler const& rhs)
{
	return
		lhs.source()       == rhs.source()     &&
		lhs.min_filter()   == rhs.min_filter() &&
		lhs.mag_filter()   == rhs.mag_filter() &&
		lhs.wrap_s()       == rhs.wrap_s()     &&
		lhs.wrap_t()       == rhs.wrap_t()     &&
		lhs.wrap_r()       == rhs.wrap_r()     &&
		lhs.border_color() == rhs.border_color();
}

BKSGE_INLINE
bool operator!=(Sampler const& lhs, Sampler const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_SAMPLER_INL_HPP
