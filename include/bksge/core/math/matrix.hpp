/**
 *	@file	matrix.hpp
 *
 *	@brief	Matrix の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_MATRIX_HPP
#define BKSGE_CORE_MATH_MATRIX_HPP

#include <bksge/core/math/fwd/matrix_fwd.hpp>
#include <bksge/core/math/vector.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <tuple>

namespace bksge
{

namespace math
{

template <typename T, bksge::size_t N, bksge::size_t M>
class Matrix
	: public Vector<Vector<T, M>, N>
{
private:
	using BaseType = Vector<Vector<T, M>, N>;

public:
	// 継承コンストラクタ
	using BaseType::BaseType;

	/**
	 *	@brief	デフォルトコンストラクタ
	 */
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
template <typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator+(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	unary operator-
 */
template <typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator-(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix += Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator+=(Matrix<T, N, M>& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix + Matrix -> Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator+(Matrix<T, N, M> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix -= Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator-=(Matrix<T, N, M>& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix - Matrix -> Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator-(Matrix<T, N, M> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix *= scalar
 */
template <
	typename T, bksge::size_t N, bksge::size_t M,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator*=(Matrix<T, N, M>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix * scalar
 */
template <
	typename T, bksge::size_t N, bksge::size_t M,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator*(Matrix<T, N, M> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	scalar * Matrix
 */
template <
	typename T, bksge::size_t N, bksge::size_t M,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator*(ArithmeticType lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix *= Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator*=(Matrix<T, N, M>& lhs, Matrix<T, M, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief Matrix * Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M, bksge::size_t L>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator*(Matrix<T, N, L> const& lhs, Matrix<T, L, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector *= Matrix
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, Matrix<T, N, N> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Vector * Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CONSTEXPR Vector<T, M>
operator*(Vector<T, N> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix /= scalar
 */
template <
	typename T, bksge::size_t N, bksge::size_t M,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator/=(Matrix<T, N, M>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Matrix / scalar
 */
template <
	typename T, bksge::size_t N, bksge::size_t M,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR Matrix<T, N, M>
operator/(Matrix<T, N, M> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	転置行列を求めます
 */
template <typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CONSTEXPR Matrix<T, M, N>
Transposed(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	行列のサイズを変更します
 *
 *	元の行列よりも大きくなる場合、対角要素は1、それ以外は0が入ります。
 */
template <bksge::size_t N2, bksge::size_t M2, typename T, bksge::size_t N, bksge::size_t M>
BKSGE_CONSTEXPR Matrix<T, N2, M2>
Resized(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	逆行列を求めます
 */
template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR Matrix<T, N, N>
Inversed(Matrix<T, N, N> const& m) BKSGE_NOEXCEPT;

/**
 *	@brief	行列式を求めます
 */
template <typename T, bksge::size_t N>
BKSGE_CONSTEXPR T
Determinant(Matrix<T, N, N> const& m) BKSGE_NOEXCEPT;

}	// namespace math

}	// namespace bksge

#include <functional>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T, bksge::size_t N, bksge::size_t M>
struct tuple_size<bksge::math::Matrix<T, N, M>>
	: public bksge::integral_constant<bksge::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename T, bksge::size_t N, bksge::size_t M>
struct tuple_element<I, bksge::math::Matrix<T, N, M>>
{
	static_assert(I < N, "Vector index out of bounds");
	using type = bksge::math::Vector<T, M>;
};

/**
 *	@brief	hash
 */
template <typename T, bksge::size_t N, bksge::size_t M>
struct hash<bksge::math::Matrix<T, N, M>>
{
	bksge::size_t operator()(bksge::math::Matrix<T, N, M> const& arg) const
	{
		return bksge::hash_combine(arg.as_array());
	}
};

}	// namespace std

#include <bksge/core/math/inl/matrix_inl.hpp>

#endif // BKSGE_CORE_MATH_MATRIX_HPP
