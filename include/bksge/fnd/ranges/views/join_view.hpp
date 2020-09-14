/**
 *	@file	join_view.hpp
 *
 *	@brief	ranges::join_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_JOIN_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_JOIN_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor_closure.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/detail/maybe_const_t.hpp>
#include <bksge/fnd/ranges/detail/has_arrow.hpp>
#include <bksge/fnd/ranges/detail/simple_view.hpp>
#include <bksge/fnd/ranges/range_reference_t.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/ranges/iter_move.hpp>
#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <ranges::input_range V>
requires
	ranges::view<V> &&
	ranges::input_range<ranges::range_reference_t<V>> &&
	(bksge::is_reference<ranges::range_reference_t<V>>::value ||
	 ranges::view<ranges::range_value_t<V>>)
#else
template <typename V,
	typename = bksge::enable_if_t<bksge::conjunction<
		ranges::input_range<V>,
		ranges::view<V>,
		ranges::input_range<ranges::range_reference_t<V>>,
		bksge::disjunction<
			bksge::is_reference<ranges::range_reference_t<V>>,
			ranges::view<ranges::range_value_t<V>>
		>
	>::value>
>
#endif
class join_view : public ranges::view_interface<join_view<V>>
{
private:
	using InnerRange = ranges::range_reference_t<V>;

	template <bool Const>
	struct Sentinel;

	template <bool Const>
	struct Iterator
	{
	private:
		using Parent    = ranges::detail::maybe_const_t<Const, join_view>;
		using Base      = ranges::detail::maybe_const_t<Const, V>;
		using OuterIter = ranges::iterator_t<Base>;
		using InnerIter = ranges::iterator_t<ranges::range_reference_t<Base>>;

		OuterIter m_outer  = {};
		InnerIter m_inner  = {};
		Parent*   m_parent = nullptr;

		using ref_is_glvalue =
			bksge::is_reference<ranges::range_reference_t<Base>>;

		template <typename R>
		BKSGE_CXX14_CONSTEXPR auto
		update_inner_impl(R& x, bksge::true_type)
		->decltype((x))
		{
			return x;
		}

		template <typename R>
		BKSGE_CXX14_CONSTEXPR auto
		update_inner_impl(R& x, bksge::false_type)
		->decltype((m_parent->m_inner = views::all(bksge::move(x))))
		{
			return (m_parent->m_inner = views::all(bksge::move(x)));
		}

		BKSGE_CXX14_CONSTEXPR auto
		update_inner(ranges::range_reference_t<Base> x)
		->decltype((update_inner_impl(x, ref_is_glvalue{})))
		{
			return update_inner_impl(x, ref_is_glvalue{});
		}

		BKSGE_CXX14_CONSTEXPR void
		satisfy_finish(bksge::true_type)
		{
			m_inner = InnerIter();
		}

		BKSGE_CXX14_CONSTEXPR void
		satisfy_finish(bksge::false_type)
		{
		}

		BKSGE_CXX14_CONSTEXPR void satisfy()
		{
			for (; m_outer != ranges::end(m_parent->m_base); ++m_outer)
			{
				auto& inner = update_inner(*m_outer);
				m_inner = ranges::begin(inner);

				if (m_inner != ranges::end(inner))
				{
					return;
				}
			}

			satisfy_finish(ref_is_glvalue{});
		}

		struct iter_concept
		{
			using type =
				bksge::conditional_t<bksge::conjunction<
					ref_is_glvalue,
					ranges::is_bidirectional_range<Base>,
					ranges::is_bidirectional_range<ranges::range_reference_t<Base>>>::value,
					bksge::bidirectional_iterator_tag,
				bksge::conditional_t<bksge::conjunction<
					ref_is_glvalue,
					ranges::is_forward_range<Base>,
					ranges::is_forward_range<ranges::range_reference_t<Base>>>::value,
					bksge::forward_iterator_tag,
				bksge::input_iterator_tag>>;
		};

		struct iter_cat
		{
			using OuterCat = typename bksge::iterator_traits<OuterIter>::iterator_category;
			using InnerCat = typename bksge::iterator_traits<InnerIter>::iterator_category;

			using type =
				bksge::conditional_t<bksge::conjunction<
					ref_is_glvalue,
					bksge::is_derived_from<OuterCat, bksge::bidirectional_iterator_tag>,
					bksge::is_derived_from<InnerCat, bksge::bidirectional_iterator_tag>>::value,
					bksge::bidirectional_iterator_tag,
				bksge::conditional_t<bksge::conjunction<
					ref_is_glvalue,
					bksge::is_derived_from<OuterCat, bksge::forward_iterator_tag>,
					bksge::is_derived_from<InnerCat, bksge::forward_iterator_tag>>::value,
					bksge::forward_iterator_tag,
				bksge::conditional_t<bksge::conjunction<
					bksge::is_derived_from<OuterCat, bksge::input_iterator_tag>,
					bksge::is_derived_from<InnerCat, bksge::input_iterator_tag>>::value,
					bksge::input_iterator_tag,
				bksge::output_iterator_tag>>>;
		};

	public:
		using iterator_concept  = typename iter_concept::type;
		using iterator_category = typename iter_cat::type;
		using value_type        = ranges::range_value_t<ranges::range_reference_t<Base>>;
		using difference_type   = bksge::common_type_t<
			ranges::range_difference_t<Base>,
			ranges::range_difference_t<ranges::range_reference_t<Base>>>;

		BKSGE_CONSTEXPR Iterator() = default;

		BKSGE_CXX14_CONSTEXPR
		Iterator(Parent& parent, OuterIter outer)
			: m_outer(bksge::move(outer))
			, m_parent(bksge::addressof(parent))
		{
			satisfy();
		}

		template <bool C2 = Const,
			typename = bksge::enable_if_t<bksge::conjunction<
				bksge::bool_constant<C2>,
				bksge::is_convertible_to<ranges::iterator_t<V>, OuterIter>,
				bksge::is_convertible_to<ranges::iterator_t<InnerRange>, InnerIter>
			>::value>
		>
		BKSGE_CONSTEXPR
		Iterator(Iterator<!Const> i)
			: m_outer(bksge::move(i.m_outer))
			, m_inner(i.m_inner)
			, m_parent(i.m_parent)
		{}

		BKSGE_CONSTEXPR auto operator*() const
		->decltype((*m_inner))
		{
			return *m_inner;
		}

		template <
			BKSGE_REQUIRES_PARAM_D(ranges::detail::has_arrow, Iter1, InnerIter),
			BKSGE_REQUIRES_PARAM_D(bksge::copyable, Iter2, InnerIter)
		>
		BKSGE_CONSTEXPR InnerIter operator->() const
		{
			return m_inner;
		}

	private:
		BKSGE_CXX14_CONSTEXPR auto
		inner_range_impl(bksge::true_type)
		->decltype((*m_outer))
		{
			return *m_outer;
		}

		BKSGE_CXX14_CONSTEXPR auto
		inner_range_impl(bksge::false_type)
		->decltype((m_parent->m_inner))
		{
			return m_parent->m_inner;
		}

		BKSGE_CXX14_CONSTEXPR auto inner_range()
		->decltype(inner_range_impl(ref_is_glvalue{}))
		{
			return inner_range_impl(ref_is_glvalue{});
		}

	public:
		BKSGE_CXX14_CONSTEXPR Iterator& operator++()
		{
			if (++m_inner == ranges::end(inner_range()))
			{
				++m_outer;
				satisfy();
			}

			return *this;
		}

	private:
		template <typename Base2 = Base,
			typename = bksge::enable_if_t<bksge::conjunction<
				ref_is_glvalue,
				ranges::is_forward_range<Base2>,
				ranges::is_forward_range<ranges::range_reference_t<Base2>>
			>::value>
		>
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
			++*this;
		}

	public:
		BKSGE_CXX14_CONSTEXPR auto operator++(int)
		->decltype(increment(bksge::detail::overload_priority<1>{}))
		{
			return increment(bksge::detail::overload_priority<1>{});
		}

		template <typename Base2 = Base,
			typename = bksge::enable_if_t<bksge::conjunction<
				ref_is_glvalue,
				ranges::is_bidirectional_range<Base2>,
				ranges::is_bidirectional_range<ranges::range_reference_t<Base2>>,
				ranges::is_common_range<ranges::range_reference_t<Base2>>
			>::value>
		>
		BKSGE_CXX14_CONSTEXPR Iterator& operator--()
		{
			if (m_outer == ranges::end(m_parent->m_base))
			{
				m_inner = ranges::end(*--m_outer);
			}

			while (m_inner == ranges::begin(*m_outer))
			{
				m_inner = ranges::end(*--m_outer);
			}

			--m_inner;
			return *this;
		}

		template <typename Base2 = Base,
			typename = bksge::enable_if_t<bksge::conjunction<
				ref_is_glvalue,
				ranges::is_bidirectional_range<Base2>,
				ranges::is_bidirectional_range<ranges::range_reference_t<Base2>>,
				ranges::is_common_range<ranges::range_reference_t<Base2>>
			>::value>
		>
		BKSGE_CXX14_CONSTEXPR Iterator operator--(int)
		{
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <
			typename OuterIter2 = OuterIter,
			typename InnerIter2 = InnerIter,
			typename = bksge::enable_if_t<bksge::conjunction<
				ref_is_glvalue,
				bksge::is_equality_comparable<OuterIter2>,
				bksge::is_equality_comparable<InnerIter2>
			>::value>
		>
		friend BKSGE_CONSTEXPR bool
		operator==(Iterator const& lhs, Iterator const& rhs)
		{
			return
				lhs.m_outer == rhs.m_outer &&
				lhs.m_inner == rhs.m_inner;
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		template <
			typename OuterIter2 = OuterIter,
			typename InnerIter2 = InnerIter,
			typename = bksge::enable_if_t<bksge::conjunction<
				ref_is_glvalue,
				bksge::is_equality_comparable<OuterIter2>,
				bksge::is_equality_comparable<InnerIter2>
			>::value>
		>
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

#if 0
		friend BKSGE_CONSTEXPR decltype(auto)
		iter_move(Iterator const& i)
			noexcept(noexcept(ranges::iter_move(i.m_inner)))
		{
			return ranges::iter_move(i.m_inner);
		}

		friend BKSGE_CXX14_CONSTEXPR void
		iter_swap(Iterator const& x, Iterator const& y)
			noexcept(noexcept(ranges::iter_swap(x.m_inner, y.m_inner)))
		{
			return ranges::iter_swap(x.m_inner, y.m_inner);
		}
#endif

		friend Iterator<!Const>;
		template <bool> friend struct Sentinel;
	};

	template <bool Const>
	struct Sentinel
	{
	private:
		using Parent = ranges::detail::maybe_const_t<Const, join_view>;
		using Base   = ranges::detail::maybe_const_t<Const, V>;

		template <bool Const2>
		BKSGE_CONSTEXPR bool equal(Iterator<Const2> const& i) const
		{
			return i.m_outer == m_end;
		}

		ranges::sentinel_t<Base> m_end = {};

	public:
		BKSGE_CONSTEXPR Sentinel() = default;

		BKSGE_CONSTEXPR explicit
		Sentinel(Parent& parent)
			: m_end(ranges::end(parent.m_base))
		{}

		template <bool Const2 = Const,
			typename = bksge::enable_if_t<
				Const2 &&
				bksge::is_convertible_to<
					ranges::sentinel_t<V>,
					ranges::sentinel_t<Base>
				>::value>>
		BKSGE_CONSTEXPR
		Sentinel(Sentinel<!Const> s)
			: m_end(bksge::move(s.m_end))
		{}

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
		operator==(Iterator<Const2> const& lhs, Sentinel const& rhs)
		{
			return rhs.equal(lhs);
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool Const2, typename = bksge::enable_if_t<IsSentinelFor<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator<Const2> const& lhs, Sentinel const& rhs)
		{
			return !(lhs == rhs);
		}

		template <bool Const2, typename = bksge::enable_if_t<IsSentinelFor<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator==(Sentinel const& lhs, Iterator<Const2> const& rhs)
		{
			return rhs == lhs;
		}

		template <bool Const2, typename = bksge::enable_if_t<IsSentinelFor<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator!=(Sentinel const& lhs, Iterator<Const2> const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

		friend Sentinel<!Const>;
	};

	V m_base = {};

	BKSGE_NO_UNIQUE_ADDRESS
	bksge::conditional_t<
		!bksge::is_reference<InnerRange>::value,
		views::all_t<InnerRange>,
		views::detail::Empty
	> m_inner;

public:
	BKSGE_CONSTEXPR join_view() = default;

	BKSGE_CONSTEXPR explicit
	join_view(V base)
		: m_base(bksge::move(base))
	{}

	template <BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, V2, V)>
	BKSGE_CONSTEXPR V base() const&
	{
		return m_base;
	}

	BKSGE_CXX14_CONSTEXPR V base() &&
	{
		return bksge::move(m_base);
	}

	BKSGE_CXX14_CONSTEXPR auto begin()
	-> Iterator<
		ranges::detail::is_simple_view<V>::value &&
		bksge::is_reference<ranges::range_reference_t<V>>::value>
	{
		return {*this, ranges::begin(m_base)};
	}

	template <typename V2 = V const,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::is_input_range<V2>,
			bksge::is_reference<ranges::range_reference_t<V2>>
		>::value>>
	BKSGE_CONSTEXPR auto begin() const
	-> Iterator<true>
	{
		return {*this, ranges::begin(m_base)};
	}

private:
	template <typename V2 = V,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::is_forward_range<V2>,
			bksge::is_reference<InnerRange>,
			ranges::is_forward_range<InnerRange>,
			ranges::is_common_range<V2>,
			ranges::is_common_range<InnerRange>
		>::value>>
	BKSGE_CXX14_CONSTEXPR auto end_impl(bksge::detail::overload_priority<1>)
	-> Iterator<ranges::detail::is_simple_view<V2>::value>
	{
		return {*this, ranges::end(m_base)};
	}

	template <typename V2 = V>
	BKSGE_CXX14_CONSTEXPR auto end_impl(bksge::detail::overload_priority<0>)
	-> Sentinel<ranges::detail::is_simple_view<V2>::value>
	{
		return Sentinel<ranges::detail::is_simple_view<V2>::value>{*this};
	}

public:
	BKSGE_CXX14_CONSTEXPR auto end()
	->decltype(end_impl(bksge::detail::overload_priority<1>{}))
	{
		return end_impl(bksge::detail::overload_priority<1>{});
	}

private:
	template <typename V2 = V const,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::is_forward_range<V2>,
			bksge::is_reference<ranges::range_reference_t<V2>>,
			ranges::is_forward_range<ranges::range_reference_t<V2>>,
			ranges::is_common_range<V2>,
			ranges::is_common_range<ranges::range_reference_t<V2>>
		>::value>>
	BKSGE_CONSTEXPR auto end_impl(bksge::detail::overload_priority<1>) const
	-> Iterator<true>
	{
		return Iterator<true>{*this, ranges::end(m_base)};
	}

	BKSGE_CONSTEXPR auto end_impl(bksge::detail::overload_priority<0>) const
	-> Sentinel<true>
	{
		return Sentinel<true>{*this};
	}

public:
	template <typename V2 = V const,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::is_input_range<V2>,
			bksge::is_reference<ranges::range_reference_t<V2>>
		>::value>>
	BKSGE_CONSTEXPR auto end() const
	->decltype(end_impl(bksge::detail::overload_priority<1>{}))
	{
		return end_impl(bksge::detail::overload_priority<1>{});
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range>
explicit join_view(Range&&) -> join_view<views::all_t<Range>>;

template <typename View>
explicit join_view(join_view<View>) -> join_view<join_view<View>>;

#endif

namespace views
{

namespace detail
{

struct join_fn
{
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range)>
	BKSGE_CONSTEXPR auto operator()(Range&& r) const
	-> join_view<views::all_t<Range>>
	{
		return join_view<views::all_t<Range>>{bksge::forward<Range>(r)};
	}

	template <typename View>
	BKSGE_CONSTEXPR auto operator()(join_view<View> v) const
	-> join_view<join_view<View>>
	{
		return join_view<join_view<View>>{v};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor_closure<views::detail::join_fn> join{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_JOIN_VIEW_HPP
