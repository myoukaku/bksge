/**
 *	@file	vector_base_inl.hpp
 *
 *	@brief	VectorBase の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_VECTOR_BASE_INL_HPP
#define BKSGE_CORE_MATH_DETAIL_VECTOR_BASE_INL_HPP

#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/stdexcept/throw_out_of_range.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/config.hpp>
#include <algorithm>	// swap_ranges
#include <cstddef>
#include <ostream>		// basic_ostream
#include <utility>		// move

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR
VectorBase<T, N>::VectorBase()
	BKSGE_NOEXCEPT_OR_NOTHROW
	: m_value{}
{}

template <typename T, std::size_t N>
template <typename... UTypes, typename>
inline BKSGE_CONSTEXPR
VectorBase<T, N>::VectorBase(UTypes const&... args)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: m_value{{static_cast<T>(args)...}}
{}

template <typename T, std::size_t N>
template <typename U, typename>
inline BKSGE_CONSTEXPR
VectorBase<T, N>::VectorBase(VectorValue<U, N> const& a)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: VectorBase(a, bksge::make_index_sequence<N>())
{}

template <typename T, std::size_t N>
template <typename U, std::size_t... Is>
inline BKSGE_CONSTEXPR
VectorBase<T, N>::VectorBase(
	VectorValue<U, N> const& a,
	bksge::index_sequence<Is...>)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: VectorBase(a[Is]...)
{}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR auto
VectorBase<T, N>::operator[](size_type pos)
	BKSGE_NOEXCEPT_OR_NOTHROW
-> reference
{
	return m_value[pos];
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::operator[](size_type pos) const
	BKSGE_NOEXCEPT_OR_NOTHROW
-> const_reference
{
	return m_value[pos];
}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4702);	// 制御が渡らないコードです。

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR auto
VectorBase<T, N>::at(size_type pos)
-> reference
{
	return (pos >= N) ?
		(bksge::throw_out_of_range("VectorBase::at"), m_value[0]) :
		m_value[pos];
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::at(size_type pos) const
-> const_reference
{
	return (pos >= N) ?
		(bksge::throw_out_of_range("VectorBase::at"), m_value[0]) :
		m_value[pos];
}

BKSGE_WARNING_POP();

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR auto
VectorBase<T, N>::data() BKSGE_NOEXCEPT_OR_NOTHROW
-> pointer
{
	return &m_value[0];
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::data() const BKSGE_NOEXCEPT_OR_NOTHROW
-> const_pointer
{
	return &m_value[0];
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR auto
VectorBase<T, N>::begin() BKSGE_NOEXCEPT_OR_NOTHROW
-> iterator
{
	return iterator(data());
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::begin() const BKSGE_NOEXCEPT_OR_NOTHROW
-> const_iterator
{
	return const_iterator(data());
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR auto
VectorBase<T, N>::end() BKSGE_NOEXCEPT_OR_NOTHROW
-> iterator
{
	return iterator(data() + N);
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::end() const BKSGE_NOEXCEPT_OR_NOTHROW
-> const_iterator
{
	return const_iterator(data() + N);
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR auto
VectorBase<T, N>::rbegin() BKSGE_NOEXCEPT_OR_NOTHROW
-> reverse_iterator
{
	return reverse_iterator(end());
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::rbegin() const BKSGE_NOEXCEPT_OR_NOTHROW
-> const_reverse_iterator
{
	return const_reverse_iterator(end());
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR auto
VectorBase<T, N>::rend() BKSGE_NOEXCEPT_OR_NOTHROW
-> reverse_iterator
{
	return reverse_iterator(begin());
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::rend() const BKSGE_NOEXCEPT_OR_NOTHROW
-> const_reverse_iterator
{
	return const_reverse_iterator(begin());
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::cbegin() const BKSGE_NOEXCEPT_OR_NOTHROW
-> const_iterator
{
	return begin();
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::cend() const BKSGE_NOEXCEPT_OR_NOTHROW
-> const_iterator
{
	return end();
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::crbegin() const BKSGE_NOEXCEPT_OR_NOTHROW
-> const_reverse_iterator
{
	return rbegin();
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::crend() const BKSGE_NOEXCEPT_OR_NOTHROW
-> const_reverse_iterator
{
	return rend();
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::empty() const BKSGE_NOEXCEPT_OR_NOTHROW
-> bool
{
	return false;
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::size() const BKSGE_NOEXCEPT_OR_NOTHROW
-> size_type
{
	return N;
}

template <typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR auto
VectorBase<T, N>::max_size() const BKSGE_NOEXCEPT_OR_NOTHROW
-> size_type
{
	return N;
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR void
VectorBase<T, N>::swap(VectorBase& other)
	BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value)
{
	std::swap_ranges(begin(), begin() + N, other.begin());
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR VectorValue<T, N>
VectorBase<T, N>::as_array(void) const
{
	return m_value;
}

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR void
swap(VectorBase<T, N>& lhs, VectorBase<T, N>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR bool
operator==(VectorBase<T, N> const& lhs, VectorBase<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return bksge::math::detail::equal_per_elem(lhs, rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR bool
operator==(VectorBase<T, N> const& lhs, VectorValue<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return lhs == VectorBase<T, N>(rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR bool
operator!=(VectorBase<T, N> const& lhs, VectorBase<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return !(lhs == rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR bool
operator!=(VectorBase<T, N> const& lhs, VectorValue<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename T, std::size_t N>
inline std::basic_ostream<CharT, Traits>&
operator<<(
	std::basic_ostream<CharT, Traits>& os,
	VectorBase<T, N> const& rhs)
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

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR T&
get(bksge::math::detail::VectorBase<T, N>& v) BKSGE_NOEXCEPT
{
	static_assert(I < N, "vector index out of bounds");
	return v[I];
}

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR T const&
get(bksge::math::detail::VectorBase<T, N> const& v) BKSGE_NOEXCEPT
{
	static_assert(I < N, "vector index out of bounds");
	return v[I];
}

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR T&&
get(bksge::math::detail::VectorBase<T, N>&& v) BKSGE_NOEXCEPT
{
	static_assert(I < N, "vector index out of bounds");
	return std::move(v[I]);
}

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR T const&&
get(bksge::math::detail::VectorBase<T, N> const&& v) BKSGE_NOEXCEPT
{
	static_assert(I < N, "vector index out of bounds");
	return std::move(v[I]);
}

}	// namespace bksge

#endif // BKSGE_CORE_MATH_DETAIL_VECTOR_BASE_INL_HPP
