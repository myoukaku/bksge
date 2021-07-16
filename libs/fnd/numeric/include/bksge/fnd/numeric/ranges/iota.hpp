/**
 *	@file	iota.hpp
 *
 *	@brief	ranges::iota の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_RANGES_IOTA_HPP
#define BKSGE_FND_NUMERIC_RANGES_IOTA_HPP

#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/ranges/concepts/output_range.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

struct iota_fn
{
	template <
		BKSGE_REQUIRES_PARAM(bksge::weakly_incrementable, T),
		BKSGE_REQUIRES_PARAM_2(bksge::output_iterator, T const&, Iter),
		BKSGE_REQUIRES_PARAM_2(bksge::sentinel_for, Iter, Sent)
	>
	BKSGE_CXX14_CONSTEXPR Iter
	operator()(Iter first, Sent last, T value) const
	{
		for (; first != last; ++first)
		{
			*first = value;
			++value;
		}
		return first;
	}

	template <
		BKSGE_REQUIRES_PARAM(bksge::weakly_incrementable, T),
		BKSGE_REQUIRES_PARAM_2(ranges::output_range, T const&, Range)
	>
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, T value) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(value));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR iota_fn iota{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_RANGES_IOTA_HPP
