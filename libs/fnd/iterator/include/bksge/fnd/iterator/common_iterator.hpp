/**
 *	@file	common_iterator.hpp
 *
 *	@brief	common_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_COMMON_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_COMMON_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_swappable.hpp>
#include <bksge/fnd/iterator/concepts/detail/dereferenceable.hpp>
#include <bksge/fnd/iterator/detail/common_iter_has_arrow.hpp>
#include <bksge/fnd/iterator/detail/clamp_iter_cat.hpp>
#include <bksge/fnd/iterator/detail/has_arrow.hpp>
#include <bksge/fnd/iterator/ranges/iter_move.hpp>
#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/iter_rvalue_reference_t.hpp>
#include <bksge/fnd/iterator/incrementable_traits.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/concepts/equality_comparable_with.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/is_trivially_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>
#include <utility>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4702);	// unreachable code

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <bksge::input_or_output_iterator It, bksge::sentinel_for<It> Sent>
requires (!bksge::same_as<It, Sent>) && bksge::copyable<It>
#else
template <typename It, typename Sent,
	typename = bksge::enable_if_t<bksge::conjunction<
		bksge::input_or_output_iterator<It>,
		bksge::sentinel_for<Sent, It>,
		bksge::negation<bksge::same_as<It, Sent>>,
		bksge::copyable<It>
	>::value>
>
#endif
class common_iterator
{
	template <typename T, typename U>
	using IsNothrowConstructible_1 =
		bksge::conditional_t<
			bksge::is_trivially_default_constructible<T>::value,
			bksge::is_nothrow_assignable<T, U>,
			bksge::is_nothrow_constructible<T, U>>;

	template <typename It2, typename Sent2>
	using IsNothrowConstructible =
		bksge::conjunction<
			IsNothrowConstructible_1<It, It2>,
			IsNothrowConstructible_1<Sent, Sent2>>;

	class Proxy
	{
		bksge::iter_value_t<It> m_keep;

		Proxy(bksge::iter_reference_t<It>&& x)
			: m_keep(bksge::move(x))
		{}

		friend class common_iterator;

	public:
		bksge::iter_value_t<It> const* operator->() const
		{
			return bksge::addressof(m_keep);
		}
	};

private:
	union
	{
		It m_it;
		Sent m_sent;
		unsigned char m_valueless;
	};
	unsigned char m_index; // 0==m_it, 1==m_sent, 2==valueless

public:
	BKSGE_CONSTEXPR common_iterator()
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_default_constructible<It>::value)
		: m_it()
		, m_index(0)
	{}

	BKSGE_CONSTEXPR common_iterator(It i)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<It>::value)
		: m_it(bksge::move(i))
		, m_index(0)
	{}

	BKSGE_CONSTEXPR common_iterator(Sent s)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<Sent>::value)
		: m_sent(bksge::move(s))
		, m_index(1)
	{}

private:
	template <typename CommonIterator>
	BKSGE_CXX14_CONSTEXPR void construct_it(CommonIterator const& x, bksge::true_type)
	{
		m_it = bksge::move(x.m_it);
	}

	template <typename CommonIterator>
	BKSGE_CXX14_CONSTEXPR void construct_it(CommonIterator const& x, bksge::false_type)
	{
		::new((void*)bksge::addressof(m_it)) It(x.m_it);
	}

	template <typename CommonIterator>
	BKSGE_CXX14_CONSTEXPR void construct_sent(CommonIterator const& x, bksge::true_type)
	{
		m_sent = bksge::move(x.m_sent);
	}

	template <typename CommonIterator>
	BKSGE_CXX14_CONSTEXPR void construct_sent(CommonIterator const& x, bksge::false_type)
	{
		::new((void*)bksge::addressof(m_sent)) Sent(x.m_sent);
	}

public:
	template <typename It2, typename Sent2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::is_convertible_to<It2 const&, It>,
			bksge::is_convertible_to<Sent2 const&, Sent>
		>::value>>
	BKSGE_CXX14_CONSTEXPR
	common_iterator(common_iterator<It2, Sent2> const& x)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<It2 const&, Sent2 const&>::value))
		: m_valueless()
		, m_index(x.m_index)
	{
		if (m_index == 0)
		{
			construct_it(x, bksge::is_trivially_default_constructible<It>{});
		}
		else if (m_index == 1)
		{
			construct_sent(x, bksge::is_trivially_default_constructible<Sent>{});
		}
	}

	BKSGE_CXX14_CONSTEXPR
	common_iterator(common_iterator const& x)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<It const&, Sent const&>::value))
		: m_valueless()
		, m_index(x.m_index)
	{
		if (m_index == 0)
		{
			construct_it(x, bksge::is_trivially_default_constructible<It>{});
		}
		else if (m_index == 1)
		{
			construct_sent(x, bksge::is_trivially_default_constructible<Sent>{});
		}
	}

	common_iterator& operator=(common_iterator const& x)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_copy_assignable<It>::value &&
			bksge::is_nothrow_copy_assignable<Sent>::value &&
			bksge::is_nothrow_copy_constructible<It>::value &&
			bksge::is_nothrow_copy_constructible<Sent>::value))
	{
		return this->operator=<It, Sent>(x);
	}

	template <typename It2, typename Sent2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::is_convertible_to<It2   const&, It>,
			bksge::is_convertible_to<Sent2 const&, Sent>,
			bksge::is_assignable_from<It&,   It2   const&>,
			bksge::is_assignable_from<Sent&, Sent2 const&>
		>::value>
	>
	common_iterator&
	operator=(common_iterator<It2, Sent2> const& x)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_constructible<It,   It2   const&>::value &&
			bksge::is_nothrow_constructible<Sent, Sent2 const&>::value &&
			bksge::is_nothrow_assignable<It,   It2   const&>::value    &&
			bksge::is_nothrow_assignable<Sent, Sent2 const&>::value))
	{
		switch (m_index << 2 | x.m_index)
		{
		case 0b0000:
			m_it = x.m_it;
			break;
		case 0b0101:
			m_sent = x.m_sent;
			break;
		case 0b0001:
			m_it.~It();
			m_index = static_cast<unsigned char>(-1);
			BKSGE_FALLTHROUGH();
		case 0b1001:
			::new((void*)bksge::addressof(m_sent)) Sent(x.m_sent);
			m_index = 1;
			break;
		case 0b0100:
			m_sent.~Sent();
			m_index = static_cast<unsigned char>(-1);
			BKSGE_FALLTHROUGH();
		case 0b1000:
			::new((void*)bksge::addressof(m_it)) It(x.m_it);
			m_index = 0;
			break;
		default:
			BKSGE_ASSERT(x.has_value());
			//__builtin_unreachable();
		}
		return *this;
	}

	~common_iterator()
	{
		switch (m_index)
		{
		case 0:
			m_it.~It();
			break;
		case 1:
			m_sent.~Sent();
			break;
		}
	}

	auto operator*()
	->decltype((*m_it))
	{
		BKSGE_ASSERT(m_index == 0);
		return *m_it;
	}

private:
	using deref_type = decltype((*m_it));

public:
	template <BKSGE_REQUIRES_PARAM_D(bksge::detail::dereferenceable, It2, It const)>
	deref_type operator*() const
	{
		BKSGE_ASSERT(m_index == 0);
		return *m_it;
	}

private:
	template <BKSGE_REQUIRES_PARAM_D(bksge::detail::has_arrow, It2, It)>
	auto operator_arrow(bksge::detail::overload_priority<2>) const
	->decltype(m_it)
	{
		return m_it;
	}

	template <typename It2 = It,
		typename = bksge::enable_if_t<bksge::is_reference<bksge::iter_reference_t<It2>>::value>>
	auto operator_arrow(bksge::detail::overload_priority<1>) const
	->decltype(bksge::addressof(std::declval<bksge::iter_reference_t<It2>>()))
	{
		auto&& tmp = *m_it;
		return bksge::addressof(tmp);
	}

	Proxy operator_arrow(bksge::detail::overload_priority<0>) const
	{
		return Proxy{*m_it};
	}

public:
	template <BKSGE_REQUIRES_PARAM_D(bksge::detail::common_iter_has_arrow, It2, It)>
	auto operator->() const
	->decltype(operator_arrow(bksge::detail::overload_priority<2>{}))
	{
		BKSGE_ASSERT(m_index == 0);
		return operator_arrow(bksge::detail::overload_priority<2>{});
	}

	common_iterator& operator++()
	{
		BKSGE_ASSERT(m_index == 0);
		++m_it;
		return *this;
	}

private:
	common_iterator post_increment(bksge::true_type)
	{
		common_iterator tmp = *this;
		++*this;
		return tmp;
	}

	auto post_increment(bksge::false_type)
	->decltype(m_it++)
	{
		return m_it++;
	}

public:
	auto operator++(int)
	->decltype(post_increment(bksge::is_forward_iterator<It>{}))
	{
		BKSGE_ASSERT(m_index == 0);
		return post_increment(bksge::is_forward_iterator<It>{});
	}

private:
	template <typename CommonIterator2>
	bool equal(CommonIterator2 const& y, bksge::false_type) const
	{
		switch (m_index << 2 | y.m_index)
		{
		case 0b0000:
		case 0b0101:
			return true;
		case 0b0001:
			return m_it == y.m_sent;
		case 0b0100:
			return m_sent == y.m_it;
		default:
			BKSGE_ASSERT(has_value());
			BKSGE_ASSERT(y.has_value());
			//__builtin_unreachable();
			return false;
		}
	}

	template <typename CommonIterator2>
	bool equal(CommonIterator2 const& y, bksge::true_type) const
	{
		switch (m_index << 2 | y.m_index)
		{
		case 0b0101:
			return true;
		case 0b0000:
			return m_it == y.m_it;
		case 0b0001:
			return m_it == y.m_sent;
		case 0b0100:
			return m_sent == y.m_it;
		default:
			BKSGE_ASSERT(has_value());
			BKSGE_ASSERT(y.has_value());
			//__builtin_unreachable();
			return false;
		}
	}

public:
	template <
		typename It2, typename Sent2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::is_sentinel_for<Sent2, It>,
			bksge::is_sentinel_for<Sent, It2>
		>::value>>
	friend bool
	operator==(common_iterator const& lhs, common_iterator<It2, Sent2> const& rhs)
	{
		return lhs.equal(rhs, bksge::is_equality_comparable_with<It, It2>{});
	}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	template <
		typename It2, typename Sent2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::is_sentinel_for<Sent2, It>,
			bksge::is_sentinel_for<Sent, It2>
		>::value>>
	friend bool
	operator!=(common_iterator const& lhs, common_iterator<It2, Sent2> const& rhs)
	{
		return !(lhs == rhs);
	}
#endif

	template <typename It2, typename Sent2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::is_sized_sentinel_for<It2, It>,
			bksge::is_sized_sentinel_for<Sent2, It>,
			bksge::is_sized_sentinel_for<Sent, It2>
		>::value>
	>
	friend bksge::iter_difference_t<It2>
	operator-(common_iterator const& x, common_iterator<It2, Sent2> const& y)
	{
		switch (x.m_index << 2 | y.m_index)
		{
		case 0b0101:
			return 0;
		case 0b0000:
			return x.m_it - y.m_it;
		case 0b0001:
			return x.m_it - y.m_sent;
		case 0b0100:
			return x.m_sent - y.m_it;
		default:
			BKSGE_ASSERT(x.has_value());
			BKSGE_ASSERT(y.has_value());
			//__builtin_unreachable();
			return false;
		}
	}

	template <BKSGE_REQUIRES_PARAM_D(bksge::input_iterator, It2, It)>
	friend bksge::iter_rvalue_reference_t<It2>
	iter_move(common_iterator<It2, Sent> const& i)
		BKSGE_NOEXCEPT_IF_EXPR((ranges::iter_move(std::declval<It2 const&>())))
	{
		BKSGE_ASSERT(i.m_index == 0);
		return ranges::iter_move(i.m_it);
	}

	template <typename Sent2, BKSGE_REQUIRES_PARAM_2(bksge::indirectly_swappable, It, It2)>
	friend void
	iter_swap(common_iterator const& x, common_iterator<It2, Sent2> const& y)
		BKSGE_NOEXCEPT_IF_EXPR((ranges::iter_swap(
			std::declval<It  const&>(),
			std::declval<It2 const&>())))
	{
		BKSGE_ASSERT(x.m_index == 0);
		BKSGE_ASSERT(y.m_index == 0);
		return ranges::iter_swap(x.m_it, y.m_it);
	}

private:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <bksge::input_or_output_iterator It2, bksge::sentinel_for<It2> Sent2>
	requires (!bksge::same_as<It2, Sent2>) && bksge::copyable<It2>
#else
	template <typename It2, typename Sent2, typename>
#endif
	friend class common_iterator;

	bool has_value() const BKSGE_NOEXCEPT { return m_index < 2; }
};

template <typename It, typename Sent>
struct incrementable_traits<common_iterator<It, Sent>>
{
	using difference_type = bksge::iter_difference_t<It>;
};

namespace iterator_traits_detail
{

// この struct ptr は iterator_traits の内部クラスにしたいところだが、
// G++10 でコンパイラ内部エラーになるので仕方なく外に出した
template <typename Iter, typename Sent, typename = bksge::detail::is_common_iter_has_arrow<Iter>>
struct ptr
{
	using type = void;
};

template <typename Iter, typename Sent>
struct ptr<Iter, Sent, bksge::true_type>
{
	using CIter = common_iterator<Iter, Sent>;
	using type = decltype(std::declval<CIter const&>().operator->());
};

}	// namespace iterator_traits_detail

template <typename It, typename Sent>
struct iterator_traits<
	detail::enable_iterator_traits_helper<
		common_iterator<It, Sent>,
		bksge::enable_if_t<bksge::is_input_iterator<It>::value>>>
{
public:
	using iterator_concept = bksge::conditional_t<bksge::is_forward_iterator<It>::value,
		bksge::forward_iterator_tag, bksge::input_iterator_tag>;
	using iterator_category = bksge::detail::clamp_iter_cat<
		typename bksge::iterator_traits<It>::iterator_category,
		bksge::forward_iterator_tag, bksge::input_iterator_tag>;
	using value_type      = bksge::iter_value_t<It>;
	using difference_type = bksge::iter_difference_t<It>;
	using pointer         = typename iterator_traits_detail::ptr<It, Sent>::type;
	using reference       = bksge::iter_reference_t<It>;
};

namespace detail
{

template <typename It, typename Sent>
struct is_iterator_traits_specialized<
	detail::enable_iterator_traits_helper<
		common_iterator<It, Sent>,
		bksge::enable_if_t<bksge::is_input_iterator<It>::value>>>
{
	static const bool value = true;
};

}	// namespace detail

}	// namespace bksge

BKSGE_WARNING_POP();

#endif // BKSGE_FND_ITERATOR_COMMON_ITERATOR_HPP
