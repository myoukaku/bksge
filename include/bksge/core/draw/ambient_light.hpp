/**
 *	@file	ambient_light.hpp
 *
 *	@brief	AmbientLight クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_AMBIENT_LIGHT_HPP
#define BKSGE_CORE_DRAW_AMBIENT_LIGHT_HPP

#include <bksge/core/draw/fwd/ambient_light_fwd.hpp>
#include <bksge/core/draw/light.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief
 */
class AmbientLight : public Light
{
public:
	/**
	 *	@brief
	 */
	AmbientLight(void);

	/**
	 *	@brief
	 */
	virtual ~AmbientLight() override;
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/ambient_light_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_AMBIENT_LIGHT_HPP
