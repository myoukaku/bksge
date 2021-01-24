/**
 *	@file	copy.hpp
 *
 *	@brief	ranges::copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_COPY_HPP
#define BKSGE_FND_ALGORITHM_RANGES_COPY_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/cstring/memmove.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/detail/is_memcpyable.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>	// is_constant_evaluated

namespace bksge
{

namespace ranges
{

template <typename Iter, typename Out>
using copy_result = in_out_result<Iter, Out>;

struct copy_fn
{
private:
	template <
		typename Iter,
		BKSGE_REQUIRES_PARAM_2(bksge::sized_sentinel_for, Iter, Sent),
		typename Out
	>
	static BKSGE_CXX14_CONSTEXPR copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		bksge::detail::overload_priority<1>)
	{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
		if (!std::is_constant_evaluated())
		{
			if constexpr (bksge::detail::is_memcpyable<Iter, Out>::value)
			{
				using ValueTypeI = bksge::iter_value_t<Iter>;
				static_assert(bksge::is_copy_assignable<ValueTypeI>::value);
				auto num = last - first;
				if (num)
				{
					bksge::memmove(result, first, sizeof(ValueTypeI) * num);
				}
				return { first + num, result + num };
			}
		}
#endif

		for (auto n = last - first; n > 0; --n)
		{
			*result = *first;
			++first;
			++result;
		}

		return { bksge::move(first), bksge::move(result) };
	}

	template <
		typename Iter,
		typename Sent,
		typename Out
	>
	static BKSGE_CXX14_CONSTEXPR copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		bksge::detail::overload_priority<0>)
	{
		while (first != last)
		{
			*result = *first;
			++first;
			++result;
		}

		return { bksge::move(first), bksge::move(result) };
	}

public:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		bksge::weakly_incrementable Out
	>
	requires bksge::indirectly_copyable<Iter, Out>
#else
	template <
		typename Iter,
		typename Sent,
		typename Out,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::weakly_incrementable<Out>,
			bksge::indirectly_copyable<Iter, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR copy_result<Iter, Out>
	operator()(Iter first, Sent last, Out result) const
	{
		return impl(
			bksge::move(first),
			bksge::move(last),
			bksge::move(result),
			bksge::detail::overload_priority<1>{});
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		bksge::weakly_incrementable Out
	>
	requires bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
#else
	template <
		typename Range,
		typename Out,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::weakly_incrementable<Out>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR copy_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(Range&& r, Out result) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(result));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR copy_fn copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_COPY_HPP
