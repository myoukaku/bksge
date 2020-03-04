/**
 *	@file	perspective_camera.hpp
 *
 *	@brief	PerspectiveCamera クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_PERSPECTIVE_CAMERA_HPP
#define BKSGE_CORE_DRAW_PERSPECTIVE_CAMERA_HPP

#include <bksge/core/draw/fwd/perspective_camera_fwd.hpp>
#include <bksge/core/draw/camera.hpp>
#include <bksge/fnd/units/radian.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief	
 */
class PerspectiveCamera : public Camera
{
public:
	using AngleType = units::radians<float>;

	PerspectiveCamera(void);

	PerspectiveCamera(
		AngleType const& fovy, float aspect, float near_z, float far_z);

	virtual ~PerspectiveCamera() override;

private:
	virtual Matrix4x4f VCalcProjectionMatrix(void) const override;

private:
	AngleType		m_fovy;
	float			m_aspect;
	float			m_near_z;
	float			m_far_z;
//	Frustum<float>	m_frustum;
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/perspective_camera_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_PERSPECTIVE_CAMERA_HPP
