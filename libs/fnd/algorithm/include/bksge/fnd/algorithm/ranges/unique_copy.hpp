/**
 *	@file	unique_copy.hpp
 *
 *	@brief	ranges::unique_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_UNIQUE_COPY_HPP
#define BKSGE_FND_ALGORITHM_RANGES_UNIQUE_COPY_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirect_equivalence_relation.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable_storable.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename Out>
using unique_copy_result = in_out_result<Iter, Out>;

struct unique_copy_fn
{
private:
	template <
		BKSGE_REQUIRES_PARAM(bksge::forward_iterator, Iter),
		typename Sent, typename Out, typename Proj, typename Comp
	>
	static BKSGE_CXX14_CONSTEXPR unique_copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result, Comp comp, Proj proj,
		bksge::detail::overload_priority<2>)
	{
		auto next_it = first;
		*result = *next_it;
		while (++next_it != last)
		{
			if (!bksge::invoke(comp,
				bksge::invoke(proj, *first),
				bksge::invoke(proj, *next_it)))
			{
				first = next_it;
				*++result = *first;
			}
		}

		return { next_it, std::move(++result) };
	}

	template <
		typename Iter, typename Sent,
		BKSGE_REQUIRES_PARAM(bksge::input_iterator, Out),
		typename Proj, typename Comp,
		typename = bksge::enable_if_t<
			bksge::is_same_as<
				bksge::iter_value_t<Iter>,
				bksge::iter_value_t<Out>
			>::value
		>
	>
	static BKSGE_CXX14_CONSTEXPR unique_copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result, Comp comp, Proj proj,
		bksge::detail::overload_priority<1>)
	{
		*result = *first;
		while (++first != last)
		{
			if (!bksge::invoke(comp,
				bksge::invoke(proj, *result),
				bksge::invoke(proj, *first)))
			{
				*++result = *first;
			}
		}

		return { std::move(first), std::move(++result) };
	}

	template <
		typename Iter, typename Sent, typename Out,
		typename Proj, typename Comp,
		typename = bksge::enable_if_t<
			bksge::is_indirectly_copyable_storable<Iter, Out>::value
		>
	>
	static BKSGE_CXX14_CONSTEXPR unique_copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result, Comp comp, Proj proj,
		bksge::detail::overload_priority<0>)
	{
		auto value = *first;
		*result = value;
		while (++first != last)
		{
			if (!(bool)bksge::invoke(comp,
				bksge::invoke(proj, *first),
				bksge::invoke(proj, value)))
			{
				value = *first;
				*++result = value;
			}
		}

		return { std::move(first), std::move(++result) };
	}

public:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		bksge::weakly_incrementable Out,
		typename Proj = bksge::identity,
		bksge::indirect_equivalence_relation<
			bksge::projected<Iter, Proj>
		> Comp = ranges::equal_to
	>
	requires
		bksge::indirectly_copyable<Iter, Out> &&
		(bksge::forward_iterator<Iter> ||
		 (bksge::input_iterator<Out> &&
			bksge::same_as<bksge::iter_value_t<Iter>, bksge::iter_value_t<Out>>) ||
		 bksge::indirectly_copyable_storable<Iter, Out>)
#else
	template <
		typename Iter,
		typename Sent,
		typename Out,
		typename Proj = bksge::identity,
		typename Comp = ranges::equal_to,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::weakly_incrementable<Out>,
			bksge::indirect_equivalence_relation<Comp,
				bksge::projected<Iter, Proj>>,
			bksge::indirectly_copyable<Iter, Out>,
			bksge::disjunction<
				bksge::forward_iterator<Iter>,
				bksge::conjunction<
					bksge::input_iterator<Out>,
					bksge::same_as<
						bksge::iter_value_t<Iter>,
						bksge::iter_value_t<Out>>>,
				bksge::indirectly_copyable_storable<Iter, Out>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR unique_copy_result<Iter, Out>
	operator()(Iter first, Sent last, Out result,
		Comp comp = {}, Proj proj = {}) const
	{
		if (first == last)
		{
			return { std::move(first), std::move(result) };
		}

		return impl(
			std::move(first),
			std::move(last),
			std::move(result),
			std::move(comp),
			std::move(proj),
			bksge::detail::overload_priority<2>{});
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		bksge::weakly_incrementable Out,
		typename Proj = bksge::identity,
		bksge::indirect_equivalence_relation<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Comp = ranges::equal_to
	>
	requires bksge::indirectly_copyable<ranges::iterator_t<Range>, Out> &&
		(bksge::forward_iterator<ranges::iterator_t<Range>> ||
		(bksge::input_iterator<Out> &&
			bksge::same_as<ranges::range_value_t<Range>, bksge::iter_value_t<Out>>) ||
		bksge::indirectly_copyable_storable<ranges::iterator_t<Range>, Out>)
#else
	template <
		typename Range,
		typename Out,
		typename Proj = bksge::identity,
		typename Comp = ranges::equal_to,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::weakly_incrementable<Out>,
			bksge::indirect_equivalence_relation<Comp,
				bksge::projected<ranges::iterator_t<Range>, Proj>>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>,
			bksge::disjunction<
				bksge::forward_iterator<
					ranges::iterator_t<Range>>,
				bksge::conjunction<
					bksge::input_iterator<Out>,
					bksge::same_as<
						ranges::range_value_t<Range>,
						bksge::iter_value_t<Out>>>,
				bksge::indirectly_copyable_storable<
					ranges::iterator_t<Range>, Out>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	unique_copy_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(Range&& r, Out result, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result),
			std::move(comp),
			std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR unique_copy_fn unique_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_UNIQUE_COPY_HPP
