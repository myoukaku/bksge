/**
 *	@file	all.hpp
 *
 *	@brief	all の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_ALL_HPP
#define BKSGE_FND_RANGES_VIEWS_ALL_HPP

#include <bksge/fnd/ranges/views/detail/range_adaptor_closure.hpp>
#include <bksge/fnd/ranges/views/ref_view.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace views
{

namespace detail
{

struct all_fn
{
private:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename Range>
	requires ranges::view<bksge::decay_t<Range>>
#else
	template <typename Range,
		typename = bksge::enable_if_t<
			ranges::view<bksge::decay_t<Range>>::value
		>
	>
#endif
	static BKSGE_CONSTEXPR auto
	impl(Range&& r, bksge::detail::overload_priority<2>)
	-> bksge::decay_t<Range>
	{
		return bksge::forward<Range>(r);
	}

	template <typename Range>
	static BKSGE_CONSTEXPR auto
	impl(Range&& r, bksge::detail::overload_priority<1>)
	-> ranges::ref_view<bksge::decay_t<Range>>
	{
		return { bksge::forward<Range>(r) };
	}

	template <typename Range>
	static BKSGE_CONSTEXPR auto
	impl(Range&& r, bksge::detail::overload_priority<0>)
	->decltype(ranges::make_subrange(bksge::forward<Range>(r)))
	{
		return ranges::make_subrange(bksge::forward<Range>(r));
	}

public:
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range)>
	BKSGE_CONSTEXPR auto operator()(Range&& r) const
	->decltype(impl(bksge::forward<Range>(r), bksge::detail::overload_priority<2>{}))
	{
		return impl(bksge::forward<Range>(r), bksge::detail::overload_priority<2>{});
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor_closure<views::detail::all_fn> all{};

template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range)>
using all_t = decltype(all(bksge::declval<Range>()));

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_ALL_HPP
