/**
 *	@file	counted_iterator.hpp
 *
 *	@brief	counted_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_COUNTED_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_COUNTED_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_swappable.hpp>
#include <bksge/fnd/iterator/concepts/detail/dereferenceable.hpp>
#include <bksge/fnd/iterator/concepts/detail/is_iterator_traits_specialized.hpp>
#include <bksge/fnd/iterator/ranges/iter_move.hpp>
#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/iter_rvalue_reference_t.hpp>
#include <bksge/fnd/iterator/default_sentinel.hpp>
#include <bksge/fnd/iterator/incrementable_traits.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/common_with.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>
#include <utility>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <bksge::input_or_output_iterator It>
#else
template <typename It>
#endif
class counted_iterator
{
private:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <bksge::input_or_output_iterator It2>
#else
	template <typename It2>
#endif
	friend class counted_iterator;

	It m_current {};
	bksge::iter_difference_t<It> m_length = 0;

public:
	using iterator_type = It;

	BKSGE_CONSTEXPR counted_iterator() = default;

	BKSGE_CXX14_CONSTEXPR
	counted_iterator(It i, bksge::iter_difference_t<It> n)
		: m_current(std::move(i))
		, m_length(n)
	{
		BKSGE_ASSERT(n >= 0);
	}

	template <typename It2
		, typename = bksge::enable_if_t<bksge::is_convertible_to<It2 const&, It>::value>>
	//requires bksge::convertible_to<It2 const&, It>
	BKSGE_CONSTEXPR
	counted_iterator(counted_iterator<It2> const& x)
		: m_current(x.m_current)
		, m_length(x.m_length)
	{}

	template <typename It2
		, typename = bksge::enable_if_t<bksge::is_assignable_from<It&, It2 const&>::value>>
	//requires bksge::assignable_from<It&, It2 const&>
	BKSGE_CXX14_CONSTEXPR counted_iterator&
	operator=(counted_iterator<It2> const& x)
	{
		m_current = x.m_current;
		m_length = x.m_length;
		return *this;
	}

	BKSGE_CONSTEXPR It base() const&
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_copy_constructible<It>::value)
		BKSGE_REQUIRES(bksge::copy_constructible<It>)
	{
		return m_current;
	}

	BKSGE_CXX14_CONSTEXPR It base() &&
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<It>::value)
	{
		return std::move(m_current);
	}

	BKSGE_CONSTEXPR bksge::iter_difference_t<It>
	count() const BKSGE_NOEXCEPT
	{
		return m_length;
	}

	BKSGE_CXX14_CONSTEXPR auto operator*()
		BKSGE_NOEXCEPT_IF_EXPR(*m_current)
	->decltype((*m_current))
	{
		return *m_current;
	}

	BKSGE_CONSTEXPR auto operator*() const
		BKSGE_NOEXCEPT_IF_EXPR(*m_current)
	->decltype((*m_current))
		BKSGE_REQUIRES(bksge::detail::dereferenceable<It const>)
	{
		return *m_current;
	}

	BKSGE_CXX14_CONSTEXPR counted_iterator& operator++()
	{
		BKSGE_ASSERT(m_length > 0);
		++m_current;
		--m_length;
		return *this;
	}

private:
	template <BKSGE_REQUIRES_PARAM_D(bksge::forward_iterator, I2, It)>
	BKSGE_CXX14_CONSTEXPR counted_iterator
	increment(bksge::detail::overload_priority<1>)
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	BKSGE_CXX14_CONSTEXPR auto
	increment(bksge::detail::overload_priority<0>)
	->decltype((m_current++))
	{
		BKSGE_ASSERT(m_length > 0);
		--m_length;

#if defined(BKSGE_HAS_CXX20_CONSTEXPR_TRY_CATCH)
		try
		{
			return m_current++;
		}
		catch(...)
		{
			++m_length;
			throw;
		}
#else
		return m_current++;
#endif
	}

public:
	BKSGE_CXX14_CONSTEXPR auto operator++(int)
	->decltype(increment(bksge::detail::overload_priority<1>{}))
	{
		return increment(bksge::detail::overload_priority<1>{});
	}

	BKSGE_CXX14_CONSTEXPR counted_iterator& operator--()
		BKSGE_REQUIRES(bksge::bidirectional_iterator<It>)
	{
		--m_current;
		++m_length;
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR counted_iterator operator--(int)
		BKSGE_REQUIRES(bksge::bidirectional_iterator<It>)
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

	BKSGE_CONSTEXPR counted_iterator
	operator+(bksge::iter_difference_t<It> n) const
		BKSGE_REQUIRES(bksge::random_access_iterator<It>)
	{
		return counted_iterator(m_current + n, m_length - n);
	}

	friend BKSGE_CONSTEXPR counted_iterator
	operator+(bksge::iter_difference_t<It> n, counted_iterator const& x)
		BKSGE_REQUIRES(bksge::random_access_iterator<It>)
	{
		return x + n;
	}

	BKSGE_CXX14_CONSTEXPR counted_iterator&
	operator+=(bksge::iter_difference_t<It> n)
		BKSGE_REQUIRES(bksge::random_access_iterator<It>)
	{
		BKSGE_ASSERT(n <= m_length);
		m_current += n;
		m_length -= n;
		return *this;
	}

	BKSGE_CONSTEXPR counted_iterator
	operator-(bksge::iter_difference_t<It> n) const
		BKSGE_REQUIRES(bksge::random_access_iterator<It>)
	{
		return counted_iterator(m_current - n, m_length + n);
	}

	template <BKSGE_REQUIRES_PARAM_2(bksge::common_with, It, It2)>
	friend BKSGE_CONSTEXPR bksge::iter_difference_t<It2>
	operator-(counted_iterator const& x, counted_iterator<It2> const& y)
	{
		return y.m_length - x.m_length;
	}

	friend BKSGE_CONSTEXPR bksge::iter_difference_t<It>
	operator-(counted_iterator const& x, bksge::default_sentinel_t)
	{
		return -x.m_length;
	}

	friend BKSGE_CONSTEXPR bksge::iter_difference_t<It>
	operator-(bksge::default_sentinel_t, counted_iterator const& y)
	{
		return y.m_length;
	}

	BKSGE_CXX14_CONSTEXPR counted_iterator&
	operator-=(bksge::iter_difference_t<It> n)
		BKSGE_REQUIRES(bksge::random_access_iterator<It>)
	{
		BKSGE_ASSERT(-n <= m_length);
		m_current -= n;
		m_length += n;
		return *this;
	}

	template <typename I2 = It,
		typename = bksge::enable_if_t<bksge::is_random_access_iterator<I2>::value>>
	BKSGE_CONSTEXPR auto
	operator[](bksge::iter_difference_t<I2> n) const
		BKSGE_NOEXCEPT_IF_EXPR(m_current[n])
	->decltype((m_current[n]))
		//BKSGE_REQUIRES(bksge::random_access_iterator<It>)
	{
		return
			BKSGE_ASSERT(n < m_length),
			m_current[n];
	}

	template <BKSGE_REQUIRES_PARAM_2(bksge::common_with, It, It2)>
	friend BKSGE_CONSTEXPR bool
	operator==(counted_iterator const& lhs, counted_iterator<It2> const& rhs)
	{
		return lhs.m_length == rhs.m_length;
	}

	friend BKSGE_CONSTEXPR bool
	operator==(counted_iterator const& lhs, bksge::default_sentinel_t)
	{
		return lhs.m_length == 0;
	}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	template <BKSGE_REQUIRES_PARAM_2(bksge::common_with, It, It2)>
	friend BKSGE_CONSTEXPR bool
	operator!=(counted_iterator const& lhs, counted_iterator<It2> const& rhs)
	{
		return !(lhs == rhs);
	}

	friend BKSGE_CONSTEXPR bool
	operator!=(counted_iterator const& lhs, bksge::default_sentinel_t rhs)
	{
		return !(lhs == rhs);
	}

	friend BKSGE_CONSTEXPR bool
	operator==(bksge::default_sentinel_t lhs, counted_iterator const& rhs)
	{
		return rhs == lhs;
	}

	friend BKSGE_CONSTEXPR bool
	operator!=(bksge::default_sentinel_t lhs, counted_iterator const& rhs)
	{
		return !(lhs == rhs);
	}
#endif

#if 0
	template <bksge::common_with<It> It2>
	friend BKSGE_CONSTEXPR std::strong_ordering
	operator<=>(counted_iterator const& x, counted_iterator<It2> const& y)
	{
		return y.m_length <=> x.m_length;
	}
#endif

	friend BKSGE_CONSTEXPR bksge::iter_rvalue_reference_t<It>
	iter_move(counted_iterator const& i)
		BKSGE_NOEXCEPT_IF_EXPR(ranges::iter_move(i.m_current))
		BKSGE_REQUIRES(bksge::input_iterator<It>)
	{
		return ranges::iter_move(i.m_current);
	}

	template <BKSGE_REQUIRES_PARAM_2(bksge::indirectly_swappable, It, It2)>
	friend BKSGE_CXX14_CONSTEXPR void
	iter_swap(counted_iterator const& x, counted_iterator<It2> const& y)
		BKSGE_NOEXCEPT_IF_EXPR(ranges::iter_swap(x.m_current, y.m_current))
	{
		ranges::iter_swap(x.m_current, y.m_current);
	}
};

template <typename It>
struct incrementable_traits<counted_iterator<It>>
{
	using difference_type = bksge::iter_difference_t<It>;
};

template <typename It>
struct iterator_traits<
	detail::enable_iterator_traits_helper<
		counted_iterator<It>,
		bksge::enable_if_t<bksge::is_input_iterator<It>::value>>>
	: public iterator_traits<It>
{
	using pointer = void;
};

namespace detail
{

template <typename It>
struct is_iterator_traits_specialized<
	detail::enable_iterator_traits_helper<
		counted_iterator<It>,
		bksge::enable_if_t<bksge::is_input_iterator<It>::value>>>
{
	static const bool value = true;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_COUNTED_ITERATOR_HPP
