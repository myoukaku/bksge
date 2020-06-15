/**
 *	@file	spot_light.hpp
 *
 *	@brief	SpotLight クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_SPOT_LIGHT_HPP
#define BKSGE_CORE_DRAW_SPOT_LIGHT_HPP

#include <bksge/core/draw/fwd/spot_light_fwd.hpp>
#include <bksge/core/draw/light.hpp>
#include <bksge/fnd/units/radian.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief
 */
class SpotLight : public Light
{
public:
	/**
	 *	@brief
	 */
	SpotLight(void);

	/**
	 *	@brief
	 */
	virtual ~SpotLight() override;

	/**
	 *	@brief
	 */
	void SetAttenuationRadius(float radius);

	/**
	 *	@brief
	 */
	void SetInnerConeAngle(units::radians<float> const& angle);

	/**
	 *	@brief
	 */
	void SetOuterConeAngle(units::radians<float> const& angle);
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/spot_light_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_SPOT_LIGHT_HPP
