/**
 *	@file	minmax.hpp
 *
 *	@brief	ranges::minmax の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_MINMAX_HPP
#define BKSGE_FND_ALGORITHM_RANGES_MINMAX_HPP

#include <bksge/fnd/algorithm/ranges/min_max_result.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable_storable.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>
#include <initializer_list>

namespace bksge
{

namespace ranges
{

template <typename T>
using minmax_result = min_max_result<T>;

struct minmax_fn
{
	template <
		typename T,
		typename Proj = bksge::identity,
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::indirect_strict_weak_order<
			bksge::projected<T const*, Proj>
		> Comp = ranges::less
#else
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<T const*, Proj>
			>::value
		>
#endif
	>
	BKSGE_CXX14_CONSTEXPR minmax_result<T const&>
	operator()(T const& a, T const& b,
		Comp comp = {}, Proj proj = {}) const
	{
		if (bksge::invoke(bksge::move(comp),
			bksge::invoke(proj, b),
			bksge::invoke(proj, a)))
		{
			return { b, a };
		}
		else
		{
			return { a, b };
		}
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		typename Proj = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Comp = ranges::less
	>
	requires bksge::indirectly_copyable_storable<
		ranges::iterator_t<Range>,
		ranges::range_value_t<Range>*>
#else
	template <
		typename Range,
		typename Proj = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<ranges::iterator_t<Range>, Proj>>,
			bksge::indirectly_copyable_storable<
				ranges::iterator_t<Range>,
				ranges::range_value_t<Range>*>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR minmax_result<ranges::range_value_t<Range>>
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	{
		auto first = ranges::begin(r);
		auto last = ranges::end(r);
		BKSGE_ASSERT(bool(first != last));
		minmax_result<ranges::range_value_t<Range>> result = { *first, *first };
		while (++first != last)
		{
			auto tmp = *first;
			if (bksge::invoke(comp,
				bksge::invoke(proj, tmp),
				bksge::invoke(proj, result.min)))
			{
				result.min = bksge::move(tmp);
			}

			if (!(bool)bksge::invoke(comp,
				bksge::invoke(proj, tmp),
				bksge::invoke(proj, result.max)))
			{
				result.max = bksge::move(tmp);
			}
		}

		return result;
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::copyable T,
		typename Proj = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<T const*, Proj>
		> Comp = ranges::less
#else
		typename T,
		typename Proj = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::copyable<T>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<T const*, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR minmax_result<T>
	operator()(std::initializer_list<T> r,
		Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(ranges::subrange<T const*>(r),
			bksge::move(comp), bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR minmax_fn minmax{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_MINMAX_HPP
