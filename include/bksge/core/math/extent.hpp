/**
 *	@file	extent.hpp
 *
 *	@brief	Extent の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_EXTENT_HPP
#define BKSGE_CORE_MATH_EXTENT_HPP

#include <bksge/core/math/fwd/extent_fwd.hpp>
#include <bksge/core/math/fwd/scale_fwd.hpp>
#include <bksge/core/math/detail/vector_whd.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <tuple>
#include <type_traits>

namespace bksge
{

namespace math
{

template <typename T, bksge::size_t N>
class Extent
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
	Extent() BKSGE_NOEXCEPT_OR_NOTHROW
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
	Extent(Extent<U, N> const& rhs)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	ゼロ初期化されたExtentを作成します
	 */
	static BKSGE_CONSTEXPR Extent
	Zero() BKSGE_NOEXCEPT;
};

/**
 *	@brief	unary operator+
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Extent<T, N>
operator+(Extent<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	unary operator-
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Extent<T, N>
operator-(Extent<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent += Extent
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator+=(Extent<T, N>& lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent + Extent -> Extent
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Extent<T, N>
operator+(Extent<T, N> const& lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent -= Extent
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator-=(Extent<T, N>& lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent - Extent -> Extent
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Extent<T, N>
operator-(Extent<T, N> const& lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent *= scalar
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator*=(Extent<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent *= Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator*=(Extent<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent * scalar
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Extent<T, N>
operator*(Extent<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Extent
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Extent<T, N>
operator*(ArithmeticType lhs, Extent<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent * Scale -> Extent
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Extent<T, N> const
operator*(Extent<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent /= scalar
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator/=(Extent<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Extent / scalar
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Extent<T, N>
operator/(Extent<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

}	// namespace math

}	// namespace bksge

#include <functional>
#include <bksge/fnd/functional/hash_combine.hpp>

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T, bksge::size_t N>
struct tuple_size<bksge::math::Extent<T, N>>
	: public std::integral_constant<bksge::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename T, bksge::size_t N>
struct tuple_element<I, bksge::math::Extent<T, N>>
{
	static_assert(I < N, "Extent index out of bounds");
	using type = T;
};

/**
 *	@brief	hash
 */
template <typename T, bksge::size_t N>
struct hash<bksge::math::Extent<T, N>>
{
	bksge::size_t operator()(bksge::math::Extent<T, N> const& arg) const
	{
		return bksge::hash_combine(arg.as_array());
	}
};

}	// namespace std

#include <bksge/core/math/inl/extent_inl.hpp>

#endif // BKSGE_CORE_MATH_EXTENT_HPP
