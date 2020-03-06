/**
 *	@file	matrix4x4.hpp
 *
 *	@brief	Matrix4x4 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_MATRIX4X4_HPP
#define BKSGE_CORE_MATH_MATRIX4X4_HPP

#include <bksge/core/math/fwd/matrix4x4_fwd.hpp>
#include <bksge/core/math/fwd/scale_fwd.hpp>
#include <bksge/core/math/fwd/quaternion_fwd.hpp>
#include <bksge/core/math/matrix.hpp>
#include <bksge/core/math/vector.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class Matrix<T, 4, 4>
	: public Vector<Vector<T, 4>, 4>
{
private:
	using BaseType = Vector<Vector<T, 4>, 4>;

public:
	// 継承コンストラクタ
	using BaseType::BaseType;

	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Matrix() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	/**
	 *	@brief	ゼロ行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix
	Zero() BKSGE_NOEXCEPT;

	/**
	 *	@brief	単位行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix
	Identity() BKSGE_NOEXCEPT;

	/**
	 *	@brief	平行移動行列を作成します
	 *
	 *	@param	trans	平行移動
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeTranslation(Vector<T, 3> const& trans) BKSGE_NOEXCEPT;

	/**
	 *	@brief	平行移動行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 *	@param	z
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeTranslation(T x, T y, T z) BKSGE_NOEXCEPT;

	/**
	 *	@brief	スケーリング行列を作成します
	 *
	 *	@param	s	スケール
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeScale(Scale<T, 3> const& s) BKSGE_NOEXCEPT;

	/**
	 *	@brief	スケーリング行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 *	@param	z
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeScale(T x, T y, T z) BKSGE_NOEXCEPT;

	/**
	 *	@brief	X軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix
	MakeRotationX(AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	Y軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix
	MakeRotationY(AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	Z軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix
	MakeRotationZ(AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	任意のベクトルを回転軸にして回転する行列を作成します。
	 *
	 *	@param	axis	回転軸(正規化していなくてもかまいません)
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CXX14_CONSTEXPR Matrix
	MakeRotation(Vector<T, 3> const& axis, AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	せん断行列を作成します
	 *
	 *	@param	x	X方向のせん断係数
	 *	@param	y	Y方向のせん断係数
	 *	@param	z	Z方向のせん断係数
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeShear(T x, T y, T z) BKSGE_NOEXCEPT;

	/**
	 *	@brief	左手座標系正射影行列を計算します
	 *
	 *	@param	left	ビューボリュームの最小X値
	 *	@param	right	ビューボリュームの最大X値
	 *	@param	bottom	ビューボリュームの最小Y値
	 *	@param	top		ビューボリュームの最大Y値
	 *	@param	near_z	ビューボリュームの最小Z値
	 *	@param	far_z	ビューボリュームの最大Z値
	 *
	 *	Clip座標系のZが0～wと想定しています。
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeOrthographic(T left, T right, T bottom, T top, T near_z, T far_z) BKSGE_NOEXCEPT;

	/**
	 *	@brief	左手座標系透視射影行列を計算します
	 *
	 *	@param	left	ビューボリュームの最小X値
	 *	@param	right	ビューボリュームの最大X値
	 *	@param	bottom	ビューボリュームの最小Y値
	 *	@param	top		ビューボリュームの最大Y値
	 *	@param	near_z	ビューボリュームの最小Z値
	 *	@param	far_z	ビューボリュームの最大Z値
	 *
	 *	Clip座標系のZが0～wと想定しています。
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeFrustum(T left, T right, T bottom, T top, T near_z, T far_z) BKSGE_NOEXCEPT;

	/**
	 *	@brief	左手座標系透視射影行列を計算します
	 *
	 *	@param	fovy	Y軸方向の視野角
	 *	@param	aspect	アスペクト比。(ビュー空間の 横幅/高さ)
	 *	@param	near_z	視点に近いほうのビュー平面のZ値
	 *	@param	far_z	視点から遠いほうのビュー平面のZ値
	 *
	 *	Clip座標系のZが0～wと想定しています。
	 */
	template <typename AngleType>
	static BKSGE_CXX14_CONSTEXPR Matrix
	MakePerspective(AngleType const& fovy, T aspect, T near_z, T far_z) BKSGE_NOEXCEPT;

	/**
	 *	@brief	視点と向きから左手座標系ビュー行列を作成します。
	 *
	 *	@param	eye			視点
	 *	@param	direction	視点の向き(正規化していなくても可)
	 *	@param	up			上方を定義するベクトル(正規化していなくても可)
	 */
	static BKSGE_CXX14_CONSTEXPR Matrix
	MakeView(
		Vector<T, 3> const& eye,
		Vector<T, 3> const& direction,
		Vector<T, 3> const& up) BKSGE_NOEXCEPT;

	/**
	 *	@brief	視点と注視点から左手座標系ビュー行列を作成します。
	 *
	 *	@param	eye			視点
	 *	@param	target		注視点
	 *	@param	up			上方を定義するベクトル(正規化していなくても可)
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeLookAt(
		Vector<T, 3> const& eye,
		Vector<T, 3> const& target,
		Vector<T, 3> const& up) BKSGE_NOEXCEPT;

	/**
	 *	@brief	ビューポート行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 *	@param	width
	 *	@param	height
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeViewport(T x, T y, T width, T height) BKSGE_NOEXCEPT;

	/**
	 *	@brief	平行移動とスケールと回転行列から行列を作成します。
	 *
	 *	スケーリング行列、回転行列、平行移動行列を順番にかけたのと結果は同じですが、
	 *	一度に計算することで計算量を減らしています。
	 *
	 *	@param	translation		平行移動
	 *	@param	Scale			スケール
	 *	@param	rotation		回転行列
	 *	@return
	 *		MakeScale(Scale) *
	 *		matrix4x4(rotation) *
	 *		MakeTranslation(translation)
	 */
	static BKSGE_CONSTEXPR Matrix
	Compose(
		Vector<T, 3> const& translation,
		Scale<T, 3> const& Scale,
		Matrix<T, 3, 3> const& rotation) BKSGE_NOEXCEPT;

	/**
	 *	@brief	平行移動とスケールとクォータニオンから行列を作成します。
	 *
	 *	スケーリング行列、クォータニオン、平行移動行列を順番にかけたのと結果は同じですが、
	 *	一度に計算することで計算量を減らしています。
	 *
	 *	@param	translation		平行移動
	 *	@param	Scale			スケール
	 *	@param	rotation		クォータニオン
	 *	@return
	 *		MakeScale(Scale) *
	 *		matrix4x4(rotation) *
	 *		MakeTranslation(translation)
	 */
	static BKSGE_CONSTEXPR Matrix
	Compose(
		Vector<T, 3> const& translation,
		Scale<T, 3> const& Scale,
		Quaternion<T> const& rotation) BKSGE_NOEXCEPT;

	/**
	 *	@brief	4x4行列から平行移動、スケール、回転行列を取り出します。
	 */
	static BKSGE_CONSTEXPR auto
	Decompose(Matrix<T, 4, 4> const& mat) BKSGE_NOEXCEPT
		-> bksge::tuple<Vector<T, 3>, Scale<T, 3>, Matrix<T, 3, 3>>;
};

}	// namespace math

}	// namespace bksge

#include <bksge/core/math/inl/matrix4x4_inl.hpp>

#endif // BKSGE_CORE_MATH_MATRIX4X4_HPP
