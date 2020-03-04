/**
 *	@file	camera.hpp
 *
 *	@brief	Camera クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_CAMERA_HPP
#define BKSGE_CORE_DRAW_CAMERA_HPP

#include <bksge/core/draw/fwd/camera_fwd.hpp>
#include <bksge/core/draw/node.hpp>
#include <bksge/core/math/fwd/vector3_fwd.hpp>
#include <bksge/core/math/fwd/matrix4x4_fwd.hpp>
#include <bksge/fnd/optional.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief	カメラの基底となるクラス
 */
class Camera : public Node
{
public:
	Camera(void);

	virtual ~Camera() override;

	/**
	 *	@brief	射影行列を取得します
	 */
	Matrix4x4f const& GetProjectionMatrix(void) const;

	/**
	 *	@brief	ビュー行列を取得します
	 */
	Matrix4x4f const& GetViewMatrix(void) const;

	/**
	 *	@brief	カメラの前方向のベクトルを取得します
	 */
	Vector3f GetForwardVector(void) const;

	/**
	 *	@brief	カメラの上方向のベクトルを取得します
	 */
	Vector3f GetUpVector(void) const;

private:
	virtual Matrix4x4f VCalcProjectionMatrix(void) const;
	virtual Matrix4x4f VCalcViewMatrix(void) const;

	mutable bksge::optional<Matrix4x4f> m_cached_view_matrix;
	mutable bksge::optional<Matrix4x4f> m_cached_proj_matrix;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar & BKSGE_SERIALIZATION_BASE_OBJECT_NVP(Node);
	}
#endif
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/camera_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_CAMERA_HPP
