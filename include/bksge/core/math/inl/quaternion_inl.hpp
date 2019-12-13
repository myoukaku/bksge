/**
 *	@file	quaternion_inl.hpp
 *
 *	@brief	Quaternion の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_INL_QUATERNION_INL_HPP
#define BKSGE_CORE_MATH_INL_QUATERNION_INL_HPP

#include <bksge/core/math/quaternion.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/config.hpp>
#include <algorithm>
#include <cmath>
#include <iterator>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T>
inline /*BKSGE_CONSTEXPR*/ Quaternion<T>
make_quaternion_from_matrix(Matrix3x3<T> const& m) BKSGE_NOEXCEPT
{
	// 最大成分を検索
	T const elem[] =
	{
		 m[0][0] - m[1][1] - m[2][2] + T(1),	// x
		-m[0][0] + m[1][1] - m[2][2] + T(1),	// y
		-m[0][0] - m[1][1] + m[2][2] + T(1),	// z
		 m[0][0] + m[1][1] + m[2][2] + T(1),	// w
	};

	auto const max_it = std::max_element(std::begin(elem), std::end(elem));

	if (*max_it < 0)
	{
		// 引数の行列に間違いあり！
		return Quaternion<T>::Identity();
	}

	// 最大要素の値を算出
	auto const v = std::sqrt(*max_it) * 0.5f;
	auto const mult = 0.25f / v;

	switch (std::distance(elem, max_it))
	{
	case 0: // x
		return Quaternion<T>
		{
			v,
			(m[0][1] + m[1][0]) * mult,
			(m[2][0] + m[0][2]) * mult,
			(m[1][2] - m[2][1]) * mult,
		};
	case 1: // y
		return Quaternion<T>
		{
			(m[0][1] + m[1][0]) * mult,
			v,
			(m[1][2] + m[2][1]) * mult,
			(m[2][0] - m[0][2]) * mult,
		};
	case 2: // z
		return Quaternion<T>
		{
			(m[2][0] + m[0][2]) * mult,
			(m[1][2] + m[2][1]) * mult,
			v,
			(m[0][1] - m[1][0]) * mult,
		};
	case 3: // w
		return Quaternion<T>
		{
			(m[1][2] - m[2][1]) * mult,
			(m[2][0] - m[0][2]) * mult,
			(m[0][1] - m[1][0]) * mult,
			v,
		};
	default:
		// ここには来るはずがない
		return Quaternion<T>::Identity();
	}
}

}	// namespace detail

template <typename T>
template <typename U, typename>
inline BKSGE_CONSTEXPR
Quaternion<T>::Quaternion(Quaternion<U> const& rhs)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: BaseType(rhs.as_array())
{}

template <typename T>
inline BKSGE_CONSTEXPR
Quaternion<T>::Quaternion(Vector3<T> const& imag, T const real)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: BaseType(imag.x(), imag.y(), imag.z(), real)
{}

template <typename T>
inline /*BKSGE_CONSTEXPR*/
Quaternion<T>::Quaternion(Matrix3x3<T> const& m) BKSGE_NOEXCEPT
	: Quaternion(detail::make_quaternion_from_matrix(m))
{}

template <typename T>
inline BKSGE_CONSTEXPR T
Quaternion<T>::real() const BKSGE_NOEXCEPT
{
	return this->w();
}

