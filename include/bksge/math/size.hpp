/**
 *	@file	size.hpp
 *
 *	@brief	Size の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_SIZE_HPP
#define BKSGE_MATH_SIZE_HPP

#include <bksge/math/fwd/size_fwd.hpp>
#include <bksge/math/detail/vector_whd.hpp>
#include <bksge/config.hpp>
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

	// デフォルトコンストラクタ
	BKSGE_CONSTEXPR
	Size() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

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
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator*=(Size<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size * scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Size<T, N>
operator*(Size<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Size
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Size<T, N>
operator*(ArithmeticType lhs, Size<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size /= scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Size<T, N>&
operator/=(Size<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Size / scalar
 */
template <
	typename T, std::size_t N,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
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

#include <bksge/math/inl/size_inl.hpp>

#endif // BKSGE_MATH_SIZE_HPP
