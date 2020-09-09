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
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>

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

#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		template <
			typename W2 = W,
			typename = bksge::enable_if_t<
				!bksge::incrementable<W2>::value
			>
		>
#endif
		BKSGE_CXX14_CONSTEXPR void operator++(int)
		{
			++*this;
		}

#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		template <
			typename W2 = W,
			typename = bksge::enable_if_t<
				bksge::incrementable<W2>::value
			>
		>
#endif
		BKSGE_CXX14_CONSTEXPR Iterator operator++(int)
			BKSGE_REQUIRES(bksge::incrementable<W>)
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		BKSGE_CXX14_CONSTEXPR Iterator& operator--()
			BKSGE_REQUIRES(detail::decrementable<W>)
		{
			--m_value;
			return *this;
		}

		BKSGE_CXX14_CONSTEXPR Iterator operator--(int)
			BKSGE_REQUIRES(detail::decrementable<W>)
		{
			auto tmp = *this;
			--*this;
			return tmp;
		}

	private:
		template <
			typename W2 = W,
			typename = bksge::enable_if_t<
				detail::is_integer_like<W2>::value &&
				!detail::is_signed_integer_like<W2>::value
			>
		>
		BKSGE_CXX14_CONSTEXPR void
		advance_impl(bksge::detail::overload_priority<1>, difference_type n)
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
		advance_impl(bksge::detail::overload_priority<0>, difference_type n)
		{
			m_value += static_cast<W>(n);
		}

	public:
		BKSGE_CXX14_CONSTEXPR Iterator& operator+=(difference_type n)
			BKSGE_REQUIRES(detail::advanceable<W>)
		{
			advance_impl(bksge::detail::overload_priority<1>{}, n);
			return *this;
		}

		BKSGE_CXX14_CONSTEXPR Iterator& operator-=(difference_type n)
			BKSGE_REQUIRES(detail::advanceable<W>)
		{
			advance_impl(bksge::detail::overload_priority<1>{}, -n);
			return *this;
		}

		BKSGE_CONSTEXPR W operator[](difference_type n) const
			BKSGE_REQUIRES(detail::advanceable<W>)
		{
			return W(m_value + n);
		}

		friend BKSGE_CONSTEXPR bool operator==(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::equality_comparable<W>)
		{
			return lhs.m_value == rhs.m_value;
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR bool operator!=(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::equality_comparable<W>)
		{
			return !(lhs == rhs);
		}
#endif

		friend BKSGE_CONSTEXPR bool operator<(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::totally_ordered<W>)
		{
			return lhs.m_value < rhs.m_value;
		}

		friend BKSGE_CONSTEXPR bool operator>(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::totally_ordered<W>)
		{
			return rhs < lhs;
		}

		friend BKSGE_CONSTEXPR bool operator<=(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::totally_ordered<W>)
		{
			return !(rhs < lhs);
		}

		friend BKSGE_CONSTEXPR bool operator>=(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::totally_ordered<W>)
		{
			return !(lhs < rhs);
		}

#ifdef __cpp_lib_three_way_comparison
		friend BKSGE_CONSTEXPR auto operator<=>(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::totally_ordered<W>&& three_way_comparable<W>)
		{
			return lhs.m_value <=> rhs.m_value;
		}
#endif

		friend BKSGE_CONSTEXPR Iterator operator+(Iterator i, difference_type n)
			BKSGE_REQUIRES(detail::advanceable<W>)
		{
			return i += n;
		}

		friend BKSGE_CONSTEXPR Iterator operator+(difference_type n, Iterator i)
			BKSGE_REQUIRES(detail::advanceable<W>)
		{
			return i += n;
		}

		friend BKSGE_CONSTEXPR Iterator operator-(Iterator i, difference_type n)
			BKSGE_REQUIRES(detail::advanceable<W>)
		{
			return i -= n;
		}

	private:
		template <
			typename W2 = W,
			typename = bksge::enable_if_t<
				!detail::is_integer_like<W2>::value
			>
		>
		BKSGE_CXX14_CONSTEXPR difference_type
		minus_impl(bksge::detail::overload_priority<2>, Iterator const& rhs) const
		{
			return m_value - rhs.m_value;
		}

		template <
			typename W2 = W,
			typename = bksge::enable_if_t<
				detail::is_signed_integer_like<W2>::value
			>
		>
		BKSGE_CXX14_CONSTEXPR difference_type
		minus_impl(bksge::detail::overload_priority<1>, Iterator const& rhs) const
		{
			using D = difference_type;
			return D(D(m_value) - D(rhs.m_value));
		}

		BKSGE_CXX14_CONSTEXPR difference_type
		minus_impl(bksge::detail::overload_priority<0>, Iterator const& rhs) const
		{
			using D = difference_type;
			return (rhs.m_value > m_value) ?
				D(-D(rhs.m_value - m_value)) :
				D(m_value - rhs.m_value);
		}

		friend BKSGE_CONSTEXPR difference_type operator-(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(detail::advanceable<W>)
		{
			return lhs.minus_impl(bksge::detail::overload_priority<2>{}, rhs);
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

		BKSGE_CONSTEXPR bksge::iter_difference_t<W> minus(Iterator const& x) const
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

		friend BKSGE_CONSTEXPR bksge::iter_difference_t<W>
		operator-(Iterator const& lhs, Sentinel const& rhs)
			BKSGE_REQUIRES(bksge::sized_sentinel_for<Bound, W>)
		{
			return rhs.minus(lhs);
		}

		friend BKSGE_CONSTEXPR bksge::iter_difference_t<W>
		operator-(Sentinel const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::sized_sentinel_for<Bound, W>)
		{
			return -(rhs - lhs);
		}
	};

	W     m_value = W();
	Bound m_bound = Bound();

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
	template <
		typename W2 = W, typename B2 = Bound,
		typename = bksge::enable_if_t<
			bksge::is_same_as<W2, B2>::value
		>
	>
	BKSGE_CONSTEXPR Iterator
	end_impl(bksge::detail::overload_priority<2>) const
	{
		return Iterator{m_bound};
	}

	template <
		typename B2 = Bound,
		typename = bksge::enable_if_t<
			bksge::is_same_as<B2, bksge::unreachable_sentinel_t>::value
		>
	>
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
BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4146);	// unary minus operator applied to unsigned type, result still unsigned

	template <
		typename W2, typename B2,
		typename = bksge::enable_if_t<
			detail::is_integer_like<W2>::value &&
			detail::is_integer_like<B2>::value
		>
	>
	static BKSGE_CONSTEXPR auto
	size_impl(bksge::detail::overload_priority<1>, W2 const& w, B2 const& b)
	->decltype(
		false ? (detail::to_unsigned_like(b) - detail::to_unsigned_like(w)) :
		false ? (detail::to_unsigned_like(w) - detail::to_unsigned_like(b)) :
		        (detail::to_unsigned_like(b) + detail::to_unsigned_like(w)))
	{
		using detail::to_unsigned_like;
		return
			!(w < 0) ? (to_unsigned_like( b) - to_unsigned_like( w)) :
			 (b < 0) ? (to_unsigned_like(-w) - to_unsigned_like(-b)) :
					   (to_unsigned_like( b) + to_unsigned_like(-w));
	}

BKSGE_WARNING_POP();

	template <typename W2, typename B2>
	static BKSGE_CONSTEXPR auto
	size_impl(bksge::detail::overload_priority<0>, W2 const& w, B2 const& b)
	->decltype(detail::to_unsigned_like(b - w))
	{
		return detail::to_unsigned_like(b - w);
	}

	static BKSGE_CONSTEXPR void
	size_impl(...);

public:
	BKSGE_CONSTEXPR auto size() const
	->decltype(size_impl(bksge::detail::overload_priority<1>{}, m_value, m_bound))
		BKSGE_REQUIRES(
			(bksge::same_as<W, Bound> && detail::advanceable<W>) ||
			(bksge::integral<W> && bksge::integral<Bound>) ||
			bksge::sized_sentinel_for<Bound, W>)
	{
		return size_impl(bksge::detail::overload_priority<1>{}, m_value, m_bound);
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
	BKSGE_CONSTEXPR iota_view<T> operator()(T&& t) const
	{
		return iota_view<T>{bksge::forward<T>(t)};
	}

	template <typename T, typename U>
	BKSGE_CONSTEXPR iota_view<T, U> operator()(T&& t, U&& f) const
	{
		return iota_view<T, U>{bksge::forward<T>(t), bksge::forward<U>(f)};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::iota_fn iota{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_IOTA_VIEW_HPP
