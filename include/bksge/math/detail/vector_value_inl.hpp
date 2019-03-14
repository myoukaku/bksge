/**
 *	@file	vector_value_inl.hpp
 *
 *	@brief	vector_value の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_DETAIL_VECTOR_VALUE_INL_HPP
#define BKSGE_MATH_DETAIL_VECTOR_VALUE_INL_HPP

#include <bksge/math/detail/vector_value.hpp>
#include <bksge/math/detail/vector_functions.hpp>
#include <bksge/stdexcept/throw_out_of_range.hpp>
#include <bksge/config.hpp>
#include <cstddef>
#include <ostream>

namespace bksge
{

namespace math
{

namespace detail
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4702);	// 制御が渡らないコードです。

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR auto
vector_value<T, N>::at(size_type pos)
-> reference
{
	return (pos >= N) ?
		(bksge::throw_out_of_range("array::at"), m_elems[0]) :
		m_elems[pos];
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
vector_value<T, N>::at(size_type pos) const
-> const_reference
{
	return (pos >= N) ?
		(bksge::throw_out_of_range("array::at"), m_elems[0]) :
		m_elems[pos];
}

BKSGE_WARNING_POP();

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR void
swap(vector_value<T, N>& lhs, vector_value<T, N>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR bool
operator==(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return bksge::math::detail::equal_per_elem(lhs, rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR bool
operator!=(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename T, std::size_t N>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, vector_value<T, N> const& rhs)
{
	os << "{ ";

	for (std::size_t i = 0; i < N; ++i)
	{
		os << rhs[i];

		if (i < (N - 1))
		{
			os << ", ";
		}
	}

	os << " }";

	return os;
}

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_MATH_DETAIL_VECTOR_VALUE_INL_HPP
