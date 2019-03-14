/**
 *	@file	quaternion.hpp
 *
 *	@brief	Quaternion の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_QUATERNION_HPP
#define BKSGE_MATH_QUATERNION_HPP

#include <bksge/math/fwd/quaternion_fwd.hpp>
#include <bksge/math/fwd/vector3_fwd.hpp>
#include <bksge/math/fwd/matrix3x3_fwd.hpp>
#include <bksge/math/detail/vector_xyzw.hpp>
#include <bksge/config.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace bksge
{

namespace math
{

template <typename T>
class Quaternion
	: public detail::VectorXYZW<T, 4>
{
private:
	using BaseType = detail::VectorXYZW<T, 4>;

public:
	// 継承コンストラクタ
	using BaseType::BaseType;

	// デフォルトコンストラクタ
	BKSGE_CONSTEXPR
	Quaternion() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	// 虚部と実部を指定するコンストラクタ
	BKSGE_CONSTEXPR
	Quaternion(Vector3<T> const& imag, T const real) BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	Matrix3x3からのコンストラクタ
	 */
	explicit /*BKSGE_CONSTEXPR*/
	Quaternion(Matrix3x3<T> const& m) BKSGE_NOEXCEPT;

	/**
	 *	@brief	クォータニオンの実部を取得します
	 *
	 *	@param	q	クォータニオン
	 *
	 *	@return	qの実部
	 */
	BKSGE_CONSTEXPR T
	real() const BKSGE_NOEXCEPT;

	/**
	 *	@brief	クォータニオンの虚部を取得します
	 *
	 *	@param	q	クォータニオン
	 *
	 *	@return	qの虚部
	 */
	BKSGE_CONSTEXPR Vector3<T>
	imag() const BKSGE_NOEXCEPT;

	/**
	 *	@brief	ゼロクォータニオンを作成します
	 */
	static BKSGE_CONSTEXPR Quaternion
	Zero() BKSGE_NOEXCEPT;

	/**
	 *	@brief	単位クォータニオンを作成します
	 */
	static BKSGE_CONSTEXPR Quaternion
	Identity() BKSGE_NOEXCEPT;

	/**
	 *	@brief	X軸で回転するクォータニオンを作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Quaternion
	MakeRotationX(AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	Y軸で回転するクォータニオンを作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Quaternion
	MakeRotationY(AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	Z軸で回転するクォータニオンを作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Quaternion
	MakeRotationZ(AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	任意のベクトルを回転軸にして回転するクォータニオンを作成します。
	 *
	 *	@param	axis	回転軸(正規化していなくてもかまいません)
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Quaternion
	MakeRotation(Vector3<T> const& axis, AngleType const& angle) BKSGE_NOEXCEPT;

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
		Vector3<T> const& up) BKSGE_NOEXCEPT;
};

/**
 *	@brief	unary operator+
 */
template <typename T>
BKSGE_CONSTEXPR Quaternion<T>
operator+(Quaternion<T> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	unary operator-
 */
template <typename T>
BKSGE_CONSTEXPR Quaternion<T>
operator-(Quaternion<T> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	Quaternion += Quaternion
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator+=(Quaternion<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Quaternion + Quaternion -> Quaternion
 */
template <typename T>
BKSGE_CONSTEXPR Quaternion<T>
operator+(Quaternion<T> const& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Quaternion -= Quaternion
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator-=(Quaternion<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Quaternion - Quaternion -> Quaternion
 */
template <typename T>
BKSGE_CONSTEXPR Quaternion<T>
operator-(Quaternion<T> const& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Quaternion *= scalar
 */
template <
	typename T,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator*=(Quaternion<T>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Quaternion * scalar
 */
template <
	typename T,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Quaternion<T>
operator*(Quaternion<T> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Quaternion
 */
template <
	typename T,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Quaternion<T>
operator*(ArithmeticType lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	２つのクォータニオンの積を計算します
 *
 *	@param	lhs	クォータニオン
 *	@param	rhs	クォータニオン
 *
 *	@return	lhsとrhsの積
 */
template <typename T>
BKSGE_CONSTEXPR Quaternion<T>
operator*(Quaternion<T> const& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Quaternion *= Quaternion
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator*=(Quaternion<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	三次元ベクトルとクォータニオンの積を計算します
 *
 *	@param	lhs	三次元ベクトル
 *	@param	rhs	クォータニオン
 *
 *	@return	lhsとrhsの積
 */
template <typename T>
BKSGE_CONSTEXPR Vector3<T>
operator*(Vector3<T> const& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector3 *= Quaternion
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR Vector3<T>&
operator*=(Vector3<T>& lhs, Quaternion<T> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Quaternion /= scalar
 */
template <
	typename T,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Quaternion<T>&
operator/=(Quaternion<T>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Quaternion / scalar
 */
template <
	typename T,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Quaternion<T>
operator/(Quaternion<T> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	クォータニオンの共役を取得します
 *
 *	@param	q	クォータニオン
 *
 *	@return	qの共役
 */
template <typename T>
BKSGE_CONSTEXPR Quaternion<T>
Conjugate(Quaternion<T> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	クォータニオンの逆数を取得します
 *
 *	@param	q	クォータニオン
 *
 *	@return	qの逆数
 */
template <typename T>
BKSGE_CONSTEXPR Quaternion<T>
Inversed(Quaternion<T> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	内積
 */
template <typename T>
BKSGE_CONSTEXPR T
Dot(Quaternion<T> const& q1, Quaternion<T> const& q2);

/**
 *	@brief	クォータニオンを正規化します
 *
 *	@param	q	クォータニオン
 *
 *	@return	qを正規化したクォータニオン
 */
template <typename T>
BKSGE_CONSTEXPR Quaternion<T>
Normalized(Quaternion<T> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	クォータニオンの長さの２乗を取得.
 *
 *	@param	q	対象となるクォータニオン
 *	@return	qの長さの２乗
 */
template <typename T>
BKSGE_CONSTEXPR T
SquaredLength(Quaternion<T> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	クォータニオンの長さを取得.
 *
 *	@param	q	対象となるクォータニオン
 *	@return	qの長さ
 */
template <typename T>
BKSGE_CONSTEXPR bksge::float_promote_t<T>
Length(Quaternion<T> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	クォータニオンのノルムを取得します
 *
 *	@param	q	クォータニオン
 *
 *	@return	qのノルム
 */
template <typename T>
BKSGE_CONSTEXPR bksge::float_promote_t<T>
Norm(Quaternion<T> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	Lerp
 */
template <
	typename T,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Quaternion<T>
Lerp(Quaternion<T> const& from, Quaternion<T> const& to, ArithmeticType const& t) BKSGE_NOEXCEPT;

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
/*BKSGE_CONSTEXPR*/ Quaternion<T>
Slerp(Quaternion<T> const& from, Quaternion<T> const& to, T t) BKSGE_NOEXCEPT;

}	// namespace math

}	// namespace bksge

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T>
struct tuple_size<bksge::math::Quaternion<T>>
	: public std::integral_constant<std::size_t, 4>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T>
struct tuple_element<I, bksge::math::Quaternion<T>>
{
	static_assert(I < 4, "Quaternion index out of bounds");
	using type = T;
};

}	// namespace std

#include <bksge/math/inl/quaternion_inl.hpp>

#endif // BKSGE_MATH_QUATERNION_HPP
