/**
 *	@file	orthographic_camera.hpp
 *
 *	@brief	OrthographicCamera クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_ORTHOGRAPHIC_CAMERA_HPP
#define BKSGE_CORE_DRAW_ORTHOGRAPHIC_CAMERA_HPP

#include <bksge/core/draw/fwd/orthographic_camera_fwd.hpp>
#include <bksge/core/draw/camera.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief	
 */
class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(void);

	virtual ~OrthographicCamera() override;

private:
	virtual Matrix4x4f VCalcProjectionMatrix(void) const override;

private:
	float			m_left;
	float			m_right;
	float			m_top;
	float			m_bottom;
	float			m_near_z;
	float			m_far_z;
//	Box<float>		m_box;
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/orthographic_camera_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_ORTHOGRAPHIC_CAMERA_HPP
