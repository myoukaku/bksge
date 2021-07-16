/**
 *	@file	rotate.hpp
 *
 *	@brief	ranges::rotate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_ROTATE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_ROTATE_HPP

#include <bksge/fnd/algorithm/ranges/swap_ranges.hpp>
#include <bksge/fnd/algorithm/ranges/move.hpp>
#include <bksge/fnd/algorithm/ranges/reverse.hpp>
#include <bksge/fnd/algorithm/ranges/move_backward.hpp>
#include <bksge/fnd/concepts/swap.hpp>
#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_subrange_t.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

inline namespace cpo
{

struct rotate_fn
{
private:
	// if constexpr (bksge::random_access_iterator<Iter>)
	template <BKSGE_REQUIRES_PARAM(bksge::random_access_iterator, Iter)>
	static BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Iter middle, Iter lasti,
		bksge::detail::overload_priority<2>)
	{
		auto n = lasti - first;
		auto k = middle - first;

		if (k == n - k)
		{
			ranges::swap_ranges(first, middle, middle, middle + k);
			return { std::move(middle), std::move(lasti) };
		}

		auto p = first;
		auto ret = first + (lasti - middle);

		for (;;)
		{
			if (k < n - k)
			{
				// TODO: is_pod is deprecated, but this condition is
				// consistent with the STL implementation.
				//if constexpr (__is_pod(bksge::iter_value_t<Iter>))
				//{
				//	if (k == 1)
				//	{
				//		auto t = std::move(*p);
				//		ranges::move(p + 1, p + n, p);
				//		*(p + n - 1) = std::move(t);
				//		return { std::move(ret), std::move(lasti) };
				//	}
				//}

				auto q = p + k;
				for (decltype(n) i = 0; i < n - k; ++i)
				{
					ranges::iter_swap(p, q);
					++p;
					++q;
				}

				n %= k;
				if (n == 0)
				{
					return { std::move(ret), std::move(lasti) };
				}

				ranges::swap(n, k);
				k = n - k;
			}
			else
			{
				k = n - k;
				// TODO: is_pod is deprecated, but this condition is
				// consistent with the STL implementation.
				//if constexpr (__is_pod(bksge::iter_value_t<Iter>))
				//{
				//	if (k == 1)
				//	{
				//		auto t = std::move(*(p + n - 1));
				//		ranges::move_backward(p, p + n - 1, p + n);
				//		*p = std::move(t);
				//		return { std::move(ret), std::move(lasti) };
				//	}
				//}

				auto q = p + n;
				p = q - k;
				for (decltype(n) i = 0; i < n - k; ++i)
				{
					--p;
					--q;
					ranges::iter_swap(p, q);
				}

				n %= k;
				if (n == 0)
				{
					return { std::move(ret), std::move(lasti) };
				}

				ranges::swap(n, k);
			}
		}
	}

	// else if constexpr (bksge::bidirectional_iterator<Iter>)
	template <BKSGE_REQUIRES_PARAM(bksge::bidirectional_iterator, Iter)>
	static BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Iter middle, Iter lasti,
		bksge::detail::overload_priority<1>)
	{
		auto tail = lasti;

		ranges::reverse(first, middle);
		ranges::reverse(middle, tail);

		while (first != middle && middle != tail)
		{
			ranges::iter_swap(first, --tail);
			++first;
		}

		if (first == middle)
		{
			ranges::reverse(middle, tail);
			return { std::move(tail), std::move(lasti) };
		}
		else
		{
			ranges::reverse(first, middle);
			return { std::move(first), std::move(lasti) };
		}
	}

	// else
	template <typename Iter>
	static BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Iter middle, Iter lasti,
		bksge::detail::overload_priority<0>)
	{
		auto first2 = middle;
		do
		{
			ranges::iter_swap(first, first2);
			++first;
			++first2;
			if (first == middle)
			{
				middle = first2;
			}
		}
		while (first2 != lasti);

		auto ret = first;

		first2 = middle;

		while (first2 != lasti)
		{
			ranges::iter_swap(first, first2);
			++first;
			++first2;
			if (first == middle)
			{
				middle = first2;
			}
			else if (first2 == lasti)
			{
				first2 = middle;
			}
		}

		return { std::move(ret), std::move(lasti) };
	}

public:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::permutable Iter,
		bksge::sentinel_for<Iter> Sent
	>
#else
	template <
		typename Iter,
		typename Sent,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::permutable<Iter>,
			bksge::sentinel_for<Sent, Iter>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(Iter first, Iter middle, Sent last) const
	{
		auto lasti = ranges::next(first, last);
		if (first == middle)
		{
			return { lasti, lasti };
		}

		if (last == middle)
		{
			return { std::move(first), std::move(lasti) };
		}

		return impl(
			std::move(first),
			std::move(middle),
			std::move(lasti),
			bksge::detail::overload_priority<2>{});
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <ranges::forward_range Range>
	requires bksge::permutable<ranges::iterator_t<Range>>
#else
	template <
		typename Range,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::permutable<ranges::iterator_t<Range>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_subrange_t<Range>
	operator()(Range&& r, ranges::iterator_t<Range> middle) const
	{
		return (*this)(
			ranges::begin(r),
			std::move(middle),
			ranges::end(r));
	}
};

BKSGE_INLINE_VAR BKSGE_CONSTEXPR rotate_fn rotate{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_ROTATE_HPP
