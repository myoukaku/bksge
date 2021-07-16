/**
 *	@file	copy_backward.hpp
 *
 *	@brief	ranges::copy_backward の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_COPY_BACKWARD_HPP
#define BKSGE_FND_ALGORITHM_RANGES_COPY_BACKWARD_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/cstring/memmove.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/detail/is_memcpyable.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename Out>
using copy_backward_result = in_out_result<Iter, Out>;

struct copy_backward_fn
{
private:
	template <
		typename Iter,
		BKSGE_REQUIRES_PARAM_2(bksge::sized_sentinel_for, Iter, Sent),
		typename Out
	>
	static BKSGE_CXX14_CONSTEXPR copy_backward_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		bksge::detail::overload_priority<1>)
	{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
		if (!std::is_constant_evaluated())
		{
			if constexpr (bksge::detail::is_memcpyable<Out, Iter>::value)
			{
				using ValueTypeI = bksge::iter_value_t<Iter>;
				static_assert(bksge::is_copy_assignable<ValueTypeI>::value, "");
				auto num = last - first;
				if (num)
				{
					bksge::memmove(result - num, first, sizeof(ValueTypeI) * num);
				}
				return { first + num, result - num };
			}
		}
#endif

		auto lasti = ranges::next(first, last);
		auto tail = lasti;

		for (auto n = last - first; n > 0; --n)
		{
			--tail;
			--result;
			*result = *tail;
		}

		return { std::move(lasti), std::move(result) };
	}

	template <typename Iter, typename Sent, typename Out>
	static BKSGE_CXX14_CONSTEXPR copy_backward_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		bksge::detail::overload_priority<0>)
	{
		auto lasti = ranges::next(first, last);
		auto tail = lasti;

		while (first != tail)
		{
			--tail;
			--result;
			*result = *tail;
		}

		return { std::move(lasti), std::move(result) };
	}

public:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::bidirectional_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		bksge::bidirectional_iterator Out
	>
	requires bksge::indirectly_copyable<Iter, Out>
#else
	template <
		typename Iter,
		typename Sent,
		typename Out,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::bidirectional_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::bidirectional_iterator<Out>,
			bksge::indirectly_copyable<Iter, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR copy_backward_result<Iter, Out>
	operator()(Iter first, Sent last, Out result) const
	{
		return impl(
			std::move(first),
			std::move(last),
			std::move(result),
			bksge::detail::overload_priority<1>{});
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::bidirectional_range Range,
		bksge::bidirectional_iterator Out
	>
	requires bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
#else
	template <
		typename Range,
		typename Out,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::bidirectional_range<Range>,
			bksge::bidirectional_iterator<Out>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	copy_backward_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(Range&& r, Out result) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR copy_backward_fn copy_backward{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_COPY_BACKWARD_HPP
