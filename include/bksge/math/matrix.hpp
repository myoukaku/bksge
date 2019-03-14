/**
 *	@file	matrix.hpp
 *
 *	@brief	Matrix の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_MATRIX_HPP
#define BKSGE_MATH_MATRIX_HPP

#include <bksge/math/fwd/matrix_fwd.hpp>
#include <bksge/math/vector.hpp>
#include <bksge/config.hpp>
#include <type_traits>
#include <tuple>
#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N, std::size_t M>
class Matrix
	: public Vector<Vector<T, M>, N>
{
private:
	using BaseType = Vector<Vector<T, M>, N>;

public:
	// 継承コンストラクタ
	using BaseType::BaseType;

	// デフォルトコンストラクタ
	BKSGE_CONSTEXPR
	Matrix() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	/**
	 *	@brief	ゼロ行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix
	Zero() BKSGE_NOEXCEPT;

	/**
	 *	@brief	単位行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix
	Identity() BKSGE_NOEXCEPT;
};

/**
 *	@brief	unary operator+
 */
template <typename T, std::size_t N, std::size_t M>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator+(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	unary operator-
 */
template <typename T, std::size_t N, std::size_t M>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator-(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix += Matrix
 */
template <typename T, std::size_t N, std::size_t M>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator+=(Matrix<T, N, M>& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix + Matrix -> Matrix
 */
template <typename T, std::size_t N, std::size_t M>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator+(Matrix<T, N, M> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix -= Matrix
 */
template <typename T, std::size_t N, std::size_t M>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator-=(Matrix<T, N, M>& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix - Matrix -> Matrix
 */
template <typename T, std::size_t N, std::size_t M>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator-(Matrix<T, N, M> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix *= scalar
 */
template <
	typename T, std::size_t N, std::size_t M,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator*=(Matrix<T, N, M>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix * scalar
 */
template <
	typename T, std::size_t N, std::size_t M,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator*(Matrix<T, N, M> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Matrix
 */
template <
	typename T, std::size_t N, std::size_t M,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator*(ArithmeticType lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix *= Matrix
 */
template <typename T, std::size_t N, std::size_t M>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator*=(Matrix<T, N, M>& lhs, Matrix<T, M, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief Matrix * Matrix
 */
template <typename T, std::size_t N, std::size_t M, std::size_t L>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator*(Matrix<T, N, L> const& lhs, Matrix<T, L, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector *= Matrix
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, Matrix<T, N, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector * Matrix
 */
template <typename T, std::size_t N, std::size_t M>
BKSGE_CONSTEXPR Vector<T, M>
operator*(Vector<T, N> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix /= scalar
 */
template <
	typename T, std::size_t N, std::size_t M,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator/=(Matrix<T, N, M>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix / scalar
 */
template <
	typename T, std::size_t N, std::size_t M,
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator/(Matrix<T, N, M> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	転置行列を求めます
 */
template <typename T, std::size_t N, std::size_t M>
BKSGE_CONSTEXPR Matrix<T, M, N>
Transposed(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	行列のサイズを変更します
 *
 *	元の行列よりも大きくなる場合、対角要素は1、それ以外は0が入ります。
 */
template <std::size_t N2, std::size_t M2, typename T, std::size_t N, std::size_t M>
BKSGE_CONSTEXPR Matrix<T, N2, M2>
Resized(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	逆行列を求めます
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, N>
Inversed(Matrix<T, N, N> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	行列式を求めます
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR T
Determinant(Matrix<T, N, N> const& m) BKSGE_NOEXCEPT;

}	// namespace math

}	// namespace bksge

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T, std::size_t N, std::size_t M>
struct tuple_size<bksge::math::Matrix<T, N, M>>
	: public std::integral_constant<std::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T, std::size_t N, std::size_t M>
struct tuple_element<I, bksge::math::Matrix<T, N, M>>
{
	static_assert(I < N, "Vector index out of bounds");
	using type = bksge::math::Vector<T, M>;
};

}	// namespace std

#include <bksge/math/inl/matrix_inl.hpp>

#endif // BKSGE_MATH_MATRIX_HPP
