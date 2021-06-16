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
#include <bksge/core/math/matrix.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/scale3.hpp>
#include <bksge/core/math/quaternion.hpp>
#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/tan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class Matrix<T, 4, 4> : public Vector<Vector<T, 4>, 4>
{
private:
	using BaseType = Vector<Vector<T, 4>, 4>;
	using VectorType = Vector<T, 4>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Matrix() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	Matrix(T const& x) BKSGE_NOEXCEPT
		: BaseType{VectorType{x}}
	{}

	/**
	 *	@brief	Vector4 4つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Matrix(VectorType const& v1, VectorType const& v2, VectorType const& v3, VectorType const& v4) BKSGE_NOEXCEPT
		: BaseType{v1, v2, v3, v4}
	{}

	/**
	 *	@brief	変換コンストラクタ
	 */
	template <
		typename U,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, U>::value
		>
	>
	BKSGE_CONSTEXPR
	Matrix(Matrix<U, 4, 4> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<VectorType>(rhs[0]),
			static_cast<VectorType>(rhs[1]),
			static_cast<VectorType>(rhs[2]),
			static_cast<VectorType>(rhs[3]),
		}
	{}

	/**
	 *	@brief	ゼロ行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	/**
	 *	@brief	単位行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	Identity() BKSGE_NOEXCEPT
	{
		return
		{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1},
		};
	}

	/**
	 *	@brief	平行移動行列を作成します
	 *
	 *	@param	trans	平行移動
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeTranslation(Vector<T, 3> const& trans) BKSGE_NOEXCEPT
	{
		return MakeTranslation(trans.x(), trans.y(), trans.z());
	}

	/**
	 *	@brief	平行移動行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 *	@param	z
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeTranslation(T x, T y, T z) BKSGE_NOEXCEPT
	{
		return
		{
			{ 1, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 1, 0 },
			{ x, y, z, 1 },
		};
	}

	/**
	 *	@brief	スケーリング行列を作成します
	 *
	 *	@param	s	スケール
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeScale(Scale<T, 3> const& s) BKSGE_NOEXCEPT
	{
		return MakeScale(s.x(), s.y(), s.z());
	}

	/**
	 *	@brief	スケーリング行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 *	@param	z
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeScale(T x, T y, T z) BKSGE_NOEXCEPT
	{
		return
		{
			{ x, 0, 0, 0 },
			{ 0, y, 0, 0 },
			{ 0, 0, z, 0 },
			{ 0, 0, 0, 1 },
		};
	}

	/**
	 *	@brief	X軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeRotationX(AngleType const& angle) BKSGE_NOEXCEPT
	{
		return
		{
			{ 1,  0,              0,             0 },
			{ 0,  T( cos(angle)), T(sin(angle)), 0 },
			{ 0,  T(-sin(angle)), T(cos(angle)), 0 },
			{ 0,  0,              0,             1 },
		};
	}

	/**
	 *	@brief	Y軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeRotationY(AngleType const& angle) BKSGE_NOEXCEPT
	{
		return
		{
			{ T(cos(angle)), 0, T(-sin(angle)), 0 },
			{ 0,             1, 0,              0 },
			{ T(sin(angle)), 0, T( cos(angle)), 0 },
			{ 0,             0, 0,              1 },
		};
	}

	/**
	 *	@brief	Z軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeRotationZ(AngleType const& angle) BKSGE_NOEXCEPT
	{
		return
		{
			{  T( cos(angle)), T(sin(angle)),  0, 0 },
			{  T(-sin(angle)), T(cos(angle)),  0, 0 },
			{  0,              0,              1, 0 },
			{  0,              0,              0, 1 },
		};
	}

	/**
	 *	@brief	任意のベクトルを回転軸にして回転する行列を作成します。
	 *
	 *	@param	axis	回転軸(正規化していなくてもかまいません)
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CXX14_CONSTEXPR Matrix4x4<T>
	MakeRotation(Vector<T, 3> const& axis, AngleType const& angle) BKSGE_NOEXCEPT
	{
		auto const na = Normalized(axis);
		auto const nx = na.x();
		auto const ny = na.y();
		auto const nz = na.z();
		auto const s = sin(angle);
		auto const c = cos(angle);
		return
		{
			{ T((nx*nx)*(1-c)+c),      T((nx*ny)*(1-c)+(nz*s)), T((nx*nz)*(1-c)-(ny*s)), 0 },
			{ T((ny*nx)*(1-c)-(nz*s)), T((ny*ny)*(1-c)+c),      T((ny*nz)*(1-c)+(nx*s)), 0 },
			{ T((nz*nx)*(1-c)+(ny*s)), T((nz*ny)*(1-c)-(nx*s)), T((nz*nz)*(1-c)+c),      0 },
			{  0,                      0,                       0,                       1 },
		};
	}

	/**
	 *	@brief	せん断行列を作成します
	 *
	 *	@param	x	X方向のせん断係数
	 *	@param	y	Y方向のせん断係数
	 *	@param	z	Z方向のせん断係数
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeShear(T x, T y, T z) BKSGE_NOEXCEPT
	{
		return
		{
			{ 1, y, z, 0 },
			{ x, 1, z, 0 },
			{ x, y, 1, 0 },
			{ 0, 0, 0, 1 },
		};
	}

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
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeOrthographic(T left, T right, T bottom, T top, T near_z, T far_z) BKSGE_NOEXCEPT
	{
		return
		{
			{2/(right-left),           0,                        0,                    0},
			{0,                        2/(top-bottom),           0,                    0},
			{0,                        0,                        1/(far_z-near_z),     0},
			{(left+right)/(left-right),(top+bottom)/(bottom-top),near_z/(near_z-far_z),1},
		};
	}

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
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeFrustum(T left, T right, T bottom, T top, T near_z, T far_z) BKSGE_NOEXCEPT
	{
		return
		{
			{(2*near_z)/(right-left),  0,                        0,                            0},
			{0,                        (2*near_z)/(top-bottom),  0,                            0},
			{(left+right)/(left-right),(top+bottom)/(bottom-top),far_z/(far_z-near_z),         1},
			{0,                        0,                        (near_z*far_z)/(near_z-far_z),0},
		};
	}

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
	static BKSGE_CXX14_CONSTEXPR Matrix4x4<T>
	MakePerspective(AngleType const& fovy, T aspect, T near_z, T far_z) BKSGE_NOEXCEPT
	{
		auto const x = T(1) / tan(fovy * T(0.5));
		auto const a = aspect;
		auto const n = near_z;
		auto const f = far_z;

		return
		{
			{ x / a, 0,  0,                 0 },
			{ 0,     x,  0,                 0 },
			{ 0,     0,  f / (f - n),       1 },
			{ 0,     0, -(n * f) / (f - n), 0 },
		};
	}

	/**
	 *	@brief	視点と向きから左手座標系ビュー行列を作成します。
	 *
	 *	@param	eye			視点
	 *	@param	direction	視点の向き(正規化していなくても可)
	 *	@param	up			上方を定義するベクトル(正規化していなくても可)
	 */
	static BKSGE_CXX14_CONSTEXPR Matrix4x4<T>
	MakeView(
		Vector<T, 3> const& eye,
		Vector<T, 3> const& direction,
		Vector<T, 3> const& up) BKSGE_NOEXCEPT
	{
		auto const zaxis = Normalized(direction);
		auto const xaxis = Normalized(Cross(up, zaxis));
		auto const yaxis = Cross(zaxis, xaxis);

		return
		{
			{ xaxis.x(), yaxis.x(), zaxis.x(), 0 },
			{ xaxis.y(), yaxis.y(), zaxis.y(), 0 },
			{ xaxis.z(), yaxis.z(), zaxis.z(), 0 },
			{ -Dot(xaxis, eye), -Dot(yaxis, eye), -Dot(zaxis, eye), 1 },
		};
	}

	/**
	 *	@brief	視点と注視点から左手座標系ビュー行列を作成します。
	 *
	 *	@param	eye			視点
	 *	@param	target		注視点
	 *	@param	up			上方を定義するベクトル(正規化していなくても可)
	 */
	static BKSGE_CXX14_CONSTEXPR Matrix4x4<T>
	MakeLookAt(
		Vector<T, 3> const& eye,
		Vector<T, 3> const& target,
		Vector<T, 3> const& up) BKSGE_NOEXCEPT
	{
		return MakeView(eye, target - eye, up);
	}

	/**
	 *	@brief	ビューポート行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 *	@param	width
	 *	@param	height
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	MakeViewport(T x, T y, T width, T height) BKSGE_NOEXCEPT
	{
		return
		{
			{ (width / 2),     0,                0, 0 },
			{ 0,               -(height / 2),    0, 0 },
			{ 0,               0,                1, 0 },
			{ x + (width / 2), y + (height / 2), 0, 1 },
		};
	}

	/**
	 *	@brief	平行移動とスケールと回転行列から行列を作成します。
	 *
	 *	スケーリング行列、回転行列、平行移動行列を順番にかけたのと結果は同じですが、
	 *	一度に計算することで計算量を減らしています。
	 *
	 *	@param	translation		平行移動
	 *	@param	scale			スケール
	 *	@param	rotation		回転行列
	 *	@return
	 *		MakeScale(scale) *
	 *		matrix4x4(rotation) *
	 *		MakeTranslation(translation)
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	Compose(
		Vector<T, 3> const& translation,
		Scale<T, 3> const& scale,
		Matrix<T, 3, 3> const& rotation) BKSGE_NOEXCEPT
	{
		return
		{
			{ scale[0] * rotation[0], 0},
			{ scale[1] * rotation[1], 0},
			{ scale[2] * rotation[2], 0},
			{ translation, 1},
		};
	}

	/**
	 *	@brief	平行移動とスケールとクォータニオンから行列を作成します。
	 *
	 *	スケーリング行列、クォータニオン、平行移動行列を順番にかけたのと結果は同じですが、
	 *	一度に計算することで計算量を減らしています。
	 *
	 *	@param	translation		平行移動
	 *	@param	scale			スケール
	 *	@param	rotation		クォータニオン
	 *	@return
	 *		MakeScale(scale) *
	 *		matrix4x4(rotation) *
	 *		MakeTranslation(translation)
	 */
	static BKSGE_CONSTEXPR Matrix4x4<T>
	Compose(
		Vector<T, 3> const& translation,
		Scale<T, 3> const& scale,
		Quaternion<T> const& rotation) BKSGE_NOEXCEPT
	{
		return Compose(translation, scale, Matrix<T, 3, 3>(rotation));
	}

	/**
	 *	@brief	4x4行列から平行移動、スケール、回転行列を取り出します。
	 */
	static BKSGE_CONSTEXPR auto
	Decompose(Matrix<T, 4, 4> const& mat) BKSGE_NOEXCEPT
		-> bksge::tuple<Vector<T, 3>, Scale<T, 3>, Matrix<T, 3, 3>>
	{
		auto v0 = mat[0].xyz();
		auto v1 = mat[1].xyz();
		auto v2 = mat[2].xyz();
		auto trans = mat[3].xyz();
		Scale<T, 3> scale
		{
			Length(v0) * ((Determinant(mat) < 0) ? -1 : 1),
			Length(v1),
			Length(v2),
		};
		Matrix<T, 3, 3> rot
		{
			v0 / scale.x(),
			v1 / scale.y(),
			v2 / scale.z(),
		};
		return bksge::make_tuple(trans, scale, rot);
	}
};

