/**
 *	@file	iota_view.hpp
 *
 *	@brief	iota_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_IOTA_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_IOTA_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/detail/advanceable.hpp>
#include <bksge/fnd/ranges/detail/decrementable.hpp>
#include <bksge/fnd/ranges/detail/iota_diff_t.hpp>
#include <bksge/fnd/ranges/detail/iota_iter_cat_t.hpp>
#include <bksge/fnd/ranges/detail/integer_like.hpp>
#include <bksge/fnd/ranges/detail/signed_integer_like.hpp>
#include <bksge/fnd/ranges/detail/to_unsigned_like.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/incrementable.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/unreachable_sentinel.hpp>
#include <bksge/fnd/compare/concepts/three_way_comparable.hpp>
#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/semiregular.hpp>
#include <bksge/fnd/concepts/totally_ordered.hpp>
#include <bksge/fnd/concepts/totally_ordered_with.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/weakly_eq_cmp_with.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <
	bksge::weakly_incrementable W,
	bksge::semiregular Bound = bksge::unreachable_sentinel_t
>
requires bksge::detail::weakly_eq_cmp_with<W, Bound> && bksge::semiregular<W>
#else
template <
	typename W,
	typename Bound = bksge::unreachable_sentinel_t,
	typename = bksge::enable_if_t<bksge::conjunction<
		bksge::weakly_incrementable<W>,
		bksge::semiregular<Bound>,
		bksge::detail::weakly_eq_cmp_with<W, Bound>,
		bksge::semiregular<W>
	>::value>
>
#endif
class iota_view : public view_interface<iota_view<W, Bound>>
{
private:
public:	// TODO
	struct Sentinel;

	struct Iterator
	{
	public:
		using iterator_category = detail::iota_iter_cat_t<W>;
		using value_type        = W;
		using difference_type   = detail::iota_diff_t<W>;

		BKSGE_CONSTEXPR Iterator() = default;

		BKSGE_CONSTEXPR explicit Iterator(W value)
			: m_value(value) {}

		BKSGE_CONSTEXPR W operator*() const
			BKSGE_NOEXCEPT_IF(bksge::is_nothrow_copy_constructible<W>::value)
		{
			return m_value;
		}

		BKSGE_CXX14_CONSTEXPR Iterator& operator++()
		{
			++m_value;
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(bksge::not_incrementable, W2, W)>
		BKSGE_CXX14_CONSTEXPR void operator++(int)
		{
			++*this;
		}

		template <BKSGE_REQUIRES_PARAM_D(bksge::incrementable, W2, W)>
		BKSGE_CXX14_CONSTEXPR Iterator operator++(int)
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		template <BKSGE_REQUIRES_PARAM_D(detail::decrementable, W2, W)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator--()
		{
			--m_value;
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(detail::decrementable, W2, W)>
		BKSGE_CXX14_CONSTEXPR Iterator operator--(int)
		{
			auto tmp = *this;
			--*this;
			return tmp;
		}

	private:
		template <
			BKSGE_REQUIRES_PARAM_D(detail::integer_like,            W2, W),
			BKSGE_REQUIRES_PARAM_D(detail::not_signed_integer_like, W3, W)>
		BKSGE_CXX14_CONSTEXPR void
		advance_impl(difference_type n, bksge::detail::overload_priority<1>)
		{
			if (n >= difference_type(0))
			{
				m_value += static_cast<W>(n);
			}
			else
			{
				m_value -= static_cast<W>(-n);
			}
		}

		BKSGE_CXX14_CONSTEXPR void
		advance_impl(difference_type n, bksge::detail::overload_priority<0>)
		{
			m_value += static_cast<W>(n);
		}

	public:
		template <BKSGE_REQUIRES_PARAM_D(detail::advanceable, W2, W)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator+=(difference_type n)
		{
			advance_impl(n, bksge::detail::overload_priority<1>{});
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(detail::advanceable, W2, W)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator-=(difference_type n)
		{
			advance_impl(-n, bksge::detail::overload_priority<1>{});
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(detail::advanceable, W2, W)>
		BKSGE_CONSTEXPR W operator[](difference_type n) const
		{
			return W(m_value + n);
		}

		template <BKSGE_REQUIRES_PARAM_D(bksge::equality_comparable, W2, W)>
		friend BKSGE_CONSTEXPR bool
		operator==(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.m_value == rhs.m_value;
		}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR auto
		operator<=>(Iterator const& lhs, Iterator const& rhs)
			requires bksge::totally_ordered<W> && bksge::three_way_comparable<W>
		{
			return lhs.m_value <=> rhs.m_value;
		}
#else
		template <BKSGE_REQUIRES_PARAM_D(bksge::equality_comparable, W2, W)>
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(lhs == rhs);
		}

		template <BKSGE_REQUIRES_PARAM_D(bksge::totally_ordered, W2, W)>
		friend BKSGE_CONSTEXPR bool
		operator<(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.m_value < rhs.m_value;
		}

		template <BKSGE_REQUIRES_PARAM_D(bksge::totally_ordered, W2, W)>
		friend BKSGE_CONSTEXPR bool
		operator>(Iterator const& lhs, Iterator const& rhs)
		{
			return rhs < lhs;
		}

		template <BKSGE_REQUIRES_PARAM_D(bksge::totally_ordered, W2, W)>
		friend BKSGE_CONSTEXPR bool
		operator<=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(rhs < lhs);
		}

		template <BKSGE_REQUIRES_PARAM_D(bksge::totally_ordered, W2, W)>
		friend BKSGE_CONSTEXPR bool
		operator>=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(lhs < rhs);
		}
#endif

		template <BKSGE_REQUIRES_PARAM_D(detail::advanceable, W2, W)>
		friend BKSGE_CONSTEXPR Iterator
		operator+(Iterator i, difference_type n)
		{
			return i += n;
		}

		template <BKSGE_REQUIRES_PARAM_D(detail::advanceable, W2, W)>
		friend BKSGE_CONSTEXPR Iterator
		operator+(difference_type n, Iterator i)
		{
			return i += n;
		}

		template <BKSGE_REQUIRES_PARAM_D(detail::advanceable, W2, W)>
		friend BKSGE_CONSTEXPR Iterator
		operator-(Iterator i, difference_type n)
		{
			return i -= n;
		}

	private:
		template <BKSGE_REQUIRES_PARAM_D(detail::not_integer_like, W2, W)>
		BKSGE_CXX14_CONSTEXPR difference_type
		minus_impl(Iterator const& rhs, bksge::detail::overload_priority<2>) const
		{
			return m_value - rhs.m_value;
		}

		template <BKSGE_REQUIRES_PARAM_D(detail::signed_integer_like, W2, W)>
		BKSGE_CXX14_CONSTEXPR difference_type
		minus_impl(Iterator const& rhs, bksge::detail::overload_priority<1>) const
		{
			using D = difference_type;
			return D(D(m_value) - D(rhs.m_value));
		}

		BKSGE_CXX14_CONSTEXPR difference_type
		minus_impl(Iterator const& rhs, bksge::detail::overload_priority<0>) const
		{
			using D = difference_type;
			return (rhs.m_value > m_value) ?
				D(-D(rhs.m_value - m_value)) :
				D(m_value - rhs.m_value);
		}

		template <BKSGE_REQUIRES_PARAM_D(detail::advanceable, W2, W)>
		friend BKSGE_CONSTEXPR difference_type
		operator-(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.minus_impl(rhs, bksge::detail::overload_priority<2>{});
		}

	private:
		W m_value = W();

		friend Sentinel;
	};

	struct Sentinel
	{
	private:
		BKSGE_CONSTEXPR bool equal(Iterator const& x) const
		{
			return x.m_value == m_bound;
		}

		BKSGE_CONSTEXPR bksge::iter_difference_t<W>
		minus(Iterator const& x) const
		{
			return x.m_value - m_bound;
		}

		Bound m_bound = Bound();

	public:
		BKSGE_CONSTEXPR Sentinel() = default;

		BKSGE_CONSTEXPR explicit Sentinel(Bound bound)
			: m_bound(bound) {}

		friend BKSGE_CONSTEXPR bool
		operator==(Iterator const& lhs, Sentinel const& rhs)
		{
			return rhs.equal(lhs);
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator const& lhs, Sentinel const& rhs)
		{
			return !(lhs == rhs);
		}

		friend BKSGE_CONSTEXPR bool
		operator==(Sentinel const& lhs, Iterator const& rhs)
		{
			return rhs == lhs;
		}

		friend BKSGE_CONSTEXPR bool
		operator!=(Sentinel const& lhs, Iterator const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

		template <BKSGE_REQUIRES_PARAM_2_D(bksge::sized_sentinel_for, W, B2, Bound)>
		friend BKSGE_CONSTEXPR bksge::iter_difference_t<W>
		operator-(Iterator const& lhs, Sentinel const& rhs)
		{
			return rhs.minus(lhs);
		}

		template <BKSGE_REQUIRES_PARAM_2_D(bksge::sized_sentinel_for, W, B2, Bound)>
		friend BKSGE_CONSTEXPR bksge::iter_difference_t<W>
		operator-(Sentinel const& lhs, Iterator const& rhs)
		{
			return -(rhs - lhs);
		}
	};

	W     m_value = W();
	BKSGE_NO_UNIQUE_ADDRESS Bound m_bound = Bound();

public:
	BKSGE_CONSTEXPR iota_view() = default;

	BKSGE_CONSTEXPR explicit iota_view(W value)
		: m_value(value)
	{}

	BKSGE_CONSTEXPR iota_view(
		bksge::type_identity_t<W> value,
		bksge::type_identity_t<Bound> bound)
		: m_value(value)
		, m_bound(bound)
	{
#if defined(BKSGE_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (bksge::is_totally_ordered_with<W, Bound>::value)
		{
			BKSGE_ASSERT(bool(value <= bound));
		}
#endif
	}

	BKSGE_CONSTEXPR Iterator begin() const
	{
		return Iterator{m_value};
	}

private:
	//template <
	//	typename W2 = W, typename B2 = Bound,
	//	typename = bksge::enable_if_t<
	//		bksge::is_same_as<W2, B2>::value
	//	>
	//>
	template <BKSGE_REQUIRES_PARAM_2_D(bksge::same_as, W, B2, Bound)>
	BKSGE_CONSTEXPR Iterator
	end_impl(bksge::detail::overload_priority<2>) const
	{
		return Iterator{m_bound};
	}

	//template <
	//	typename B2 = Bound,
	//	typename = bksge::enable_if_t<
	//		bksge::is_same_as<B2, bksge::unreachable_sentinel_t>::value
	//	>
	//>
	template <BKSGE_REQUIRES_PARAM_2_D(bksge::same_as, bksge::unreachable_sentinel_t, B2, Bound)>
	BKSGE_CONSTEXPR bksge::unreachable_sentinel_t
	end_impl(bksge::detail::overload_priority<1>) const
	{
		return bksge::unreachable_sentinel;
	}

	BKSGE_CONSTEXPR Sentinel
	end_impl(bksge::detail::overload_priority<0>) const
	{
		return Sentinel{m_bound};
	}

public:
	BKSGE_CONSTEXPR auto end() const
	->decltype(end_impl(bksge::detail::overload_priority<2>{}))
	{
		return end_impl(bksge::detail::overload_priority<2>{});
	}

private:
	template <
		typename W2, typename B2,
		typename = bksge::enable_if_t<
			bksge::is_integral<W2>::value &&
			bksge::is_integral<B2>::value>>
	static BKSGE_CONSTEXPR auto
	size_impl(W2 const& w, B2 const& b, bksge::detail::overload_priority<2>)
	-> bksge::make_unsigned_t<decltype(b - w)>
	{
	    using U = bksge::make_unsigned_t<decltype(b - w)>;
	    return U(b) - U(w);
	}

	template <
		typename W2, typename B2,
		typename = bksge::enable_if_t<
			detail::is_integer_like<W2>::value>>
	static BKSGE_CONSTEXPR auto
	size_impl(W2 const& w, B2 const& b, bksge::detail::overload_priority<1>)
	->decltype(detail::to_unsigned_like(b) - detail::to_unsigned_like(w))
	{
	    return detail::to_unsigned_like(b) - detail::to_unsigned_like(w);
	}

	template <typename W2, typename B2>
	static BKSGE_CONSTEXPR auto
	size_impl(W2 const& w, B2 const& b, bksge::detail::overload_priority<0>)
	->decltype(detail::to_unsigned_like(b - w))
	{
		return detail::to_unsigned_like(b - w);
	}

public:
	template <
		typename W2 = W, typename B2 = Bound,
		typename = bksge::enable_if_t<
			(bksge::is_same_as<W2, B2>::value && detail::is_advanceable<W2>::value) ||
			(bksge::is_integral<W2>::value && bksge::is_integral<B2>::value) ||
			bksge::is_sized_sentinel_for<B2, W2>::value
		>
	>
	BKSGE_CONSTEXPR auto size() const
	->decltype(size_impl(std::declval<W2>(), std::declval<B2>(), bksge::detail::overload_priority<2>{}))
	{
		return size_impl(m_value, m_bound, bksge::detail::overload_priority<2>{});
	}
};

// deduction guide
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename W, typename Bound>
BKSGE_REQUIRES(
	!detail::integer_like<W> ||
	!detail::integer_like<Bound> ||
	(detail::signed_integer_like<W> == detail::signed_integer_like<Bound>))
iota_view(W, Bound) -> iota_view<W, Bound>;

#endif

// specialize enable_borrowed_range
template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::weakly_incrementable W, bksge::semiregular Bound
#else
	typename W, typename Bound
#endif
>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, iota_view<W, Bound>);

namespace views
{

namespace detail
{

struct iota_fn
{
	template <typename T>
	BKSGE_CXX14_CONSTEXPR iota_view<T> operator()(T t) const
	{
		return iota_view<T>{std::move(t)};
	}

	template <typename T, typename U>
	BKSGE_CXX14_CONSTEXPR iota_view<T, U> operator()(T t, U f) const
	{
		return iota_view<T, U>{std::move(t), std::move(f)};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::iota_fn iota{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_IOTA_VIEW_HPP
