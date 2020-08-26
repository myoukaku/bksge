/**
 *	@file	fill.hpp
 *
 *	@brief	ranges::fill の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_FILL_HPP
#define BKSGE_FND_ALGORITHM_RANGES_FILL_HPP

#include <bksge/fnd/algorithm/ranges/fill_n.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/iterator/concepts/output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/ranges/concepts/output_range.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/is_scalar.hpp>

namespace bksge
{

namespace ranges
{

struct fill_fn
{
private:
	template <
		typename T,
		typename Out,
		BKSGE_REQUIRES_PARAM_2(bksge::sized_sentinel_for, Out, Sent)
	>
	static BKSGE_CXX14_CONSTEXPR Out
	impl(Out first, Sent last, T const& value,
		bksge::detail::overload_priority<2>)
	{
		auto const len = last - first;
		return ranges::fill_n(first, len, value);
	}

	template <typename T, typename Out, typename Sent,
		typename = bksge::enable_if_t<bksge::is_scalar<T>::value>>
	static BKSGE_CXX14_CONSTEXPR Out
	impl(Out first, Sent last, T const& value,
		bksge::detail::overload_priority<1>)
	{
		const auto tmp = value;
		for (; first != last; ++first)
		{
			*first = tmp;
		}

		return first;
	}

	template <typename T, typename Out, typename Sent>
	static BKSGE_CXX14_CONSTEXPR Out
	impl(Out first, Sent last, T const& value,
		bksge::detail::overload_priority<0>)
	{
		for (; first != last; ++first)
		{
			*first = value;
		}

		return first;
	}

public:
	template <
		typename T,
		BKSGE_REQUIRES_PARAM_2(bksge::output_iterator, T const&, Out),
		BKSGE_REQUIRES_PARAM_2(bksge::sentinel_for, Out, Sent)
	>
	BKSGE_CXX14_CONSTEXPR Out operator()(
		Out first, Sent last, T const& value) const
	{
		return impl(
			bksge::move(first),
			bksge::move(last),
			value,
			bksge::detail::overload_priority<2>{});
	}

	template <
		typename T,
		BKSGE_REQUIRES_PARAM_2(ranges::output_range, T const&, Range)
	>
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, T const& value) const
	{
		return (*this)(ranges::begin(r), ranges::end(r), value);
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR fill_fn fill{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_FILL_HPP
