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
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T, bksge::size_t N, bksge::size_t M>
class Matrix : public Vector<Vector<T, M>, N>
{
private:
	using BaseType = Vector<Vector<T, M>, N>;

public:
	using BaseType::BaseType;
};

/**
 *	@brief	Matrix *= Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator*=(Matrix<T, N, M>& lhs, Matrix<T, M, M> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

/**
 *	@brief Matrix * Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M, bksge::size_t L>
inline BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>
operator*(Matrix<T, N, L> const& lhs, Matrix<T, L, M> const& rhs) BKSGE_NOEXCEPT
{
	Matrix<T, N, M> result{};
	for (bksge::size_t i = 0; i < N; ++i)
	{
		for (bksge::size_t j = 0; j < M; ++j)
		{
			for (bksge::size_t k = 0; k < L; ++k)
			{
				result[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}
	return result;
}

/**
 *	@brief	Vector *= Matrix
 */
template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, Matrix<T, N, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

/**
 *	@brief	Vector * Matrix
 */
template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CXX14_CONSTEXPR Vector<T, M>
operator*(Vector<T, N> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT
{
	return (Matrix<T, 1, N>{ lhs } * rhs).front();
}

/**
 *	@brief	転置行列を求めます
 */
template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CXX14_CONSTEXPR Matrix<T, M, N>
Transposed(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT
{
	Matrix<T, M, N> result{};
	for (bksge::size_t i = 0; i < N; ++i)
	{
		for (bksge::size_t j = 0; j < M; ++j)
		{
			result[j][i] = m[i][j];
		}
	}
	return result;
}

}	// namespace math

}	// namespace bksge

#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>

namespace BKSGE_TUPLE_NAMESPACE
{

/**
 *	@brief	tuple_size
 */
template <typename T, bksge::size_t N, bksge::size_t M>
struct tuple_size<bksge::math::Matrix<T, N, M>>
	: public tuple_size<bksge::math::Vector<bksge::math::Vector<T, M>, N>>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename T, bksge::size_t N, bksge::size_t M>
struct tuple_element<I, bksge::math::Matrix<T, N, M>>
	: public tuple_element<I, bksge::math::Vector<bksge::math::Vector<T, M>, N>>
{};

}	// namespace BKSGE_TUPLE_NAMESPACE

#include <bksge/fnd/functional/hash.hpp>

namespace BKSGE_HASH_NAMESPACE
{

/**
 *	@brief	hash
 */
template <typename T, bksge::size_t N, bksge::size_t M>
struct hash<bksge::math::Matrix<T, N, M>>
	: public hash<bksge::math::Vector<bksge::math::Vector<T, M>, N>>
{};

}	// namespace BKSGE_HASH_NAMESPACE

#endif // BKSGE_CORE_MATH_MATRIX_HPP
