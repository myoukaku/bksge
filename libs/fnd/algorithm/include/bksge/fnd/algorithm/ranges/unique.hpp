/**
 *	@file	unique.hpp
 *
 *	@brief	ranges::unique の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_UNIQUE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_UNIQUE_HPP

#include <bksge/fnd/algorithm/ranges/adjacent_find.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_equivalence_relation.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_subrange_t.hpp>
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

struct unique_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::permutable Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Proj = bksge::identity,
		bksge::indirect_equivalence_relation<
			bksge::projected<Iter, Proj>
		> Comp = ranges::equal_to
	>
#else
	template <
		typename Iter,
		typename Sent,
		typename Proj = bksge::identity,
		typename Comp = ranges::equal_to,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::permutable<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_equivalence_relation<Comp,
				bksge::projected<Iter, Proj>
			>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(Iter first, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		first = ranges::adjacent_find(first, last, comp, proj);
		if (first == last)
		{
			return { first, first };
		}

		auto dest = first;
		++first;
		while (++first != last)
		{
			if (!bksge::invoke(comp,
				bksge::invoke(proj, *dest),
				bksge::invoke(proj, *first)))
			{
				*++dest = std::move(*first);
			}
		}

		return { ++dest, first };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::forward_range Range,
		typename Proj = bksge::identity,
		bksge::indirect_equivalence_relation<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Comp = ranges::equal_to
	>
	requires bksge::permutable<ranges::iterator_t<Range>>
#else
	template <
		typename Range,
		typename Proj = bksge::identity,
		typename Comp = ranges::equal_to,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::indirect_equivalence_relation<Comp,
				bksge::projected<ranges::iterator_t<Range>, Proj>
			>,
			bksge::permutable<ranges::iterator_t<Range>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_subrange_t<Range>
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(comp), std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR unique_fn unique{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_UNIQUE_HPP
