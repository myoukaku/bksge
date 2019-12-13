/**
 *	@file	vector.hpp
 *
 *	@brief	Vector の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_VECTOR_HPP
#define BKSGE_CORE_MATH_VECTOR_HPP

#include <bksge/core/math/fwd/vector_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/vector_xyzw.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
class Vector
	: public detail::VectorXYZW<T, N>
{
private:
	using BaseType = detail::VectorXYZW<T, N>;

public:
	// 継承コンストラクタ
	using BaseType::BaseType;

	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Vector() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	/**
	 *	@brief	変換コンストラクタ
	 */
	template <
		typename U,
		typename = bksge::enable_if_t<
			std::is_constructible<T, U>::value
		>
	>
	BKSGE_CONSTEXPR
	Vector(Vector<U, N> const& rhs)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	ゼロベクトルを作成します
	 */
	static BKSGE_CONSTEXPR Vector
	Zero() BKSGE_NOEXCEPT;
};

/**
 *	@brief	unary operator+
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Vector<T, N>
operator+(Vector<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	unary operator-
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Vector<T, N>
operator-(Vector<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector += Vector
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator+=(Vector<T, N>& lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector + Vector -> Vector
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Vector<T, N>
operator+(Vector<T, N> const& lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector -= Vector
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator-=(Vector<T, N>& lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector - Vector -> Vector
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Vector<T, N>
operator-(Vector<T, N> const& lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector *= scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector * scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Vector<T, N>
operator*(Vector<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Vector
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Vector<T, N>
operator*(ArithmeticType lhs, Vector<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector /= scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator/=(Vector<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector / scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Vector<T, N>
operator/(Vector<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	内積
 *
 *	@param	v1	ベクトルその１
 *	@param	v2	ベクトルその２
 *	@return	v1とv2の内積
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR T
Dot(Vector<T, N> const& v1, Vector<T, N> const& v2);

/**
 *	@brief	ベクトルの長さの２乗を取得.
 *
 *	@param	v	対象となるベクトル
 *	@return	vの長さの２乗
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR T
SquaredLength(Vector<T, N> const& v);

/**
 *	@brief	ベクトルの長さを取得.
 *
 *	@param	v	対象となるベクトル
 *	@return	vの長さ
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR bksge::float_promote_t<T>
Length(Vector<T, N> const& v);

/**
 *	@brief	ベクトルを正規化.
 *
 *	引数vは変更しません。
 *	vがゼロベクトルの時はゼロベクトルを返します。
 *
 *	@param	v	対象となるベクトル
 *	@return	vを正規化したベクトル
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Vector<T, N>
Normalized(Vector<T, N> const& v);

/**
 *	@brief	Lerp
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Vector<T, N>
Lerp(Vector<T, N> const& from, Vector<T, N> const& to, ArithmeticType const& t) BKSGE_NOEXCEPT;

}	// namespace math

}	// namespace bksge

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T, std::size_t N>
struct tuple_size<bksge::math::Vector<T, N>>
	: public std::integral_constant<std::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T, std::size_t N>
struct tuple_element<I, bksge::math::Vector<T, N>>
{
	static_assert(I < N, "Vector index out of bounds");
	using type = T;
};

}	// namespace std

#include <bksge/core/math/inl/vector_inl.hpp>

#endif // BKSGE_CORE_MATH_VECTOR_HPP
