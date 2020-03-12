/**
 *	@file	matrix4x4_inl.hpp
 *
 *	@brief	Matrix4x4 の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_INL_MATRIX4X4_INL_HPP
#define BKSGE_CORE_MATH_INL_MATRIX4X4_INL_HPP

#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/vector.hpp>
#include <bksge/core/math/scale.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/cmath/tan.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::Zero() BKSGE_NOEXCEPT
-> Matrix
{
	return {};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::Identity() BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 4>{ 1, 0, 0, 0 },
		Vector<T, 4>{ 0, 1, 0, 0 },
		Vector<T, 4>{ 0, 0, 1, 0 },
		Vector<T, 4>{ 0, 0, 0, 1 },
	};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeTranslation(Vector<T, 3> const& trans) BKSGE_NOEXCEPT
-> Matrix
{
	return MakeTranslation(trans.x(), trans.y(), trans.z());
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeTranslation(T x, T y, T z) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 4>{ 1, 0, 0, 0 },
		Vector<T, 4>{ 0, 1, 0, 0 },
		Vector<T, 4>{ 0, 0, 1, 0 },
		Vector<T, 4>{ x, y, z, 1 },
	};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeScale(Scale<T, 3> const& s) BKSGE_NOEXCEPT
-> Matrix
{
	return Resized<4, 4>(Matrix<T, 3, 3>::MakeScale(s));
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeScale(T x, T y, T z) BKSGE_NOEXCEPT
-> Matrix
{
	return Resized<4, 4>(Matrix<T, 3, 3>::MakeScale(x, y, z));
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeRotationX(AngleType const& angle) BKSGE_NOEXCEPT
-> Matrix
{
	return Resized<4, 4>(Matrix<T, 3, 3>::MakeRotationX(angle));
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeRotationY(AngleType const& angle) BKSGE_NOEXCEPT
-> Matrix
{
	return Resized<4, 4>(Matrix<T, 3, 3>::MakeRotationY(angle));
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeRotationZ(AngleType const& angle) BKSGE_NOEXCEPT
-> Matrix
{
	return Resized<4, 4>(Matrix<T, 3, 3>::MakeRotationZ(angle));
}

template <typename T>
template <typename AngleType>
inline BKSGE_CXX14_CONSTEXPR auto
Matrix<T, 4, 4>::MakeRotation(Vector<T, 3> const& axis, AngleType const& angle) BKSGE_NOEXCEPT
-> Matrix
{
	return Resized<4, 4>(Matrix<T, 3, 3>::MakeRotation(axis, angle));
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeShear(T x, T y, T z) BKSGE_NOEXCEPT
-> Matrix
{
	return Resized<4, 4>(Matrix<T, 3, 3>::MakeShear(x, y, z));
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeOrthographic(T l, T r, T b, T t, T n, T f) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 4> { 2 / (r - l),        0,                  0,           0 },
		Vector<T, 4> { 0,                  2 / (t - b),        0,           0 },
		Vector<T, 4> { 0,                  0,                  1 / (f - n), 0 },
		Vector<T, 4> { (l + r) / (l - r), (t + b) / (b - t),   n / (n - f), 1 },
	};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeFrustum(T l, T r, T b, T t, T n, T f) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 4> { (2 * n) / (r - l), 0,                 0,                 0 },
		Vector<T, 4> { 0,                 (2 * n) / (t - b), 0,                 0 },
		Vector<T, 4> { (l + r) / (l - r), (t + b) / (b - t), f / (f - n),       1 },
		Vector<T, 4> { 0,                 0,                 (n * f) / (n - f), 0 },
	};
}

template <typename T>
template <typename AngleType>
inline BKSGE_CXX14_CONSTEXPR auto
Matrix<T, 4, 4>::MakePerspective(AngleType const& fovy, T aspect, T near_z, T far_z) BKSGE_NOEXCEPT
-> Matrix
{
	auto const x = T(1) / tan(fovy * T(0.5));
	auto const a = aspect;
	auto const n = near_z;
	auto const f = far_z;

	return
	{
		Vector<T, 4>{ x / a, 0,  0,                 0 },
		Vector<T, 4>{ 0,     x,  0,                 0 },
		Vector<T, 4>{ 0,     0,  f / (f - n),       1 },
		Vector<T, 4>{ 0,     0, -(n * f) / (f - n), 0 },
	};
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR auto
Matrix<T, 4, 4>::MakeView(
	Vector<T, 3> const& eye,
	Vector<T, 3> const& direction,
	Vector<T, 3> const& up) BKSGE_NOEXCEPT
-> Matrix
{
	auto const zaxis = Normalized(direction);
	auto const xaxis = Normalized(Cross(up, zaxis));
	auto const yaxis = Cross(zaxis, xaxis);

	return Matrix<T, 4, 4>
	{
		Vector<T, 4>{ xaxis.x(), yaxis.x(), zaxis.x(), 0 },
		Vector<T, 4>{ xaxis.y(), yaxis.y(), zaxis.y(), 0 },
		Vector<T, 4>{ xaxis.z(), yaxis.z(), zaxis.z(), 0 },
		Vector<T, 4>{ -Dot(xaxis, eye), -Dot(yaxis, eye), -Dot(zaxis, eye), 1 },
	};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeLookAt(
	Vector<T, 3> const& eye,
	Vector<T, 3> const& target,
	Vector<T, 3> const& up) BKSGE_NOEXCEPT
-> Matrix
{
	return MakeView(eye, target - eye, up);
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::MakeViewport(T x, T y, T width, T height) BKSGE_NOEXCEPT
-> Matrix
{
	return
	{
		Vector<T, 4>{ (width / 2),     0,                0, 0 },
		Vector<T, 4>{ 0,               -(height / 2),    0, 0 },
		Vector<T, 4>{ 0,               0,                1, 0 },
		Vector<T, 4>{ x + (width / 2), y + (height / 2), 0, 1 },
	};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::Compose(
	Vector<T, 3> const& translation,
	Scale<T, 3> const& scale_value,
	Matrix<T, 3, 3> const& rotation) BKSGE_NOEXCEPT
-> Matrix
{
	return Resized<4, 4>(Matrix<T, 4, 3>
	{
		scale_value.x() * rotation[0],
		scale_value.y() * rotation[1],
		scale_value.z() * rotation[2],
		translation,
	});
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::Compose(
	Vector<T, 3> const& translation,
	Scale<T, 3> const& scale_value,
	Quaternion<T> const& rotation) BKSGE_NOEXCEPT
-> Matrix
{
	return Compose(translation, scale_value, Matrix<T, 3, 3>(rotation));
}

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR auto
decompose_impl_2(
	Vector<T, 3> const& m0,
	Vector<T, 3> const& m1,
	Vector<T, 3> const& m2,
	Vector<T, 3> const& t,
	Scale<T, 3> const& s) BKSGE_NOEXCEPT
-> bksge::tuple<Vector<T, 3>, Scale<T, 3>, Matrix<T, 3, 3>>
{
	return bksge::make_tuple(
		t,
		s,
		Matrix<T, 3, 3>
		{
			m0 / s.x(),
			m1 / s.y(),
			m2 / s.z(),
		}
	);
}

template <typename T>
inline BKSGE_CONSTEXPR auto
decompose_impl(
	T d,
	Vector<T, 3> const& m0,
	Vector<T, 3> const& m1,
	Vector<T, 3> const& m2,
	Vector<T, 3> const& m3) BKSGE_NOEXCEPT
-> bksge::tuple<Vector<T, 3>, Scale<T, 3>, Matrix<T, 3, 3>>
{
	return decompose_impl_2(
		m0,
		m1,
		m2,
		m3,
		Scale<T, 3> {
			Length(m0) * ((d < 0) ? -1 : 1),
			Length(m1),
			Length(m2),
		});
}

}	// namespace detail

template <typename T>
inline BKSGE_CONSTEXPR auto
Matrix<T, 4, 4>::Decompose(Matrix<T, 4, 4> const& mat) BKSGE_NOEXCEPT
-> bksge::tuple<Vector<T, 3>, Scale<T, 3>, Matrix<T, 3, 3>>
{
	return detail::decompose_impl(
		Determinant(mat),
		Vector<T, 3>{ mat[0].xyz() },
		Vector<T, 3>{ mat[1].xyz() },
		Vector<T, 3>{ mat[2].xyz() },
		Vector<T, 3>{ mat[3].xyz() });
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
inline BKSGE_CXX14_CONSTEXPR Matrix4x4<T> const
Inversed(Matrix4x4<T> const& m) BKSGE_NOEXCEPT
{
	Matrix4x4<T> const tmp =
	{
		Vector<T, 4>
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
		Vector<T, 4>
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
		Vector<T, 4>
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
		Vector<T, 4>
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

#endif // BKSGE_CORE_MATH_INL_MATRIX4X4_INL_HPP
