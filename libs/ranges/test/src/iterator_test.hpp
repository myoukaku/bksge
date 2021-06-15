/**
 *	@file	iterator_test.hpp
 *
 *	@brief	
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_ITERATOR_TEST_HPP
#define UNIT_TEST_ITERATOR_TEST_HPP

#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge_iterator_test
{

template <typename T>
struct weakly_incrementable_wrapper
{
	using difference_type = bksge::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR weakly_incrementable_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR void                          operator++(int);
};

template <typename T>
struct incrementable_wrapper
{
	using difference_type = bksge::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR incrementable_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR incrementable_wrapper  operator++(int);
	BKSGE_CXX14_CONSTEXPR bool operator==(const incrementable_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator!=(const incrementable_wrapper&) const;
};

template <typename T>
struct indirectly_readable_wrapper
{
	T*	m_ptr;
	using value_type = T;
	BKSGE_CXX14_CONSTEXPR T const& operator*() const { return *m_ptr; }
};

template <typename T>
struct indirectly_writable_wrapper
{
	T*	m_ptr;
	BKSGE_CXX14_CONSTEXPR T& operator*() const { return *m_ptr; }
};

template <typename T>
struct input_or_output_iterator_wrapper
{
	T*	m_ptr;
	using difference_type = bksge::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR input_or_output_iterator_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR void                              operator++(int);
	BKSGE_CXX14_CONSTEXPR T                                 operator*();
};

template <typename T>
struct input_iterator_wrapper
{
	T*	m_ptr;
	using iterator_category = bksge::input_iterator_tag;
	using value_type        = T;
	using difference_type   = bksge::ptrdiff_t;
	using reference         = T&;
	BKSGE_CXX14_CONSTEXPR input_iterator_wrapper& operator++() { ++m_ptr; return *this; }
	BKSGE_CXX14_CONSTEXPR void                    operator++(int) { ++m_ptr; }
	BKSGE_CXX14_CONSTEXPR T&                      operator*() const { return *m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator==(const input_iterator_wrapper& rhs) const { return m_ptr == rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator!=(const input_iterator_wrapper& rhs) const { return !(*this == rhs); }
};

template <typename T>
struct output_iterator_wrapper
{
	T*	m_ptr;
	using iterator_category = bksge::output_iterator_tag;
	using difference_type   = bksge::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR output_iterator_wrapper& operator++() { ++m_ptr; return *this; }
	BKSGE_CXX14_CONSTEXPR output_iterator_wrapper  operator++(int) { auto t = *this; ++m_ptr; return t; }
	BKSGE_CXX14_CONSTEXPR T&                       operator*() const { return *m_ptr; }
};

template <typename T>
struct forward_iterator_wrapper
{
	T*	m_ptr;
	using iterator_category = bksge::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = bksge::ptrdiff_t;
	using reference         = T&;
	BKSGE_CXX14_CONSTEXPR forward_iterator_wrapper& operator++() { ++m_ptr; return *this; }
	BKSGE_CXX14_CONSTEXPR forward_iterator_wrapper  operator++(int) { auto t = *this; ++m_ptr; return t; }
	BKSGE_CXX14_CONSTEXPR T&                        operator*() const { return *m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator==(const forward_iterator_wrapper& rhs) const { return m_ptr == rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator!=(const forward_iterator_wrapper& rhs) const { return !(*this == rhs); }
};

template <typename T>
struct bidirectional_iterator_wrapper
{
	T*	m_ptr;
	using iterator_category = bksge::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = bksge::ptrdiff_t;
	using reference         = T&;
	BKSGE_CXX14_CONSTEXPR bidirectional_iterator_wrapper& operator++() { ++m_ptr; return *this; }
	BKSGE_CXX14_CONSTEXPR bidirectional_iterator_wrapper  operator++(int) { auto t = *this; ++m_ptr; return t; }
	BKSGE_CXX14_CONSTEXPR bidirectional_iterator_wrapper& operator--() { --m_ptr; return *this; }
	BKSGE_CXX14_CONSTEXPR bidirectional_iterator_wrapper  operator--(int);
	BKSGE_CXX14_CONSTEXPR T&                              operator*() const { return *m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator==(const bidirectional_iterator_wrapper& rhs) const { return m_ptr == rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator!=(const bidirectional_iterator_wrapper& rhs) const { return !(*this == rhs); }
};

template <typename T>
struct random_access_iterator_wrapper
{
	T*	m_ptr;
	using iterator_category = bksge::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = bksge::ptrdiff_t;
	using reference         = T&;
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper& operator++() { ++m_ptr; return *this; }
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper  operator++(int) { auto t = *this; ++m_ptr; return t; }
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper& operator+=(difference_type n) { m_ptr += n; return *this; }
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper  operator+(difference_type n) const { return {m_ptr + n}; }
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper& operator--() { --m_ptr; return *this; }
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper  operator--(int) { auto t = *this; --m_ptr; return t; }
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper& operator-=(difference_type n) { m_ptr += n; return *this; }
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper  operator-(difference_type n) const { return {m_ptr - n}; }
	BKSGE_CXX14_CONSTEXPR difference_type                 operator-(random_access_iterator_wrapper const& rhs) const { return m_ptr - rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR T&                              operator*() const { return *m_ptr; }
	BKSGE_CXX14_CONSTEXPR T&                              operator[](difference_type i) const { return m_ptr[i]; }
	BKSGE_CXX14_CONSTEXPR bool operator==(const random_access_iterator_wrapper& rhs) const { return m_ptr == rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator!=(const random_access_iterator_wrapper& rhs) const { return m_ptr != rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator< (const random_access_iterator_wrapper& rhs) const { return m_ptr <  rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator> (const random_access_iterator_wrapper& rhs) const { return m_ptr >  rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator<=(const random_access_iterator_wrapper& rhs) const { return m_ptr <= rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator>=(const random_access_iterator_wrapper& rhs) const { return m_ptr >= rhs.m_ptr; }
};

template <typename T>
BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper<T>
operator+(bksge::ptrdiff_t, random_access_iterator_wrapper<T> const&);

template <typename T>
struct contiguous_iterator_wrapper
{
	T*	m_ptr;
	using iterator_concept  = bksge::contiguous_iterator_tag;
	using iterator_category = bksge::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = bksge::ptrdiff_t;
	using reference         = T&;
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper& operator++() { ++m_ptr; return *this; }
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper  operator++(int) { auto t = *this; ++m_ptr; return t; }
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper& operator+=(difference_type n) { m_ptr += n; return *this; }
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper  operator+(difference_type n) const { return {m_ptr + n}; }
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper& operator--() { --m_ptr; return *this; }
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper  operator--(int) { auto t = *this; --m_ptr; return t; }
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper& operator-=(difference_type n) { m_ptr -= n; return *this; }
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper  operator-(difference_type n) const { return {m_ptr - n}; }
	BKSGE_CXX14_CONSTEXPR difference_type              operator-(contiguous_iterator_wrapper const& rhs) const { return m_ptr - rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR T&                           operator*() const { return *m_ptr; }
	BKSGE_CXX14_CONSTEXPR T&                           operator[](difference_type i) const { return m_ptr[i]; }
	BKSGE_CXX14_CONSTEXPR T*                           operator->() const { return m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator==(const contiguous_iterator_wrapper& rhs) const { return m_ptr == rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator!=(const contiguous_iterator_wrapper& rhs) const { return m_ptr != rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator< (const contiguous_iterator_wrapper& rhs) const { return m_ptr <  rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator> (const contiguous_iterator_wrapper& rhs) const { return m_ptr >  rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator<=(const contiguous_iterator_wrapper& rhs) const { return m_ptr <= rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator>=(const contiguous_iterator_wrapper& rhs) const { return m_ptr >= rhs.m_ptr; }
};

template <typename T>
BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper<T>
operator+(bksge::ptrdiff_t, contiguous_iterator_wrapper<T> const&);

}	// namespace bksge_iterator_test

using namespace bksge_iterator_test;

#endif // UNIT_TEST_ITERATOR_TEST_HPP
