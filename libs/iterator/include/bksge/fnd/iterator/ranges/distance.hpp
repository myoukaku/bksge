/**
 *	@file	distance.hpp
 *
 *	@brief	ranges::distance 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_RANGES_DISTANCE_HPP
#define BKSGE_FND_ITERATOR_RANGES_DISTANCE_HPP

#include <iterator>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)

namespace bksge
{
namespace ranges
{

using std::ranges::distance;

}	// namespace ranges
}	// namespace bksge

#else

#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <
	typename It,
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::sized_sentinel_for<It> Sent
#else
	typename Sent,
	typename = bksge::enable_if_t<bksge::sized_sentinel_for<Sent, It>::value>
#endif
>
inline BKSGE_CXX14_CONSTEXPR bksge::iter_difference_t<It>
distance_impl_1(bksge::detail::overload_priority<1>, It first, Sent last)
{
	return last - first;
}

template <typename It, typename Sent>
inline BKSGE_CXX14_CONSTEXPR bksge::iter_difference_t<It>
distance_impl_1(bksge::detail::overload_priority<0>, It first, Sent last)
{
	bksge::iter_difference_t<It> n = 0;
	while (first != last)
	{
		++first;
		++n;
	}
	return n;
}

}	// namespace detail

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::input_or_output_iterator It, bksge::sentinel_for<It> Sent
#else
	typename It, typename Sent,
	typename = bksge::enable_if_t<bksge::conjunction<
		bksge::input_or_output_iterator<It>,
		bksge::sentinel_for<Sent, It>
	>::value>
#endif
>
inline BKSGE_CXX14_CONSTEXPR bksge::iter_difference_t<It>
distance(It first, Sent last)
{
	return ranges::detail::distance_impl_1(
		bksge::detail::overload_priority<1>{}, first, last);
}

namespace detail
{

template <BKSGE_REQUIRES_PARAM(ranges::sized_range, Range)>
inline BKSGE_CXX14_CONSTEXPR ranges::range_difference_t<Range>
distance_impl_2(bksge::detail::overload_priority<1>, Range&& r)
{
	return static_cast<ranges::range_difference_t<Range>>(ranges::size(r));
}

template <typename Range>
inline BKSGE_CXX14_CONSTEXPR ranges::range_difference_t<Range>
distance_impl_2(bksge::detail::overload_priority<0>, Range&& r)
{
	return ranges::distance(ranges::begin(r), ranges::end(r));
}

}	// namespace detail

template <BKSGE_REQUIRES_PARAM(ranges::range, Range)>
inline BKSGE_CXX14_CONSTEXPR ranges::range_difference_t<Range>
distance(Range&& r)
{
	return ranges::detail::distance_impl_2(
		bksge::detail::overload_priority<1>{}, bksge::forward<Range>(r));
}

}	// namespace ranges

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_RANGES_DISTANCE_HPP
