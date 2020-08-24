/**
 *	@file	search_n.hpp
 *
 *	@brief	ranges::search_n の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_SEARCH_N_HPP
#define BKSGE_FND_ALGORITHM_RANGES_SEARCH_N_HPP

#include <bksge/fnd/algorithm/ranges/find_if.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_comparable.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_subrange_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

struct search_n_fn
{
private:
	template <typename T, typename Pred>
	struct value_comp_t
	{
		T    const& m_value;
		Pred const& m_pred;

		template <typename R>
		BKSGE_CXX14_CONSTEXPR auto operator()(R&& arg) const
		->decltype(bksge::invoke(m_pred, bksge::forward<R>(arg), m_value))
		{
			return bksge::invoke(m_pred, bksge::forward<R>(arg), m_value);
		}
	};

	template <
		typename Iter,
		BKSGE_REQUIRES_PARAM_2(bksge::sized_sentinel_for, Iter, Sent),
		typename Difference,
		typename ValueComp,
		typename Proj>
	static BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Sent last, Difference count,
		ValueComp const& value_comp, Proj proj,
		bksge::detail::overload_priority<1>)
	{
		auto tail_size = last - first;
		auto remainder = count;

		while (remainder <= tail_size)
		{
			auto f = first + remainder;
			auto r = remainder;
			while (value_comp(bksge::invoke(proj, *--f)))
			{
				if (--r == 0)
				{
					return { f, f + count };
				}
			}
			first += r;
			tail_size -= r;
		}

		auto i = first + tail_size;
		return { i, i };
	}

	template <
		typename Iter,
		typename Sent,
		typename Difference,
		typename ValueComp,
		typename Proj>
	static BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Sent last, Difference count,
		ValueComp const& value_comp, Proj proj,
		bksge::detail::overload_priority<0>)
	{
		first = ranges::find_if(first, last, value_comp, proj);
		while (first != last)
		{
			auto n = count;
			auto i = first;
			++i;
			while (i != last && n != 1 &&
				value_comp(bksge::invoke(proj, *i)))
			{
				++i;
				--n;
			}

			if (n == 1)
			{
				return { first, i };
			}

			if (i == last)
			{
				return { i, i };
			}

			first = ranges::find_if(++i, last, value_comp, proj);
		}

		return { first, first };
	}

public:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::forward_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename T,
		typename Pred = ranges::equal_to,
		typename Proj = bksge::identity
	>
	requires bksge::indirectly_comparable<Iter, T const*, Pred, Proj>
#else
	template <
		typename Iter,
		typename Sent,
		typename T,
		typename Pred = ranges::equal_to,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::forward_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirectly_comparable<Iter, T const*, Pred, Proj>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(
		Iter first, Sent last, bksge::iter_difference_t<Iter> count,
		T const& value, Pred pred = {}, Proj proj = {}) const
	{
		if (count <= 0)
		{
			return { first, first };
		}

		value_comp_t<T, Pred> value_comp { value, pred };

		if (count == 1)
		{
			first = ranges::find_if(
				bksge::move(first),
				last,
				bksge::move(value_comp),
				bksge::move(proj));

			if (first == last)
			{
				return { first, first };
			}
			else
			{
				auto e = first;
				return { first, ++e };
			}
		}

		return impl(
			bksge::move(first),
			bksge::move(last),
			bksge::move(count),
			value_comp,
			bksge::move(proj),
			bksge::detail::overload_priority<1>{});
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::forward_range Range,
		typename T,
		typename Pred = ranges::equal_to,
		typename Proj = bksge::identity
	>
	requires bksge::indirectly_comparable<
		ranges::iterator_t<Range>, T const*, Pred, Proj>
#else
	template <
		typename Range,
		typename T,
		typename Pred = ranges::equal_to,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::indirectly_comparable<
				ranges::iterator_t<Range>, T const*, Pred, Proj>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_subrange_t<Range>
	operator()(
		Range&& r, ranges::range_difference_t<Range> count,
		T const& value, Pred pred = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(count),
			value,
			bksge::move(pred),
			bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR search_n_fn search_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_SEARCH_N_HPP
