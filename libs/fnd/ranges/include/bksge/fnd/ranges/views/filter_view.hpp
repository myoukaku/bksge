/**
 *	@file	filter_view.hpp
 *
 *	@brief	filter_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_FILTER_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_FILTER_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/detail/has_arrow.hpp>
#include <bksge/fnd/ranges/detail/box.hpp>
#include <bksge/fnd/ranges/detail/cached_position.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/range_reference_t.hpp>
#include <bksge/fnd/ranges/range_rvalue_reference_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/algorithm/ranges/find_if.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/functional/ref.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_swappable.hpp>
#include <bksge/fnd/iterator/ranges/iter_move.hpp>
#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <
	ranges::input_range V,
	bksge::indirect_unary_predicate<ranges::iterator_t<V>> Pred
>
requires ranges::view<V> && bksge::is_object<Pred>::value
#else
template <
	typename V, typename Pred,
	typename = bksge::enable_if_t<bksge::conjunction<
		ranges::input_range<V>,
		bksge::indirect_unary_predicate<Pred, ranges::iterator_t<V>>,
		ranges::view<V>,
		bksge::is_object<Pred>
	>::value>
>
#endif
class filter_view : public ranges::view_interface<filter_view<V, Pred>>
{
private:
	struct Sentinel;

	struct Iterator
	{
	private:
		friend filter_view;

		using v_iter = ranges::iterator_t<V>;

		struct iter_concept
		{
			using type =
				bksge::conditional_t<ranges::is_bidirectional_range<V>::value,
					bksge::bidirectional_iterator_tag,
				bksge::conditional_t<ranges::is_forward_range<V>::value,
					bksge::forward_iterator_tag,
					bksge::input_iterator_tag>>;
		};

		struct iter_cat
		{
			using Cat = typename bksge::iterator_traits<v_iter>::iterator_category;
			using type =
				bksge::conditional_t<bksge::is_derived_from<Cat, bksge::bidirectional_iterator_tag>::value,
					bksge::bidirectional_iterator_tag,
				bksge::conditional_t<bksge::is_derived_from<Cat, bksge::forward_iterator_tag>::value,
					bksge::forward_iterator_tag,
					Cat>>;
		};

	private:
		v_iter       m_current = {};
		filter_view* m_parent  = nullptr;

	public:
		using iterator_concept  = typename iter_concept::type;
		using iterator_category = typename iter_cat::type;
		using value_type        = ranges::range_value_t<V>;
		using difference_type   = ranges::range_difference_t<V>;

		BKSGE_CONSTEXPR Iterator() = default;

		BKSGE_CXX14_CONSTEXPR
		Iterator(filter_view* parent, v_iter current)
			: m_current(std::move(current))
			, m_parent(parent)
		{}

		BKSGE_CONSTEXPR v_iter base() const&
			BKSGE_REQUIRES(bksge::copyable<v_iter>)
		{
			return m_current;
		}

		BKSGE_CXX14_CONSTEXPR v_iter base() &&
		{
			return std::move(m_current);
		}

		BKSGE_CONSTEXPR ranges::range_reference_t<V>
		operator*() const
		{
			return *m_current;
		}

		BKSGE_CONSTEXPR v_iter operator->() const
			BKSGE_REQUIRES(
				ranges::detail::has_arrow<v_iter> &&
				bksge::copyable<v_iter>)
		{
			return m_current;
		}

		BKSGE_CXX14_CONSTEXPR Iterator& operator++()
		{
			m_current = ranges::find_if(std::move(++m_current),
				ranges::end(m_parent->m_base),
				bksge::ref(m_parent->pred()));
			return *this;
		}

	private:
		template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, V2, V)>
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

		template <BKSGE_REQUIRES_PARAM_D(ranges::bidirectional_range, V2, V)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator--()
		{
			do
			{
				--m_current;
			}
			while (!bksge::invoke(m_parent->pred(), *m_current));

			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::bidirectional_range, V2, V)>
		BKSGE_CXX14_CONSTEXPR Iterator operator--(int)
		{
			auto tmp = *this;
			--*this;
			return tmp;
		}

		friend BKSGE_CONSTEXPR bool
		operator==(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::equality_comparable<v_iter>)
		{
			return lhs.m_current == rhs.m_current;
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator const& lhs, Iterator const& rhs)
			BKSGE_REQUIRES(bksge::equality_comparable<v_iter>)
		{
			return !(lhs == rhs);
		}
#endif

#if 0
		friend BKSGE_CONSTEXPR ranges::range_rvalue_reference_t<V>
		iter_move(Iterator const& i)
			BKSGE_NOEXCEPT_IF_EXPR(ranges::iter_move(i.m_current))
		{
			return ranges::iter_move(i.m_current);
		}

		friend BKSGE_CXX14_CONSTEXPR void
		iter_swap(Iterator const& x, Iterator const& y)
			BKSGE_NOEXCEPT_IF_EXPR(ranges::iter_swap(x.m_current, y.m_current))
			BKSGE_REQUIRES(bksge::indirectly_swappable<v_iter>)
		{
			ranges::iter_swap(x.m_current, y.m_current);
		}
#endif
	};

	struct Sentinel
	{
	private:
		ranges::sentinel_t<V> m_end {};

		BKSGE_CONSTEXPR bool equal(Iterator const& i) const
		{
			return i.m_current == m_end;
		}

	public:
		BKSGE_CONSTEXPR Sentinel() = default;

		BKSGE_CONSTEXPR explicit
		Sentinel(filter_view* parent)
			: m_end(ranges::end(parent->m_base))
		{}

		BKSGE_CONSTEXPR ranges::sentinel_t<V> base() const
		{
			return m_end;
		}

		friend BKSGE_CONSTEXPR bool
		operator==(Iterator const& lhs, const Sentinel& rhs)
		{
			return rhs.equal(lhs);
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator const& lhs, const Sentinel& rhs)
		{
			return !(lhs == rhs);
		}

		friend BKSGE_CONSTEXPR bool
		operator==(Sentinel const& lhs, const Iterator& rhs)
		{
			return rhs == lhs;
		}

		friend BKSGE_CONSTEXPR bool
		operator!=(Sentinel const& lhs, const Iterator& rhs)
		{
			return !(lhs == rhs);
		}
#endif
	};

	BKSGE_NO_UNIQUE_ADDRESS ranges::detail::box<Pred> m_pred;
	BKSGE_NO_UNIQUE_ADDRESS ranges::detail::cached_position<V> m_cached_begin;
	V m_base = {};

public:
	BKSGE_CONSTEXPR filter_view() = default;

	BKSGE_CXX14_CONSTEXPR
	filter_view(V base, Pred pred)
		: m_pred(std::move(pred))
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

	BKSGE_CONSTEXPR Pred const& pred() const
	{
		return *m_pred;
	}

	BKSGE_CXX14_CONSTEXPR Iterator begin()
	{
		if (m_cached_begin.has_value())
		{
			return { this, m_cached_begin.get(m_base) };
		}

#if BKSGE_CXX_STANDARD >= 17
		BKSGE_ASSERT(m_pred.has_value());
#endif

		auto it = ranges::find_if(
			ranges::begin(m_base),
			ranges::end(m_base),
			bksge::ref(pred()));
		m_cached_begin.set(m_base, it);
		return { this, std::move(it) };
	}

private:
	template <BKSGE_REQUIRES_PARAM_D(ranges::common_range, V2, V)>
	BKSGE_CXX14_CONSTEXPR Iterator
	end_impl(bksge::detail::overload_priority<1>)
	{
		return Iterator{ this, ranges::end(m_base) };
	}

	BKSGE_CXX14_CONSTEXPR Sentinel
	end_impl(bksge::detail::overload_priority<0>)
	{
		return Sentinel{ this };
	}

public:
	BKSGE_CXX14_CONSTEXPR auto end()
	->decltype(end_impl(bksge::detail::overload_priority<1>{}))
	{
		return end_impl(bksge::detail::overload_priority<1>{});
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range, typename Pred>
filter_view(Range&&, Pred) -> filter_view<views::all_t<Range>, Pred>;

#endif

namespace views
{

namespace detail
{

struct filter_fn
{
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range), typename Pred>
	BKSGE_CONSTEXPR auto operator()(Range&& r, Pred&& p) const
	-> filter_view<views::all_t<Range>, Pred>
	{
		return filter_view<views::all_t<Range>, Pred>
		{
			bksge::forward<Range>(r), bksge::forward<Pred>(p)
		};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor<views::detail::filter_fn> filter{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_FILTER_VIEW_HPP
