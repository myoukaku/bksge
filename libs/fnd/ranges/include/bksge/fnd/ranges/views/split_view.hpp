/**
 *	@file	split_view.hpp
 *
 *	@brief	split_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_SPLIT_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_SPLIT_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/single_view.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/detail/maybe_const_t.hpp>
#include <bksge/fnd/ranges/detail/simple_view.hpp>
#include <bksge/fnd/ranges/detail/tiny_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/algorithm/ranges/mismatch.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_comparable.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/iterator/default_sentinel.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <ranges::input_range V, ranges::forward_range Pattern>
requires
	ranges::view<V> &&
	ranges::view<Pattern> &&
	bksge::indirectly_comparable<
		ranges::iterator_t<V>,
		ranges::iterator_t<Pattern>,
		ranges::equal_to> &&
	(ranges::forward_range<V> || detail::tiny_range<Pattern>)
#else
template <typename V, typename Pattern,
	typename = bksge::enable_if_t<bksge::conjunction<
		ranges::input_range<V>,
		ranges::forward_range<Pattern>,
		ranges::view<V>,
		ranges::view<Pattern>,
		bksge::indirectly_comparable<
			ranges::iterator_t<V>,
			ranges::iterator_t<Pattern>,
			ranges::equal_to>,
		bksge::disjunction<ranges::forward_range<V>, detail::tiny_range<Pattern>>
	>::value>
>
#endif
class split_view : public ranges::view_interface<split_view<V, Pattern>>
{
private:
	template <bool Const>
	struct InnerIter;

	template <bool Const>
	struct OuterIter
	{
	private:
		using Parent = ranges::detail::maybe_const_t<Const, split_view>;
		using Base   = ranges::detail::maybe_const_t<Const, V>;

		Parent* m_parent = nullptr;

		BKSGE_NO_UNIQUE_ADDRESS
		bksge::conditional_t<
			ranges::is_forward_range<V>::value,
			ranges::iterator_t<Base>,
			views::detail::Empty
		> m_current;

		BKSGE_CONSTEXPR bool at_end() const
		{
			return current() == ranges::end(m_parent->m_base);
		}

		// [range.split.outer] p1
		//  Many of the following specifications refer to the notional member
		//  current of outer-iterator.  current is equivalent to current_ if
		//  V models ranges::forward_range, and parent_->current_ otherwise.

		template <typename ThisType>
		static BKSGE_CONSTEXPR auto
		current_impl(ThisType* this_, bksge::true_type) BKSGE_NOEXCEPT
		->decltype((this_->m_current))
		{
			return this_->m_current;
		}

		template <typename ThisType>
		static BKSGE_CONSTEXPR auto
		current_impl(ThisType* this_, bksge::false_type) BKSGE_NOEXCEPT
		->decltype((this_->m_parent->m_current))
		{
			return this_->m_parent->m_current;
		}

		BKSGE_CXX14_CONSTEXPR auto current() BKSGE_NOEXCEPT
		->decltype(current_impl(this, ranges::is_forward_range<V>{}))
		{
			return current_impl(this, ranges::is_forward_range<V>{});
		}

		BKSGE_CONSTEXPR auto current() const BKSGE_NOEXCEPT
		->decltype(current_impl(this, ranges::is_forward_range<V>{}))
		{
			return current_impl(this, ranges::is_forward_range<V>{});
		}

	public:
		using iterator_concept =
			bksge::conditional_t<ranges::is_forward_range<Base>::value,
				bksge::forward_iterator_tag,
				bksge::input_iterator_tag>;
		using iterator_category = bksge::input_iterator_tag;
		using difference_type   = ranges::range_difference_t<Base>;

		struct value_type : ranges::view_interface<value_type>
		{
		private:
			OuterIter m_i = {};

		public:
			BKSGE_CONSTEXPR value_type() = default;

			BKSGE_CXX14_CONSTEXPR explicit
			value_type(OuterIter i)
				: m_i(std::move(i))
			{}

			template <BKSGE_REQUIRES_PARAM_D(bksge::copyable, I2, OuterIter)>
			BKSGE_CONSTEXPR InnerIter<Const> begin() const
			{
				return InnerIter<Const>{m_i};
			}

			template <BKSGE_REQUIRES_PARAM_D(bksge::not_copyable, I2, OuterIter)>
			BKSGE_CXX14_CONSTEXPR InnerIter<Const> begin()
			{
				return InnerIter<Const>{std::move(m_i)};
			}

			BKSGE_CONSTEXPR bksge::default_sentinel_t end() const
			{
				return bksge::default_sentinel;
			}
		};

		BKSGE_CONSTEXPR OuterIter() = default;

		template <BKSGE_REQUIRES_PARAM_D(ranges::not_forward_range, B2, Base)>
		BKSGE_CONSTEXPR explicit
		OuterIter(Parent* parent)
			: m_parent(parent)
		{}

		template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR
		OuterIter(Parent* parent, ranges::iterator_t<Base> current)
			: m_parent(parent)
			, m_current(std::move(current))
		{}

		template <bool Const2 = Const,
			typename = bksge::enable_if_t<
				Const2 &&
				bksge::is_convertible_to<
					ranges::iterator_t<V>,
					ranges::iterator_t<Base>
				>::value>>
		BKSGE_CXX14_CONSTEXPR
		OuterIter(OuterIter<!Const> i)
			: m_parent(i.m_parent)
			, m_current(std::move(i.m_current))
		{}

		BKSGE_CONSTEXPR value_type operator*() const
		{
			return value_type{*this};
		}

		BKSGE_CXX14_CONSTEXPR OuterIter& operator++()
		{
			const auto end = ranges::end(m_parent->m_base);

			if (current() == end)
			{
				return *this;
			}

			const auto sr = ranges::make_subrange(m_parent->m_pattern);
			const auto pbegin = sr.begin();
			const auto pend   = sr.end();
			if (pbegin == pend)
			{
				++current();
			}
			else
			{
				do
				{
					auto ret = ranges::mismatch(std::move(current()), end, pbegin, pend);
					current() = std::move(ret.in1);
					if (ret.in2 == pend)
					{
						break;
					}
				}
				while (++current() != end);
			}

			return *this;
		}

	private:
		BKSGE_CXX14_CONSTEXPR OuterIter increment(bksge::true_type)
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		BKSGE_CXX14_CONSTEXPR void increment(bksge::false_type)
		{
			++*this;
		}

	public:
		BKSGE_CXX14_CONSTEXPR auto operator++(int)
		->decltype(increment(ranges::is_forward_range<Base>{}))
		{
			return increment(ranges::is_forward_range<Base>{});
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator==(OuterIter const& lhs, OuterIter const& rhs)
		{
			return lhs.m_current == rhs.m_current;
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator!=(OuterIter const& lhs, OuterIter const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

		friend BKSGE_CONSTEXPR bool
		operator==(OuterIter const& lhs, bksge::default_sentinel_t)
		{
			return lhs.at_end();
		};

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR bool
		operator!=(OuterIter const& lhs, bksge::default_sentinel_t rhs)
		{
			return !(lhs == rhs);
		};

		friend BKSGE_CONSTEXPR bool
		operator==(bksge::default_sentinel_t lhs, OuterIter const& rhs)
		{
			return rhs == lhs;
		};

		friend BKSGE_CONSTEXPR bool
		operator!=(bksge::default_sentinel_t lhs, OuterIter const& rhs)
		{
			return !(lhs == rhs);
		};
#endif

		friend OuterIter<!Const>;
		friend InnerIter<Const>;
	};

	template <bool Const>
	struct InnerIter
	{
	private:
		using Base = ranges::detail::maybe_const_t<Const, V>;

		OuterIter<Const> m_i = {};
		bool m_incremented = false;

		BKSGE_CXX14_CONSTEXPR bool at_end_impl(bksge::true_type) const
		{
			auto sr = ranges::make_subrange(m_i.m_parent->m_pattern);
			auto pcur = sr.begin();
			auto pend = sr.end();
			auto end = ranges::end(m_i.m_parent->m_base);
			auto const& cur = m_i_current();
			if (cur == end)
			{
				return true;
			}

			if (pcur == pend)
			{
				return m_incremented;
			}

			return *cur == *pcur;
		}

		BKSGE_CXX14_CONSTEXPR bool at_end_impl(bksge::false_type) const
		{
			auto sr = ranges::make_subrange(m_i.m_parent->m_pattern);
			auto pcur = sr.begin();
			auto pend = sr.end();
			auto end = ranges::end(m_i.m_parent->m_base);
			auto cur = m_i_current();
			if (cur == end)
			{
				return true;
			}

			if (pcur == pend)
			{
				return m_incremented;
			}

			do
			{
				if (*cur != *pcur)
				{
					return false;
				}

				if (++pcur == pend)
				{
					return true;
				}
			}
			while (++cur != end);

			return false;
		}

		BKSGE_CXX14_CONSTEXPR bool at_end() const
		{
			return at_end_impl(detail::is_tiny_range<Pattern>{});
		}

		struct iter_cat
		{
			using Cat = typename bksge::iterator_traits<
				ranges::iterator_t<Base>
			>::iterator_category;

			using type =
				bksge::conditional_t<
					bksge::is_derived_from<Cat, bksge::forward_iterator_tag>::value,
					bksge::forward_iterator_tag,
					Cat
				>;
		};

		BKSGE_CXX14_CONSTEXPR auto m_i_current() BKSGE_NOEXCEPT
		->decltype((m_i.current()))
		{
			return m_i.current();
		}

		BKSGE_CONSTEXPR auto m_i_current() const BKSGE_NOEXCEPT
		->decltype((m_i.current()))
		{
			return m_i.current();
		}

	public:
		using iterator_concept  = typename OuterIter<Const>::iterator_concept;
		using iterator_category = typename iter_cat::type;
		using value_type        = ranges::range_value_t<Base>;
		using difference_type   = ranges::range_difference_t<Base>;

		BKSGE_CONSTEXPR InnerIter() = default;

		BKSGE_CXX14_CONSTEXPR explicit
		InnerIter(OuterIter<Const> i)
			: m_i(std::move(i))
		{}

		BKSGE_CONSTEXPR auto operator*() const
		->decltype((*m_i_current()))
		{
			return *m_i_current();
		}

	private:
		template <
			typename B2 = Base,
			typename P2 = Pattern,
			typename = bksge::enable_if_t<
				!ranges::is_forward_range<B2>::value &&
				P2::size() == 0>>
		BKSGE_CXX14_CONSTEXPR InnerIter&
		pre_increment(bksge::detail::overload_priority<1>)
		{
			return *this;
		}

		BKSGE_CXX14_CONSTEXPR InnerIter&
		pre_increment(bksge::detail::overload_priority<0>)
		{
			++m_i_current();
			return *this;
		}

	public:
		BKSGE_CXX14_CONSTEXPR InnerIter& operator++()
		{
			m_incremented = true;
			return pre_increment(bksge::detail::overload_priority<1>{});
		}

	private:
		BKSGE_CXX14_CONSTEXPR InnerIter post_increment(bksge::true_type)
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		BKSGE_CXX14_CONSTEXPR void post_increment(bksge::false_type)
		{
			++*this;
		}

	public:
		BKSGE_CXX14_CONSTEXPR auto operator++(int)
		->decltype(post_increment(ranges::is_forward_range<V>{}))
		{
			return post_increment(ranges::is_forward_range<V>{});
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator==(InnerIter const& lhs, InnerIter const& rhs)
		{
			return lhs.m_i == rhs.m_i;
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator!=(InnerIter const& lhs, InnerIter const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

		friend BKSGE_CONSTEXPR bool
		operator==(InnerIter const& lhs, bksge::default_sentinel_t)
		{
			return lhs.at_end();
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR bool
		operator!=(InnerIter const& lhs, bksge::default_sentinel_t rhs)
		{
			return !(lhs == rhs);
		}

		friend BKSGE_CONSTEXPR bool
		operator==(bksge::default_sentinel_t lhs, InnerIter const& rhs)
		{
			return rhs == lhs;
		}

		friend BKSGE_CONSTEXPR bool
		operator!=(bksge::default_sentinel_t lhs, InnerIter const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

#if 0
		friend BKSGE_CONSTEXPR decltype(auto)
		iter_move(InnerIter const& i)
			noexcept(noexcept(ranges::iter_move(i.m_i_current())))
		{
			return ranges::iter_move(i.m_i_current());
		}

		friend BKSGE_CXX14_CONSTEXPR void
		iter_swap(InnerIter const& x, InnerIter const& y)
			noexcept(noexcept(ranges::iter_swap(x.m_i_current(),
				y.m_i_current())))
			requires indirectly_swappable<ranges::iterator_t<Base>>
		{
			ranges::iter_swap(x.m_i_current(), y.m_i_current());
		}
#endif
	};

	Pattern m_pattern = {};

	BKSGE_NO_UNIQUE_ADDRESS
	bksge::conditional_t<
		!ranges::is_forward_range<V>::value,
		ranges::iterator_t<V>,
		views::detail::Empty
	> m_current = {};

	V       m_base    = {};

public:
	BKSGE_CONSTEXPR split_view() = default;

	BKSGE_CXX14_CONSTEXPR
	split_view(V base, Pattern pattern)
		: m_pattern(std::move(pattern))
		, m_base(std::move(base))
	{}

	template <BKSGE_REQUIRES_PARAM(ranges::input_range, Range),
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::is_constructible_from<V, views::all_t<Range>>,
			bksge::is_constructible_from<Pattern, ranges::single_view<ranges::range_value_t<Range>>>
		>::value>>
	BKSGE_CXX14_CONSTEXPR
	split_view(Range&& r, ranges::range_value_t<Range> e)
		: m_pattern(std::move(e))
		, m_base(views::all(bksge::forward<Range>(r)))
	{}

	template <BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, V2, V)>
	BKSGE_CONSTEXPR V base() const&
	{
		return m_base;
	}

	BKSGE_CXX14_CONSTEXPR V base() &&
	{
		return std::move(m_base);
	}

private:
	BKSGE_CXX14_CONSTEXPR auto begin_impl(bksge::true_type)
	-> OuterIter<(ranges::detail::is_simple_view<V>::value)>
	{
		return { this, ranges::begin(m_base) };
	}

	BKSGE_CXX14_CONSTEXPR auto begin_impl(bksge::false_type)
	-> OuterIter<false>
	{
		m_current = ranges::begin(m_base);
		return OuterIter<false>{this};
	}

public:
	BKSGE_CXX14_CONSTEXPR auto begin()
	->decltype(begin_impl(ranges::is_forward_range<V>{}))
	{
		return begin_impl(ranges::is_forward_range<V>{});
	}

	template <
		BKSGE_REQUIRES_PARAM_D(ranges::forward_range, V2, V),
		BKSGE_REQUIRES_PARAM_D(ranges::forward_range, V3, V const)
	>
	BKSGE_CONSTEXPR auto begin() const
	-> OuterIter<true>
	{
		return {this, ranges::begin(m_base)};
	}

	template <
		BKSGE_REQUIRES_PARAM_D(ranges::forward_range, V2, V),
		BKSGE_REQUIRES_PARAM_D(ranges::common_range,  V3, V)
	>
	BKSGE_CXX14_CONSTEXPR auto end()
	-> OuterIter<ranges::detail::is_simple_view<V>::value>
	{
		return {this, ranges::end(m_base)};
	}

private:
	BKSGE_CONSTEXPR auto end_impl(bksge::true_type) const
	-> OuterIter<true>
	{
		return {this, ranges::end(m_base)};
	}

	BKSGE_CONSTEXPR auto end_impl(bksge::false_type) const
	-> bksge::default_sentinel_t
	{
		return bksge::default_sentinel;
	}

public:
	BKSGE_CONSTEXPR auto end() const
	->decltype(end_impl(bksge::conjunction<
			ranges::is_forward_range<V>,
			ranges::is_forward_range<V const>,
			ranges::is_common_range<V const>
		>{}))
	{
		return end_impl(bksge::conjunction<
			ranges::is_forward_range<V>,
			ranges::is_forward_range<V const>,
			ranges::is_common_range<V const>
		>{});
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range, typename Pred>
split_view(Range&&, Pred&&)
-> split_view<views::all_t<Range>, views::all_t<Pred>>;

template <BKSGE_REQUIRES_PARAM(ranges::input_range, Range)>
split_view(Range&&, ranges::range_value_t<Range>)
-> split_view<views::all_t<Range>, ranges::single_view<ranges::range_value_t<Range>>>;

#endif

namespace views
{

namespace detail
{

struct split_fn
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range), typename F>
	BKSGE_CONSTEXPR auto operator()(Range&& r, F&& f) const
	{
		return split_view{ bksge::forward<Range>(r), bksge::forward<F>(f) };
	}
#else
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range), typename Pred>
	BKSGE_CXX14_CONSTEXPR auto operator()(Range&& r, Pred&& pred) const
	-> split_view<views::all_t<Range>, views::all_t<Pred>>
	{
		return split_view<views::all_t<Range>, views::all_t<Pred>>
		{
			bksge::forward<Range>(r), bksge::forward<Pred>(pred)
		};
	}

	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range)>
	BKSGE_CXX14_CONSTEXPR auto operator()(Range&& r, ranges::range_value_t<Range> v) const
	-> split_view<views::all_t<Range>, ranges::single_view<ranges::range_value_t<Range>>>
	{
		return split_view<views::all_t<Range>, ranges::single_view<ranges::range_value_t<Range>>>
		{
			bksge::forward<Range>(r), std::move(v)
		};
	}
#endif
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor<views::detail::split_fn> split{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_SPLIT_VIEW_HPP
