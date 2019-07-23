/**
 *	@file	color.hpp
 *
 *	@brief	Color の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_COLOR_HPP
#define BKSGE_MATH_COLOR_HPP

#include <bksge/math/fwd/color_fwd.hpp>
#include <bksge/math/detail/vector_base.hpp>
#include <bksge/math/detail/vector_rgba.hpp>
#include <bksge/config.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
class Color
	: public detail::VectorRGBA<T, N>
{
private:
	using BaseType = detail::VectorRGBA<T, N>;

public:
	// 継承コンストラクタ
	using BaseType::BaseType;

	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Color() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	/**
	 *	@brief	変換コンストラクタ
	 */
	template <
		typename U,
		typename = typename std::enable_if<
			std::is_constructible<T, U>::value
		>::type
	>
	BKSGE_CONSTEXPR
	Color(Color<U, N> const& rhs)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	ゼロ初期化されたColorを作成します
	 */
	static BKSGE_CONSTEXPR Color
	Zero() BKSGE_NOEXCEPT;
};

/**
 *	@brief	unary operator+
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Color<T, N>
operator+(Color<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	unary operator-
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Color<T, N>
operator-(Color<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	Color += Color
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator+=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color + Color -> Color
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Color<T, N>
operator+(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color -= Color
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator-=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color - Color -> Color
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Color<T, N>
operator-(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color *= scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator*=(Color<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color * scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Color<T, N>
operator*(Color<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Color
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Color<T, N>
operator*(ArithmeticType lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color *= Color
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator*=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color * Color -> Color
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Color<T, N> const
operator*(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color /= scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator/=(Color<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color / scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Color<T, N>
operator/(Color<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color /= Color
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator/=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Color / Color -> Color
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Color<T, N> const
operator/(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Lerp
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Color<T, N>
Lerp(Color<T, N> const& from, Color<T, N> const& to, ArithmeticType const& t) BKSGE_NOEXCEPT;

}	// namespace math

}	// namespace bksge

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T, std::size_t N>
struct tuple_size<bksge::math::Color<T, N>>
	: public std::integral_constant<std::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T, std::size_t N>
struct tuple_element<I, bksge::math::Color<T, N>>
{
	static_assert(I < N, "Color index out of bounds");
	using type = T;
};

}	// namespace std

#include <bksge/math/inl/color_inl.hpp>

#endif // BKSGE_MATH_COLOR_HPP
