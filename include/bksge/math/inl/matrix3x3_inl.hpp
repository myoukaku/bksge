/**
 *	@file	matrix3x3_inl.hpp
 *
 *	@brief	Matrix3x3 の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_INL_MATRIX3X3_INL_HPP
#define BKSGE_MATH_INL_MATRIX3X3_INL_HPP

#include <bksge/math/matrix3x3.hpp>
#include <bksge/math/vector.hpp>
#include <bksge/math/scale.hpp>
#include <bksge/config.hpp>
#include <cmath>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR Matrix<T, 3, 3>
make_matrix_from_quaternion(T xx, T xy, T xz, T xw, T yy, T yz, T yw, T zz, T zw) BKSGE_NOEXCEPT
{
	return
	{
		Vector<T, 3>{ 1 - yy - zz, xy + zw,     xz - yw },
		Vector<T, 3>{ xy - zw,     1 - xx - zz, yz + xw },
		Vector<T, 3>{ xz + yw,     yz - xw,     1 - xx - yy },
	};
}

}	// namespace detail

template <typename T>
template <typename U>
inline BKSGE_CONSTEXPR
Matrix<T, 3, 3>::Matrix(Quaternion<U> const& q) BKSGE_NOEXCEPT
	: BaseType(detail::make_matrix_from_quaternion(
		2 * q.x() * q.x(),
		2 * q.x() * q.y(),
		2 * q.x() * q.z(),
		2 * q.x() * q.w(),
		2 * q.y() * q.y(),
		2 * q.y() * q.z(),
		2 * q.y() * q.w(),
		2 * q.z() * q.z(),
		2 * q.z() * q.w()))
{}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::Zero() BKSGE_NOEXCEPT
-> Matrix
{
	return {};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::Identity() BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 3>{ 1, 0, 0 },
		Vector<T, 3>{ 0, 1, 0 },
		Vector<T, 3>{ 0, 0, 1 },
	};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::MakeTranslation(Vector<T, 2> const& trans) BKSGE_NOEXCEPT
-> Matrix
{
	return MakeTranslation(trans.x(), trans.y());
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::MakeTranslation(T x, T y) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 3>{ 1, 0, 0 },
		Vector<T, 3>{ 0, 1, 0 },
		Vector<T, 3>{ x, y, 1 },
	};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::MakeScale(Scale<T, 3> const& s) BKSGE_NOEXCEPT
-> Matrix
{
	return MakeScale(s.x(), s.y(), s.z());
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::MakeScale(T x, T y, T z) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 3>{ x, 0, 0 },
		Vector<T, 3>{ 0, y, 0 },
		Vector<T, 3>{ 0, 0, z },
	};
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::MakeRotationX(AngleType const& angle) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 3> { T(1),  T(0),       T(0) },
		Vector<T, 3> { T(0),  cos(angle), sin(angle) },
		Vector<T, 3> { T(0), -sin(angle), cos(angle) },
	};
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::MakeRotationY(AngleType const& angle) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 3> { cos(angle),  T(0), -sin(angle) },
		Vector<T, 3> { T(0),        T(1),  T(0) },
		Vector<T, 3> { sin(angle),  T(0),  cos(angle) },
	};
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::MakeRotationZ(AngleType const& angle) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 3> {  cos(angle),  sin(angle),  T(0) },
		Vector<T, 3> { -sin(angle),  cos(angle),  T(0) },
		Vector<T, 3> {  T(0),        T(0),        T(1) },
	};
}

template <typename T>
template <typename AngleType>
inline BKSGE_CXX14_CONSTEXPR auto
Matrix<T, 3, 3>::MakeRotation(Vector<T, 3> const& axis, AngleType const& angle) BKSGE_NOEXCEPT
-> Matrix
{
	auto const na = Normalized(axis);
	auto const nx = na.x();
	auto const ny = na.y();
	auto const nz = na.z();
	auto const s = sin(angle);
	auto const c = cos(angle);
	return
	{
		Vector<T, 3> { (nx*nx)*(1-c)+c,      (nx*ny)*(1-c)+(nz*s), (nx*nz)*(1-c)-(ny*s) },
		Vector<T, 3> { (ny*nx)*(1-c)-(nz*s), (ny*ny)*(1-c)+c,      (ny*nz)*(1-c)+(nx*s) },
		Vector<T, 3> { (nz*nx)*(1-c)+(ny*s), (nz*ny)*(1-c)-(nx*s), (nz*nz)*(1-c)+c      },
	};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 3, 3>::MakeShear(T x, T y, T z) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 3> { 1, y, z },
		Vector<T, 3> { x, 1, z },
		Vector<T, 3> { x, y, 1 },
	};
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
inline BKSGE_CXX14_CONSTEXPR Matrix3x3<T> const
Inversed(Matrix3x3<T> const& m) BKSGE_NOEXCEPT
{
	Matrix3x3<T> const tmp =
	{
		Vector<T, 3>
		{
			m[1][1] * m[2][2] - m[1][2] * m[2][1],
			m[2][1] * m[0][2] - m[2][2] * m[0][1],
			m[0][1] * m[1][2] - m[0][2] * m[1][1],
		},
		Vector<T, 3>
		{
			m[1][2] * m[2][0] - m[1][0] * m[2][2],
			m[2][2] * m[0][0] - m[2][0] * m[0][2],
			m[0][2] * m[1][0] - m[0][0] * m[1][2],
		},
		Vector<T, 3>
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

#endif // BKSGE_MATH_INL_MATRIX3X3_INL_HPP
