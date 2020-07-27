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
#include <cstddef>

namespace
{

template <typename T>
struct weakly_incrementable_wrapper
{
	using difference_type = std::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR weakly_incrementable_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR void                          operator++(int);
};

template <typename T>
struct incrementable_wrapper
{
	using difference_type = std::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR incrementable_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR incrementable_wrapper  operator++(int);
	BKSGE_CXX14_CONSTEXPR bool operator==(const incrementable_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator!=(const incrementable_wrapper&) const;
};

template <typename T>
struct indirectly_readable_wrapper
{
	using value_type = T;
	BKSGE_CXX14_CONSTEXPR T const& operator*() const;
};

template <typename T>
struct indirectly_writable_wrapper
{
	BKSGE_CXX14_CONSTEXPR T& operator*() const;
};

template <typename T>
struct input_or_output_iterator_wrapper
{
	T*	m_ptr;
	using difference_type = std::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR input_or_output_iterator_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR void                              operator++(int);
	BKSGE_CXX14_CONSTEXPR T                                 operator*();
};

template <typename T>
struct input_iterator_wrapper
{
	T*	m_ptr;
	using value_type      = T;
	using difference_type = std::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR input_iterator_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR void                    operator++(int);
	BKSGE_CXX14_CONSTEXPR T&                      operator*() const;
};

template <typename T>
struct output_iterator_wrapper
{
	T*	m_ptr;
	using difference_type = std::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR output_iterator_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR output_iterator_wrapper  operator++(int);
	BKSGE_CXX14_CONSTEXPR T&                       operator*() const;
};

template <typename T>
struct forward_iterator_wrapper
{
	T*	m_ptr;
	using value_type      = T;
	using difference_type = std::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR forward_iterator_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR forward_iterator_wrapper  operator++(int);
	BKSGE_CXX14_CONSTEXPR T&                        operator*() const;
	BKSGE_CXX14_CONSTEXPR bool operator==(const forward_iterator_wrapper& rhs) const { return m_ptr == rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator!=(const forward_iterator_wrapper& rhs) const { return !(*this == rhs); }
};

template <typename T>
struct bidirectional_iterator_wrapper
{
	T*	m_ptr;
	using value_type      = T;
	using difference_type = std::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR bidirectional_iterator_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR bidirectional_iterator_wrapper  operator++(int);
	BKSGE_CXX14_CONSTEXPR bidirectional_iterator_wrapper& operator--();
	BKSGE_CXX14_CONSTEXPR bidirectional_iterator_wrapper  operator--(int);
	BKSGE_CXX14_CONSTEXPR T&                              operator*() const;
	BKSGE_CXX14_CONSTEXPR bool operator==(const bidirectional_iterator_wrapper& rhs) const { return m_ptr == rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator!=(const bidirectional_iterator_wrapper& rhs) const { return !(*this == rhs); }
};

template <typename T>
struct random_access_iterator_wrapper
{
	T*	m_ptr;
	using value_type      = T;
	using difference_type = std::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper  operator++(int);
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper& operator+=(difference_type);
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper  operator+(difference_type) const;
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper& operator--();
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper  operator--(int);
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper& operator-=(difference_type);
	BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper  operator-(difference_type) const;
	BKSGE_CXX14_CONSTEXPR difference_type                 operator-(random_access_iterator_wrapper const& rhs) const { return m_ptr - rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR T&                              operator*() const;
	BKSGE_CXX14_CONSTEXPR T&                              operator[](difference_type) const;
	BKSGE_CXX14_CONSTEXPR bool operator==(const random_access_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator!=(const random_access_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator< (const random_access_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator> (const random_access_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator<=(const random_access_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator>=(const random_access_iterator_wrapper&) const;
};

template <typename T>
BKSGE_CXX14_CONSTEXPR random_access_iterator_wrapper<T>
operator+(std::ptrdiff_t, random_access_iterator_wrapper<T> const&);

template <typename T>
struct contiguous_iterator_wrapper
{
	T*	m_ptr;
	using iterator_concept = bksge::contiguous_iterator_tag;
	using value_type      = T;
	using difference_type = std::ptrdiff_t;
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper& operator++();
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper  operator++(int);
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper& operator+=(difference_type);
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper  operator+(difference_type) const;
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper& operator--();
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper  operator--(int);
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper& operator-=(difference_type);
	BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper  operator-(difference_type) const;
	BKSGE_CXX14_CONSTEXPR difference_type              operator-(contiguous_iterator_wrapper const& rhs) const { return m_ptr - rhs.m_ptr; }
	BKSGE_CXX14_CONSTEXPR T&                           operator*() const { return *m_ptr; }
	BKSGE_CXX14_CONSTEXPR T&                           operator[](difference_type i) const { return m_ptr[i]; }
	BKSGE_CXX14_CONSTEXPR T*                           operator->() const { return m_ptr; }
	BKSGE_CXX14_CONSTEXPR bool operator==(const contiguous_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator!=(const contiguous_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator< (const contiguous_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator> (const contiguous_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator<=(const contiguous_iterator_wrapper&) const;
	BKSGE_CXX14_CONSTEXPR bool operator>=(const contiguous_iterator_wrapper&) const;
};

template <typename T>
BKSGE_CXX14_CONSTEXPR contiguous_iterator_wrapper<T>
operator+(std::ptrdiff_t, contiguous_iterator_wrapper<T> const&);

}	// namespace

#endif // UNIT_TEST_ITERATOR_TEST_HPP
