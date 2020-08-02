/**
 *	@file	ranges_test.hpp
 *
 *	@brief	
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_RANGES_TEST_HPP
#define UNIT_TEST_RANGES_TEST_HPP

#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include "iterator_test.hpp"

namespace
{

template <typename Iterator,
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bool = bksge::random_access_iterator<Iterator>
#else
	bool = bksge::random_access_iterator<Iterator>::value
#endif
>
struct test_sentinel
{
	Iterator m_it;

	BKSGE_CXX14_CONSTEXPR bool
	operator==(Iterator const& i) const noexcept
	{
		return m_it.m_ptr == i.m_ptr;
	}

	BKSGE_CXX14_CONSTEXPR bool
	operator!=(Iterator const& i) const noexcept
	{
		return !(*this == i);
	}

	friend BKSGE_CXX14_CONSTEXPR bool
	operator==(Iterator const& i, test_sentinel const& s) noexcept
	{
		return s == i;
	}

	friend BKSGE_CXX14_CONSTEXPR bool
	operator!=(Iterator const& i, test_sentinel const& s) noexcept
	{
		return !(i == s);
	}
};

template <typename Iterator>
struct test_sentinel<Iterator, true>
	: test_sentinel<Iterator, false>
{
	friend BKSGE_CXX14_CONSTEXPR auto
	operator-(test_sentinel const& s, Iterator const& i) noexcept
	->decltype(s.m_it.m_ptr - i.m_ptr)
	{
		return s.m_it.m_ptr - i.m_ptr;
	}

	friend BKSGE_CXX14_CONSTEXPR auto
	operator-(Iterator const& i, test_sentinel const& s) noexcept
	->decltype(i.m_ptr - s.m_it.m_ptr)
	{
		return i.m_ptr - s.m_it.m_ptr;
	}
};

template <typename T, template <typename> class Iterator>
struct test_range
{
	T* m_first;
	T* m_last;

	using iterator = Iterator<T>;
	using sentinel = test_sentinel<iterator>;

	BKSGE_CXX14_CONSTEXPR test_range(): m_first(nullptr), m_last(nullptr) {}
	BKSGE_CXX14_CONSTEXPR test_range(T* first, T* last) : m_first(first), m_last(last) {}
	BKSGE_CXX14_CONSTEXPR iterator begin() const { return iterator{m_first}; }
	BKSGE_CXX14_CONSTEXPR sentinel end()   const { return sentinel{iterator{m_last}}; }
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
	using test_range<T, Iterator>::test_range;

	BKSGE_CXX14_CONSTEXPR std::size_t size() const noexcept
	{
		return m_last - m_first;
	}
};

template <typename T> using test_contiguous_sized_range    = test_sized_range<T, contiguous_iterator_wrapper>;
template <typename T> using test_random_access_sized_range = test_sized_range<T, random_access_iterator_wrapper>;
template <typename T> using test_bidirectional_sized_range = test_sized_range<T, bidirectional_iterator_wrapper>;
template <typename T> using test_forward_sized_range       = test_sized_range<T, forward_iterator_wrapper>;
template <typename T> using test_input_sized_range         = test_sized_range<T, input_iterator_wrapper>;
template <typename T> using test_output_sized_range        = test_sized_range<T, output_iterator_wrapper>;

}	// namespace

#endif // UNIT_TEST_RANGES_TEST_HPP
