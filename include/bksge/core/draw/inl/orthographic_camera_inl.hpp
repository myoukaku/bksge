/**
 *	@file	orthographic_camera_inl.hpp
 *
 *	@brief	OrthographicCamera クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_ORTHOGRAPHIC_CAMERA_INL_HPP
#define BKSGE_CORE_DRAW_INL_ORTHOGRAPHIC_CAMERA_INL_HPP

#include <bksge/core/draw/orthographic_camera.hpp>
#include <bksge/core/math/matrix4x4.hpp>

namespace bksge
{

namespace draw
{

BKSGE_INLINE
OrthographicCamera::OrthographicCamera(void)
	: m_left()
	, m_right()
	, m_top()
	, m_bottom()
	, m_near_z()
	, m_far_z()
{}

BKSGE_INLINE
OrthographicCamera::~OrthographicCamera()
{}

BKSGE_INLINE Matrix4x4f
OrthographicCamera::VCalcProjectionMatrix(void) const
{
	return Matrix4x4f::MakeOrthographic(
		m_left, m_right, m_top, m_bottom, m_near_z, m_far_z);
}

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_ORTHOGRAPHIC_CAMERA_INL_HPP
