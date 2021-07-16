/**
 *	@file	equal.hpp
 *
 *	@brief	ranges::equal の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_EQUAL_HPP
#define BKSGE_FND_ALGORITHM_RANGES_EQUAL_HPP

#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/cstring/memcmp.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_comparable.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/ranges/distance.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace ranges
{

struct equal_fn
{
private:
	template <
		typename Iter1, typename Iter2,
		typename Pred, typename Proj1, typename Proj2,
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::sized_sentinel_for<Iter1> Sent1,
		bksge::sized_sentinel_for<Iter2> Sent2
#else
		typename Sent1,
		typename Sent2,
		typename = bksge::enable_if_t<bksge::sized_sentinel_for<Sent1, Iter1>::value>,
		typename = bksge::enable_if_t<bksge::sized_sentinel_for<Sent2, Iter2>::value>
#endif
	>
	static BKSGE_CXX14_CONSTEXPR bool impl(
		bksge::detail::overload_priority<1>,
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred, Proj1 proj1, Proj2 proj2)
	{
		auto d1 = ranges::distance(first1, last1);
		auto d2 = ranges::distance(first2, last2);
		if (d1 != d2)
		{
			return false;
		}

		/*
		using ValueType1 = bksge::iter_value_t<Iter1>;
		using ValueType2 = bksge::iter_value_t<Iter2>;
		constexpr bool use_memcmp
			= ((bksge::is_integral<ValueType1>::value || bksge::is_pointer<ValueType1>::value)
			//&& __memcmpable<Iter1, Iter2>::__value
			&& bksge::is_same<Pred, ranges::equal_to>::value
			&& bksge::is_same<Proj1, bksge::identity>::value
			&& bksge::is_same<Proj2, bksge::identity>::value);
		if constexpr (use_memcmp)
		{
			if (const std::size_t len = (last1 - first1))
			{
				return !bksge::memcmp(first1, first2, len);
			}
			return true;
		}
		else
		*/
		{
			for (; first1 != last1; ++first1, (void)++first2)
			{
				if (!(bool)bksge::invoke(pred,
					bksge::invoke(proj1, *first1),
					bksge::invoke(proj2, *first2)))
				{
					return false;
				}
			}
			return true;
		}
	}

	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Pred, typename Proj1, typename Proj2
	>
	static BKSGE_CXX14_CONSTEXPR bool impl(
		bksge::detail::overload_priority<0>,
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred, Proj1 proj1, Proj2 proj2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, (void)++first2)
		{
			if (!(bool)bksge::invoke(pred,
				bksge::invoke(proj1, *first1),
				bksge::invoke(proj2, *first2)))
			{
				return false;
			}
		}
		return first1 == last1 && first2 == last2;
	}

public:
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::input_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::input_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
#else
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
#endif
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::input_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
		>::value>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires bksge::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
#endif
	BKSGE_CXX14_CONSTEXPR bool operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return impl(bksge::detail::overload_priority<1>{},
			first1, last1,
			first2, last2,
			pred, proj1, proj2);
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::input_range Range1,
		ranges::input_range Range2,
#else
		typename Range1,
		typename Range2,
#endif
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range1>,
			ranges::input_range<Range2>,
			bksge::indirectly_comparable<
				ranges::iterator_t<Range1>,
				ranges::iterator_t<Range2>,
				Pred, Proj1, Proj2
			>
		>::value>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires bksge::indirectly_comparable<
		ranges::iterator_t<Range1>,
		ranges::iterator_t<Range2>,
		Pred, Proj1, Proj2
	>
#endif
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
			std::move(pred),
			std::move(proj1),
			std::move(proj2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR equal_fn equal{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_EQUAL_HPP
