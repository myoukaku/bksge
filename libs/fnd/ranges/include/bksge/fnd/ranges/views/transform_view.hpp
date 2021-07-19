/**
 *	@file	transform_view.hpp
 *
 *	@brief	ranges::transform_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_TRANSFORM_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_TRANSFORM_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/detail/maybe_const_t.hpp>
#include <bksge/fnd/ranges/detail/box.hpp>
#include <bksge/fnd/ranges/range_reference_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/compare/concepts/three_way_comparable.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/concepts/regular_invocable.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/detail/can_reference.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_swappable.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <ranges::input_range V, bksge::copy_constructible F>
requires
	ranges::view<V> &&
	bksge::is_object<F>::value &&
	bksge::regular_invocable<F&, ranges::range_reference_t<V>> &&
	bksge::detail::can_reference<bksge::invoke_result_t<F&, ranges::range_reference_t<V>>>
#else
template <typename V, typename F,
	typename = bksge::enable_if_t<bksge::conjunction<
		ranges::input_range<V>,
		bksge::copy_constructible<F>,
		ranges::view<V>,
		bksge::is_object<F>,
		bksge::regular_invocable<F&, ranges::range_reference_t<V>>,
		bksge::detail::can_reference<bksge::invoke_result_t<F&, ranges::range_reference_t<V>>>
	>::value>
>
#endif
class transform_view : public view_interface<transform_view<V, F>>
{
private:
	template <bool Const>
	struct Sentinel;

	template <bool Const>
	struct Iterator
	{
	private:
		using Parent   = ranges::detail::maybe_const_t<Const, transform_view>;
		using Base     = ranges::detail::maybe_const_t<Const, V>;
		using BaseIter = ranges::iterator_t<Base>;
		using Result   = bksge::invoke_result_t<F&, ranges::range_reference_t<Base>>;

		struct iter_concept
		{
			using type =
				bksge::conditional_t<ranges::is_random_access_range<V>::value,
					bksge::random_access_iterator_tag,
				bksge::conditional_t<ranges::is_bidirectional_range<V>::value,
					bksge::bidirectional_iterator_tag,
				bksge::conditional_t<ranges::is_forward_range<V>::value,
					bksge::forward_iterator_tag,
					bksge::input_iterator_tag>>>;
		};

		template <typename Iter, typename R, bool = bksge::is_lvalue_reference<R>::value>
		struct iter_cat
		{
			using Cat = typename bksge::iterator_traits<Iter>::iterator_category;
			using type =
				bksge::conditional_t<
					bksge::is_derived_from<Cat, bksge::contiguous_iterator_tag>::value,
					bksge::random_access_iterator_tag,
					Cat>;
		};

		template <typename Iter, typename R>
		struct iter_cat<Iter, R, false>
		{
			using type = bksge::input_iterator_tag;
		};

	private:
		BaseIter  m_current = {};
		Parent*   m_parent  = nullptr;

	public:
		using iterator_concept  = typename iter_concept::type;
		using iterator_category = typename iter_cat<BaseIter, Result>::type;
		using value_type        = bksge::remove_cvref_t<Result>;
		using difference_type   = ranges::range_difference_t<Base>;

		Iterator() = default;

		BKSGE_CXX14_CONSTEXPR
		Iterator(Parent* parent, BaseIter current)
			: m_current(std::move(current))
			, m_parent(parent)
		{}

		template <bool C2 = Const,
			typename = bksge::enable_if_t<
				C2 &&
				bksge::is_convertible_to<ranges::iterator_t<V>, BaseIter>::value>>
		BKSGE_CXX14_CONSTEXPR
		Iterator(Iterator<!Const> i)
			: m_current(std::move(i.m_current))
			, m_parent(i.m_parent)
		{}

		template <BKSGE_REQUIRES_PARAM_D(bksge::copyable, B2, BaseIter)>
		BKSGE_CONSTEXPR BaseIter base() const&
		{
			return m_current;
		}

		BKSGE_CXX14_CONSTEXPR BaseIter base() &&
		{
			return std::move(m_current);
		}

		BKSGE_CONSTEXPR Result operator*() const
			BKSGE_NOEXCEPT_IF_EXPR(bksge::invoke(m_parent->fun(), *m_current))
		{
			return bksge::invoke(m_parent->fun(), *m_current);
		}

		BKSGE_CXX14_CONSTEXPR Iterator& operator++()
		{
			++m_current;
			return *this;
		}

	private:
		template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator
		increment(bksge::detail::overload_priority<1>)
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		BKSGE_CXX14_CONSTEXPR void
		increment(bksge::detail::overload_priority<0>)
		{
			++m_current;
		}

	public:
		BKSGE_CXX14_CONSTEXPR auto operator++(int)
		->decltype(increment(bksge::detail::overload_priority<1>{}))
		{
			return increment(bksge::detail::overload_priority<1>{});
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::bidirectional_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator--()
		{
			--m_current;
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::bidirectional_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator operator--(int)
		{
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator+=(difference_type n)
		{
			m_current += n;
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator-=(difference_type n)
		{
			m_current -= n;
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		BKSGE_CONSTEXPR Result operator[](difference_type n) const
		{
			return bksge::invoke(m_parent->fun(), m_current[n]);
		}

		template <BKSGE_REQUIRES_PARAM_D(bksge::equality_comparable, B2, BaseIter)>
		friend BKSGE_CONSTEXPR bool
		operator==(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.m_current == rhs.m_current;
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		template <BKSGE_REQUIRES_PARAM_D(bksge::equality_comparable, B2, BaseIter)>
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator<(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.m_current < rhs.m_current;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator>(Iterator const& lhs, Iterator const& rhs)
		{
			return rhs < lhs;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator<=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(rhs < lhs);
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator>=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(lhs < rhs);
		}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR auto
		operator<=>(Iterator const& x, Iterator const& y)
			requires
				ranges::random_access_range<Base> &&
				bksge::three_way_comparable<BaseIter>
		{
			return x.m_current <=> y.m_current;
		}
#endif

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR Iterator
		operator+(Iterator i, difference_type n)
		{
			return { i.m_parent, i.m_current + n };
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR Iterator
		operator+(difference_type n, Iterator i)
		{
			return { i.m_parent, i.m_current + n };
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR Iterator
		operator-(Iterator i, difference_type n)
		{
			return { i.m_parent, i.m_current - n };
		}

		template <typename B2 = Base,
			typename = bksge::enable_if_t<
				bksge::is_sized_sentinel_for<
					ranges::iterator_t<B2>,
					ranges::iterator_t<B2>
				>::value>>
		friend BKSGE_CONSTEXPR difference_type
		operator-(Iterator const& x, Iterator const& y)
		{
			return x.m_current - y.m_current;
		}

#if 0	// TODO
		friend BKSGE_CXX14_CONSTEXPR decltype(auto)
		iter_move(Iterator const& i)
			BKSGE_NOEXCEPT_IF_EXPR(*i)
		{
			if constexpr (bksge::is_lvalue_reference<decltype(*i)>::value)
			{
				return std::move(*i);
			}
			else
			{
				return *i;
			}
		}

		friend BKSGE_CXX14_CONSTEXPR void
		iter_swap(Iterator const& x, Iterator const& y)
			BKSGE_NOEXCEPT_IF_EXPR(ranges::iter_swap(x.m_current, y.m_current))
			BKSGE_REQUIRES(bksge::indirectly_swappable<BaseIter>)
		{
			return ranges::iter_swap(x.m_current, y.m_current);
		}
#endif

		friend Iterator<!Const>;
		template <bool> friend struct Sentinel;
	};

	template <bool Const>
	struct Sentinel
	{
	private:
		using Parent = ranges::detail::maybe_const_t<Const, transform_view>;
		using Base   = ranges::detail::maybe_const_t<Const, V>;

		ranges::sentinel_t<Base> m_end {};

		template <bool Const2>
		BKSGE_CONSTEXPR auto
		distance_from(Iterator<Const2> const& i) const
		->decltype(m_end - i.m_current)
		{
			return m_end - i.m_current;
		}

		template <bool Const2>
		BKSGE_CONSTEXPR bool
		equal(Iterator<Const2> const& i) const
		{
			return i.m_current == m_end;
		}

	public:
		Sentinel() = default;

		BKSGE_CONSTEXPR explicit
		Sentinel(ranges::sentinel_t<Base> end)
			: m_end(end)
		{}

		template <bool C2 = Const,
			typename = bksge::enable_if_t<
				C2 &&
				bksge::is_convertible_to<
					ranges::sentinel_t<V>,
					ranges::sentinel_t<Base>>::value>>
		BKSGE_CXX14_CONSTEXPR
		Sentinel(Sentinel<!Const> i)
			: m_end(std::move(i.m_end))
		{}

		BKSGE_CONSTEXPR ranges::sentinel_t<Base> base() const
		{
			return m_end;
		}

	private:
		template <bool Const2>
		using IsSentinelFor =
			bksge::is_sentinel_for<
				ranges::sentinel_t<Base>,
				ranges::iterator_t<ranges::detail::maybe_const_t<Const2, V>>
			>;

	public:
		template <bool Const2, typename = bksge::enable_if_t<IsSentinelFor<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator==(Sentinel const& lhs, Iterator<Const2> const& rhs)
		{
			return lhs.equal(rhs);
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool Const2, typename = bksge::enable_if_t<IsSentinelFor<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator!=(Sentinel const& lhs, Iterator<Const2> const& rhs)
		{
			return !(lhs == rhs);
		}

		template <bool Const2, typename = bksge::enable_if_t<IsSentinelFor<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator==(Iterator<Const2> const& lhs, Sentinel const& rhs)
		{
			return rhs == lhs;
		}

		template <bool Const2, typename = bksge::enable_if_t<IsSentinelFor<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator<Const2> const& lhs, Sentinel const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

	private:
		template <typename Base2>
		using IsSizedSentinelFor =
			bksge::is_sized_sentinel_for<
				ranges::sentinel_t<Base>,
				ranges::iterator_t<Base2>
			>;

	public:
		template <bool Const2,
			typename Base2 = ranges::detail::maybe_const_t<Const2, V>,
			typename = bksge::enable_if_t<IsSizedSentinelFor<Base2>::value>
		>
		friend BKSGE_CONSTEXPR ranges::range_difference_t<Base2>
		operator-(Sentinel const& lhs, Iterator<Const2> const& rhs)
		{
			return lhs.distance_from(rhs);
		}

		template <bool Const2,
			typename Base2 = ranges::detail::maybe_const_t<Const2, V>,
			typename = bksge::enable_if_t<IsSizedSentinelFor<Base2>::value>
		>
		friend BKSGE_CONSTEXPR ranges::range_difference_t<Base2>
		operator-(Iterator<Const2> const& lhs, Sentinel const& rhs)
		{
			return -(rhs - lhs);
		}

		friend Sentinel<!Const>;
	};

	BKSGE_NO_UNIQUE_ADDRESS ranges::detail::box<F> m_fun;
	V	m_base = {};

	BKSGE_CONSTEXPR F const& fun() const
	{
		return *m_fun;
	}

public:
	transform_view() = default;

	BKSGE_CXX14_CONSTEXPR
	transform_view(V base, F fun)
		: m_fun(std::move(fun))
		, m_base(std::move(base))
	{}

	BKSGE_CONSTEXPR V base() const&
		BKSGE_REQUIRES(bksge::copy_constructible<V>)
	{
		return m_base;
	}

	BKSGE_CXX14_CONSTEXPR V base() &&
	{
		return std::move(m_base);
	}

	BKSGE_CXX14_CONSTEXPR Iterator<false> begin()
	{
		return Iterator<false>{this, ranges::begin(m_base)};
	}

	template <typename V2 = V,
		typename = bksge::enable_if_t<
			ranges::is_range<V2 const>::value &&
			bksge::is_regular_invocable<F const&, ranges::range_reference_t<V2 const>>::value
		>
	>
	BKSGE_CONSTEXPR Iterator<true> begin() const
	{
		return Iterator<true>{this, ranges::begin(m_base)};
	}

private:
	template <BKSGE_REQUIRES_PARAM_D(ranges::common_range, V2, V)>
	BKSGE_CXX14_CONSTEXPR Iterator<false>
	end_impl(bksge::detail::overload_priority<1>)
	{
		return Iterator<false>{this, ranges::end(m_base)};
	}

	BKSGE_CXX14_CONSTEXPR Sentinel<false>
	end_impl(bksge::detail::overload_priority<0>)
	{
		return Sentinel<false>{ranges::end(m_base)};
	}

public:
	BKSGE_CXX14_CONSTEXPR auto end()
	->decltype(end_impl(bksge::detail::overload_priority<1>{}))
	{
		return end_impl(bksge::detail::overload_priority<1>{});
	}

private:
	template <BKSGE_REQUIRES_PARAM_D(ranges::common_range, V2, V)>
	BKSGE_CONSTEXPR Iterator<true>
	end_impl(bksge::detail::overload_priority<1>) const
	{
		return Iterator<true>{this, ranges::end(m_base)};
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::range, V2, V)>
	BKSGE_CONSTEXPR Sentinel<true>
	end_impl(bksge::detail::overload_priority<0>) const
	{
		return Sentinel<true>{ranges::end(m_base)};
	}

public:
	template <typename V2 = V,
		typename = bksge::enable_if_t<
			bksge::is_regular_invocable<F const&, ranges::range_reference_t<V2 const>>::value>>
	BKSGE_CXX14_CONSTEXPR auto end() const
	->decltype(end_impl(bksge::detail::overload_priority<1>{}))
	{
		return end_impl(bksge::detail::overload_priority<1>{});
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto size()
	->decltype(ranges::size(std::declval<V2>()))
	{
		return ranges::size(m_base);
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V const)>
	BKSGE_CONSTEXPR auto size() const
	->decltype(ranges::size(std::declval<V2>()))
	{
		return ranges::size(m_base);
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range, typename F>
transform_view(Range&&, F) -> transform_view<views::all_t<Range>, F>;

#endif

namespace views
{

namespace detail
{

struct transform_fn
{
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range), typename F>
	BKSGE_CONSTEXPR auto operator()(Range&& r, F&& f) const
	-> transform_view<views::all_t<Range>, F>
	{
		return transform_view<views::all_t<Range>, F>
		{
			std::forward<Range>(r), std::forward<F>(f)
		};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor<views::detail::transform_fn> transform{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_TRANSFORM_VIEW_HPP
