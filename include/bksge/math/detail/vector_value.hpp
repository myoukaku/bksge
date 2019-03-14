/**
 *	@file	vector_value.hpp
 *
 *	@brief	vector_value の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_DETAIL_VECTOR_VALUE_HPP
#define BKSGE_MATH_DETAIL_VECTOR_VALUE_HPP

#include <bksge/type_traits/conjunction.hpp>
#include <bksge/type_traits/is_nothrow_swappable.hpp>
#include <bksge/utility/make_index_sequence.hpp>
#include <bksge/utility/index_sequence.hpp>
#include <bksge/config.hpp>
#include <algorithm>	// swap_ranges
#include <iterator>		// reverse_iterator
#include <iosfwd>		// basic_ostream
#include <cstddef>
#include <utility>
#include <type_traits>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, std::size_t N>
class vector_value
{
#if defined(_MSC_VER)
public:
#else
private:
#endif
	template <bool, typename... UTypes>
	struct CheckArgsCtorImpl
	{
		static constexpr bool enable_implicit = false;
		static constexpr bool enable_explicit = false;
	};

	template <typename... UTypes>
	struct CheckArgsCtorImpl<true, UTypes...>
	{
		static constexpr bool enable_implicit =
			bksge::conjunction<std::is_convertible<UTypes, T>...>::value;

		static constexpr bool enable_explicit =
			bksge::conjunction<std::is_constructible<T, UTypes>...>::value &&
			!enable_implicit;
	};

	template <typename... UTypes>
	struct CheckArgsCtor
		: public CheckArgsCtorImpl<
			sizeof...(UTypes) == N,
			UTypes...
		>
	{};

	template <typename... UTypes>
	struct IsNothrowArgsConstructible
		: public bksge::conjunction<
			std::is_nothrow_constructible<T, UTypes>...
		>
	{};

public:
	using value_type             = T;
	using size_type              = std::size_t;
	using difference_type        = std::ptrdiff_t;
	using reference              = T&;
	using const_reference        = T const&;
	using pointer                = T*;
	using const_pointer          = T const*;
	using iterator               = T*;
	using const_iterator         = T const*;
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// Default ctor
	BKSGE_CONSTEXPR
	vector_value() BKSGE_NOEXCEPT_OR_NOTHROW
		: m_elems{}
	{}

	// Converting ctor
	template <
		typename... UTypes,
		typename std::enable_if<CheckArgsCtor<UTypes&&...>::enable_implicit>::type* = nullptr
	>
	BKSGE_CONSTEXPR
	vector_value(UTypes&&... args)
		BKSGE_NOEXCEPT_IF(IsNothrowArgsConstructible<UTypes...>::value)
		: m_elems{static_cast<T>(args)...}
	{}

	template <
		typename... UTypes,
		typename std::enable_if<CheckArgsCtor<UTypes&&...>::enable_explicit>::type* = nullptr
	>
	explicit BKSGE_CONSTEXPR
	vector_value(UTypes&&... args)
		BKSGE_NOEXCEPT_IF(IsNothrowArgsConstructible<UTypes...>::value)
		: m_elems{static_cast<T>(args)...}
	{}

	// Converting copy-ctor
	template <
		typename U,
		typename std::enable_if<CheckArgsCtorImpl<true, U const&>::enable_implicit>::type* = nullptr
	>
	BKSGE_CONSTEXPR
	vector_value(vector_value<U, N> const& other)
		BKSGE_NOEXCEPT_IF(IsNothrowArgsConstructible<U>::value)
		: vector_value(other, bksge::make_index_sequence<N>())
	{}

	template <
		typename U,
		typename std::enable_if<CheckArgsCtorImpl<true, U const&>::enable_explicit>::type* = nullptr
	>
	explicit BKSGE_CONSTEXPR
	vector_value(vector_value<U, N> const& other)
		BKSGE_NOEXCEPT_IF(IsNothrowArgsConstructible<U>::value)
		: vector_value(other, bksge::make_index_sequence<N>())
	{}

private:
	template <typename Vector, std::size_t... Is>
	BKSGE_CONSTEXPR
	vector_value(Vector const& other, bksge::index_sequence<Is...>)
		BKSGE_NOEXCEPT_OR_NOTHROW
		: m_elems{static_cast<T>(other[Is])...}
	{}

public:
	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reference
	operator[](size_type pos) BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return m_elems[pos];
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reference
	operator[](size_type pos) const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return m_elems[pos];
	}

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reference
	at(size_type pos);

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reference
	at(size_type pos) const;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR pointer
	data() BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return m_elems;
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_pointer
	data() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return m_elems;
	}

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR iterator
	begin() BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return iterator(data());
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_iterator
	begin() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return const_iterator(data());
	}

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR iterator
	end() BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return iterator(data() + N);
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_iterator
	end() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return const_iterator(data() + N);
	}

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reverse_iterator
	rbegin() BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return reverse_iterator(end());
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reverse_iterator
	rbegin() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return const_reverse_iterator(end());
	}

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reverse_iterator
	rend() BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return reverse_iterator(begin());
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reverse_iterator
	rend() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return const_reverse_iterator(begin());
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_iterator
	cbegin() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return begin();
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_iterator
	cend() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return end();
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reverse_iterator
	crbegin() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return rbegin();
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reverse_iterator
	crend() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return rend();
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR bool
	empty() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return false;
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR size_type
	size() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return N;
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR size_type
	max_size() const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return N;
	}

	BKSGE_CXX14_CONSTEXPR void swap(vector_value& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value)
	{
		std::swap_ranges(m_elems, m_elems + N, other.m_elems);
	}

private:
	T		m_elems[N];
};

/**
 *	@brief	swap
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR void
swap(vector_value<T, N>& lhs, vector_value<T, N>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs));

/**
 *	@brief	operator==
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR bool
operator==(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

/**
 *	@brief	operator!=
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR bool
operator!=(vector_value<T, N> const& lhs, vector_value<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits, typename T, std::size_t N>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, vector_value<T, N> const& rhs);

}	// namespace detail

}	// namespace math

}	// namespace bksge

namespace bksge
{

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR T&
get(bksge::math::detail::vector_value<T, N>& v) noexcept
{
	static_assert(I < N, "vector index out of bounds");
	return v[I];
}

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CONSTEXPR T const&
get(bksge::math::detail::vector_value<T, N> const& v) noexcept
{
	static_assert(I < N, "vector index out of bounds");
	return v[I];
}

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR T&&
get(bksge::math::detail::vector_value<T, N>&& v) noexcept
{
	static_assert(I < N, "vector index out of bounds");
	return std::move(v[I]);
}

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CONSTEXPR T const&&
get(bksge::math::detail::vector_value<T, N> const&& v) noexcept
{
	static_assert(I < N, "vector index out of bounds");
	return std::move(v[I]);
}

}	// namespace bksge

#include <bksge/math/detail/vector_value_inl.hpp>

#endif // BKSGE_MATH_DETAIL_VECTOR_VALUE_HPP
