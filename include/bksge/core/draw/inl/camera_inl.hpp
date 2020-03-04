/**
 *	@file	camera_inl.hpp
 *
 *	@brief	Camera クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_CAMERA_INL_HPP
#define BKSGE_CORE_DRAW_INL_CAMERA_INL_HPP

#include <bksge/core/draw/camera.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/matrix4x4.hpp>

namespace bksge
{

namespace draw
{

BKSGE_INLINE
Camera::Camera(void)
{}

BKSGE_INLINE
Camera::~Camera()
{}

BKSGE_INLINE Matrix4x4f const&
Camera::GetProjectionMatrix(void) const
{
	//if (!m_cached_proj_matrix)
	{
		m_cached_proj_matrix = VCalcProjectionMatrix();
	}

	return *m_cached_proj_matrix;
}

BKSGE_INLINE Matrix4x4f const&
Camera::GetViewMatrix(void) const
{
	//if (!m_cached_view_matrix)
	{
		m_cached_view_matrix = VCalcViewMatrix();
	}

	return *m_cached_view_matrix;
}

BKSGE_INLINE Vector3f
Camera::GetForwardVector(void) const
{
	return Vector3f(0, 0, -1) * GetDerivedRotation();
}

BKSGE_INLINE Vector3f
Camera::GetUpVector(void) const
{
	return Vector3f(0, 1, 0) * GetDerivedRotation();
}

BKSGE_INLINE Matrix4x4f
Camera::VCalcProjectionMatrix(void) const
{
	return Matrix4x4f::Identity();
}

BKSGE_INLINE Matrix4x4f
Camera::VCalcViewMatrix(void) const
{
	return Matrix4x4f::MakeView(
		GetDerivedPosition(), GetForwardVector(), GetUpVector());
}

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_CAMERA_INL_HPP
