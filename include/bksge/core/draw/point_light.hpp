/**
 *	@file	point_light.hpp
 *
 *	@brief	PointLight クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_POINT_LIGHT_HPP
#define BKSGE_CORE_DRAW_POINT_LIGHT_HPP

#include <bksge/core/draw/fwd/point_light_fwd.hpp>
#include <bksge/core/draw/light.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief
 */
class PointLight : public Light
{
public:
	/**
	 *	@brief
	 */
	PointLight(void);

	/**
	 *	@brief
	 */
	virtual ~PointLight() override;

	/**
	 *	@brief
	 */
	void SetAttenuationRadius(float radius);
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/point_light_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_POINT_LIGHT_HPP
