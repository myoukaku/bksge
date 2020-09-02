/**
 *	@file	lexicographical_compare.hpp
 *
 *	@brief	ranges::lexicographical_compare の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_LEXICOGRAPHICAL_COMPARE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_LEXICOGRAPHICAL_COMPARE_HPP

#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
//#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/iterator/projected.hpp>
//#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

struct lexicographical_compare_fn
{
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::input_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::input_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<Iter1, Proj1>,
			bksge::projected<Iter2, Proj2>
		> Comp = ranges::less
#else
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::input_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<Iter1, Proj1>,
				bksge::projected<Iter2, Proj2>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR bool
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
#if 0
		if constexpr (
			detail::is_normal_iterator<Iter1> &&
			same_as<Iter1, Sent1>)
		{
			return (*this)(first1.base(), last1.base(),
				bksge::move(first2), bksge::move(last2),
				bksge::move(comp),
				bksge::move(proj1), bksge::move(proj2));
		}
		else if constexpr (
			detail::is_normal_iterator<Iter2> &&
			same_as<Iter2, Sent2>)
		{
			return (*this)(bksge::move(first1), bksge::move(last1),
				first2.base(), last2.base(),
				bksge::move(comp),
				bksge::move(proj1), bksge::move(proj2));
		}
		else
#endif
		{
#if 0
			constexpr bool sized_iters =
				(bksge::sized_sentinel_for<Sent1, Iter1> &&
				 bksge::sized_sentinel_for<Sent2, Iter2>);
			if constexpr (sized_iters)
			{
				using ValueType1 = bksge::iter_value_t<Iter1>;
				using ValueType2 = bksge::iter_value_t<Iter2>;
				// This condition is consistent with the one in
				// lexicographical_compare_aux in <bits/stl_algobase.h>.
				constexpr bool use_memcmp = (is_byte<ValueType1>::value
						&& is_byte<ValueType2>::value
						&& !gnu_cxx::numeric_traits<ValueType1>::is_signed
						&& !gnu_cxx::numeric_traits<ValueType2>::is_signed
						&& ptr_to_nonvolatile<Iter1>
						&& ptr_to_nonvolatile<Iter2>
						&& (is_same_v<Comp, ranges::less>
							|| is_same_v<Comp, ranges::greater>)
						&& is_same_v<Proj1, bksge::identity>
						&& is_same_v<Proj2, bksge::identity>);
				if constexpr (use_memcmp)
				{
					const auto d1 = last1 - first1;
					const auto d2 = last2 - first2;

					if (const auto len = std::min(d1, d2))
					{
						const auto c = std::memcmp(first1, first2, len);
						if constexpr (is_same_v<Comp, ranges::less>)
						{
							if (c < 0)
							{
								return true;
							}
							if (c > 0)
							{
								return false;
							}
						}
						else if constexpr (is_same_v<Comp, ranges::greater>)
						{
							if (c > 0)
							{
								return true;
							}
							if (c < 0)
							{
								return false;
							}
						}
					}

					return d1 < d2;
				}
			}
#endif

			for (; first1 != last1 && first2 != last2; ++first1, (void)++first2)
			{
				if (bksge::invoke(comp,
					bksge::invoke(proj1, *first1),
					bksge::invoke(proj2, *first2)))
				{
					return true;
				}

				if (bksge::invoke(comp,
					bksge::invoke(proj2, *first2),
					bksge::invoke(proj1, *first1)))
				{
					return false;
				}
			}

			return first1 == last1 && first2 != last2;
		}
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::input_range Range1,
		ranges::input_range Range2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<ranges::iterator_t<Range1>, Proj1>,
			bksge::projected<ranges::iterator_t<Range2>, Proj2>
		> Comp = ranges::less
#else
		typename Range1,
		typename Range2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range1>,
			ranges::input_range<Range2>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<ranges::iterator_t<Range1>, Proj1>,
				bksge::projected<ranges::iterator_t<Range2>, Proj2>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR bool
	operator()(Range1&& r1, Range2&& r2,
		Comp comp = {},
		Proj1 proj1 = {}, Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			bksge::move(comp),
			bksge::move(proj1), bksge::move(proj2));
	}

private:
#if 0
	template <typename Iter, typename Ref = iter_reference_t<Iter>>
	static constexpr bool ptr_to_nonvolatile =
		is_pointer_v<Iter> && !is_volatile_v<remove_reference_t<Ref>>;
#endif
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR lexicographical_compare_fn lexicographical_compare{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_LEXICOGRAPHICAL_COMPARE_HPP
