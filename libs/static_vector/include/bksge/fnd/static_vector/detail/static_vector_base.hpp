/**
 *	@file	static_vector_base.hpp
 *
 *	@brief	static_vector_base クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_VECTOR_DETAIL_STATIC_VECTOR_BASE_HPP
#define BKSGE_FND_STATIC_VECTOR_DETAIL_STATIC_VECTOR_BASE_HPP

#include <bksge/fnd/static_vector/detail/static_storage_allocator.hpp>
#include <bksge/fnd/algorithm/fill_n.hpp>
#include <bksge/fnd/algorithm/move_backward.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/memory/allocator_traits.hpp>
#include <bksge/fnd/new/bad_alloc.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T, bksge::size_t Capacity, bool = bksge::is_trivially_destructible<T>::value>
class static_vector_base
{
public:
	using allocator_type = detail::static_storage_allocator<T, Capacity>;

private:
    using alloc_traits = bksge::allocator_traits<allocator_type>;

public:
	using value_type             = T;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = typename alloc_traits::size_type;
	using difference_type        = typename alloc_traits::difference_type;
	using pointer                = typename alloc_traits::pointer;
	using const_pointer          = typename alloc_traits::const_pointer;

	static_vector_base()
	{
		m_begin = m_end = alloc_traits::allocate(m_allocator, Capacity);
	}

	~static_vector_base()
	{
		clear();
		alloc_traits::deallocate(m_allocator, begin(), Capacity);
	}

	BKSGE_CXX20_CONSTEXPR size_type size() const BKSGE_NOEXCEPT
	{
		return static_cast<size_type>(end() - begin());
	}

	void clear()
	{
		pop_back_n(size());
	}

	void reserve(size_type new_cap)
	{
		if (new_cap > Capacity)
		{
			bksge::throw_bad_alloc();
		}
	}

	void push_back_n(size_type count, const_reference value)
	{
		insert_n(end(), count, value);
	}

	template <typename... Args>
	void emplace_back_n(size_type count, Args&&... args)
	{
		emplace(end(), count, bksge::forward<Args>(args)...);
	}

	template <typename InputIterator>
	void push_back_iter(InputIterator first, InputIterator last)
	{
		insert_iter(end(), first, last);
	}

	void pop_back_n(size_type count) BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(count <= size());

		pointer p = m_end;
		for (size_type i = 0; i < count; ++i)
		{
			alloc_traits::destroy(m_allocator, --p);
		}
		m_end = p;
	}

	void move_range_backword(pointer first, pointer last, pointer dst)
	{
		while (first != last)
		{
			if (dst > m_end)
			{
				alloc_traits::construct(m_allocator, --dst, bksge::move(*--last));
			}
			else
			{
				*--dst = bksge::move(*--last);
			}
		}
	}

	void insert_n(pointer p, size_type count, const_reference value)
	{
		reserve(size() + count);

		move_range_backword(p, m_end, m_end + count);

		for (size_type i = 0; i < count; ++i)
		{
			if (p >= m_end)
			{
				alloc_traits::construct(m_allocator, p, value);
			}
			else
			{
				*p = value;
			}
			++p;
		}

		m_end += count;
	}

	template <typename... Args>
	void emplace(pointer p, size_type count, Args&&... args)
	{
		reserve(size() + count);

		move_range_backword(p, m_end, m_end + count);

		for (size_type i = 0; i < count; ++i)
		{
			if (p >= m_end)
			{
				alloc_traits::construct(m_allocator, p, bksge::forward<Args>(args)...);
			}
			else
			{
				*p = T(bksge::forward<Args>(args)...);
			}
			++p;
		}

		m_end += count;
	}

	template <typename InputIterator>
	void insert_iter(pointer p, InputIterator first, InputIterator last)
	{
		difference_type count = bksge::distance(first, last);

		reserve(size() + count);

		move_range_backword(p, m_end, m_end + count);

		for (auto it = first; it != last; ++it)
		{
			if (p >= m_end)
			{
				alloc_traits::construct(m_allocator, p, *it);
			}
			else
			{
				*p = *it;
			}
			++p;
		}

		m_end += count;
	}

	BKSGE_CXX20_CONSTEXPR pointer begin() const { return m_begin; }
	BKSGE_CXX20_CONSTEXPR pointer end() const { return m_end; }

private:
	allocator_type	m_allocator;
	pointer			m_begin;
	pointer			m_end;
};

template <typename T, bksge::size_t Capacity>
class static_vector_base<T, Capacity, true>
{
public:
	using allocator_type = detail::static_storage_allocator<T, Capacity>;

private:
    using alloc_traits = bksge::allocator_traits<allocator_type>;

public:
	using value_type             = T;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = typename alloc_traits::size_type;
	using difference_type        = typename alloc_traits::difference_type;
	using pointer                = typename alloc_traits::pointer;
	using const_pointer          = typename alloc_traits::const_pointer;

	BKSGE_CXX14_CONSTEXPR static_vector_base()
		: m_begin(m_allocator.allocate(Capacity))
		, m_end(m_begin)
	{
	}

	//~static_vector_base() {}

	BKSGE_CXX14_CONSTEXPR size_type size() const BKSGE_NOEXCEPT
	{
		return static_cast<size_type>(end() - begin());
	}

	BKSGE_CXX14_CONSTEXPR void clear()
	{
		pop_back_n(size());
	}

	BKSGE_CXX14_CONSTEXPR void reserve(size_type new_cap)
	{
		if (new_cap > Capacity)
		{
			bksge::throw_bad_alloc();
		}
	}

	BKSGE_CXX14_CONSTEXPR void push_back_n(size_type count, const_reference value)
	{
		insert_n(end(), count, value);
	}

	template <typename... Args>
	BKSGE_CXX14_CONSTEXPR void emplace_back_n(size_type count, Args&&... args)
	{
		emplace(end(), count, bksge::forward<Args>(args)...);
	}

	template <typename InputIterator>
	BKSGE_CXX14_CONSTEXPR void push_back_iter(InputIterator first, InputIterator last)
	{
		insert_iter(end(), first, last);
	}

	BKSGE_CXX14_CONSTEXPR void pop_back_n(size_type count) BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(count <= size());

		m_end -= count;
	}

	BKSGE_CXX14_CONSTEXPR void insert_n(pointer p, size_type count, const_reference value)
	{
		reserve(size() + count);
		bksge::move_backward(p, m_end, m_end + count);
		bksge::fill_n(p, count, value);
		m_end += count;
	}

	template <typename... Args>
	BKSGE_CXX14_CONSTEXPR void emplace(pointer p, size_type count, Args&&... args)
	{
		reserve(size() + count);

		bksge::move_backward(p, m_end, m_end + count);

		for (size_type i = 0; i < count; ++i)
		{
			*p = T(bksge::forward<Args>(args)...);
			++p;
		}

		m_end += count;
	}

	template <typename InputIterator>
	BKSGE_CXX14_CONSTEXPR void insert_iter(pointer p, InputIterator first, InputIterator last)
	{
		difference_type count = bksge::distance(first, last);

		reserve(size() + count);

		bksge::move_backward(p, m_end, m_end + count);

		for (auto it = first; it != last; ++it)
		{
			*p = *it;
			++p;
		}

		m_end += count;
	}

	BKSGE_CXX14_CONSTEXPR pointer begin() const { return m_begin; }
	BKSGE_CXX14_CONSTEXPR pointer end() const { return m_end; }

private:
	allocator_type	m_allocator;
	pointer			m_begin;
	pointer			m_end;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STATIC_VECTOR_DETAIL_STATIC_VECTOR_BASE_HPP
