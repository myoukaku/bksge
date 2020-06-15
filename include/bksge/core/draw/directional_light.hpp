/**
 *	@file	directional_light.hpp
 *
 *	@brief	DirectionalLight クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_DIRECTIONAL_LIGHT_HPP
#define BKSGE_CORE_DRAW_DIRECTIONAL_LIGHT_HPP

#include <bksge/core/draw/fwd/directional_light_fwd.hpp>
#include <bksge/core/draw/light.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief
 */
class DirectionalLight : public Light
{
public:
	/**
	 *	@brief
	 */
	DirectionalLight(void);

	/**
	 *	@brief
	 */
	virtual ~DirectionalLight() override;
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/directional_light_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_DIRECTIONAL_LIGHT_HPP
