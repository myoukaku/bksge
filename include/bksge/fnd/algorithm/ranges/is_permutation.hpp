/**
 *	@file	is_permutation.hpp
 *
 *	@brief	ranges::is_permutation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_IS_PERMUTATION_HPP
#define BKSGE_FND_ALGORITHM_RANGES_IS_PERMUTATION_HPP

#include <bksge/fnd/algorithm/ranges/find_if.hpp>
#include <bksge/fnd/algorithm/ranges/count_if.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_equivalence_relation.hpp>
#include <bksge/fnd/iterator/ranges/distance.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
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

struct is_permutation_fn
{
private:
	template <typename Pred, typename Proj, typename Iter>
	struct comp_scan_t
	{
		Pred& m_pred;
		Proj& m_proj;
		Iter& m_scan;

		template <typename T>
		BKSGE_CXX14_CONSTEXPR auto operator()(T&& arg) const
		->decltype(bksge::invoke(m_pred, bksge::invoke(m_proj, *m_scan), bksge::forward<T>(arg)))
		{
			return bksge::invoke(m_pred, bksge::invoke(m_proj, *m_scan), bksge::forward<T>(arg));
		}
	};

public:
	template<
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::forward_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::forward_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		bksge::indirect_equivalence_relation<
			bksge::projected<Iter1, Proj1>,
			bksge::projected<Iter2, Proj2>
		> Pred = ranges::equal_to
#else
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename Pred = ranges::equal_to,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::forward_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::forward_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::indirect_equivalence_relation<
				Pred,
				bksge::projected<Iter1, Proj1>,
				bksge::projected<Iter2, Proj2>
			>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR bool operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		constexpr bool sized_iters =
			(bksge::is_sized_sentinel_for<Sent1, Iter1>::value &&
			 bksge::is_sized_sentinel_for<Sent2, Iter2>::value);

#if defined(BKSGE_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (sized_iters)
#else
		if (sized_iters)
#endif
		{
			auto d1 = ranges::distance(first1, last1);
			auto d2 = ranges::distance(first2, last2);
			if (d1 != d2)
			{
				return false;
			}
		}

		// Efficiently compare identical prefixes:  O(N) if sequences
		// have the same elements in the same order.
		for (; first1 != last1 && first2 != last2; ++first1, (void)++first2)
		{
			if (!(bool)bksge::invoke(pred,
				bksge::invoke(proj1, *first1),
				bksge::invoke(proj2, *first2)))
			{
				break;
			}
		}

#if defined(BKSGE_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (sized_iters)
#else
		if (sized_iters)
#endif
		{
			if (first1 == last1)
			{
				return true;
			}
		}
		else
		{
			auto d1 = ranges::distance(first1, last1);
			auto d2 = ranges::distance(first2, last2);
			if (d1 == 0 && d2 == 0)
			{
				return true;
			}

			if (d1 != d2)
			{
				return false;
			}
		}

		for (auto scan = first1; scan != last1; ++scan)
		{
			auto comp_scan = comp_scan_t<Pred, Proj1, Iter1> {pred, proj1, scan};

			if (scan != ranges::find_if(first1, scan, comp_scan, proj1))
			{
				continue; // We've seen this one before.
			}

			auto matches = ranges::count_if(first2, last2, comp_scan, proj2);
			if (matches == 0 || ranges::count_if(scan, last1, comp_scan, proj1) != matches)
			{
				return false;
			}
		}

		return true;
	}

	template<
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::forward_range Range1,
		ranges::forward_range Range2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		bksge::indirect_equivalence_relation<
			bksge::projected<iterator_t<Range1>, Proj1>,
			bksge::projected<iterator_t<Range2>, Proj2>
		> Pred = ranges::equal_to
#else
		typename Range1,
		typename Range2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename Pred = ranges::equal_to,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range1>,
			ranges::forward_range<Range2>,
			bksge::indirect_equivalence_relation<
				Pred,
				bksge::projected<iterator_t<Range1>, Proj1>,
				bksge::projected<iterator_t<Range2>, Proj2>
			>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR bool operator()(
		Range1&& r1,
		Range2&& r2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			bksge::move(pred),
			bksge::move(proj1),
			bksge::move(proj2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR is_permutation_fn is_permutation{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_IS_PERMUTATION_HPP
