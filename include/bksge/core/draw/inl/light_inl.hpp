/**
 *	@file	light_inl.hpp
 *
 *	@brief	Light クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_LIGHT_INL_HPP
#define BKSGE_CORE_DRAW_INL_LIGHT_INL_HPP

#include <bksge/core/draw/light.hpp>

namespace bksge
{

namespace draw
{

BKSGE_INLINE
Light::Light(void)
	: m_color(1, 1, 1)
	, m_intensity(1)
{}

BKSGE_INLINE
Light::~Light()
{}

BKSGE_INLINE
void Light::SetColor(ColorType const& color)
{
	m_color = color;
}

BKSGE_INLINE
auto Light::GetColor(void) const -> ColorType const&
{
	return m_color;
}

BKSGE_INLINE
void Light::SetIntensity(float intensity)
{
	m_intensity = intensity;
}

BKSGE_INLINE
float Light::GetIntensity(void) const
{
	return m_intensity;
}

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_LIGHT_INL_HPP