/**
 *	@brief	逆行列を求めます
 */
template <typename T>
inline BKSGE_CXX14_CONSTEXPR Matrix4x4<T> const
Inversed(Matrix4x4<T> const& m) BKSGE_NOEXCEPT
{
	Matrix4x4<T> const tmp =
	{
		{
			m[1][1]*m[2][2]*m[3][3] +
		    m[1][2]*m[2][3]*m[3][1] +
			m[1][3]*m[2][1]*m[3][2] -
			m[1][1]*m[2][3]*m[3][2] -
			m[1][2]*m[2][1]*m[3][3] -
			m[1][3]*m[2][2]*m[3][1],
			m[0][1]*m[2][3]*m[3][2] +
			m[0][2]*m[2][1]*m[3][3] +
			m[0][3]*m[2][2]*m[3][1] -
			m[0][1]*m[2][2]*m[3][3] -
			m[0][2]*m[2][3]*m[3][1] -
			m[0][3]*m[2][1]*m[3][2],
			m[0][1]*m[1][2]*m[3][3] +
			m[0][2]*m[1][3]*m[3][1] +
			m[0][3]*m[1][1]*m[3][2] -
			m[0][1]*m[1][3]*m[3][2] -
			m[0][2]*m[1][1]*m[3][3] -
			m[0][3]*m[1][2]*m[3][1],
			m[0][1]*m[1][3]*m[2][2] +
			m[0][2]*m[1][1]*m[2][3] +
			m[0][3]*m[1][2]*m[2][1] -
			m[0][1]*m[1][2]*m[2][3] -
			m[0][2]*m[1][3]*m[2][1] -
			m[0][3]*m[1][1]*m[2][2],
		},
		{
			m[1][0]*m[2][3]*m[3][2] +
			m[1][2]*m[2][0]*m[3][3] +
			m[1][3]*m[2][2]*m[3][0] -
			m[1][0]*m[2][2]*m[3][3] -
			m[1][2]*m[2][3]*m[3][0] -
			m[1][3]*m[2][0]*m[3][2],
			m[0][0]*m[2][2]*m[3][3] +
			m[0][2]*m[2][3]*m[3][0] +
			m[0][3]*m[2][0]*m[3][2] -
			m[0][0]*m[2][3]*m[3][2] -
			m[0][2]*m[2][0]*m[3][3] -
			m[0][3]*m[2][2]*m[3][0],
			m[0][0]*m[1][3]*m[3][2] +
			m[0][2]*m[1][0]*m[3][3] +
			m[0][3]*m[1][2]*m[3][0] -
			m[0][0]*m[1][2]*m[3][3] -
			m[0][2]*m[1][3]*m[3][0] -
			m[0][3]*m[1][0]*m[3][2],
			m[0][0]*m[1][2]*m[2][3] +
			m[0][2]*m[1][3]*m[2][0] +
			m[0][3]*m[1][0]*m[2][2] -
			m[0][0]*m[1][3]*m[2][2] -
			m[0][2]*m[1][0]*m[2][3] -
			m[0][3]*m[1][2]*m[2][0],
		},
		{
			m[1][0]*m[2][1]*m[3][3] +
			m[1][1]*m[2][3]*m[3][0] +
			m[1][3]*m[2][0]*m[3][1] -
			m[1][0]*m[2][3]*m[3][1] -
			m[1][1]*m[2][0]*m[3][3] -
			m[1][3]*m[2][1]*m[3][0],
			m[0][0]*m[2][3]*m[3][1] +
			m[0][1]*m[2][0]*m[3][3] +
			m[0][3]*m[2][1]*m[3][0] -
			m[0][0]*m[2][1]*m[3][3] -
			m[0][1]*m[2][3]*m[3][0] -
			m[0][3]*m[2][0]*m[3][1],
			m[0][0]*m[1][1]*m[3][3] +
			m[0][1]*m[1][3]*m[3][0] +
			m[0][3]*m[1][0]*m[3][1] -
			m[0][0]*m[1][3]*m[3][1] -
			m[0][1]*m[1][0]*m[3][3] -
			m[0][3]*m[1][1]*m[3][0],
			m[0][0]*m[1][3]*m[2][1] +
			m[0][1]*m[1][0]*m[2][3] +
			m[0][3]*m[1][1]*m[2][0] -
			m[0][0]*m[1][1]*m[2][3] -
			m[0][1]*m[1][3]*m[2][0] -
			m[0][3]*m[1][0]*m[2][1],
		},
		{
			m[1][0]*m[2][2]*m[3][1] +
			m[1][1]*m[2][0]*m[3][2] +
			m[1][2]*m[2][1]*m[3][0] -
			m[1][0]*m[2][1]*m[3][2] -
			m[1][1]*m[2][2]*m[3][0] -
			m[1][2]*m[2][0]*m[3][1],
			m[0][0]*m[2][1]*m[3][2] +
			m[0][1]*m[2][2]*m[3][0] +
			m[0][2]*m[2][0]*m[3][1] -
			m[0][0]*m[2][2]*m[3][1] -
			m[0][1]*m[2][0]*m[3][2] -
			m[0][2]*m[2][1]*m[3][0],
			m[0][0]*m[1][2]*m[3][1] +
			m[0][1]*m[1][0]*m[3][2] +
			m[0][2]*m[1][1]*m[3][0] -
			m[0][0]*m[1][1]*m[3][2] -
			m[0][1]*m[1][2]*m[3][0] -
			m[0][2]*m[1][0]*m[3][1],
			m[0][0]*m[1][1]*m[2][2] +
			m[0][1]*m[1][2]*m[2][0] +
			m[0][2]*m[1][0]*m[2][1] -
			m[0][0]*m[1][2]*m[2][1] -
			m[0][1]*m[1][0]*m[2][2] -
			m[0][2]*m[1][1]*m[2][0],
		},
	};

	auto const det =
		m[0][0] * tmp[0][0] +
		m[0][1] * tmp[1][0] +
		m[0][2] * tmp[2][0] +
		m[0][3] * tmp[3][0];

	return
		det == 0 ?
			Matrix4x4<T>::Identity() :
			tmp / static_cast<bksge::float_promote_t<T>>(det);
}

