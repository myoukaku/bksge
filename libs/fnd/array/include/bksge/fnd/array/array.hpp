/**
 *	@file	array.hpp
 *
 *	@brief	array クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ARRAY_ARRAY_HPP
#define BKSGE_FND_ARRAY_ARRAY_HPP

#include <bksge/fnd/array/config.hpp>

#if defined(BKSGE_USE_STD_ARRAY)

#include <array>

namespace bksge
{

using std::array;

}	// namespace bksge

#else

#include <bksge/fnd/algorithm/fill_n.hpp>
#include <bksge/fnd/algorithm/swap_ranges.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/algorithm/lexicographical_compare.hpp>
#include <bksge/fnd/compare/detail/synth3way.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/cstring/memcmp.hpp>
#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/type_traits/detail/is_memcmp_ordered.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <cstddef>

namespace bksge
{

namespace detail
{

template <typename T, std::size_t N>
struct array_traits
{
	using type = T[N];

	static BKSGE_CONSTEXPR T&
	ref(type const& t, std::size_t n) BKSGE_NOEXCEPT
	{
		return const_cast<T&>(t[n]);
	}

	static BKSGE_CONSTEXPR T*
	ptr(type const& t) BKSGE_NOEXCEPT
	{
		return const_cast<T*>(t);
	}
};

template <typename T>
struct array_traits<T, 0>
{
	struct type {};

	static BKSGE_CONSTEXPR T&
	ref(type const&, std::size_t) BKSGE_NOEXCEPT
	{
		return *static_cast<T*>(nullptr);
	}

	static BKSGE_CONSTEXPR T*
	ptr(type const&) BKSGE_NOEXCEPT
	{
		return nullptr;
	}
};

}	// namespace detail

template <typename T, std::size_t N>
struct array
{
	using value_type             = T;
	using pointer                = value_type*;
	using const_pointer          = value_type const*;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using iterator               = value_type*;
	using const_iterator         = value_type const*;
	using size_type              = std::size_t;
	using difference_type        = std::ptrdiff_t;
	using reverse_iterator       = bksge::reverse_iterator<iterator>;
	using const_reverse_iterator = bksge::reverse_iterator<const_iterator>;

	// Support for zero-sized arrays mandatory.
	using traits_type = bksge::detail::array_traits<T, N>;
	typename traits_type::type m_elems;

	// No explicit construct/copy/destroy for aggregate type.

	BKSGE_CXX14_CONSTEXPR void
	fill(value_type const& u)
	{
		bksge::fill_n(begin(), size(), u);
	}

	BKSGE_CXX14_CONSTEXPR void
	swap(array& other)
		BKSGE_NOEXCEPT_IF(N == 0 || bksge::is_nothrow_swappable<T>::value)
	{
		bksge::swap_ranges(begin(), end(), other.begin());
	}

	// Iterators.
	BKSGE_CXX14_CONSTEXPR iterator begin() BKSGE_NOEXCEPT
	{
		return iterator(data());
	}

	BKSGE_CXX14_CONSTEXPR const_iterator begin() const BKSGE_NOEXCEPT
	{
		return const_iterator(data());
	}

	BKSGE_CXX14_CONSTEXPR iterator end() BKSGE_NOEXCEPT
	{
		return iterator(data() + N);
	}

	BKSGE_CXX14_CONSTEXPR const_iterator end() const BKSGE_NOEXCEPT
	{
		return const_iterator(data() + N);
	}

	BKSGE_CXX14_CONSTEXPR reverse_iterator rbegin() BKSGE_NOEXCEPT
	{
		return reverse_iterator(end());
	}

	BKSGE_CXX14_CONSTEXPR const_reverse_iterator rbegin() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(end());
	}

	BKSGE_CXX14_CONSTEXPR reverse_iterator rend() BKSGE_NOEXCEPT
	{
		return reverse_iterator(begin());
	}

	BKSGE_CXX14_CONSTEXPR const_reverse_iterator rend() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(begin());
	}

	BKSGE_CXX14_CONSTEXPR const_iterator cbegin() const BKSGE_NOEXCEPT
	{
		return const_iterator(data());
	}

	BKSGE_CXX14_CONSTEXPR const_iterator cend() const BKSGE_NOEXCEPT
	{
		return const_iterator(data() + N);
	}

	BKSGE_CXX14_CONSTEXPR const_reverse_iterator crbegin() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(end());
	}

	BKSGE_CXX14_CONSTEXPR const_reverse_iterator crend() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(begin());
	}

	// Capacity.
	BKSGE_CONSTEXPR size_type size() const BKSGE_NOEXCEPT
	{
		return N;
	}

	BKSGE_CONSTEXPR size_type max_size() const BKSGE_NOEXCEPT
	{
		return N;
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR bool empty() const BKSGE_NOEXCEPT
	{
		return size() == 0;
	}

	// Element access.
	BKSGE_CXX14_CONSTEXPR reference operator[](size_type n) BKSGE_NOEXCEPT
	{
		return traits_type::ref(m_elems, n);
	}

	BKSGE_CONSTEXPR const_reference operator[](size_type n) const BKSGE_NOEXCEPT
	{
		return traits_type::ref(m_elems, n);
	}

	BKSGE_CXX14_CONSTEXPR reference at(size_type n)
	{
		if (n >= N)
		{
			bksge::throw_out_of_range("array::at");
		}
		return traits_type::ref(m_elems, n);
	}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4702);	// unreachable code
	BKSGE_CONSTEXPR const_reference at(size_type n) const
	{
		// Result of conditional expression must be an lvalue so use
		// boolean ? lvalue : (throw-expr, lvalue)
		return n < N ? traits_type::ref(m_elems, n)
			: (bksge::throw_out_of_range("array::at"), traits_type::ref(m_elems, 0));
	}
BKSGE_WARNING_POP();

	BKSGE_CXX14_CONSTEXPR reference front() BKSGE_NOEXCEPT
	{
		return traits_type::ref(m_elems, 0);
	}

	BKSGE_CONSTEXPR const_reference front() const BKSGE_NOEXCEPT
	{
		return traits_type::ref(m_elems, 0);
	}

	BKSGE_CXX14_CONSTEXPR reference back() BKSGE_NOEXCEPT
	{
		return traits_type::ref(m_elems, N - 1);
	}

	BKSGE_CONSTEXPR const_reference back() const BKSGE_NOEXCEPT
	{
		return traits_type::ref(m_elems, N - 1);
	}

	BKSGE_CXX14_CONSTEXPR pointer data() BKSGE_NOEXCEPT
	{
		return traits_type::ptr(m_elems);
	}

	BKSGE_CXX14_CONSTEXPR const_pointer data() const BKSGE_NOEXCEPT
	{
		return traits_type::ptr(m_elems);
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
template <typename T, typename... U>
array(T, U...)
->array<bksge::enable_if_t<(bksge::is_same<T, U>::value && ...), T>, 1 + sizeof...(U)>;
#endif

// Array comparisons.
template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
operator==(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return bksge::equal(lhs.begin(), lhs.end(), rhs.begin());
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bksge::detail::synth3way_t<T>
operator<=>(array<T, N> const& lhs, array<T, N> const& rhs)
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if constexpr (N != 0 && detail::is_memcmp_ordered<T>::value)
	{
		if (!std::is_constant_evaluated())
		{
			constexpr std::size_t n = N * sizeof(T);
			return bksge::memcmp(lhs.data(), rhs.data(), n) <=> 0;
		}
	}
#endif

	for (std::size_t i = 0; i < N; ++i)
	{
		auto c = bksge::detail::synth3way(lhs[i], rhs[i]);
		if (c != 0)
		{
			return c;
		}
	}

	return bksge::detail::synth3way_t<T>::equal;
}

#else

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
operator!=(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return !(lhs == rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
operator<(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return bksge::lexicographical_compare(
		lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end());
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
operator>(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return rhs < lhs;
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
operator<=(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return !(lhs > rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
operator>=(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return !(lhs < rhs);
}

#endif

// Specialized algorithms.
template <typename T, std::size_t N,
	typename = bksge::enable_if_t<
		N == 0 || bksge::is_swappable<T>::value
	>
>
inline BKSGE_CXX14_CONSTEXPR void
swap(array<T, N>& lhs, array<T, N>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_ARRAY)

#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/config.hpp>

#if !defined(BKSGE_USE_STD_TUPLE) || !defined(BKSGE_USE_STD_ARRAY)

#include <bksge/fnd/type_traits/integral_constant.hpp>

namespace BKSGE_TUPLE_NAMESPACE
{

template <typename T, std::size_t N>
struct tuple_size<bksge::array<T, N>>
	: public bksge::integral_constant<std::size_t, N> {};

template <std::size_t I, typename T, std::size_t N>
struct tuple_element<I, bksge::array<T, N>>
{
	static_assert(I < N, "index is out of bounds");
	using type = T;
};

}	// namespace BKSGE_TUPLE_NAMESPACE

#endif

#endif // BKSGE_FND_ARRAY_ARRAY_HPP
