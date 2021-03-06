﻿/**
 *	@file	ranges_test.hpp
 *
 *	@brief	
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_RANGES_TEST_HPP
#define UNIT_TEST_RANGES_TEST_HPP

#include <bksge/fnd/ranges/views/view_base.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include "iterator_test.hpp"

namespace bksge_ranges_test
{

template <typename T, template <typename> class Iterator>
struct test_container
{
	T* m_first;
	T* m_last;

	using iterator = Iterator<T>;

	BKSGE_CONSTEXPR test_container() : m_first(nullptr), m_last(nullptr) {}
	BKSGE_CONSTEXPR test_container(T* first, T* last) : m_first(first), m_last(last) {}

	BKSGE_CONSTEXPR test_container(test_container const&) = default;
	BKSGE_CONSTEXPR test_container(test_container &&) = default;

	BKSGE_CXX14_CONSTEXPR test_container& operator=(test_container const&) = default;
	BKSGE_CXX14_CONSTEXPR test_container& operator=(test_container &&) = default;

	template <bksge::size_t N>
	explicit BKSGE_CONSTEXPR test_container(T (&arr)[N]) : test_container(arr, arr+N) {}

	BKSGE_CONSTEXPR iterator begin() const { return iterator{m_first}; }
	BKSGE_CONSTEXPR iterator end()   const { return iterator{m_last}; }
};


template <typename Iterator>
struct test_sentinel
{
	Iterator m_it;

	BKSGE_CONSTEXPR bool
	operator==(Iterator const& i) const noexcept
	{
		return m_it.m_ptr == i.m_ptr;
	}

	BKSGE_CONSTEXPR bool
	operator!=(Iterator const& i) const noexcept
	{
		return !(*this == i);
	}
};

template <typename Iterator>
BKSGE_CONSTEXPR bool
operator==(Iterator const& i, test_sentinel<Iterator> const& s) noexcept
{
	return s == i;
}

template <typename Iterator>
BKSGE_CONSTEXPR bool
operator!=(Iterator const& i, test_sentinel<Iterator> const& s) noexcept
{
	return !(i == s);
}

template <BKSGE_REQUIRES_PARAM(bksge::random_access_iterator, Iterator)>
BKSGE_CONSTEXPR auto
operator-(test_sentinel<Iterator> const& s, Iterator const& i) noexcept
->decltype(s.m_it.m_ptr - i.m_ptr)
{
	return s.m_it.m_ptr - i.m_ptr;
}

template <BKSGE_REQUIRES_PARAM(bksge::random_access_iterator, Iterator)>
BKSGE_CONSTEXPR auto
operator-(Iterator const& i, test_sentinel<Iterator> const& s) noexcept
->decltype(i.m_ptr - s.m_it.m_ptr)
{
	return i.m_ptr - s.m_it.m_ptr;
}

template <typename T, template <typename> class Iterator>
struct test_range
{
	T* m_first;
	T* m_last;

	using iterator = Iterator<T>;
	using sentinel = test_sentinel<iterator>;

	BKSGE_CONSTEXPR test_range() : m_first(nullptr), m_last(nullptr) {}
	BKSGE_CONSTEXPR test_range(T* first, T* last) : m_first(first), m_last(last) {}

	BKSGE_CONSTEXPR test_range(test_range const&) = default;
	BKSGE_CONSTEXPR test_range(test_range &&) = default;

	BKSGE_CXX14_CONSTEXPR test_range& operator=(test_range const&) = default;
	BKSGE_CXX14_CONSTEXPR test_range& operator=(test_range &&) = default;

	template <bksge::size_t N>
	explicit BKSGE_CONSTEXPR test_range(T (&arr)[N]) : test_range(arr, arr+N) {}

	BKSGE_CONSTEXPR iterator begin() const { return iterator{m_first}; }
	BKSGE_CONSTEXPR sentinel end()   const { return sentinel{iterator{m_last}}; }
};

template <typename T> using test_contiguous_range    = test_range<T, contiguous_iterator_wrapper>;
template <typename T> using test_random_access_range = test_range<T, random_access_iterator_wrapper>;
template <typename T> using test_bidirectional_range = test_range<T, bidirectional_iterator_wrapper>;
template <typename T> using test_forward_range       = test_range<T, forward_iterator_wrapper>;
template <typename T> using test_input_range         = test_range<T, input_iterator_wrapper>;
template <typename T> using test_output_range        = test_range<T, output_iterator_wrapper>;

template <typename T, template <typename> class Iterator>
struct test_sized_range : public test_range<T, Iterator>
{
	using base_t = test_range<T, Iterator>;
	using test_range<T, Iterator>::test_range;

	BKSGE_CONSTEXPR bksge::size_t size() const noexcept
	{
		return base_t::m_last - base_t::m_first;
	}
};

template <typename T> using test_contiguous_sized_range    = test_sized_range<T, contiguous_iterator_wrapper>;
template <typename T> using test_random_access_sized_range = test_sized_range<T, random_access_iterator_wrapper>;
template <typename T> using test_bidirectional_sized_range = test_sized_range<T, bidirectional_iterator_wrapper>;
template <typename T> using test_forward_sized_range       = test_sized_range<T, forward_iterator_wrapper>;
template <typename T> using test_input_sized_range         = test_sized_range<T, input_iterator_wrapper>;
template <typename T> using test_output_sized_range        = test_sized_range<T, output_iterator_wrapper>;

template <typename T, bksge::size_t N, template <typename> class Iterator>
struct test_static_sized_range : public test_range<T, Iterator>
{
	using test_range<T, Iterator>::test_range;

	static BKSGE_CONSTEXPR bksge::size_t size() noexcept
	{
		return N;
	}
};

template <typename T, bksge::size_t N> using test_contiguous_static_sized_range    = test_static_sized_range<T, N, contiguous_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_random_access_static_sized_range = test_static_sized_range<T, N, random_access_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_bidirectional_static_sized_range = test_static_sized_range<T, N, bidirectional_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_forward_static_sized_range       = test_static_sized_range<T, N, forward_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_input_static_sized_range         = test_static_sized_range<T, N, input_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_output_static_sized_range        = test_static_sized_range<T, N, output_iterator_wrapper>;

template <typename T, bksge::size_t N, template <typename> class Iterator>
struct test_static_sized_view : public test_static_sized_range<T, N, Iterator>, bksge::ranges::view_base
{
	using test_static_sized_range<T, N, Iterator>::test_static_sized_range;
};

template <typename T, bksge::size_t N> using test_contiguous_static_sized_view    = test_static_sized_view<T, N, contiguous_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_random_access_static_sized_view = test_static_sized_view<T, N, random_access_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_bidirectional_static_sized_view = test_static_sized_view<T, N, bidirectional_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_forward_static_sized_view       = test_static_sized_view<T, N, forward_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_input_static_sized_view         = test_static_sized_view<T, N, input_iterator_wrapper>;
template <typename T, bksge::size_t N> using test_output_static_sized_view        = test_static_sized_view<T, N, output_iterator_wrapper>;

}	// namespace bksge_ranges_test

using namespace bksge_ranges_test;

#endif // UNIT_TEST_RANGES_TEST_HPP
