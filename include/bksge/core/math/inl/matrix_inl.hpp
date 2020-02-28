/**
 *	@file	matrix_inl.hpp
 *
 *	@brief	Matrix の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_INL_MATRIX_INL_HPP
#define BKSGE_CORE_MATH_INL_MATRIX_INL_HPP

#include <bksge/core/math/matrix.hpp>
#include <bksge/core/math/scale.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace math
{

namespace detail
{

// make_matrix
template <typename T, bksge::size_t M, typename F, bksge::size_t... Js>
static BKSGE_CONSTEXPR Vector<T, M>
make_matrix_3(F f, bksge::size_t I, bksge::index_sequence<Js...>) BKSGE_NOEXCEPT
{
	return Vector<T, M>{ f(I, Js)... };
}

template <typename T, bksge::size_t N, bksge::size_t M, typename F, bksge::size_t... Is>
static BKSGE_CONSTEXPR Matrix<T, N, M>
make_matrix_2(F f, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT
{
	return Matrix<T, N, M> { make_matrix_3<T, M>(f, Is, bksge::make_index_sequence<M>())... };
}

template <typename T, bksge::size_t N, bksge::size_t M, typename F>
static BKSGE_CONSTEXPR Matrix<T, N, M>
make_matrix(F f) BKSGE_NOEXCEPT
{
	return make_matrix_2<T, N, M>(f, bksge::make_index_sequence<N>());
}

// make_identity_elem_t
template <typename T>
struct make_identity_elem_t
{
	BKSGE_CONSTEXPR T operator()(bksge::size_t i, bksge::size_t j) const BKSGE_NOEXCEPT
	{
		return i == j ? T(1) : T(0);
	}
};

// make_transposed_t
template <typename T, bksge::size_t N, bksge::size_t M>
struct make_transposed_t
{
	BKSGE_CONSTEXPR make_transposed_t(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT
		: m_ref(m)
	{}

	BKSGE_CONSTEXPR T operator()(bksge::size_t i, bksge::size_t j) const BKSGE_NOEXCEPT
	{
		return m_ref[j][i];
	}

private:
	make_transposed_t& operator=(make_transposed_t const&) = delete;

	Matrix<T, N, M> const& m_ref;
};

// mul_matrix_t
template <typename T, bksge::size_t N, bksge::size_t M, bksge::size_t L>
struct mul_matrix_t
{
	BKSGE_CONSTEXPR mul_matrix_t(
		Matrix<T, N, L> const& lhs,
		Matrix<T, L, M> const& rhs) BKSGE_NOEXCEPT
		: m_lhs(lhs)
		, m_rhs(rhs)
	{}

	BKSGE_CONSTEXPR T operator()(bksge::size_t i, bksge::size_t j) const BKSGE_NOEXCEPT
	{
		return invoke(i, j, bksge::make_index_sequence<L>());
	}

private:
	mul_matrix_t& operator=(mul_matrix_t const&) = delete;

	template <bksge::size_t... Ks>
	BKSGE_CONSTEXPR T invoke(bksge::size_t i, bksge::size_t j, bksge::index_sequence<Ks...>) const BKSGE_NOEXCEPT
	{
		return detail::accumulate(VectorBase<T, L>{m_lhs[i][Ks] * m_rhs[Ks][j]...});
	}

	Matrix<T, N, L> const& m_lhs;
	Matrix<T, L, M> const& m_rhs;
};

// make_resized_t
template <typename T, bksge::size_t N, bksge::size_t M>
struct make_resized_t
{
	BKSGE_CONSTEXPR make_resized_t(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT
		: m_ref(m)
	{}

	BKSGE_CONSTEXPR T operator()(bksge::size_t i, bksge::size_t j) const BKSGE_NOEXCEPT
	{
		return (i < N && j < M) ? m_ref[i][j] : make_identity_elem_t<T>()(i, j);
	}

private:
	make_resized_t& operator=(make_resized_t const&) = delete;

	Matrix<T, N, M> const& m_ref;
};

}	// namespace detail

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CONSTEXPR auto
Matrix<T, N, M>::Zero() BKSGE_NOEXCEPT
-> Matrix
{
	return {};
}

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CONSTEXPR auto
Matrix<T, N, M>::Identity() BKSGE_NOEXCEPT
-> Matrix
{
	return detail::make_matrix<T, N, M>(detail::make_identity_elem_t<T>());
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CONSTEXPR Matrix<T, N, M>
operator+(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT
{
	return m;
}

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CONSTEXPR Matrix<T, N, M>
operator-(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT
{
	return detail::negate_per_elem(m);
}

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator+=(Matrix<T, N, M>& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs + rhs;
	return lhs;
}

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CONSTEXPR Matrix<T, N, M>
operator+(Matrix<T, N, M> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT
{
	return detail::add_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator-=(Matrix<T, N, M>& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs - rhs;
	return lhs;
}

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CONSTEXPR Matrix<T, N, M>
operator-(Matrix<T, N, M> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT
{
	return detail::sub_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, bksge::size_t M, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator*=(Matrix<T, N, M>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, bksge::size_t N, bksge::size_t M, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Matrix<T, N, M>
operator*(Matrix<T, N, M> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return detail::mul_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, bksge::size_t M, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Matrix<T, N, M>
operator*(ArithmeticType lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT
{
	return rhs * lhs;
}

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator*=(Matrix<T, N, M>& lhs, Matrix<T, M, M> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, bksge::size_t N, bksge::size_t M, bksge::size_t L>
inline BKSGE_CONSTEXPR Matrix<T, N, M>
operator*(
	Matrix<T, N, L> const& lhs,
	Matrix<T, L, M> const& rhs) BKSGE_NOEXCEPT
{
	return detail::make_matrix<T, N, M>(detail::mul_matrix_t<T, N, M, L>(lhs, rhs));
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, Matrix<T, N, N> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CONSTEXPR Vector<T, M>
operator*(Vector<T, N> const& lhs, Matrix<T, N, M> const& rhs) BKSGE_NOEXCEPT
{
	return *(Matrix<T, 1, N> { lhs } * rhs).cbegin();
}

template <typename T, bksge::size_t N, bksge::size_t M, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR Matrix<T, N, M>&
operator/=(Matrix<T, N, M>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename T, bksge::size_t N, bksge::size_t M, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR Matrix<T, N, M>
operator/(Matrix<T, N, M> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	return detail::div_per_elem(lhs, rhs);
}

template <typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CONSTEXPR Matrix<T, M, N>
Transposed(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT
{
	return detail::make_matrix<T, M, N>(detail::make_transposed_t<T, N, M>(m));
}

template <bksge::size_t N2, bksge::size_t M2, typename T, bksge::size_t N, bksge::size_t M>
inline BKSGE_CONSTEXPR Matrix<T, N2, M2>
Resized(Matrix<T, N, M> const& m) BKSGE_NOEXCEPT
{
	return detail::make_matrix<T, N2, M2>(detail::make_resized_t<T, N, M>(m));
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_INL_MATRIX_INL_HPP
