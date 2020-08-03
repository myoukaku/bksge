/**
 *	@file	prev.hpp
 *
 *	@brief	ranges::prev 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_RANGES_PREV_HPP
#define BKSGE_FND_ITERATOR_RANGES_PREV_HPP

#include <iterator>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)

namespace bksge
{
namespace ranges
{

using std::ranges::prev;

}	// namespace ranges
}	// namespace bksge

#else

#include <bksge/fnd/iterator/prev.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <BKSGE_REQUIRE(bksge::bidirectional_iterator, It)>
inline BKSGE_CXX14_CONSTEXPR It
prev(It x)
{
	--x;
	return x;
}

template <BKSGE_REQUIRE(bksge::bidirectional_iterator, It)>
inline BKSGE_CXX14_CONSTEXPR It
prev(It x, bksge::iter_difference_t<It> n)
{
	ranges::advance(x, -n);
	return x;
}

template <BKSGE_REQUIRE(bksge::bidirectional_iterator, It)>
inline BKSGE_CXX14_CONSTEXPR It
prev(It x, bksge::iter_difference_t<It> n, It bound)
{
	ranges::advance(x, -n, bound);
	return x;
}

}	// namespace ranges

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_RANGES_PREV_HPP
