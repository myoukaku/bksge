/**
 *	@file	sampler_inl.hpp
 *
 *	@brief	Sampler の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_SAMPLER_INL_HPP
#define BKSGE_CORE_RENDER_INL_SAMPLER_INL_HPP

#include <bksge/core/render/sampler.hpp>
#include <bksge/fnd/limits.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Sampler::Sampler(void)
	: m_min_filter(FilterMode::kNearest)
	, m_mag_filter(FilterMode::kNearest)
	, m_mip_filter(MipmapMode::kDisable)
	, m_address_mode_u(AddressMode::kRepeat)
	, m_address_mode_v(AddressMode::kRepeat)
	, m_address_mode_w(AddressMode::kRepeat)
	, m_border_color(BorderColor::kOpaqueBlack)
	, m_min_lod(bksge::numeric_limits<float>::lowest())
	, m_max_lod(bksge::numeric_limits<float>::max())
{}

BKSGE_INLINE void
Sampler::SetMinFilter(FilterMode min_filter)
{
	m_min_filter = min_filter;
}

BKSGE_INLINE void
Sampler::SetMagFilter(FilterMode mag_filter)
{
	m_mag_filter = mag_filter;
}

BKSGE_INLINE void
Sampler::SetMipFilter(MipmapMode mip_filter)
{
	m_mip_filter = mip_filter;
}

BKSGE_INLINE void
Sampler::SetAddressModeU(AddressMode address_mode_u)
{
	m_address_mode_u = address_mode_u;
}

BKSGE_INLINE void
Sampler::SetAddressModeV(AddressMode address_mode_v)
{
	m_address_mode_v = address_mode_v;
}

BKSGE_INLINE void
Sampler::SetAddressModeW(AddressMode address_mode_w)
{
	m_address_mode_w = address_mode_w;
}

BKSGE_INLINE void
Sampler::SetBorderColor(BorderColor border_color)
{
	m_border_color = border_color;
}

BKSGE_INLINE void
Sampler::SetMinLod(float min_lod)
{
	m_min_lod = min_lod;
}

BKSGE_INLINE void
Sampler::SetMaxLod(float max_lod)
{
	m_max_lod = max_lod;
}

BKSGE_INLINE FilterMode
Sampler::min_filter(void) const
{
	return m_min_filter;
}

BKSGE_INLINE FilterMode
Sampler::mag_filter(void) const
{
	return m_mag_filter;
}

BKSGE_INLINE MipmapMode
Sampler::mip_filter(void) const
{
	return m_mip_filter;
}

BKSGE_INLINE AddressMode
Sampler::address_mode_u(void) const
{
	return m_address_mode_u;
}

BKSGE_INLINE AddressMode
Sampler::address_mode_v(void) const
{
	return m_address_mode_v;
}

BKSGE_INLINE AddressMode
Sampler::address_mode_w(void) const
{
	return m_address_mode_w;
}

BKSGE_INLINE BorderColor
Sampler::border_color(void) const
{
	return m_border_color;
}

BKSGE_INLINE float
Sampler::min_lod(void) const
{
	return m_min_lod;
}

BKSGE_INLINE float
Sampler::max_lod(void) const
{
	return m_max_lod;
}

BKSGE_INLINE bool
Sampler::enable_mipmap(void) const
{
	return mip_filter() != MipmapMode::kDisable;
}

BKSGE_INLINE bool
operator==(Sampler const& lhs, Sampler const& rhs)
{
	return
		lhs.min_filter()     == rhs.min_filter()     &&
		lhs.mag_filter()     == rhs.mag_filter()     &&
		lhs.mip_filter()     == rhs.mip_filter()     &&
		lhs.address_mode_u() == rhs.address_mode_u() &&
		lhs.address_mode_v() == rhs.address_mode_v() &&
		lhs.address_mode_w() == rhs.address_mode_w() &&
		lhs.border_color()   == rhs.border_color()   &&
		lhs.min_lod()        == rhs.min_lod()        &&
		lhs.max_lod()        == rhs.max_lod();
}

BKSGE_INLINE bool
operator!=(Sampler const& lhs, Sampler const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_SAMPLER_INL_HPP
