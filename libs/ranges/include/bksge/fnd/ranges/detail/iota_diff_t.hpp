/**
 *	@file	iota_diff_t.hpp
 *
 *	@brief	iota_diff_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_IOTA_DIFF_T_HPP
#define BKSGE_FND_RANGES_DETAIL_IOTA_DIFF_T_HPP

#include <bksge/fnd/ranges/detail/max_diff_type.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <typename W>
using iota_diff_t =
	bksge::conditional_t<!bksge::is_integral<W>::value,
		bksge::iter_difference_t<W>,
	bksge::conditional_t<(sizeof(bksge::iter_difference_t<W>) > sizeof(W)),
		bksge::iter_difference_t<W>,
	bksge::conditional_t<(sizeof(bksge::ptrdiff_t) > sizeof(W)),
		bksge::ptrdiff_t,
	bksge::conditional_t<(sizeof(long long) > sizeof(W)),
		long long,
#if defined(__SIZEOF_INT128__)
	bksge::conditional_t<(__SIZEOF_INT128__ > sizeof(W)),
		__int128,
#endif
		detail::max_diff_type
#if defined(__SIZEOF_INT128__)
	>
#endif
	>>>>;

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_IOTA_DIFF_T_HPP
