/**
 *	@file	next.hpp
 *
 *	@brief	ranges::next 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_RANGES_NEXT_HPP
#define BKSGE_FND_ITERATOR_RANGES_NEXT_HPP

#include <iterator>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)

namespace bksge
{
namespace ranges
{

using std::ranges::next;

}	// namespace ranges
}	// namespace bksge

#else

#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <BKSGE_REQUIRE(bksge::input_or_output_iterator, It)>
inline BKSGE_CXX14_CONSTEXPR It
next(It x)
{
	++x;
	return x;
}

template <BKSGE_REQUIRE(bksge::input_or_output_iterator, It)>
inline BKSGE_CXX14_CONSTEXPR It
next(It x, bksge::iter_difference_t<It> n)
{
	ranges::advance(x, n);
	return x;
}

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
inline BKSGE_CXX14_CONSTEXPR It
next(It x, Sent bound)
{
	ranges::advance(x, bound);
	return x;
}

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
inline BKSGE_CXX14_CONSTEXPR It
next(It x, bksge::iter_difference_t<It> n, Sent bound)
{
	ranges::advance(x, n, bound);
	return x;
}

}	// namespace ranges

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_RANGES_NEXT_HPP
