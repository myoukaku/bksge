/**
 *	@file	partial_sort_copy.hpp
 *
 *	@brief	ranges::partial_sort_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_PARTIAL_SORT_COPY_HPP
#define BKSGE_FND_ALGORITHM_RANGES_PARTIAL_SORT_COPY_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/algorithm/ranges/make_heap.hpp>
#include <bksge/fnd/algorithm/ranges/pop_heap.hpp>
#include <bksge/fnd/algorithm/ranges/push_heap.hpp>
#include <bksge/fnd/algorithm/ranges/sort_heap.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/iterator/concepts/sortable.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename Out>
using partial_sort_copy_result = in_out_result<Iter, Out>;

struct partial_sort_copy_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator         Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::random_access_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
		typename Comp = ranges::less,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires
		bksge::indirectly_copyable<Iter1, Iter2> &&
		bksge::sortable<Iter2, Comp, Proj2> &&
		bksge::indirect_strict_weak_order<Comp,
			bksge::projected<Iter1, Proj1>,
			bksge::projected<Iter2, Proj2>>
#else
	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Comp = ranges::less,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator <Iter1>,
			bksge::sentinel_for<Sent1, Iter1>,
			bksge::random_access_iterator<Iter2>,
			bksge::sentinel_for<Sent2, Iter2>,
			bksge::indirectly_copyable<Iter1, Iter2>,
			bksge::sortable<Iter2, Comp, Proj2>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<Iter1, Proj1>,
				bksge::projected<Iter2, Proj2>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR partial_sort_copy_result<Iter1, Iter2>
	operator()(
		Iter1 first,        Sent1 last,
		Iter2 result_first, Sent2 result_last,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		if (result_first == result_last)
		{
			// TODO: Eliminating the variable lasti triggers an ICE.
			auto lasti = ranges::next(std::move(first), std::move(last));
			return { std::move(lasti), std::move(result_first) };
		}

		auto result_real_last = result_first;
		while (first != last && result_real_last != result_last)
		{
			*result_real_last = *first;
			++result_real_last;
			++first;
		}

		ranges::make_heap(result_first, result_real_last, comp, proj2);
		for (; first != last; ++first)
		{
			if (bksge::invoke(comp,
				bksge::invoke(proj1, *first),
				bksge::invoke(proj2, *result_first)))
			{
				ranges::pop_heap(result_first, result_real_last, comp, proj2);
				*(result_real_last-1) = *first;
				ranges::push_heap(result_first, result_real_last, comp, proj2);
			}
		}

		ranges::sort_heap(result_first, result_real_last, comp, proj2);

		return { std::move(first), std::move(result_real_last) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range         Range1,
		ranges::random_access_range Range2,
		typename Comp = ranges::less,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires
		bksge::indirectly_copyable<
			ranges::iterator_t<Range1>,
			ranges::iterator_t<Range2>> &&
		bksge::sortable<ranges::iterator_t<Range2>, Comp, Proj2> &&
		bksge::indirect_strict_weak_order<Comp,
			bksge::projected<ranges::iterator_t<Range1>, Proj1>,
			bksge::projected<ranges::iterator_t<Range2>, Proj2>>
#else
	template <
		typename Range1,
		typename Range2,
		typename Comp = ranges::less,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range1>,
			ranges::random_access_range<Range2>,
			bksge::indirectly_copyable<
				ranges::iterator_t<Range1>,
				ranges::iterator_t<Range2>>,
			bksge::sortable<ranges::iterator_t<Range2>, Comp, Proj2>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<ranges::iterator_t<Range1>, Proj1>,
				bksge::projected<ranges::iterator_t<Range2>, Proj2>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR partial_sort_copy_result<
		ranges::borrowed_iterator_t<Range1>,
		ranges::borrowed_iterator_t<Range2>>
	operator()(
		Range1&& r, Range2&& out,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			ranges::begin(out), ranges::end(out),
			std::move(comp),
			std::move(proj1),
			std::move(proj2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR partial_sort_copy_fn partial_sort_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_PARTIAL_SORT_COPY_HPP
