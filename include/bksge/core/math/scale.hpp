/**
 *	@file	scale.hpp
 *
 *	@brief	Scale の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_SCALE_HPP
#define BKSGE_CORE_MATH_SCALE_HPP

#include <bksge/core/math/fwd/scale_fwd.hpp>
#include <bksge/core/math/fwd/vector_fwd.hpp>
#include <bksge/core/math/detail/vector_xyzw.hpp>
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
		typename = bksge::enable_if_t<
			std::is_constructible<T, U>::value
		>
	>
	BKSGE_CONSTEXPR
	Scale(Scale<U, N> const& rhs)
		BKSGE_NOEXCEPT_OR_NOTHROW;

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
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Scale<T, N>
operator+(Scale<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	unary operator-
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Scale<T, N>
operator-(Scale<T, N> const& v) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale += Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator+=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale + Scale -> Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Scale<T, N>
operator+(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale -= Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator-=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale - Scale -> Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Scale<T, N>
operator-(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale *= scalar
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator*=(Scale<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale * scalar
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Scale<T, N>
operator*(Scale<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Scale
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Scale<T, N>
operator*(ArithmeticType lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale *= Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator*=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale * Scale -> Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Scale<T, N> const
operator*(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale /= scalar
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator/=(Scale<T, N>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale / scalar
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Scale<T, N>
operator/(Scale<T, N> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale /= Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator/=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scale / Scale -> Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Scale<T, N> const
operator/(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector *= Scale
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector * Scale -> Vector
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR Vector<T, N> const
operator*(Vector<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Lerp
 */
template <
	typename T, bksge::size_t N,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Scale<T, N>
Lerp(Scale<T, N> const& from, Scale<T, N> const& to, ArithmeticType const& t) BKSGE_NOEXCEPT;

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
struct tuple_size<bksge::math::Scale<T, N>>
	: public std::integral_constant<bksge::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename T, bksge::size_t N>
struct tuple_element<I, bksge::math::Scale<T, N>>
{
	static_assert(I < N, "Scale index out of bounds");
	using type = T;
};

/**
 *	@brief	hash
 */
template <typename T, bksge::size_t N>
struct hash<bksge::math::Scale<T, N>>
{
	bksge::size_t operator()(bksge::math::Scale<T, N> const& arg) const
	{
		return bksge::hash_combine(arg.as_array());
	}
};

}	// namespace std

#include <bksge/core/math/inl/scale_inl.hpp>

#endif // BKSGE_CORE_MATH_SCALE_HPP
