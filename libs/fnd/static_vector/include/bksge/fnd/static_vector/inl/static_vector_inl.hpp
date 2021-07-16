/**
 *	@file	static_vector_inl.hpp
 *
 *	@brief	static_vector クラステンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_VECTOR_INL_STATIC_VECTOR_INL_HPP
#define BKSGE_FND_STATIC_VECTOR_INL_STATIC_VECTOR_INL_HPP

#include <bksge/fnd/static_vector/static_vector.hpp>
#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/algorithm/lexicographical_compare.hpp>
#include <bksge/fnd/algorithm/remove.hpp>
#include <bksge/fnd/algorithm/remove_if.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/make_move_iterator.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>
#include <initializer_list>
#include <cstddef>
#include <utility>

namespace bksge
{

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR
static_vector<T, C>::static_vector() BKSGE_NOEXCEPT
{
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR
static_vector<T, C>::static_vector(size_type count)
{
	base_t::emplace_back_n(count);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR
static_vector<T, C>::static_vector(size_type count, value_type const& value)
{
	base_t::push_back_n(count, value);
}

template <typename T, std::size_t C>
template <typename InputIterator, typename>
inline BKSGE_CXX14_CONSTEXPR
static_vector<T, C>::static_vector(InputIterator first, InputIterator last)
{
	base_t::push_back_iter(first, last);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR
static_vector<T, C>::static_vector(static_vector const& other)
{
	base_t::push_back_iter(other.begin(), other.end());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR
static_vector<T, C>::static_vector(static_vector&& other)
	BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<value_type>::value)
{
	base_t::push_back_iter(
		bksge::make_move_iterator(other.begin()),
		bksge::make_move_iterator(other.end()));
	other.clear();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR
static_vector<T, C>::static_vector(std::initializer_list<value_type> il)
	: static_vector(il.begin(), il.end())
{
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::operator=(static_vector const& other) -> static_vector&
{
	if (&other != this)
	{
		assign(other.begin(), other.end());
	}

	return *this;
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::operator=(static_vector&& other)
	BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_assignable<value_type>::value) -> static_vector&
{
	if (&other != this)
	{
		assign(
			bksge::make_move_iterator(other.begin()),
			bksge::make_move_iterator(other.end()));
		other.clear();
	}

	return *this;
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::operator=(std::initializer_list<value_type> il)
 -> static_vector&
{
	assign(il);
	return *this;
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::assign(size_type count, value_type const& value)
{
	clear();
	base_t::push_back_n(count, value);
}

template <typename T, std::size_t C>
template <typename InputIterator, typename>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::assign(InputIterator first, InputIterator last)
{
	clear();
	for (; first != last; ++first)
	{
		emplace_back(*first);
	}
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::assign(std::initializer_list<value_type> il)
{
	assign(il.begin(), il.end());
}

//BKSGE_CXX20_CONSTEXPR allocator_type get_allocator() const BKSGE_NOEXCEPT;

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::at(size_type pos) -> reference
{
	if (pos >= size())
	{
		bksge::throw_out_of_range("static_vector");
	}

	return base_t::begin()[pos];
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::at(size_type pos) const -> const_reference
{
	if (pos >= size())
	{
		bksge::throw_out_of_range("static_vector");
	}

	return base_t::begin()[pos];
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::operator[](size_type pos) -> reference
{
	BKSGE_ASSERT_MSG(pos < size(), "static_vector[] index out of bounds");
	return base_t::begin()[pos];
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::operator[](size_type pos) const -> const_reference
{
	BKSGE_ASSERT_MSG(pos < size(), "static_vector[] index out of bounds");
	return base_t::begin()[pos];
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::front() -> reference
{
	BKSGE_ASSERT_MSG(!empty(), "front() called for empty vector");
	return *base_t::begin();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::front() const -> const_reference
{
	BKSGE_ASSERT_MSG(!empty(), "front() called for empty vector");
	return *base_t::begin();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::back() -> reference
{
	BKSGE_ASSERT_MSG(!empty(), "back() called for empty vector");
	return *(base_t::end() - 1);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::back() const -> const_reference
{
	BKSGE_ASSERT_MSG(!empty(), "back() called for empty vector");
	return *(base_t::end() - 1);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::data() BKSGE_NOEXCEPT -> value_type*
{
	return base_t::begin();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::data() const BKSGE_NOEXCEPT -> value_type const*
{
	return base_t::begin();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::begin() BKSGE_NOEXCEPT -> iterator
{
	return iterator(base_t::begin());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::begin() const BKSGE_NOEXCEPT -> const_iterator
{
	return const_iterator(base_t::begin());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::end() BKSGE_NOEXCEPT -> iterator
{
	return iterator(base_t::end());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::end() const BKSGE_NOEXCEPT -> const_iterator
{
	return const_iterator(base_t::end());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::rbegin() BKSGE_NOEXCEPT -> reverse_iterator
{
	return reverse_iterator(end());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::rbegin() const BKSGE_NOEXCEPT -> const_reverse_iterator
{
	return const_reverse_iterator(end());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::rend() BKSGE_NOEXCEPT -> reverse_iterator
{
	return reverse_iterator(begin());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::rend() const BKSGE_NOEXCEPT -> const_reverse_iterator
{
	return const_reverse_iterator(begin());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::cbegin() const BKSGE_NOEXCEPT -> const_iterator
{
	return begin();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::cend() const BKSGE_NOEXCEPT -> const_iterator
{
	return end();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::crbegin() const BKSGE_NOEXCEPT -> const_reverse_iterator
{
	return rbegin();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::crend()   const BKSGE_NOEXCEPT -> const_reverse_iterator
{
	return rend();
}

template <typename T, std::size_t C>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR bool
static_vector<T, C>::empty() const BKSGE_NOEXCEPT
{
	return size() == 0;
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::size() const BKSGE_NOEXCEPT -> size_type
{
	return base_t::size();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::reserve(size_type new_cap)
{
	base_t::reserve(new_cap);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::shrink_to_fit()
{
	// do nothing
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::clear() BKSGE_NOEXCEPT
{
	base_t::clear();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::insert(const_iterator pos, const_reference value) -> iterator
{
	pointer p = base_t::begin() + (pos - cbegin());
	base_t::insert_n(p, 1, value);
	return iterator(p);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::insert(const_iterator pos, value_type&& value) -> iterator
{
	pointer p = base_t::begin() + (pos - cbegin());
	base_t::emplace(p, 1, std::move(value));
	return iterator(p);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::insert(const_iterator pos, size_type count, const_reference value)
-> iterator
{
	pointer p = base_t::begin() + (pos - cbegin());
	base_t::insert_n(p, count, value);
	return iterator(p);
}

template <typename T, std::size_t C>
template <typename InputIterator, typename>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::insert(const_iterator pos, InputIterator first, InputIterator last)
-> iterator
{
	pointer p = base_t::begin() + (pos - cbegin());
	base_t::insert_iter(p, first, last);
	return iterator(p);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::insert(const_iterator pos, std::initializer_list<value_type> il)
-> iterator
{
	return insert(pos, il.begin(), il.end());
}

template <typename T, std::size_t C>
template <typename... Args>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::emplace(const_iterator pos, Args&&... args) -> iterator
{
	pointer p = base_t::begin() + (pos - cbegin());
	base_t::emplace(p, 1, bksge::forward<Args>(args)...);
	return iterator(p);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::erase(const_iterator pos) -> iterator
{
	BKSGE_ASSERT_MSG(pos != end(), "vector::erase(iterator) called with a non-dereferenceable iterator");
	pointer p = base_t::begin() + (pos - cbegin());
	bksge::move(p + 1, base_t::end(), p);
	base_t::pop_back_n(1);
	return iterator(p);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::erase(const_iterator first, const_iterator last) -> iterator
{
	BKSGE_ASSERT_MSG(first <= last, "vector::erase(first, last) called with invalid range");
	pointer p = base_t::begin() + (first - cbegin());
	if (first != last)
	{
		bksge::move(p + (last - first), base_t::end(), p);
		base_t::pop_back_n(last - first);
	}
	return iterator(p);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::push_back(const_reference value)
{
	base_t::push_back_n(1, value);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::push_back(value_type&& value)
{
	base_t::emplace_back_n(1, std::move(value));
}

template <typename T, std::size_t C>
template <typename... Args>
inline BKSGE_CXX14_CONSTEXPR auto
static_vector<T, C>::emplace_back(Args&&... args) -> reference
{
	base_t::emplace_back_n(1, bksge::forward<Args>(args)...);
	return back();
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::pop_back()
{
    BKSGE_ASSERT_MSG(!empty(), "static_vector::pop_back called for empty vector");
	base_t::pop_back_n(1);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::resize(size_type count)
{
	size_type current_size = size();
	if (current_size < count)
	{
		base_t::emplace_back_n(count - current_size);
	}
	else if (current_size > count)
	{
		base_t::pop_back_n(current_size - count);
	}
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::resize(size_type count, value_type const& value)
{
	size_type current_size = size();
	if (current_size < count)
	{
		base_t::push_back_n(count - current_size, value);
	}
	else if (current_size > count)
	{
		base_t::pop_back_n(current_size - count);
	}
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
static_vector<T, C>::swap(static_vector& other)
	BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<value_type>::value)
{
	static_vector tmp(std::move(other));
	other = std::move(*this);
	*this = std::move(tmp);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR void
swap(static_vector<T, C>& lhs, static_vector<T, C>& rhs)
	BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR bool
operator==(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs)
{
	return bksge::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR bool
operator!=(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs)
{
	return !(lhs == rhs);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR bool
operator<(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs)
{
	return bksge::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR bool
operator>(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs)
{
	return rhs < lhs;
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR bool
operator<=(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs)
{
	return !(rhs < lhs);
}

template <typename T, std::size_t C>
inline BKSGE_CXX14_CONSTEXPR bool
operator>=(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs)
{
	return !(lhs < rhs);
}

template <typename T, std::size_t C, typename U>
inline BKSGE_CXX14_CONSTEXPR typename static_vector<T, C>::size_type
erase(static_vector<T, C>& c, U const& value)
{
	auto it = bksge::remove(c.begin(), c.end(), value);
	auto r = bksge::distance(it, c.end());
	c.erase(it, c.end());
	return r;
}

template <typename T, std::size_t C, typename Pred>
inline BKSGE_CXX14_CONSTEXPR typename static_vector<T, C>::size_type
erase_if(static_vector<T, C>& c, Pred pred)
{
	auto it = bksge::remove_if(c.begin(), c.end(), pred);
	auto r = bksge::distance(it, c.end());
	c.erase(it, c.end());
	return r;
}

}	// namespace bksge

#endif // BKSGE_FND_STATIC_VECTOR_INL_STATIC_VECTOR_INL_HPP
