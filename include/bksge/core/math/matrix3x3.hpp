/**
 *	@file	matrix3x3.hpp
 *
 *	@brief	Matrix3x3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_MATRIX3X3_HPP
#define BKSGE_CORE_MATH_MATRIX3X3_HPP

#include <bksge/core/math/fwd/matrix3x3_fwd.hpp>
#include <bksge/core/math/matrix.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/scale3.hpp>
#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class Matrix<T, 3, 3> : public Vector<Vector<T, 3>, 3>
{
private:
	using BaseType = Vector<Vector<T, 3>, 3>;
	using VectorType = Vector<T, 3>;

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
	 *	@brief	Vector3 3つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Matrix(VectorType const& v1, VectorType const& v2, VectorType const& v3) BKSGE_NOEXCEPT
		: BaseType{v1, v2, v3}
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
	Matrix(Matrix<U, 3, 3> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<VectorType>(rhs[0]),
			static_cast<VectorType>(rhs[1]),
			static_cast<VectorType>(rhs[2]),
		}
	{}

	/**
	 *	@brief	ゼロ行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix3x3<T>
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	/**
	 *	@brief	単位行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix3x3<T>
	Identity() BKSGE_NOEXCEPT
	{
		return
		{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1},
		};
	}

	/**
	 *	@brief	平行移動行列を作成します
	 *
	 *	@param	trans	平行移動
	 */
	static BKSGE_CONSTEXPR Matrix3x3<T>
	MakeTranslation(Vector<T, 2> const& trans) BKSGE_NOEXCEPT
	{
		return MakeTranslation(trans.x(), trans.y());
	}

	/**
	 *	@brief	平行移動行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 */
	static BKSGE_CONSTEXPR Matrix3x3<T>
	MakeTranslation(T x, T y) BKSGE_NOEXCEPT
	{
		return
		{
			{ 1, 0, 0 },
			{ 0, 1, 0 },
			{ x, y, 1 },
		};
	}

	/**
	 *	@brief	スケーリング行列を作成します
	 *
	 *	@param	s	スケール
	 */
	static BKSGE_CONSTEXPR Matrix3x3<T>
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
	static BKSGE_CONSTEXPR Matrix3x3<T>
	MakeScale(T x, T y, T z) BKSGE_NOEXCEPT
	{
		return
		{
			{ x, 0, 0 },
			{ 0, y, 0 },
			{ 0, 0, z },
		};
	}

	/**
	 *	@brief	X軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix3x3<T>
	MakeRotationX(AngleType const& angle) BKSGE_NOEXCEPT
	{
		return
		{
			{ 1,  0,              0             },
			{ 0,  T( cos(angle)), T(sin(angle)) },
			{ 0,  T(-sin(angle)), T(cos(angle)) },
		};
	}

	/**
	 *	@brief	Y軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix3x3<T>
	MakeRotationY(AngleType const& angle) BKSGE_NOEXCEPT
	{
		return
		{
			{ T(cos(angle)), 0, T(-sin(angle)) },
			{ 0,             1, 0              },
			{ T(sin(angle)), 0, T( cos(angle)) },
		};
	}

	/**
	 *	@brief	Z軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix3x3<T>
	MakeRotationZ(AngleType const& angle) BKSGE_NOEXCEPT
	{
		return
		{
			{  T( cos(angle)), T(sin(angle)),  0 },
			{  T(-sin(angle)), T(cos(angle)),  0 },
			{  0,              0,              1 },
		};
	}

	/**
	 *	@brief	任意のベクトルを回転軸にして回転する行列を作成します。
	 *
	 *	@param	axis	回転軸(正規化していなくてもかまいません)
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CXX14_CONSTEXPR Matrix3x3<T>
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
			{ T((nx*nx)*(1-c)+c),      T((nx*ny)*(1-c)+(nz*s)), T((nx*nz)*(1-c)-(ny*s)) },
			{ T((ny*nx)*(1-c)-(nz*s)), T((ny*ny)*(1-c)+c),      T((ny*nz)*(1-c)+(nx*s)) },
			{ T((nz*nx)*(1-c)+(ny*s)), T((nz*ny)*(1-c)-(nx*s)), T((nz*nz)*(1-c)+c)      },
		};
	}

	/**
	 *	@brief	せん断行列を作成します
	 *
	 *	@param	x	X方向のせん断係数
	 *	@param	y	Y方向のせん断係数
	 *	@param	z	Z方向のせん断係数
	 */
	static BKSGE_CONSTEXPR Matrix3x3<T>
	MakeShear(T x, T y, T z) BKSGE_NOEXCEPT
	{
		return
		{
			{ 1, y, z },
			{ x, 1, z },
			{ x, y, 1 },
		};
	}
};

/**
 *	@brief	逆行列を求めます
 */
template <typename T>
inline BKSGE_CXX14_CONSTEXPR Matrix3x3<T> const
Inversed(Matrix3x3<T> const& m) BKSGE_NOEXCEPT
{
	Matrix3x3<T> const tmp =
	{
		{
			m[1][1] * m[2][2] - m[1][2] * m[2][1],
			m[2][1] * m[0][2] - m[2][2] * m[0][1],
			m[0][1] * m[1][2] - m[0][2] * m[1][1],
		},
		{
			m[1][2] * m[2][0] - m[1][0] * m[2][2],
			m[2][2] * m[0][0] - m[2][0] * m[0][2],
			m[0][2] * m[1][0] - m[0][0] * m[1][2],
		},
		{
			m[1][0] * m[2][1] - m[1][1] * m[2][0],
			m[2][0] * m[0][1] - m[2][1] * m[0][0],
			m[0][0] * m[1][1] - m[0][1] * m[1][0],
		},
	};

	auto const det =
		m[0][0] * tmp[0][0] +
		m[0][1] * tmp[1][0] +
		m[0][2] * tmp[2][0];

	return
		det == 0 ?
			Matrix3x3<T>::Identity() :
			tmp / static_cast<bksge::float_promote_t<T>>(det);
}

/**
 *	@brief	行列式を求めます
 */
template <typename T>
inline BKSGE_CONSTEXPR T
Determinant(Matrix3x3<T> const& m) BKSGE_NOEXCEPT
{
	return
		m[0][0] * m[1][1] * m[2][2] +
		m[1][0] * m[2][1] * m[0][2] +
		m[2][0] * m[0][1] * m[1][2] -
		m[0][0] * m[2][1] * m[1][2] -
		m[2][0] * m[1][1] * m[0][2] -
		m[1][0] * m[0][1] * m[2][2];
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_MATRIX3X3_HPP
