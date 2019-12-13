/**
 *	@file	size.hpp
 *
 *	@brief	Size の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_SIZE_HPP
#define BKSGE_CORE_MATH_SIZE_HPP

#include <bksge/core/math/fwd/size_fwd.hpp>
#include <bksge/core/math/fwd/scale_fwd.hpp>
#include <bksge/core/math/detail/vector_whd.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
class Size
	: public detail::VectorWHD<T, N>
{
private:
	using BaseType = detail::VectorWHD<T, N>;

public:
	// 継承コンストラクタ
	using BaseType::BaseType;

	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Size() BKSGE_NOEXCEPT_OR_NOTHROW
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
	Size(Size<U, N> const& rhs)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	ゼロ初期化されたSizeを作成します
	 */
	static BKSGE_CONSTEXPR Size
	Zero() BKSGE_NOEXCEPT;
};

/**
 *	@brief	unary operator+
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Size<T, N>
operator+(Size<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	unary operator-
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Size<T, N>
operator-(Size<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	Size += Size
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator+=(Size<T, N>& lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size + Size -> Size
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Size<T, N>
operator+(Size<T, N> const& lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size -= Size
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator-=(Size<T, N>& lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size - Size -> Size
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Size<T, N>
operator-(Size<T, N> const& lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size *= scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator*=(Size<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size *= Scale
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator*=(Size<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size * scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Size<T, N>
operator*(Size<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Size
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Size<T, N>
operator*(ArithmeticType lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size * Scale -> Size
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Size<T, N> const
operator*(Size<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size /= scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator/=(Size<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size / scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Size<T, N>
operator/(Size<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

}	// namespace math

}	// namespace bksge

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T, std::size_t N>
struct tuple_size<bksge::math::Size<T, N>>
	: public std::integral_constant<std::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T, std::size_t N>
struct tuple_element<I, bksge::math::Size<T, N>>
{
	static_assert(I < N, "Size index out of bounds");
	using type = T;
};

}	// namespace std

#include <bksge/core/math/inl/size_inl.hpp>

#endif // BKSGE_CORE_MATH_SIZE_HPP