/**
 *	@brief	行列式を求めます
 */
template <typename T>
inline BKSGE_CONSTEXPR T
Determinant(Matrix4x4<T> const& m) BKSGE_NOEXCEPT
{
	return
		m[0][0] * (m[1][1]*m[2][2]*m[3][3] +
			       m[1][2]*m[2][3]*m[3][1] +
			       m[1][3]*m[2][1]*m[3][2] -
			       m[1][1]*m[2][3]*m[3][2] -
			       m[1][2]*m[2][1]*m[3][3] -
			       m[1][3]*m[2][2]*m[3][1]) +
		m[0][1] * (m[1][0]*m[2][3]*m[3][2] +
			       m[1][2]*m[2][0]*m[3][3] +
			       m[1][3]*m[2][2]*m[3][0] -
			       m[1][0]*m[2][2]*m[3][3] -
			       m[1][2]*m[2][3]*m[3][0] -
			       m[1][3]*m[2][0]*m[3][2]) +
		m[0][2] * (m[1][0]*m[2][1]*m[3][3] +
			       m[1][1]*m[2][3]*m[3][0] +
			       m[1][3]*m[2][0]*m[3][1] -
			       m[1][0]*m[2][3]*m[3][1] -
			       m[1][1]*m[2][0]*m[3][3] -
			       m[1][3]*m[2][1]*m[3][0]) +
		m[0][3] * (m[1][0]*m[2][2]*m[3][1] +
			       m[1][1]*m[2][0]*m[3][2] +
			       m[1][2]*m[2][1]*m[3][0] -
			       m[1][0]*m[2][1]*m[3][2] -
			       m[1][1]*m[2][2]*m[3][0] -
			       m[1][2]*m[2][0]*m[3][1]);
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_MATRIX4X4_HPP
