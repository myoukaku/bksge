/**
 *	@file	scale.hpp
 *
 *	@brief	Scale の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_SCALE_HPP
#define BKSGE_MATH_SCALE_HPP

#include <bksge/math/fwd/scale_fwd.hpp>
#include <bksge/math/fwd/vector_fwd.hpp>
#include <bksge/math/detail/vector_xyzw.hpp>
#include <bksge/config.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
class Scale
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
	Scale() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	/**
	 *	@brief	変換コンストラクタ
	 */
	template <
		typename U,
		typename std::enable_if<
			std::is_constructible<T, U>::value
		>::type* = nullptr
	>
	BKSGE_CONSTEXPR
	Scale(Scale<U, N> const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType(rhs.as_array())
	{}

	/**
	 *	@brief	ゼロスケールを作成します
	 */
	static BKSGE_CONSTEXPR Scale
	Zero() BKSGE_NOEXCEPT;

	/**
	 *	@brief	単位スケールを作成します
	 */
	static BKSGE_CONSTEXPR Scale
	Identity() BKSGE_NOEXCEPT;
};

/**
 *	@brief	unary operator+
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Scale<T, N>
operator+(Scale<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	unary operator-
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Scale<T, N>
operator-(Scale<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale += Scale
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator+=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale + Scale -> Scale
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Scale<T, N>
operator+(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale -= Scale
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator-=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale - Scale -> Scale
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Scale<T, N>
operator-(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale *= scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator*=(Scale<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale * scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Scale<T, N>
operator*(Scale<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Scale
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Scale<T, N>
operator*(ArithmeticType lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale *= Scale
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator*=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale * Scale -> Scale
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Scale<T, N> const
operator*(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale /= scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator/=(Scale<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale / scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Scale<T, N>
operator/(Scale<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale /= Scale
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator/=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale / Scale -> Scale
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Scale<T, N> const
operator/(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector *= Scale
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector * Scale -> Vector
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Vector<T, N> const
operator*(Vector<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

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
BKSGE_CONSTEXPR Scale<T, N>
Lerp(Scale<T, N> const& from, Scale<T, N> const& to, ArithmeticType const& t) BKSGE_NOEXCEPT;

}	// namespace math

}	// namespace bksge

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T, std::size_t N>
struct tuple_size<bksge::math::Scale<T, N>>
	: public std::integral_constant<std::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T, std::size_t N>
struct tuple_element<I, bksge::math::Scale<T, N>>
{
	static_assert(I < N, "Scale index out of bounds");
	using type = T;
};

}	// namespace std

#include <bksge/math/inl/scale_inl.hpp>

#endif // BKSGE_MATH_SCALE_HPP
