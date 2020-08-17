/**
 *	@file	borrowed_subrange_t.hpp
 *
 *	@brief	ranges::borrowed_subrange_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_BORROWED_SUBRANGE_T_HPP
#define BKSGE_FND_RANGES_BORROWED_SUBRANGE_T_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/borrowed_range.hpp>
#include <bksge/fnd/ranges/subrange.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/dangling.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <BKSGE_REQUIRES_PARAM(ranges::range, Range)>
using borrowed_subrange_t =
	bksge::conditional_t<
		ranges::is_borrowed_range<Range>::value,
		ranges::subrange<ranges::iterator_t<Range>>,
		ranges::dangling
	>;

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_BORROWED_SUBRANGE_T_HPP
