/**
 *	@file	static_vector.hpp
 *
 *	@brief	static_vector クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_VECTOR_STATIC_VECTOR_HPP
#define BKSGE_FND_STATIC_VECTOR_STATIC_VECTOR_HPP

#include <bksge/fnd/static_vector/detail/static_vector_base.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/initializer_list.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, bksge::size_t Capacity>
class static_vector
	: private detail::static_vector_base<T, Capacity>
{
private:
	using base_t = detail::static_vector_base<T, Capacity>;

public:
	using allocator_type         = typename base_t::allocator_type;
	using value_type             = typename base_t::value_type;
	using reference              = typename base_t::reference;
	using const_reference        = typename base_t::const_reference;
	using size_type              = typename base_t::size_type;
	using difference_type        = typename base_t::difference_type;
	using pointer                = typename base_t::pointer;
	using const_pointer          = typename base_t::const_pointer;
	using iterator               = pointer;
	using const_iterator         = const_pointer;
	using reverse_iterator       = bksge::reverse_iterator<iterator>;
	using const_reverse_iterator = bksge::reverse_iterator<const_iterator>;

	static const size_type static_capacity = Capacity;

	BKSGE_CXX14_CONSTEXPR static_vector() BKSGE_NOEXCEPT;

	explicit BKSGE_CXX14_CONSTEXPR static_vector(size_type count);

	BKSGE_CXX14_CONSTEXPR static_vector(size_type count, value_type const& value);

	template <
		typename InputIterator,
		typename = bksge::enable_if_t<
			bksge::is_input_iterator<InputIterator>::value
		>
	>
	BKSGE_CXX14_CONSTEXPR static_vector(InputIterator first, InputIterator last);

	BKSGE_CXX14_CONSTEXPR static_vector(static_vector const& other);

	BKSGE_CXX14_CONSTEXPR static_vector(static_vector&& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<value_type>::value);

	BKSGE_CXX14_CONSTEXPR static_vector(bksge::initializer_list<value_type> il);

	//BKSGE_CXX20_CONSTEXPR ~static_vector();

	BKSGE_CXX14_CONSTEXPR static_vector& operator=(static_vector const& other);

	BKSGE_CXX14_CONSTEXPR static_vector& operator=(static_vector&& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_assignable<value_type>::value);

	BKSGE_CXX14_CONSTEXPR static_vector& operator=(bksge::initializer_list<value_type> il);

	BKSGE_CXX14_CONSTEXPR void assign(size_type count, value_type const& value);

	template <
		typename InputIterator,
		typename = bksge::enable_if_t<
			bksge::is_input_iterator<InputIterator>::value
		>
	>
	BKSGE_CXX14_CONSTEXPR void assign(InputIterator first, InputIterator last);

	BKSGE_CXX14_CONSTEXPR void assign(bksge::initializer_list<value_type> il);

	//BKSGE_CXX20_CONSTEXPR allocator_type get_allocator() const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR reference       at(size_type pos);
	BKSGE_CXX14_CONSTEXPR const_reference at(size_type pos) const;

	BKSGE_CXX14_CONSTEXPR reference       operator[](size_type pos);
	BKSGE_CXX14_CONSTEXPR const_reference operator[](size_type pos) const;

	BKSGE_CXX14_CONSTEXPR reference       front();
	BKSGE_CXX14_CONSTEXPR const_reference front() const;

	BKSGE_CXX14_CONSTEXPR reference       back();
	BKSGE_CXX14_CONSTEXPR const_reference back() const;

	BKSGE_CXX14_CONSTEXPR value_type*       data()       BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR value_type const* data() const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR iterator       begin()       BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR const_iterator begin() const BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR iterator       end()         BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR const_iterator end()   const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR reverse_iterator       rbegin()       BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR const_reverse_iterator rbegin() const BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR reverse_iterator       rend()         BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR const_reverse_iterator rend()   const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR const_iterator cbegin() const BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR const_iterator cend()   const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR const_reverse_iterator crbegin() const BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR const_reverse_iterator crend()   const BKSGE_NOEXCEPT;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR bool empty() const BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR size_type size() const BKSGE_NOEXCEPT;

	static BKSGE_CXX14_CONSTEXPR size_type max_size() BKSGE_NOEXCEPT
	{
		return static_capacity;
	}

	static BKSGE_CXX14_CONSTEXPR size_type capacity() BKSGE_NOEXCEPT
	{
		return static_capacity;
	}

	BKSGE_CXX14_CONSTEXPR void reserve(size_type new_cap);

	BKSGE_CXX14_CONSTEXPR void shrink_to_fit();

	BKSGE_CXX14_CONSTEXPR void clear() BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR iterator insert(const_iterator pos, const_reference value);
	BKSGE_CXX14_CONSTEXPR iterator insert(const_iterator pos, value_type&& value);
	BKSGE_CXX14_CONSTEXPR iterator insert(const_iterator pos, size_type count, const_reference value);

	template <
		typename InputIterator,
		typename = bksge::enable_if_t<
			bksge::is_input_iterator<InputIterator>::value
		>
	>
	BKSGE_CXX14_CONSTEXPR iterator insert(const_iterator pos, InputIterator first, InputIterator last);

	BKSGE_CXX14_CONSTEXPR iterator insert(const_iterator pos, bksge::initializer_list<value_type> il);

	template <typename... Args>
	BKSGE_CXX14_CONSTEXPR iterator emplace(const_iterator pos, Args&&... args);

	BKSGE_CXX14_CONSTEXPR iterator erase(const_iterator pos);
	BKSGE_CXX14_CONSTEXPR iterator erase(const_iterator first, const_iterator last);

	BKSGE_CXX14_CONSTEXPR void push_back(const_reference value);
	BKSGE_CXX14_CONSTEXPR void push_back(value_type&& value);

	template <typename... Args>
	BKSGE_CXX14_CONSTEXPR reference emplace_back(Args&&... args);

	BKSGE_CXX14_CONSTEXPR void pop_back();

	BKSGE_CXX14_CONSTEXPR void resize(size_type count);
	BKSGE_CXX14_CONSTEXPR void resize(size_type count, value_type const& value);

	BKSGE_CXX14_CONSTEXPR void swap(static_vector& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<value_type>::value);
};

template <typename T, bksge::size_t C>
BKSGE_CXX14_CONSTEXPR void swap(static_vector<T, C>& lhs, static_vector<T, C>& rhs)
	BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs));

template <typename T, bksge::size_t C>
BKSGE_CXX14_CONSTEXPR bool operator==(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs);

template <typename T, bksge::size_t C>
BKSGE_CXX14_CONSTEXPR bool operator!=(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs);

template <typename T, bksge::size_t C>
BKSGE_CXX14_CONSTEXPR bool operator<(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs);

template <typename T, bksge::size_t C>
BKSGE_CXX14_CONSTEXPR bool operator<=(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs);

template <typename T, bksge::size_t C>
BKSGE_CXX14_CONSTEXPR bool operator>(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs);

template <typename T, bksge::size_t C>
BKSGE_CXX14_CONSTEXPR bool operator>=(static_vector<T, C> const& lhs, static_vector<T, C> const& rhs);

template <typename T, bksge::size_t C, typename U>
BKSGE_CXX14_CONSTEXPR typename static_vector<T, C>::size_type
erase(static_vector<T, C>& c, U const& value);

template <typename T, bksge::size_t C, typename Pred>
BKSGE_CXX14_CONSTEXPR typename static_vector<T, C>::size_type
erase_if(static_vector<T, C>& c, Pred pred);

}	// namespace bksge

#include <bksge/fnd/static_vector/inl/static_vector_inl.hpp>

#endif // BKSGE_FND_STATIC_VECTOR_STATIC_VECTOR_HPP
