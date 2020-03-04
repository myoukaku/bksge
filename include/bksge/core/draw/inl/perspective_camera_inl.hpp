/**
 *	@file	perspective_camera_inl.hpp
 *
 *	@brief	PerspectiveCamera クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_PERSPECTIVE_CAMERA_INL_HPP
#define BKSGE_CORE_DRAW_INL_PERSPECTIVE_CAMERA_INL_HPP

#include <bksge/core/draw/perspective_camera.hpp>
#include <bksge/core/math/matrix4x4.hpp>

namespace bksge
{

namespace draw
{

BKSGE_INLINE
PerspectiveCamera::PerspectiveCamera(void)
	: m_fovy()
	, m_aspect()
	, m_near_z()
	, m_far_z()
{}

BKSGE_INLINE
PerspectiveCamera::PerspectiveCamera(
	AngleType const& fovy, float aspect, float near_z, float far_z)
	: m_fovy(fovy)
	, m_aspect(aspect)
	, m_near_z(near_z)
	, m_far_z(far_z)
{
}

BKSGE_INLINE
PerspectiveCamera::~PerspectiveCamera()
{}

BKSGE_INLINE Matrix4x4f
PerspectiveCamera::VCalcProjectionMatrix(void) const
{
	return Matrix4x4f::MakePerspective(
		m_fovy, m_aspect, m_near_z, m_far_z);
}

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_PERSPECTIVE_CAMERA_INL_HPP
