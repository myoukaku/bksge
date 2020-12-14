/**
 *	@file	quaternion.hpp
 *
 *	@brief	Quaternion の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_QUATERNION_HPP
#define BKSGE_CORE_MATH_QUATERNION_HPP

#include <bksge/core/math/fwd/quaternion_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/swizzle_operator.hpp>
#include <bksge/core/math/detail/quaternion_to_matrix3x3.hpp>
#include <bksge/core/math/detail/matrix3x3_to_quaternion.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/numeric/ranges/inner_product.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class Quaternion : public detail::VectorBase<T, 4>
{
private:
	using BaseType = detail::VectorBase<T, 4>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Quaternion() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値4つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Quaternion(T const& v1, T const& v2, T const& v3, T const& v4) BKSGE_NOEXCEPT
		: BaseType{v1, v2, v3, v4}
	{}

	/**
	 *	@brief	Vector3と値1つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Quaternion(Vector<T, 3> const& v1, T const& v2) BKSGE_NOEXCEPT
		: BaseType{v1[0], v1[1], v1[2], v2}
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
	Quaternion(Quaternion<U> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<T>(rhs[0]),
			static_cast<T>(rhs[1]),
			static_cast<T>(rhs[2]),
			static_cast<T>(rhs[3]),
		}
	{}

	/**
	 *	@brief	Matrix3x3 からのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	Quaternion(Matrix3x3<T> const& q) BKSGE_NOEXCEPT
		: BaseType(detail::matrix3x3_to_quaternion(q))
	{}

	/**
	 *	@brief	Matrix3x3 への変換
	 */
	explicit BKSGE_CXX14_CONSTEXPR
	operator Matrix3x3<T>() const BKSGE_NOEXCEPT
	{
		return detail::quaternion_to_matrix3x3(*this);
	}

	/**
	 *	@brief	クォータニオンの実部を取得します
	 *
	 *	@param	q	クォータニオン
	 *
	 *	@return	qの実部
	 */
	BKSGE_CONSTEXPR T
	real() const BKSGE_NOEXCEPT
	{
		return this->w();
	}

	/**
	 *	@brief	クォータニオンの虚部を取得します
	 *
	 *	@param	q	クォータニオン
	 *
	 *	@return	qの虚部
	 */
	BKSGE_CONSTEXPR Vector3<T>
	imag() const BKSGE_NOEXCEPT
	{
		return this->xyz();
	}

	/**
	 *	@brief	ゼロクォータニオンを作成します
	 */
	static BKSGE_CONSTEXPR Quaternion
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	/**
	 *	@brief	単位クォータニオンを作成します
	 */
	static BKSGE_CONSTEXPR Quaternion
	Identity() BKSGE_NOEXCEPT
	{
		return {0, 0, 0, 1};
	}

	/**
	 *	@brief	X軸で回転するクォータニオンを作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Quaternion
	MakeRotationX(AngleType const& angle) BKSGE_NOEXCEPT
	{
		return {T(sin(angle * 0.5)), 0, 0, T(cos(angle * 0.5))};
	}

	/**
	 *	@brief	Y軸で回転するクォータニオンを作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Quaternion
	MakeRotationY(AngleType const& angle) BKSGE_NOEXCEPT
	{
		return {0, T(sin(angle * 0.5)), 0, T(cos(angle * 0.5))};
	}

	/**
	 *	@brief	Z軸で回転するクォータニオンを作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Quaternion
	MakeRotationZ(AngleType const& angle) BKSGE_NOEXCEPT
	{
		return {0, 0, T(sin(angle * 0.5)), T(cos(angle * 0.5))};
	}

	/**
	 *	@brief	任意のベクトルを回転軸にして回転するクォータニオンを作成します。
	 *
	 *	@param	axis	回転軸(正規化していなくてもかまいません)
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Quaternion
	MakeRotation(Vector3<T> const& axis, AngleType const& angle) BKSGE_NOEXCEPT
	{
		return
		{
			Normalized(axis) * T(sin(angle * 0.5)),
			T(cos(angle * 0.5))
		};
	}

	/**
	 *	任意の方向を向くクォータニオンを取得します
	 *
	 *	@param	eye		視点位置
	 *	@param	lookat	注視点
	 *	@param	up		上方向(正規化していなくても可)
	 */
	static BKSGE_CXX14_CONSTEXPR Quaternion
	MakeLookAt(
		Vector3<T> const& eye,
		Vector3<T> const& lookat,
		Vector3<T> const& up) BKSGE_NOEXCEPT
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

	BKSGE_CORE_MATH_NAMED_ACCESS(x, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(y, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(z, 2);
	BKSGE_CORE_MATH_NAMED_ACCESS(w, 3);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((x)(y)(z)(w));
};

/**
 *	@brief	２つのクォータニオンの積を計算します
 *
 *	@param	lhs	クォータニオン
 *	@param	rhs	クォータニオン
 *
 *	@return	lhsとrhsの積
 */
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

/**
 *	@brief	Quaternion *= Quaternion
 */
template <typename T>
inline BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator*=(Quaternion<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	三次元ベクトルとクォータニオンの積を計算します
 *
 *	@param	lhs	三次元ベクトル
 *	@param	rhs	クォータニオン
 *
 *	@return	lhsとrhsの積
 */
template <typename T>
inline BKSGE_CONSTEXPR Vector3<T>
operator*(Vector3<T> const& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	return (rhs * Quaternion<T>(lhs, 0) * Conjugate(rhs)).imag();
}

/**
 *	@brief	Vector3 *= Quaternion
 */
template <typename T>
inline BKSGE_CXX14_CONSTEXPR Vector3<T>&
operator*=(Vector3<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	クォータニオンの共役を取得します
 *
 *	@param	q	クォータニオン
 *
 *	@return	qの共役
 */
template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
Conjugate(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return {-q.imag(), q.real()};
}

/**
 *	@brief	クォータニオンの逆数を取得します
 *
 *	@param	q	クォータニオン
 *
 *	@return	qの逆数
 */
template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
Inversed(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return
		SquaredLength(q) == 0 ?
		Quaternion<T>::Identity() :
		Conjugate(q) / SquaredLength(q);
}

/**
 *	@brief	内積
 */
template <typename T>
inline BKSGE_CONSTEXPR T
Dot(Quaternion<T> const& q1, Quaternion<T> const& q2)
{
	return bksge::ranges::inner_product(q1, q2, T{});
}

/**
 *	@brief	クォータニオンを正規化します
 *
 *	@param	q	クォータニオン
 *
 *	@return	qを正規化したクォータニオン
 */
template <typename T>
inline BKSGE_CONSTEXPR Quaternion<T>
Normalized(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return
		SquaredLength(q) == 0 ?
		Quaternion<T>::Identity() :
		q / Length(q);
}

/**
 *	@brief	クォータニオンの長さの２乗を取得.
 *
 *	@param	q	対象となるクォータニオン
 *	@return	qの長さの２乗
 */
template <typename T>
inline BKSGE_CONSTEXPR T
SquaredLength(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return Dot(q, q);
}

/**
 *	@brief	クォータニオンの長さを取得.
 *
 *	@param	q	対象となるクォータニオン
 *	@return	qの長さ
 */
template <typename T>
inline BKSGE_CONSTEXPR bksge::float_promote_t<T>
Length(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return bksge::sqrt(SquaredLength(q));
}

/**
 *	@brief	クォータニオンのノルムを取得します
 *
 *	@param	q	クォータニオン
 *
 *	@return	qのノルム
 */
template <typename T>
inline BKSGE_CONSTEXPR bksge::float_promote_t<T>
Norm(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return Length(q);
}

/**
 *	@brief	球面線形補間
 *
 *	@param	from	開始クォータニオン
 *	@param	to		終了クォータニオン
 *	@param	t		補間係数
 *
 *	@return	from と to を 係数t で球面線形補間したクォータニオン
 */
template <typename T>
inline BKSGE_CXX14_CONSTEXPR Quaternion<T>
Slerp(Quaternion<T> const& from, Quaternion<T> const& to, T t) BKSGE_NOEXCEPT
{
	if (t <= T(0.0))
	{
		return from;
	}

	if (t >= T(1.0))
	{
		return to;
	}

	auto const cos_half_theta = Dot(from, to);

	if (cos_half_theta >= T(1.0))
	{
		return Lerp(from, to, t);
	}

	auto const half_theta = std::acos(cos_half_theta);
	auto const inv_sin_half_theta = T(1.0) / bksge::sin(half_theta);
	auto const ratio_a = bksge::sin(half_theta * (T(1.0) - t)) * inv_sin_half_theta;
	auto const ratio_b = bksge::sin(half_theta * t) * inv_sin_half_theta;

	return (from * ratio_a) + (to * ratio_b);
}

}	// namespace math

}	// namespace bksge

#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>

namespace BKSGE_TUPLE_NAMESPACE
{

/**
 *	@brief	tuple_size
 */
template <typename T>
struct tuple_size<bksge::math::Quaternion<T>>
	: public tuple_size<bksge::math::detail::VectorBase<T, 4>>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T>
struct tuple_element<I, bksge::math::Quaternion<T>>
	: public tuple_element<I, bksge::math::detail::VectorBase<T, 4>>
{};

}	// namespace BKSGE_TUPLE_NAMESPACE

#include <functional>

namespace std
{

/**
 *	@brief	hash
 */
template <typename T>
struct hash<bksge::math::Quaternion<T>>
	: public hash<bksge::math::detail::VectorBase<T, 4>>
{};

}	// namespace std

#endif // BKSGE_CORE_MATH_QUATERNION_HPP