template <typename T>
inline BKSGE_CONSTEXPR Vector3<T>
Quaternion<T>::imag() const BKSGE_NOEXCEPT
{
	return this->xyz();
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Quaternion<T>::Zero() BKSGE_NOEXCEPT
-> Quaternion
{
	return Quaternion{};
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Quaternion<T>::Identity() BKSGE_NOEXCEPT
-> Quaternion
{
	return {0, 0, 0, 1};
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Quaternion<T>::MakeRotationX(AngleType const& angle) BKSGE_NOEXCEPT
-> Quaternion
{
	return {sin(angle * 0.5f), 0.0f, 0.0f, cos(angle * 0.5f)};
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Quaternion<T>::MakeRotationY(AngleType const& angle) BKSGE_NOEXCEPT
-> Quaternion
{
	return {0.0f, sin(angle * 0.5f), 0.0f, cos(angle * 0.5f)};
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Quaternion<T>::MakeRotationZ(AngleType const& angle) BKSGE_NOEXCEPT
-> Quaternion
{
	return {0.0f, 0.0f, sin(angle * 0.5f), cos(angle * 0.5f)};
}

template <typename T>
template <typename AngleType>
inline BKSGE_CONSTEXPR auto
Quaternion<T>::MakeRotation(Vector3<T> const& axis, AngleType const& angle)
	BKSGE_NOEXCEPT
-> Quaternion
{
	return
	{
		Normalized(axis) * sin(angle * 0.5f),
		static_cast<T>(cos(angle * 0.5f))
	};
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR auto
Quaternion<T>::MakeLookAt(
	Vector3<T> const& eye,
	Vector3<T> const& lookat,
	Vector3<T> const& up) BKSGE_NOEXCEPT
	-> Quaternion
{
	auto const zaxis = Normalized(eye - lookat);
	auto const xaxis = Normalized(Cross(up, zaxis));
	auto const yaxis = Cross(zaxis, xaxis);

	return Normalized(Quaternion
		{
			yaxis.z() - zaxis.y(),
			zaxis.x() - xaxis.z(),
			xaxis.y() - yaxis.x(),
			xaxis.x() + yaxis.y() + zaxis.z() + 1.0f
		});
}

template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
operator+(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return q;
}

template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
operator-(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return bksge::math::detail::negate_per_elem(q);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator+=(Quaternion<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs + rhs;
	return lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
operator+(Quaternion<T> const& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::add_per_elem(lhs, rhs);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator-=(Quaternion<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs - rhs;
	return lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
operator-(Quaternion<T> const& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::sub_per_elem(lhs, rhs);
}

template <typename T, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator*=(Quaternion<T>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Quaternion<T>
operator*(Quaternion<T> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::mul_per_elem(lhs, rhs);
}

template <typename T, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Quaternion<T>
operator*(ArithmeticType lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	return rhs * lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
operator*(Quaternion<T> const& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	return
	{
		(lhs.w() * rhs.x()) + (lhs.x() * rhs.w()) + (lhs.y() * rhs.z()) - (lhs.z() * rhs.y()),
		(lhs.w() * rhs.y()) - (lhs.x() * rhs.z()) + (lhs.y() * rhs.w()) + (lhs.z() * rhs.x()),
		(lhs.w() * rhs.z()) + (lhs.x() * rhs.y()) - (lhs.y() * rhs.x()) + (lhs.z() * rhs.w()),
		(lhs.w() * rhs.w()) - (lhs.x() * rhs.x()) - (lhs.y() * rhs.y()) - (lhs.z() * rhs.z()),
	};
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator*=(Quaternion<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR Vector3<T>
operator*(Vector3<T> const& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	return (rhs * Quaternion<T>(lhs, 0) * Conjugate(rhs)).imag();
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR Vector3<T>&
operator*=(Vector3<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator/=(Quaternion<T>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename T, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Quaternion<T>
operator/(Quaternion<T> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::div_per_elem(lhs, rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
Conjugate(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return {-q.imag(), q.real()};
}

template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
Inversed(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return
		SquaredLength(q) == 0 ?
		Quaternion<T>::Identity() :
		Conjugate(q) / SquaredLength(q);
}

template <typename T>
inline BKSGE_CONSTEXPR T
Dot(Quaternion<T> const& q1, Quaternion<T> const& q2)
{
	return bksge::math::detail::accumulate(
		bksge::math::detail::mul_per_elem(q1, q2));
}

template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
Normalized(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return
		SquaredLength(q) == 0 ?
		Quaternion<T>::Identity() :
		q / Length(q);
}

template <typename T>
inline BKSGE_CONSTEXPR T
SquaredLength(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return Dot(q, q);
}

template <typename T>
inline BKSGE_CONSTEXPR bksge::float_promote_t<T>
Length(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return std::sqrt(SquaredLength(q));
}

template <typename T>
inline BKSGE_CONSTEXPR bksge::float_promote_t<T>
Norm(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return Length(q);
}

template <typename T, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Quaternion<T>
Lerp(Quaternion<T> const& from, Quaternion<T> const& to, ArithmeticType const& t) BKSGE_NOEXCEPT
{
	return bksge::math::detail::lerp_per_elem(from, to, t);
}

template <typename T>
inline /*BKSGE_CONSTEXPR*/ Quaternion<T>
Slerp(Quaternion<T> const& from, Quaternion<T> const& to, T t) BKSGE_NOEXCEPT
{
	auto const one = T(1.0);

	if (t <= T(0.0))
	{
		return from;
	}

	if (t >= one)
	{
		return to;
	}

	auto const cos_half_theta = Dot(from, to);

	if (cos_half_theta >= one)
	{
		return Lerp(from, to, t);
	}

	auto const half_theta = std::acos(cos_half_theta);
	auto const inv_sin_half_theta = one / std::sin(half_theta);
	auto const ratio_a = std::sin(half_theta * (one - t)) * inv_sin_half_theta;
	auto const ratio_b = std::sin(half_theta * t) * inv_sin_half_theta;

	return (from * ratio_a) + (to * ratio_b);
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_INL_QUATERNION_INL_HPP
